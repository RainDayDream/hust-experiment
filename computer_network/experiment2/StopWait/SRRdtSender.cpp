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
		ACK[nextseqnum] = false;  //����Ӧ������ŵ�ACK����
		this->packetWaitingAck[nextseqnum].acknum = -1; //���Ը��ֶ�
		this->packetWaitingAck[nextseqnum].seqnum = this->nextseqnum;
		this->packetWaitingAck[nextseqnum].checksum = 0;
		memcpy(this->packetWaitingAck[nextseqnum].payload, message.data, sizeof(message.data));
		this->packetWaitingAck[nextseqnum].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[nextseqnum]);
		pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck[nextseqnum]);

		//��ÿһ�����Ķ���ʱ
		pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);			//�������ͷ���ʱ��
		pns->sendToNetworkLayer(RECEIVER, packetWaitingAck[nextseqnum]);								//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
		this->nextseqnum = (this->nextseqnum + 1) % SR_seqnum;
		if ((nextseqnum - sendbase + SR_seqnum) % SR_seqnum == SR_Winsize) {
			waitingstate = true;
		}
		printf("***************���ͱ��ĺ�,���ͷ���ǰ���ڣ�[%d,%d]\t��sendbase=%d��nextseqnum=%d************************************\n", sendbase, (sendbase - 1 + SR_Winsize) % SR_seqnum, sendbase, nextseqnum);
		return true;
	}
	else {
		return false;
	}
}

void SRRdtSender::receive(const Packet& ackPkt) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ������ȷ������ڴ�����
	if (ackPkt.acknum < 0 || ackPkt.acknum > SR_seqnum - 1) {  //���ķ����𻵣�������������Խ��
		return;
	}
	//����ŵ�ȷ�ϻ�δ�յ�����У�����ȷ����ȷ�Ϻ���[base,base+N-1]��
	if (!ACK[ackPkt.acknum] && checkSum == ackPkt.checksum && ((ackPkt.acknum - sendbase >= 0 && ackPkt.acknum - sendbase <= SR_Winsize - 1) || (ackPkt.acknum + 1 + SR_seqnum - sendbase <= SR_Winsize))) {
		waitingstate = false;
		ACK[ackPkt.acknum] = true;
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		pns->stopTimer(SENDER, ackPkt.acknum);		//�رն�ʱ��
		if (sendbase == ackPkt.acknum) {
			//�������� 
			ACK[ackPkt.acknum] = false;  //����֮�⣬ACK����ȫ������
			int len = (nextseqnum - sendbase + SR_seqnum) % SR_seqnum;  //��ǰ���ڳ���
			int flag = 1;  //�����Ƿ�ȫ����ȷ��
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
			/*printf("��ǰACK����Ϊ:\n");
			for (int i = 0; i < SR_seqnum; i++) {
				printf("%d", ACK[i] == true ? 1 : 0);
			}*/
			if (flag) { //[sendbase,nextseqnum)�ڱ����Ѿ�ȫ���յ�ȷ��
				sendbase = nextseqnum;
				printf("***************�յ�ȷ�ϱ��ģ����ͷ���ǰ���ڣ�[%d,%d]\t��sendbase=%d��nextseqnum=%d************************************\n", sendbase, (sendbase - 1 + SR_Winsize) % SR_seqnum, sendbase, nextseqnum);
			}
			else {
				printf("***************�յ�ȷ�ϱ��ģ����ͷ���ǰ���ڣ�[%d,%d]\t��sendbase=%d��nextseqnum=%d************************************\n", sendbase, (sendbase - 1 + SR_Winsize) % SR_seqnum, sendbase, nextseqnum);
			}
		}
	}
}

void SRRdtSender::timeoutHandler(int seqNum) {
	pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط��ϴη��͵ı���", this->packetWaitingAck[seqNum]);
	pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//�����������ͷ���ʱ��
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum]);			//���·������ݰ�

}
