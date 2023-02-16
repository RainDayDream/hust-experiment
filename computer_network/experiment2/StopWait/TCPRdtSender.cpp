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



//�������Ϊ3-bit��Լ��ͬʱ��෢����7������
bool TCPRdtSender::send(const Message& message) {
	if (waitingState) return false;

	this->packetWaitingAck[nextseqnum].acknum = -1; //���Ը��ֶ�
	this->packetWaitingAck[nextseqnum].seqnum = this->nextseqnum;
	this->packetWaitingAck[nextseqnum].checksum = 0;
	memcpy(this->packetWaitingAck[nextseqnum].payload, message.data, sizeof(message.data));
	this->packetWaitingAck[nextseqnum].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[nextseqnum]);


	pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck[nextseqnum]);


	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[nextseqnum]);								//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�


	if (sendbase == nextseqnum) {
		pns->startTimer(SENDER, Configuration::TIME_OUT, packetWaitingAck[nextseqnum].seqnum);			//�������ͷ���ʱ��
	}
	//nextSeqNum++;


	nextseqnum = (nextseqnum + 1) % TCP_seqnum;  //8 = 2^k;
	printf("***************���ͱ��ĺ󣬵�ǰ���ڣ�[%d,%d]\t��base=%d��nextseqnum=%d *****************************\n", sendbase, (sendbase - 1 + TCP_Winsize) % TCP_seqnum, sendbase, nextseqnum);
	if ((nextseqnum - sendbase + TCP_seqnum) % TCP_seqnum == TCP_Winsize) {
		waitingState = true;
	}
	return true;

}

void TCPRdtSender::receive(const Packet& ackPkt) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ������ȷ�����������[base,base+N-1]
	if (checkSum == ackPkt.checksum) {
		if (((ackPkt.acknum - sendbase+1)%GBN_seqnum >= 0 && (ackPkt.acknum - sendbase + 1) % GBN_seqnum <= TCP_Winsize) || (ackPkt.acknum + 1 + TCP_seqnum - sendbase <= TCP_Winsize)) {
			waitingState = false;
			y = -1;
			num = 0;
			if (ackPkt.acknum  == nextseqnum) {
				pns->stopTimer(SENDER, sendbase);		//�رն�ʱ��
			}
			else {
				pns->stopTimer(SENDER, sendbase);		//�رն�ʱ��
				//pns->startTimer(SENDER, Configuration::TIME_OUT, (ackPkt.acknum  + 1) % GBN_seqnum);
				pns->startTimer(SENDER, Configuration::TIME_OUT, ackPkt.acknum );
			}
			sendbase = ackPkt.acknum ;
			printf("***************�յ�ȷ�ϱ��ģ���ǰ���ڣ�[%d,%d]\t��base=%d��nextseqnum=%d *****************************\n", sendbase, (sendbase - 1 + TCP_Winsize) % TCP_seqnum, sendbase, nextseqnum);
			pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		}
		else {
			printf("-------------------------���ͷ��յ�seqnum = %d�����౨��\n", ackPkt.acknum);
			if (y == ackPkt.acknum) {
				num++;
			}
			else {
				y = ackPkt.acknum;
				num = 1;
			}
			if (num == 3) {
				pUtils->printPacket("-----------------------���������յ����౨�ģ����ͷ����·��ͱ���", this->packetWaitingAck[y]);
				pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[y]);								//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
				y = -1;
				num = 0;
			}
		}
	}
}

void TCPRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط��ϴη��͵ı���", this->packetWaitingAck[sendbase]);
	pns->stopTimer(SENDER, seqNum);				//���ȹرն�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum]);			//���·������ݰ�

}
