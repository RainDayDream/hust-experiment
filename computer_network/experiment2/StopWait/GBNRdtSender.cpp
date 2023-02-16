#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"



GBNRdtSender::GBNRdtSender() : nextSeqNum(0), base(0), waitingState(false)
{
}


GBNRdtSender::~GBNRdtSender()
{
}



bool GBNRdtSender::getWaitingState() {
	return waitingState;
}




bool GBNRdtSender::send(const Message& message) {
	if (this->waitingState) { //发送方处于等待确认状态
		return false;
	}

	this->packetWaitingAck[nextSeqNum].acknum = -1; //忽略该字段
	this->packetWaitingAck[nextSeqNum].seqnum = this->nextSeqNum;
	this->packetWaitingAck[nextSeqNum].checksum = 0;
	memcpy(this->packetWaitingAck[nextSeqNum].payload, message.data, sizeof(message.data));
	this->packetWaitingAck[nextSeqNum].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[nextSeqNum]);
	pUtils->printPacket("发送方发送报文", this->packetWaitingAck[nextSeqNum]);
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[nextSeqNum]);								//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
	if(base==nextSeqNum) pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[nextSeqNum].seqnum);			//启动发送方定时器
	printf("当前窗口为:[%d,%d]\n",base,base+GBN_Winsize-1);
	nextSeqNum = (nextSeqNum + 1) % GBN_seqnum;
	if((nextSeqNum-base+GBN_Winsize)%GBN_Winsize>=GBN_Winsize) 
		this->waitingState = true;																					//进入等待状态
	return true;
}

void GBNRdtSender::receive(const Packet& ackPkt) {
		//检查校验和是否正确
		int checkSum = pUtils->calculateCheckSum(ackPkt);

		//如果校验和正确，并且确认序号=发送方已发送并等待确认的数据包序号
		if (checkSum == ackPkt.checksum && ackPkt.acknum == this->base) {
			pUtils->printPacket("发送方正确收到确认", ackPkt);
			pns->stopTimer(SENDER, this->packetWaitingAck[this->base].seqnum);		//关闭定时器
			this->base = (1 + this->base) % GBN_seqnum;			//下一个发送序号
			//if(this->base==this->nextSeqNum)
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[base].seqnum);			//启动发送方定时器
		}
		else {
			pUtils->printPacket("发送方没有正确收到确认，重发上次发送的报文", this->packetWaitingAck[this->base]);
			pns->stopTimer(SENDER, this->packetWaitingAck[this->base].seqnum);									//首先关闭定时器
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[this->base].seqnum);			//重新启动发送方定时器
			pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[this->base]);								//重新发送数据包
			this->nextSeqNum = (this->base + 1) % GBN_Winsize;
		}
		this->waitingState = false;
}

void GBNRdtSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	pUtils->printPacket("发送方定时器时间到，重发上次发送的报文,起始报文为：", this->packetWaitingAck[base]);
	pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
	this->nextSeqNum = this->base;
	this->waitingState = false;
	//找到超时的报文并重新发送
}

