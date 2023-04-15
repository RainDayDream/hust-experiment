#include "stdafx.h"
#include "Global.h"
#include "TCPRdtReceiver.h"

char receive_tcp_ok[20] = "receive success!";
char receive_tcp_error[20] = "receive error!";
//N=4,k=3
TCPRdtReceiver::TCPRdtReceiver() :expectSequenceNumberRcvd(0)
{
	lastAckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为0
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//忽略该字段
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastAckPkt.payload[i] = receive_tcp_ok[i];
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


TCPRdtReceiver::~TCPRdtReceiver()
{
}

//这里实现接收端无缓存，只接受连续的报文
void TCPRdtReceiver::receive(const Packet& packet) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(packet);

	//如果校验和正确，同时收到报文的序号等于接收方期待收到的报文序号一致
	if (checkSum == packet.checksum && expectSequenceNumberRcvd == packet.seqnum) {
		pUtils->printPacket("接收方正确收到发送方的报文", packet);

		//取出Message，向上递交给应用层
		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);

		lastAckPkt.acknum = (packet.seqnum+1)%GBN_seqnum; //确认序号等于收到的报文序号
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("接收方发送确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
		this->expectSequenceNumberRcvd = (this->expectSequenceNumberRcvd + 1) % TCP_seqnum;
	}
	else {  //数据错误和序列号不对的情况下，laskackpkt不变，仍然表示接受方希望接受的packet
		if (checkSum != packet.checksum) { //数据错误
			pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		}
		else {  //序列号不对
			pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
		}
		for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
			lastAckPkt.payload[i] = receive_tcp_error[i];
		}
		lastAckPkt.acknum = packet.seqnum;
		pUtils->printPacket("接收方重新发送上次的确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送上次的确认报文

	}
}