#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"
class SRRdtReceiver :public RdtReceiver
{
private:
	int rcvbase; //���շ����ڵĻ����

	bool rcvseq[SR_seqnum];  //��¼�Ƿ��ѻ�������±�ı���
	Packet lastAckPkt;				//���͸����ͷ���ȷ�ϱ���
	Message rcvmsg[SR_seqnum];             // ���ػ���ı���

public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();

public:

	void receive(const Packet& packet);	//���ձ��ģ�����NetworkService����
};

#endif


