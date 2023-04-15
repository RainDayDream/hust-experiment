#ifndef SR_RDT_SENDER_H
#define SR_RDT_SENDER_H
#include "RdtSender.h"

//N=4,k=3
class SRRdtSender :public RdtSender
{
private:
	bool waitingstate;
	int sendbase;  
	int nextseqnum;	// ��һ��������� 
	Packet packetWaitingAck[SR_seqnum];		//�ѷ��Ͳ��ȴ�Ack�����ݰ�
	bool ACK[SR_seqnum];  //�������յ���ACK��ţ�true��ʾ��Ӧ�±�ı���ȷ���ź����յ�

public:

	bool getWaitingState();
	bool send(const Message& message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet& ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	SRRdtSender();
	virtual ~SRRdtSender();
};

#endif


