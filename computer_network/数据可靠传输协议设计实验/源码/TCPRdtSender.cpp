#include "stdafx.h"
#include "Global.h"
#include "TCPRdtSender.h"


TCPRdtSender::TCPRdtSender() :sendbase(0), waitingState(false), y(-1), num(0), nextseqnum(0)
{
}


TCPRdtSender::~TCPRdtSender()
{
}



bool TCPRdtSender::getWaitingState() {
	return waitingState;
}



//报文序号为3-bit，约定同时最多发送了7个报文
bool TCPRdtSender::send(const Message& message) {
	if (waitingState) return false;

	this->packetWaitingAck[nextseqnum].acknum = -1; //忽略该字段
	this->packetWaitingAck[nextseqnum].seqnum = this->nextseqnum;
	this->packetWaitingAck[nextseqnum].checksum = 0;
	memcpy(this->packetWaitingAck[nextseqnum].payload, message.data, sizeof(message.data));
	this->packetWaitingAck[nextseqnum].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[nextseqnum]);


	pUtils->printPacket("发送方发送报文", this->packetWaitingAck[nextseqnum]);


	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[nextseqnum]);								//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方


	if (sendbase == nextseqnum) {
		pns->startTimer(SENDER, Configuration::TIME_OUT, packetWaitingAck[nextseqnum].seqnum);			//启动发送方定时器
	}
	//nextSeqNum++;


	nextseqnum = (nextseqnum + 1) % TCP_seqnum;  //8 = 2^k;
	printf("***************发送报文后，当前窗口：[%d,%d]\t且base=%d，nextseqnum=%d *****************************\n", sendbase, (sendbase - 1 + TCP_Winsize) % TCP_seqnum, sendbase, nextseqnum);
	if ((nextseqnum - sendbase + TCP_seqnum) % TCP_seqnum == TCP_Winsize) {
		waitingState = true;
	}
	return true;

}

void TCPRdtSender::receive(const Packet& ackPkt) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确，并且确认序号在区间[base,base+N-1]
	if (checkSum == ackPkt.checksum) {
		if (((ackPkt.acknum - sendbase+1)%GBN_seqnum >= 0 && (ackPkt.acknum - sendbase + 1) % GBN_seqnum <= TCP_Winsize) || (ackPkt.acknum + 1 + TCP_seqnum - sendbase <= TCP_Winsize)) {
			waitingState = false;
			y = -1;
			num = 0;
			if (ackPkt.acknum  == nextseqnum) {
				pns->stopTimer(SENDER, sendbase);		//关闭定时器
			}
			else {
				pns->stopTimer(SENDER, sendbase);		//关闭定时器
				//pns->startTimer(SENDER, Configuration::TIME_OUT, (ackPkt.acknum  + 1) % GBN_seqnum);
				pns->startTimer(SENDER, Configuration::TIME_OUT, ackPkt.acknum );
			}
			sendbase = ackPkt.acknum ;
			printf("***************收到确认报文，当前窗口：[%d,%d]\t且base=%d，nextseqnum=%d *****************************\n", sendbase, (sendbase - 1 + TCP_Winsize) % TCP_seqnum, sendbase, nextseqnum);
			pUtils->printPacket("发送方正确收到确认", ackPkt);
		}
		else {
			printf("-------------------------发送方收到seqnum = %d的冗余报文\n", ackPkt.acknum);
			if (y == ackPkt.acknum) {
				num++;
			}
			else {
				y = ackPkt.acknum;
				num = 1;
			}
			if (num == 3) {
				pUtils->printPacket("-----------------------连续三次收到冗余报文，发送方重新发送报文", this->packetWaitingAck[y]);
				pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[y]);								//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
				y = -1;
				num = 0;
			}
		}
	}
}

void TCPRdtSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	pUtils->printPacket("发送方定时器时间到，重发上次发送的报文", this->packetWaitingAck[sendbase]);
	pns->stopTimer(SENDER, seqNum);				//首先关闭定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum]);			//重新发送数据包

}
