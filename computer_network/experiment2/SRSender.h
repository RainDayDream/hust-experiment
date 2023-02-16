#ifndef STOP_WAIT_RDT_SENDER_H
#define STOP_WAIT_RDT_SENDER_H
#include "RdtSender.h"
#include <deque>
struct waitPck {
	bool flag;     //��δ���յ�ACKʱ��Ϊfalse
	Packet winPck;
};

class SRSender :public RdtSender
{
private:
	int expectSequenceNumberSend;	// ��һ��������� 
	bool full;				// �����Ƿ�����
	int base;                       //��ǰ���ڻ����
	int winlen;                     //���ڴ�С
	int seqlen;                     //��ſ��
	deque<waitPck> window;           //���ڶ���
	Packet packetWaitingAck;		//�ѷ��Ͳ��ȴ�ȷ�ϵķ���


public:

	bool getWaitingState();
	bool send(const Message &message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet &ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	SRSender();
	virtual ~SRSender();
};


#endif

