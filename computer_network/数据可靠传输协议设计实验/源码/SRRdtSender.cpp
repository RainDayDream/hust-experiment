#include "stdafx.h"
#include "Global.h"
#include "SRRdtSender.h"


SRRdtSender::SRRdtSender() :nextseqnum(0), sendbase(0), waitingstate(false)
{
	memset(ACK, TCP_seqnum, false);
}


SRRdtSender::~SRRdtSender()
{
}



bool SRRdtSender::getWaitingState() {
	return waitingstate;
}

bool SRRdtSender::send(const Message& message) {
	if (!waitingstate) {
		ACK[nextseqnum] = false;  //将对应报文序号的ACK置零
		this->packetWaitingAck[nextseqnum].acknum = -1; //忽略该字段
		this->packetWaitingAck[nextseqnum].seqnum = this->nextseqnum;
		this->packetWaitingAck[nextseqnum].checksum = 0;
		memcpy(this->packetWaitingAck[nextseqnum].payload, message.data, sizeof(message.data));
		this->packetWaitingAck[nextseqnum].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[nextseqnum]);
		pUtils->printPacket("发送方发送报文", this->packetWaitingAck[nextseqnum]);

		//对每一个报文都计时
		pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);			//启动发送方定时器
		pns->sendToNetworkLayer(RECEIVER, packetWaitingAck[nextseqnum]);								//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
		this->nextseqnum = (this->nextseqnum + 1) % SR_seqnum;
		if ((nextseqnum - sendbase + SR_seqnum) % SR_seqnum == SR_Winsize) {
			waitingstate = true;
		}
		printf("***************发送报文后,发送方当前窗口：[%d,%d]\t且sendbase=%d，nextseqnum=%d************************************\n", sendbase, (sendbase - 1 + SR_Winsize) % SR_seqnum, sendbase, nextseqnum);
		return true;
	}
	else {
		return false;
	}
}

void SRRdtSender::receive(const Packet& ackPkt) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确，并且确认序号在窗口内
	if (ackPkt.acknum < 0 || ackPkt.acknum > SR_seqnum - 1) {  //报文发生损坏，避免下面数组越界
		return;
	}
	//该序号的确认还未收到过，校验和正确，该确认号在[base,base+N-1]内
	if (!ACK[ackPkt.acknum] && checkSum == ackPkt.checksum && ((ackPkt.acknum - sendbase >= 0 && ackPkt.acknum - sendbase <= SR_Winsize - 1) || (ackPkt.acknum + 1 + SR_seqnum - sendbase <= SR_Winsize))) {
		waitingstate = false;
		ACK[ackPkt.acknum] = true;
		pUtils->printPacket("发送方正确收到确认", ackPkt);
		pns->stopTimer(SENDER, ackPkt.acknum);		//关闭定时器
		if (sendbase == ackPkt.acknum) {
			//滑动窗口 
			ACK[ackPkt.acknum] = false;  //窗口之外，ACK数组全部置零
			int len = (nextseqnum - sendbase + SR_seqnum) % SR_seqnum;  //当前窗口长度
			int flag = 1;  //窗口是否全部被确认
			for (int i = 0, j = (sendbase + 1) % SR_seqnum; i < len - 1; i++, j = (j + 1) % SR_seqnum) {
				if (ACK[j]) {
					continue;
					ACK[j] = false;
				}
				else {
					sendbase = j;
					flag = 0;
					break;
				}
			}
			/*printf("当前ACK数组为:\n");
			for (int i = 0; i < SR_seqnum; i++) {
				printf("%d", ACK[i] == true ? 1 : 0);
			}*/
			if (flag) { //[sendbase,nextseqnum)内报文已经全部收到确认
				sendbase = nextseqnum;
				printf("***************收到确认报文，发送方当前窗口：[%d,%d]\t且sendbase=%d，nextseqnum=%d************************************\n", sendbase, (sendbase - 1 + SR_Winsize) % SR_seqnum, sendbase, nextseqnum);
			}
			else {
				printf("***************收到确认报文，发送方当前窗口：[%d,%d]\t且sendbase=%d，nextseqnum=%d************************************\n", sendbase, (sendbase - 1 + SR_Winsize) % SR_seqnum, sendbase, nextseqnum);
			}
		}
	}
}

void SRRdtSender::timeoutHandler(int seqNum) {
	pUtils->printPacket("发送方定时器时间到，重发上次发送的报文", this->packetWaitingAck[seqNum]);
	pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//重新启动发送方定时器
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum]);			//重新发送数据包

}
