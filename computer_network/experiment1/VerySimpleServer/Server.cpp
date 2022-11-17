#pragma once
#include "winsock2.h"
#include <stdio.h>
#include <iostream>
#include<fstream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

#define setdeploy //1-1�����ü�����ַ�������˿ں���Ŀ¼
#define output //2-2�ڷ������˵���Ļ�����ÿ���������Դ  2-3��Ļ���ܹ������ÿһ��������Ľ��
#define response //1-4 �ܹ���Ӧ�ͻ��˵����󣬲���λ��Ӧ�� html �ļ� 1-5 �ܹ����첢���Ϳɱ��ͻ��˽�������Ӧ����

void main(){
	WSADATA wsaData;
	/*
		select()�������ṩ��fd_set�����ݽṹ��ʵ������long���͵����飬
		ÿһ������Ԫ�ض�����һ�򿪵��ļ������������socket��������������ļ��������ܵ����豸�����������ϵ��������ϵ�Ĺ����ɳ���Ա���.
		������select()ʱ�����ں˸���IO״̬�޸�fd_set�����ݣ��ɴ���ִ֪ͨ����select()�Ľ����ĸ�socket���ļ���������˿ɶ����д�¼���
	*/
	fd_set rfds;				//���ڼ��socket�Ƿ������ݵ����ĵ��ļ�������������socket������ģʽ�µȴ������¼�֪ͨ�������ݵ�����
	fd_set wfds;				//���ڼ��socket�Ƿ���Է��͵��ļ�������������socket������ģʽ�µȴ������¼�֪ͨ�����Է������ݣ�
	bool first_connetion = true;

	//1-1���÷������Ķ˿ں͵�ַ����Ŀ¼
	#ifdef setdeploy
		int p1, p2, p3, p4;
		char c;
		std::cout << "���ü�����ַΪ��";
		do {
			cin >> p1 >> c >> p2 >> c >> p3 >> c >> p4;
			if (p1 > 255 || p2 > 255 || p3 > 255 || p4 > 255)
			{
				printf("IP ERROR!\n�������������ַ:");
			}
		} while (p1 > 255 || p2 > 255 || p3 > 255 || p4 > 255);//�ж�IP�Ƿ�������ȷ
		printf("IP RIGHT!\n");
		int presult;
		presult = p1 << 24 + p2 << 16 + p3 << 8 + p4;//IP��ַ
		int portnumber;//�˿ں�
		std::cout << "���ö˿ں�Ϊ��";
		do {
			cin >> portnumber;
			if (portnumber > 65535)
			{
				std::cout << "�˿ںŴ���" << endl << "��������˿ںţ�";
			}
		} while (portnumber > 65535);//�ж��˿ں��Ƿ�������ȷ
		std::cout << "�˿ں���ȷ!" << endl;
		std::cout << "������Ŀ¼Ϊ��";
		string s;
		cin >> s;
		const char* cata = s.c_str();
		int i = 0;
		int len = s.length();
		char catalog[10];
		for (i = 0; i < len; i++)
			catalog[i] = cata[i];
		catalog[len] = '\0';//������Ŀ¼
	#endif // setdeploy



	int nRc = WSAStartup(0x0202,&wsaData);

	if(nRc){
		printf("Winsock  startup failed with error!\n");
	}

	if(wsaData.wVersion != 0x0202){
		printf("Winsock version is not correct!\n");
	}

	printf("Winsock  startup Ok!\n");


	//����socket
	SOCKET srvSocket;	

	//��������ַ�Ϳͻ��˵�ַ
	sockaddr_in addr,clientAddr;

	//�Ựsocket�������client����ͨ��
	SOCKET sessionSocket;

	//ip��ַ����
	int addrLen;

	//��������socket
	srvSocket = socket(AF_INET,SOCK_STREAM,0);
	if(srvSocket != INVALID_SOCKET)
		printf("Socket create Ok!\n");


	//1-1���÷������Ķ˿ں͵�ַ����ǰ�治����һ������Ϊ��Ҫ�������ٴ����׽��ֲ���
	#ifdef setdeploy
	addr.sin_family = AF_INET;
	addr.sin_port = htons(portnumber);//�����趨�Ķ˿ں�
	addr.sin_addr.S_un.S_addr = htonl(presult); //�����趨�ļ�����ַ
	std::cout << "������ַ���˿ںš���Ŀ¼������ϣ�"<<endl;
	#else
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5050);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //����������һ��������IP��ַ
	std::cout << "������ַ���˿ںš���Ŀ¼������ϣ�" << endl;
	#endif // setdeploy




	//binding �󶨶˿ںźͼ���socket
	int rtn = bind(srvSocket,(LPSOCKADDR)&addr,sizeof(addr));
	if(rtn != SOCKET_ERROR)
		printf("Socket bind Ok!\n");

	//����1-2
	rtn = listen(srvSocket,5);
	if(rtn != SOCKET_ERROR)
		printf("Socket listen Ok!\n");

	clientAddr.sin_family =AF_INET;
	addrLen = sizeof(clientAddr);

	//���ý��ջ�����
	char recvBuf[4096];

	u_long blockMode = 1;//��srvSock��Ϊ������ģʽ�Լ����ͻ���������

	//����ioctlsocket����srvSocket��Ϊ������ģʽ���ĳɷ������fd_setԪ�ص�״̬����ÿ��Ԫ�ض�Ӧ�ľ���Ƿ�ɶ����д
	if ((rtn = ioctlsocket(srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO��������ֹ�׽ӿ�s�ķ�����ģʽ��
		std::cout << "ioctlsocket() failed with error!\n";
		return;
	}
	std::cout << "ioctlsocket() for server socket ok!	Waiting for client connection and data\n";

	while(true){
		//���rfds��wfds����
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);

		//��srvSocket����rfds����
		//�������ͻ�������������ʱ��rfds������srvSocket��Ӧ�ĵ�״̬Ϊ�ɶ�
		//��������������þ��ǣ����õȴ��ͻ���������
		FD_SET(srvSocket, &rfds);

		//���first_connetionΪtrue��sessionSocket��û�в���
		if (!first_connetion) {
			//��sessionSocket����rfds�����wfds����
			//�������ͻ��˷������ݹ���ʱ��rfds������sessionSocket�Ķ�Ӧ��״̬Ϊ�ɶ��������Է������ݵ��ͻ���ʱ��wfds������sessionSocket�Ķ�Ӧ��״̬Ϊ��д
			//�����������������þ��ǣ�
			//���õȴ��ỰSOKCET�ɽ������ݻ�ɷ�������
			if (sessionSocket != INVALID_SOCKET) { //���sessionSocket����Ч��
				FD_SET(sessionSocket, &rfds);
				FD_SET(sessionSocket, &wfds);
			}
			
		}
		
		/*
			select����ԭ������Ҫ�������ļ����������ϣ��ɶ�����д�����쳣����ʼ������select��������״̬��
			���пɶ�д�¼����������õĵȴ�ʱ��timeout���˾ͻ᷵�أ�����֮ǰ�Զ�ȥ�����������¼��������ļ�������������ʱ�������¼��������ļ����������ϡ�
			��select�����ļ��ϲ�û�и����û������а����ļ����������ļ�����������Ҫ�û��������б�������(ͨ��FD_ISSET���ÿ�������״̬)��
		*/
		//��ʼ�ȴ����ȴ�rfds���Ƿ��������¼���wfds���Ƿ��п�д�¼�
		//The select function returns the total number of socket handles that are ready and contained in the fd_set structure
		//�����ܹ����Զ���д�ľ������
		int nTotal = select(0, &rfds, &wfds, NULL, NULL);

		//���srvSock�յ��������󣬽��ܿͻ���������
		if (FD_ISSET(srvSocket, &rfds)) {
			nTotal--;   //��Ϊ�ͻ���������Ҳ��ɶ��¼������-1��ʣ�µľ��������пɶ��¼��ľ�����������ж��ٸ�socket�յ������ݣ�

			//�����ỰSOCKET    1-3
			sessionSocket = accept(srvSocket, (LPSOCKADDR)&clientAddr, &addrLen);
			if (sessionSocket != INVALID_SOCKET)
				printf("Socket listen one client request!\n");
			#ifdef output //2-2
			std::cout << "�����IP��ַΪ:" << clientAddr.sin_addr.S_un.S_addr << endl;
			std::cout << "����Ķ˿ڵ�ַ��" << clientAddr.sin_port << endl;
			#endif // output


			//�ѻỰSOCKET��Ϊ������ģʽ
			if ((rtn = ioctlsocket(sessionSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO��������ֹ�׽ӿ�s�ķ�����ģʽ��
				std::cout << "ioctlsocket() failed with error!\n";
				return;
			}
			std::cout << "ioctlsocket() for session socket ok!	Waiting for client connection and data\n";

			//���õȴ��ỰSOKCET�ɽ������ݻ�ɷ�������
			FD_SET(sessionSocket, &rfds);
			FD_SET(sessionSocket, &wfds);

			first_connetion = false;

		}

		//���ỰSOCKET�Ƿ������ݵ���
		if (nTotal >= 0) { //��������пɶ��¼���˵���ǻỰsocket�����ݵ���
			//����ỰSOCKET�����ݵ���������ܿͻ�������
			if (FD_ISSET(sessionSocket, &rfds)) {
				//receiving data from client
				memset(recvBuf, '\0', 4096);
				rtn = recv(sessionSocket, recvBuf, 256, 0);
				if (rtn > 0) {
					//2-2 ���http����
					#ifdef output
					printf("HTTP����Ϊ %d bytes �ģ� %s\n", rtn, recvBuf); 
					#endif // output

				#ifdef response//1-4,2-1
					char request[10000], detail[1000];
					int i = 0;
					//��ȡhttp����
					//cout << "response";
					for (i = 0; recvBuf[i] != ' '; i++)
						request[i] = recvBuf[i];
					request[i] = '\0';
					//std::cout << "request:" << request << endl;
					i += 1;//�ҵ��ļ�λ��
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
						std::cout << "�û������ȡ���ļ��ǣ�" << filename << endl;
						#endif // outout
						//���ļ�
						FILE* fp;
						fp = fopen(filename, "rb");
						//���ļ�ʧ��
						if (!fp)
						{
							std::cout << filename <<"�ļ���ʧ��" << endl;
							std::cout << "���û�����404" << endl;//���������Ĵ�����
							string message;
							message = "http/1.1 404 NOTFOUND\r\n";
							rtn = send(sessionSocket, message.c_str(), message.length(), 0);
							message = "Content-Type: text/html\r\n";
							rtn = send(sessionSocket, message.c_str(), message.length(), 0);
							message = "\r\n";
							rtn = send(sessionSocket, message.c_str(), message.length(), 0);
							message = "<html><body><h1>404</h1><p> FILE Not Found!</p></body></html>";
							rtn = send(sessionSocket, message.c_str(), message.length(), 0);
							if (rtn == SOCKET_ERROR) std::cout << "��������Ӧ���ķ���ʧ�ܣ�" << endl;
							else cout << "��Ӧ�����ѷ��ͣ�" << endl;
						}
						else {//���ļ��ɹ�
							std::cout << filename << "�ļ��򿪳ɹ�" << endl;
							std::cout << "���û�����200 OK" << endl;//���������Ĵ�����
							string message;
							message = "http/1.1 200 OK\r\n";
							rtn = send(sessionSocket, message.c_str(), message.length(), 0);
							int messagelength;
							//��ȡ�����ܳ���
							fseek(fp, 0, SEEK_END);
							messagelength = ftell(fp);
							rewind(fp);
							//�������ݳ��ȷ����ڴ�buffer
							char* Buffer = (char*)malloc((messagelength + 1) * sizeof(char));
							memset( Buffer, 0, messagelength+1);
							//�����ݶ���buffer
							fread(Buffer,1,messagelength, fp);
							fclose(fp);

							if (filename[length - 2] == 'n')//png
							{
								message = "Content-Type: application/octet-stream\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								message = "\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								rtn = send(sessionSocket, Buffer, messagelength, 0);
								if (rtn == SOCKET_ERROR) std::cout << "��������Ӧ���ķ���ʧ�ܣ�" << endl;
								else cout << "���ݱ����ѷ��ͣ�" << endl;
							}
							else if (filename[length - 2] == 'p')//jpg
							{
								message = "Content-Type: image/jpeg\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								message = "\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								rtn = send(sessionSocket, Buffer, messagelength, 0);
								if (rtn == SOCKET_ERROR) std::cout << "��������Ӧ���ķ���ʧ�ܣ�" << endl;
								else cout << "���ݱ����ѷ��ͣ�" << endl;
							}
							else//txt/html
							{
								message = "Content-Type: text/html;charset=utf-8\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								message = "\r\n";
								rtn = send(sessionSocket, message.c_str(), message.length(), 0);
								rtn = send(sessionSocket, Buffer, messagelength, 0);
								if (rtn == SOCKET_ERROR) std::cout << "��������Ӧ���ķ���ʧ�ܣ�" << endl;
								else cout << "���ݱ����ѷ��ͣ�" << endl;
							}
						}

					}
				#endif // response


				}
				else { //�������յ��˿ͻ��˶Ͽ����ӵ�����Ҳ��ɶ��¼����������������FD_ISSET(sessionSocket, &rfds)����false
					printf("Client leaving ...\n");
					closesocket(sessionSocket);  //��Ȼclient�뿪�ˣ��͹ر�sessionSocket
					nTotal--;	//��Ϊ�ͻ����뿪Ҳ���ڿɶ��¼���������Ҫ-1
					sessionSocket = INVALID_SOCKET; //��sessionSocket��ΪINVALID_SOCKET
				}
			}
		}	
	}

}