#pragma once
#include "winsock2.h"
#include <stdio.h>
#include <iostream>
#include<fstream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

#define setdeploy //1-1可配置监听地址、监听端口和主目录
#define output //2-2在服务器端的屏幕上输出每个请求的来源  2-3屏幕上能够输出对每一个请求处理的结果
#define response //1-4 能够响应客户端的请求，并定位相应的 html 文件 1-5 能够构造并发送可被客户端解析的响应报文

void main(){
	WSADATA wsaData;
	/*
		select()机制中提供的fd_set的数据结构，实际上是long类型的数组，
		每一个数组元素都能与一打开的文件句柄（不管是socket句柄，还是其他文件或命名管道或设备句柄）建立联系，建立联系的工作由程序员完成.
		当调用select()时，由内核根据IO状态修改fd_set的内容，由此来通知执行了select()的进程哪个socket或文件句柄发生了可读或可写事件。
	*/
	fd_set rfds;				//用于检查socket是否有数据到来的的文件描述符，用于socket非阻塞模式下等待网络事件通知（有数据到来）
	fd_set wfds;				//用于检查socket是否可以发送的文件描述符，用于socket非阻塞模式下等待网络事件通知（可以发送数据）
	bool first_connetion = true;

	//1-1设置服务器的端口和地址、主目录
	#ifdef setdeploy
		int p1, p2, p3, p4;
		char c;
		std::cout << "设置监听地址为：";
		do {
			cin >> p1 >> c >> p2 >> c >> p3 >> c >> p4;
			if (p1 > 255 || p2 > 255 || p3 > 255 || p4 > 255)
			{
				printf("IP ERROR!\n重新输入监听地址:");
			}
		} while (p1 > 255 || p2 > 255 || p3 > 255 || p4 > 255);//判定IP是否输入正确
		printf("IP RIGHT!\n");
		int presult;
		presult = p1 << 24 + p2 << 16 + p3 << 8 + p4;//IP地址
		int portnumber;//端口号
		std::cout << "设置端口号为：";
		do {
			cin >> portnumber;
			if (portnumber > 65535)
			{
				std::cout << "端口号错误！" << endl << "重新输入端口号：";
			}
		} while (portnumber > 65535);//判定端口号是否输入正确
		std::cout << "端口号正确!" << endl;
		std::cout << "设置主目录为：";
		string s;
		cin >> s;
		const char* cata = s.c_str();
		int i = 0;
		int len = s.length();
		char catalog[10];
		for (i = 0; i < len; i++)
			catalog[i] = cata[i];
		catalog[len] = '\0';//设置主目录
	#endif // setdeploy



	int nRc = WSAStartup(0x0202,&wsaData);

	if(nRc){
		printf("Winsock  startup failed with error!\n");
	}

	if(wsaData.wVersion != 0x0202){
		printf("Winsock version is not correct!\n");
	}

	printf("Winsock  startup Ok!\n");


	//监听socket
	SOCKET srvSocket;	

	//服务器地址和客户端地址
	sockaddr_in addr,clientAddr;

	//会话socket，负责和client进程通信
	SOCKET sessionSocket;

	//ip地址长度
	int addrLen;

	//创建监听socket
	srvSocket = socket(AF_INET,SOCK_STREAM,0);
	if(srvSocket != INVALID_SOCKET)
		printf("Socket create Ok!\n");


	//1-1设置服务器的端口和地址，和前面不放在一块是因为想要先输入再创建套接字并绑定
	#ifdef setdeploy
	addr.sin_family = AF_INET;
	addr.sin_port = htons(portnumber);//设置设定的端口号
	addr.sin_addr.S_un.S_addr = htonl(presult); //设置设定的监听地址
	std::cout << "监听地址、端口号、主目录设置完毕！"<<endl;
	#else
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5050);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //主机上任意一块网卡的IP地址
	std::cout << "监听地址、端口号、主目录设置完毕！" << endl;
	#endif // setdeploy




	//binding 绑定端口号和监听socket
	int rtn = bind(srvSocket,(LPSOCKADDR)&addr,sizeof(addr));
	if(rtn != SOCKET_ERROR)
		printf("Socket bind Ok!\n");

	//监听1-2
	rtn = listen(srvSocket,5);
	if(rtn != SOCKET_ERROR)
		printf("Socket listen Ok!\n");

	clientAddr.sin_family =AF_INET;
	addrLen = sizeof(clientAddr);

	//设置接收缓冲区
	char recvBuf[4096];

	u_long blockMode = 1;//将srvSock设为非阻塞模式以监听客户连接请求

	//调用ioctlsocket，将srvSocket改为非阻塞模式，改成反复检查fd_set元素的状态，看每个元素对应的句柄是否可读或可写
	if ((rtn = ioctlsocket(srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
		std::cout << "ioctlsocket() failed with error!\n";
		return;
	}
	std::cout << "ioctlsocket() for server socket ok!	Waiting for client connection and data\n";

	while(true){
		//清空rfds和wfds数组
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);

		//将srvSocket加入rfds数组
		//即：当客户端连接请求到来时，rfds数组里srvSocket对应的的状态为可读
		//因此这条语句的作用就是：设置等待客户连接请求
		FD_SET(srvSocket, &rfds);

		//如果first_connetion为true，sessionSocket还没有产生
		if (!first_connetion) {
			//将sessionSocket加入rfds数组和wfds数组
			//即：当客户端发送数据过来时，rfds数组里sessionSocket的对应的状态为可读；当可以发送数据到客户端时，wfds数组里sessionSocket的对应的状态为可写
			//因此下面二条语句的作用就是：
			//设置等待会话SOKCET可接受数据或可发送数据
			if (sessionSocket != INVALID_SOCKET) { //如果sessionSocket是有效的
				FD_SET(sessionSocket, &rfds);
				FD_SET(sessionSocket, &wfds);
			}
			
		}
		
		/*
			select工作原理：传入要监听的文件描述符集合（可读、可写，有异常）开始监听，select处于阻塞状态。
			当有可读写事件发生或设置的等待时间timeout到了就会返回，返回之前自动去除集合中无事件发生的文件描述符，返回时传出有事件发生的文件描述符集合。
			但select传出的集合并没有告诉用户集合中包括哪几个就绪的文件描述符，需要用户后续进行遍历操作(通过FD_ISSET检查每个句柄的状态)。
		*/
		//开始等待，等待rfds里是否有输入事件，wfds里是否有可写事件
		//The select function returns the total number of socket handles that are ready and contained in the fd_set structure
		//返回总共可以读或写的句柄个数
		int nTotal = select(0, &rfds, &wfds, NULL, NULL);

		//如果srvSock收到连接请求，接受客户连接请求
		if (FD_ISSET(srvSocket, &rfds)) {
			nTotal--;   //因为客户端请求到来也算可读事件，因此-1，剩下的就是真正有可读事件的句柄个数（即有多少个socket收到了数据）

			//产生会话SOCKET    1-3
			sessionSocket = accept(srvSocket, (LPSOCKADDR)&clientAddr, &addrLen);
			if (sessionSocket != INVALID_SOCKET)
				printf("Socket listen one client request!\n");
			#ifdef output //2-2
			std::cout << "请求的IP地址为:" << clientAddr.sin_addr.S_un.S_addr << endl;
			std::cout << "请求的端口地址：" << clientAddr.sin_port << endl;
			#endif // output


			//把会话SOCKET设为非阻塞模式
			if ((rtn = ioctlsocket(sessionSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
				std::cout << "ioctlsocket() failed with error!\n";
				return;
			}
			std::cout << "ioctlsocket() for session socket ok!	Waiting for client connection and data\n";

			//设置等待会话SOKCET可接受数据或可发送数据
			FD_SET(sessionSocket, &rfds);
			FD_SET(sessionSocket, &wfds);

			first_connetion = false;

		}

		//检查会话SOCKET是否有数据到来
		if (nTotal >= 0) { //如果还有有可读事件，说明是会话socket有数据到来
			//如果会话SOCKET有数据到来，则接受客户的数据
			if (FD_ISSET(sessionSocket, &rfds)) {
				//receiving data from client
				memset(recvBuf, '\0', 4096);
				rtn = recv(sessionSocket, recvBuf, 256, 0);
				if (rtn > 0) {
					//2-2 输出http请求
					#ifdef output
					printf("HTTP请求为 %d bytes 的： %s\n", rtn, recvBuf); 
					#endif // output

				#ifdef response//1-4,2-1
					char request[10000], detail[1000];
					int i = 0;
					//获取http请求
					//cout << "response";
					for (i = 0; recvBuf[i] != ' '; i++)
						request[i] = recvBuf[i];
					request[i] = '\0';
					//std::cout << "request:" << request << endl;
					i += 1;//找到文件位置
					int cur = i;
					for (; recvBuf[i] != ' '; i++)
						detail[i - cur] = recvBuf[i];
					detail[i - cur] = '\0';
					//std::cout << "detail:" << detail << endl;
					char filename[100];
					int length = 0;
					for (length = 0; catalog[length] != '\0'; length++)
						filename[length] = catalog[length];
					cur = length;
					for (; detail[length-cur] != '\0'; length++)
						filename[length] = detail[length-cur];
					filename[length] = '\0';
					//std::cout << "filename:" << filename << endl;
					if (request[0] == 'G')
					{
						#ifdef outout
						std::cout << "用户请求获取的文件是：" << filename << endl;
						#endif // outout
						//读文件
						FILE* fp;
						fp = fopen(filename, "rb");
						//读文件失败
						if (!fp)
						{
							std::cout << filename <<"文件打开失败" << endl;
							std::cout << "向用户返回404" << endl;//输出对请求的处理结果
							string message;
							message = "http/1.1 404 NOTFOUND\r\n";
							rtn = send(sessionSocket, message.c_str(), message.length(), 0);
							message = "Content-Type: text/html\r\n";
							rtn = send(sessionSocket, message.c_str(), message.length(), 0);
							message = "\r\n";
							rtn = send(sessionSocket, message.c_str(), message.length(), 0);
							message = "<html><body><h1>404</h1><p> FILE Not Found!</p></body></html>";
							rtn = send(sessionSocket, message.c_str(), message.length(), 0);
							if (rtn == SOCKET_ERROR) std::cout << "服务器响应报文发送失败！" << endl;
							else cout << "响应报文已发送！" << endl;
						}
						else {//读文件成功
							std::cout << filename << "文件打开成功" << endl;
							std::cout << "向用户返回200 OK" << endl;//输出对请求的处理结果
							string message;
							message = "http/1.1 200 OK\r\n";
							rtn = send(sessionSocket, message.c_str(), message.length(), 0);
							int messagelength;
							//获取数据总长度
							fseek(fp, 0, SEEK_END);
							messagelength = ftell(fp);
							rewind(fp);
							//根据数据长度分配内存buffer
							char* Buffer = (char*)malloc((messagelength + 1) * sizeof(char));
							memset( Buffer, 0, messagelength+1);
							//将数据读入buffer
							fread(Buffer,1,messagelength, fp);
							fclose(fp);

							if (filename[length - 2] == 'n')//png
							{
								message = "Content-Type: application/octet-stream\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								message = "\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								rtn = send(sessionSocket, Buffer, messagelength, 0);
								if (rtn == SOCKET_ERROR) std::cout << "服务器响应报文发送失败！" << endl;
								else cout << "数据报文已发送！" << endl;
							}
							else if (filename[length - 2] == 'p')//jpg
							{
								message = "Content-Type: image/jpeg\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								message = "\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								rtn = send(sessionSocket, Buffer, messagelength, 0);
								if (rtn == SOCKET_ERROR) std::cout << "服务器响应报文发送失败！" << endl;
								else cout << "数据报文已发送！" << endl;
							}
							else//txt/html
							{
								message = "Content-Type: text/html;charset=utf-8\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								message = "\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								rtn = send(sessionSocket, Buffer, messagelength, 0);
								if (rtn == SOCKET_ERROR) std::cout << "服务器响应报文发送失败！" << endl;
								else cout << "数据报文已发送！" << endl;
							}
						}

					}
				#endif // response


				}
				else { //否则是收到了客户端断开连接的请求，也算可读事件。但是这种情况下FD_ISSET(sessionSocket, &rfds)返回false
					printf("Client leaving ...\n");
					closesocket(sessionSocket);  //既然client离开了，就关闭sessionSocket
					nTotal--;	//因为客户端离开也属于可读事件，所以需要-1
					sessionSocket = INVALID_SOCKET; //把sessionSocket设为INVALID_SOCKET
				}
			}
		}	
	}

}