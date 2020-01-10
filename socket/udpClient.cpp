#include<WinSock2.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) //忽略旧函数使用缺陷的警告

using namespace std;

int main(int argc, char * argv[]) {
	const int BUFSIZE = 1024;
	WSADATA		WSAData;
	SOCKET		ClientSocket;
	SOCKADDR_IN ClientAddr;
	char		buf[BUFSIZE];
	
	WSAStartup(MAKEWORD(2, 2), &WSAData);


	//创建套接字
	ClientSocket = socket(AF_INET,SOCK_DGRAM , IPPROTO_UDP);
	
	ClientAddr.sin_addr.s_addr = inet_addr(argv[1]);
	ClientAddr.sin_port = htons(atoi(argv[2]));
	ClientAddr.sin_family = AF_INET;
	
	int ClientAddrLen = sizeof(ClientAddr);
	//发送数据
	while (true) {
		ZeroMemory(buf, sizeof(buf));
		cout << "客户端: ";
		cin >> buf;
		sendto(ClientSocket, buf, sizeof(buf), 0, (SOCKADDR *)&ClientAddr, sizeof(ClientAddr));
		recvfrom(ClientSocket, buf, sizeof(buf), 0, (SOCKADDR *)&ClientAddr, &ClientAddrLen);

		cout << "服务端: " << buf << endl;
	}

	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}