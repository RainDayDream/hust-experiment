#include "stdafx.h"
#include "Global.h"
#include "TCPRdtReceiver.h"

char receive_tcp_ok[20] = "receive success!";
char receive_tcp_error[20] = "receive error!";
//N=4,k=3
TCPRdtReceiver::TCPRdtReceiver() :expectSequenceNumberRcvd(0)
{
	lastAckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ0
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//���Ը��ֶ�
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastAckPkt.payload[i] = receive_tcp_ok[i];
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


TCPRdtReceiver::~TCPRdtReceiver()
{
}

//����ʵ�ֽ��ն��޻��棬ֻ���������ı���
void TCPRdtReceiver::receive(const Packet& packet) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(packet);

	//���У�����ȷ��ͬʱ�յ����ĵ���ŵ��ڽ��շ��ڴ��յ��ı������һ��
	if (checkSum == packet.checksum && expectSequenceNumberRcvd == packet.seqnum) {
		pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���", packet);

		//ȡ��Message�����ϵݽ���Ӧ�ò�
		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);

		lastAckPkt.acknum = (packet.seqnum+1)%GBN_seqnum; //ȷ����ŵ����յ��ı������
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�
		this->expectSequenceNumberRcvd = (this->expectSequenceNumberRcvd + 1) % TCP_seqnum;
	}
	else {  //���ݴ�������кŲ��Ե�����£�laskackpkt���䣬��Ȼ��ʾ���ܷ�ϣ�����ܵ�packet
		if (checkSum != packet.checksum) { //���ݴ���
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,����У�����", packet);
		}
		else {  //���кŲ���
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,������Ų���", packet);
		}
		for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
			lastAckPkt.payload[i] = receive_tcp_error[i];
		}
		lastAckPkt.acknum = packet.seqnum;
		pUtils->printPacket("���շ����·����ϴε�ȷ�ϱ���", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢���ϴε�ȷ�ϱ���

	}
}