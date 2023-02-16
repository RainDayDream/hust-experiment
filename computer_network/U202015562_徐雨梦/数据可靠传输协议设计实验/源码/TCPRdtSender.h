#ifndef TCP_RDT_SENDER_H
#define TCP_RDT_SENDER_H
#include "RdtSender.h"

//选择重传，超时重传最早发送但未确认的，接收方无缓存，发送方报文序号的二进制位数=3，有窗口大小约束
//约定同时最多发送7个报文
class TCPRdtSender :public RdtSender
{
private:
	int sendbase;	// 当前还未确认的最小的segment序号 
	int nextseqnum;   //已发送到的序号
	int y;  //收到的冗余ACK序号
	int num;   //y收到的次数
	bool waitingState;				// 是否处于等待Ack的状态
	Packet packetWaitingAck[TCP_seqnum];		//发送方缓存

public:

	bool getWaitingState();
	bool send(const Message& message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet& ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	TCPRdtSender();
	virtual ~TCPRdtSender();
};

#endif

