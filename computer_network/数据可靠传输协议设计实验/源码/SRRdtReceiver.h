#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"
class SRRdtReceiver :public RdtReceiver
{
private:
	int rcvbase; //接收方窗口的基序号

	bool rcvseq[SR_seqnum];  //记录是否已缓存对于下标的报文
	Packet lastAckPkt;				//发送给发送方的确认报文
	Message rcvmsg[SR_seqnum];             // 本地缓存的报文

public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();

public:

	void receive(const Packet& packet);	//接收报文，将被NetworkService调用
};

#endif


