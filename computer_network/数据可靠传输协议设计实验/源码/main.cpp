// StopWait.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "StopWaitRdtSender.h"
#include "StopWaitRdtReceiver.h"
#include "GBNRdtReceiver.h"
#include "GBNRdtSender.h"
#include "SRRdtReceiver.h"
#include "SRRdtSender.h"
#include "TCPRdtReceiver.h"
#include "TCPRdtSender.h"

#define GBN_ 0
#define SR_ 0
#define TCP_ 1


int main(int argc, char* argv[])
{
#if GBN_
	printf("----------GBN RUN----------\n");
	RdtSender* ps = new GBNRdtSender();
	RdtReceiver* pr = new GBNRdtReceiver();

#elif SR_
	printf("----------SR RUN----------\n");
	RdtSender* ps = new SRRdtSender();
	RdtReceiver* pr = new SRRdtReceiver();

#elif TCP_
	printf("----------TCP RUN----------\n");
	RdtSender* ps = new TCPRdtSender();
	RdtReceiver* pr = new TCPRdtReceiver();

#else
	printf("----------StopWait RUN----------\n");
	RdtSender* ps = new StopWaitRdtSender();
	RdtReceiver* pr = new StopWaitRdtReceiver();

#endif

	pns->setRunMode(0);  //VERBOS模式
	//pns->setRunMode(1);  //安静模式
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	//D:\study\hust_experiment\computer_network\experiment2\StopWait
	pns->setInputFile("D:\\study\\hust_experiment\\computer_network\\experiment2\\StopWait\\Debug\\input.txt");
	pns->setOutputFile("D:\\study\\hust_experiment\\computer_network\\experiment2\\StopWait\\Debug\\output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;									//指向唯一的工具类实例，只在main函数结束前delete
	delete pns;										//指向唯一的模拟网络环境类实例，只在main函数结束前delete
	
	return 0;
}

