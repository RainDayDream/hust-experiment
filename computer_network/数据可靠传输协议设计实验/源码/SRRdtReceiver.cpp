#include "stdafx.h"
#include "Global.h"
#include "SRRdtReceiver.h"
char receive_sr_ok[20] = "receive success!";
char receive_sr_error[20] = "receive error!";

SRRdtReceiver::SRRdtReceiver() :rcvbase(0)
{
	for (int i = 0; i < SR_seqnum; i++) {
		rcvseq[i] = false;
	}
	lastAckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//忽略该字段
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastAckPkt.payload[i] = receive_sr_ok[i];
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


SRRdtReceiver::~SRRdtReceiver()
{
}

void SRRdtReceiver::receive(const Packet& packet) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(packet);

	//如果校验和正确
	if (checkSum == packet.checksum) {
		if ((packet.seqnum - rcvbase >= 0 && packet.seqnum - rcvbase <= SR_Winsize - 1) || (packet.seqnum + 1 + SR_seqnum - rcvbase <= SR_Winsize)) {
			//报文序号在[rcvbase,revbase+N-1]区间内
			//pUtils->printPacket("接收方正确收到发送方的报文", packet);
			if (packet.seqnum == rcvbase) {
				Message msg;
				memcpy(msg.data, packet.payload, sizeof(packet.payload));
				int flag = rcvbase;  //[rvcbase,flag]为传给应用层的报文序号区间
				//下面检查是否缓存了连续序号的报文
				for (int i = (rcvbase + 1) % SR_seqnum, j = 1; j < SR_Winsize; j++, i = (i + 1) % SR_seqnum) {
					if (rcvseq[i] == true) {
						flag = i;
						//rcvseq[i] = false;
					}
					else {
						break;
					}
				}
				if (flag == rcvbase) {
					printf("接收方没有缓存的连续的报文，直接将报文序号为%d的报文递交给应用层\n", rcvbase);
					pns->delivertoAppLayer(RECEIVER, msg);
				}
				else {
					printf("接收方将缓存的 %d ~ %d 的报文递交给应用层\n", rcvbase, flag);
					pns->delivertoAppLayer(RECEIVER, msg);
					for (int i = (rcvbase + 1) % SR_seqnum, j = 0; j < (flag - rcvbase + SR_seqnum) % SR_seqnum; j++, i = (i + 1) % SR_seqnum) {
						pns->delivertoAppLayer(RECEIVER, rcvmsg[i]);
						rcvseq[i] = false;
					}
				}
				rcvbase = (flag + 1) % SR_seqnum;
				printf("***************递交报文后，接收方当前窗口：[%d,%d]*********************************************\n", rcvbase, (rcvbase - 1 + SR_Winsize) % SR_seqnum);
			}
			else {
				memcpy(rcvmsg[packet.seqnum].data, packet.payload, sizeof(packet.payload));
				rcvseq[packet.seqnum] = true;
				printf("报文序号不连续，接受方将序号为%d的报文缓存，当前窗口基序号rcvbase=%d\n", packet.seqnum, rcvbase);
			}

			lastAckPkt.acknum = packet.seqnum; //确认序号等于收到的报文序号
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("接收方发送确认报文", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
		}
		else { //报文序号非期待序号
			lastAckPkt.acknum = packet.seqnum; //确认序号等于收到的报文序号
			for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
				lastAckPkt.payload[i] = receive_sr_error[i];
			}
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("接收方收到已确认报文，重新发送确认报文", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
		}
	}
	//校验和错误不作反应
}