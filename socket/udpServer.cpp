#include<WinSock2.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main(int argc, char * argv[]) {
	const int BUFSIZE = 1024;
	SOCKET		ServerSocket;
	SOCKADDR_IN ServerAddr;
	SOCKADDR_IN ClientAddr;
	WSADATA		wsaData;
	char		buf[BUFSIZE];
	int ret;
	
	if ((ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		cout << "WSAStartup调用失败" << endl;
		return -1;
	}

	//创建套接字socket

	if((ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
		cout << "创建套接字失败" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}

	//绑定套接字
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(atoi(argv[1]));
	
	if(bind(ServerSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		cout << "绑定套接字失败 " << WSAGetLastError() << endl;
		closesocket(ServerSocket);
		WSACleanup();
		return -1;
	}
	int ClientLen = sizeof(ClientAddr);
	cout << "端口:" << argv[1] << "正在接收数据...." << endl;
	while (true) {
		//接收数据
		ZeroMemory(buf, sizeof(buf));
		if ((ret = recvfrom(ServerSocket, buf, sizeof(buf), 0, (SOCKADDR *)&ClientAddr, &ClientLen)) == SOCKET_ERROR) {
			cout << "接收数据失败" << WSAGetLastError() << endl;
			closesocket(ServerSocket);
			WSACleanup();
			return -1;
		}
		else {
			//发送数据
			cout << "服务端: " << buf << endl;
			sendto(ServerSocket, buf, sizeof(buf), 0, (SOCKADDR *)&ClientAddr, ClientLen);
		}
	}

	closesocket(ServerSocket);
	WSACleanup();
	return 0;
}