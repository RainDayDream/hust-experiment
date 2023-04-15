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
	if (this->waitingState) { //���ͷ����ڵȴ�ȷ��״̬
		return false;
	}

	this->packetWaitingAck[nextSeqNum].acknum = -1; //���Ը��ֶ�
	this->packetWaitingAck[nextSeqNum].seqnum = this->nextSeqNum;
	this->packetWaitingAck[nextSeqNum].checksum = 0;
	memcpy(this->packetWaitingAck[nextSeqNum].payload, message.data, sizeof(message.data));
	this->packetWaitingAck[nextSeqNum].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[nextSeqNum]);
	pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck[nextSeqNum]);
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[nextSeqNum]);								//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
	if(base==nextSeqNum) pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[nextSeqNum].seqnum);			//�������ͷ���ʱ��
	printf("��ǰ����Ϊ:[%d,%d]\n",base,base+GBN_Winsize-1);
	nextSeqNum = (nextSeqNum + 1) % GBN_seqnum;
	if((nextSeqNum-base+GBN_Winsize)%GBN_Winsize>=GBN_Winsize) 
		this->waitingState = true;																					//����ȴ�״̬
	return true;
}

void GBNRdtSender::receive(const Packet& ackPkt) {
		//���У����Ƿ���ȷ
		int checkSum = pUtils->calculateCheckSum(ackPkt);

		//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
		if (checkSum == ackPkt.checksum && ackPkt.acknum == this->base) {
			pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
			pns->stopTimer(SENDER, this->packetWaitingAck[this->base].seqnum);		//�رն�ʱ��
			this->base = (1 + this->base) % GBN_seqnum;			//��һ���������
			//if(this->base==this->nextSeqNum)
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[base].seqnum);			//�������ͷ���ʱ��
		}
		else {
			pUtils->printPacket("���ͷ�û����ȷ�յ�ȷ�ϣ��ط��ϴη��͵ı���", this->packetWaitingAck[this->base]);
			pns->stopTimer(SENDER, this->packetWaitingAck[this->base].seqnum);									//���ȹرն�ʱ��
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[this->base].seqnum);			//�����������ͷ���ʱ��
			pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[this->base]);								//���·������ݰ�
			this->nextSeqNum = (this->base + 1) % GBN_Winsize;
		}
		this->waitingState = false;
}

void GBNRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط��ϴη��͵ı���,��ʼ����Ϊ��", this->packetWaitingAck[base]);
	pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
	this->nextSeqNum = this->base;
	this->waitingState = false;
	//�ҵ���ʱ�ı��Ĳ����·���
}

