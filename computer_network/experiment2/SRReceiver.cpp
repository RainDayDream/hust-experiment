#include "stdafx.h"
#include "Global.h"
#include "SRReceiver.h"


SRReceiver::SRReceiver():expectSequenceNumberRcvd(0),seqlen(8),base(0), winlen(4)
{
	lastAckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//���Ը��ֶ�
	for(int i = 0; i < Configuration::PAYLOAD_SIZE;i++){
		lastAckPkt.payload[i] = '.';
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);

	//����������������Ϊ�հ���flag��Ϊfalse�������������
	for (int i = 0; i < winlen; i++) {
		rcvPck blank;
		blank.flag = false;
		blank.winPck.seqnum = -1;
		window.push_back(blank);
	}                                

}


SRReceiver::~SRReceiver()
{
}

void SRReceiver::receive(const Packet &packet) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(packet);
	int offseqnum = (packet.seqnum - this->base + this->seqlen) % this->seqlen;

	//���У�����ȷ��ͬʱ�յ����ĵ�����ڽ��մ��ڷ�Χ��
	if (checkSum == packet.checksum && offseqnum < this->winlen && window.at(offseqnum).flag == false) {
		window.at(offseqnum).flag = true;
		window.at(offseqnum).winPck = packet;

		//���ô���״̬����Ϊture��ռ��
		printf("���շ�����:[ ");
		for (int i = 0; i < window.size(); i++) {
			if(window.at(i).flag == true)
				printf("%dY ", (this->base + i) % seqlen);
			else printf("%dN ", (this->base + i) % seqlen);
		}
		printf("]\n");  //���յ�����ǰ�Ĵ�������

		pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���", packet);

		while (window.front().flag == true) {
			Message msg;
			memcpy(msg.data, window.front().winPck.payload, sizeof(window.front().winPck.payload));
			pns->delivertoAppLayer(RECEIVER, msg);
			this->base = (this->base + 1) % seqlen;
			rcvPck blank;
			blank.flag = false;
			blank.winPck.seqnum = -1;
			window.pop_front();
			window.push_back(blank); //�������һ���һ��
		}

		printf("���շ������󴰿�:[ ");
		for (int i = 0; i < window.size(); i++) {
			if (window.at(i).flag == true)
				printf("%dY ", (this->base + i) % seqlen);
			else printf("%dN ", (this->base + i) % seqlen);
		}
		printf("]\n");  //���ձ��ĺ�Ĵ�������

		lastAckPkt.acknum = packet.seqnum; //ȷ����ŵ����յ��ı������
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
		//����ȷ�ϱ��ĵ��Է�
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	


	}
	else {
		if (checkSum != packet.checksum) {
			pUtils->printPacket("���ձ�������У�����", packet);
		}
		else {
			pUtils->printPacket("���Ĳ��ڽ��մ���", packet);
			//SR����Ϊ���Ͷ��յ��ñ��ĵ�ȷ�ϣ�����������ȷ�ϵ����С�ڵ�ǰ���մ��ڻ���ţ�������С�ڷ��ʹ��ڻ���ţ����ܷ��ʹ��ڵĲ�һ�£�
			lastAckPkt.acknum = packet.seqnum; 

			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("���շ����·����ϴε�ȷ�ϱ���", lastAckPkt);
			//������ȷ�ϱ��ĵ�ACK
			pns->sendToNetworkLayer(SENDER, lastAckPkt);	
		}
	}
}