#ifndef TCP_RDT_SENDER_H
#define TCP_RDT_SENDER_H
#include "RdtSender.h"

//ѡ���ش�����ʱ�ش����緢�͵�δȷ�ϵģ����շ��޻��棬���ͷ�������ŵĶ�����λ��=3���д��ڴ�СԼ��
//Լ��ͬʱ��෢��7������
class TCPRdtSender :public RdtSender
{
private:
	int sendbase;	// ��ǰ��δȷ�ϵ���С��segment��� 
	int nextseqnum;   //�ѷ��͵������
	int y;  //�յ�������ACK���
	int num;   //y�յ��Ĵ���
	bool waitingState;				// �Ƿ��ڵȴ�Ack��״̬
	Packet packetWaitingAck[TCP_seqnum];		//���ͷ�����

public:

	bool getWaitingState();
	bool send(const Message& message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet& ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	TCPRdtSender();
	virtual ~TCPRdtSender();
};

#endif

