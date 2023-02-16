#ifndef GBN_RDT_SENDER_H
#define GBN_RDT_SENDER_H
#include "RdtSender.h"



//设置N=4,k=3
class GBNRdtSender :public RdtSender
{
private:
	int nextSeqNum;	// 下一个发送序号 
	int base; //基序号
	bool waitingState;				// 是否处于等待Ack的状态
	Packet packetWaitingAck[GBN_seqnum];    //报文序号为0~7，储存所有以发送待确认报文

public:

	bool getWaitingState();
	bool send(const Message& message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet& ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	GBNRdtSender();
	virtual ~GBNRdtSender();
};

#endif

