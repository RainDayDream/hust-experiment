#ifndef SR_RDT_SENDER_H
#define SR_RDT_SENDER_H
#include "RdtSender.h"

//N=4,k=3
class SRRdtSender :public RdtSender
{
private:
	bool waitingstate;
	int sendbase;  
	int nextseqnum;	// 下一个发送序号 
	Packet packetWaitingAck[SR_seqnum];		//已发送并等待Ack的数据包
	bool ACK[SR_seqnum];  //储存已收到的ACK序号，true表示对应下标的报文确认信号已收到

public:

	bool getWaitingState();
	bool send(const Message& message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet& ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	SRRdtSender();
	virtual ~SRRdtSender();
};

#endif


