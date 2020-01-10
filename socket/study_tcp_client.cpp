#include<WinSock2.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib") //添加动态链接库
#pragma warning(disable:4996) //忽略旧函数使用缺陷的警告

using namespace std;

int main(int argc, char * argv[]) {
	const int	BUFSIZE = 1024;
	SOCKET		ClientSocket;
	SOCKADDR_IN ServerAddr;
	char		SendBuf[BUFSIZE];  //发送存储的数据缓冲区
	char		BufRecv[BUFSIZE]; //接收收到的数据缓冲区
	
	ZeroMemory(SendBuf, BUFSIZE);
	ZeroMemory(BufRecv, BUFSIZE);
	strcpy(SendBuf, "Hello, My Name is Client");

	if (argc <= 2)
	{
		cout << "USAGE: TcpServer <Server IP> <Server PORT>" << endl;
		return -1;
	}

	WSADATA		WSAData;
	int			ret;
	if ((ret = WSAStartup(MAKEWORD(2, 2), &WSAData)) != 0) {
		cout << "WSAStartup初始化失败 with error " << ret << endl;
		return -1;
	}
	

	//创建套接字
	if ((ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR) {
		cout << "创建套接字失败 with error " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}

	//连接connet服务端
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = inet_addr(argv[1]);
	ServerAddr.sin_port = htons(atoi(argv[2]));
	if (connect(ClientSocket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		cout << "连接服务端失败 with error " << WSAGetLastError() << endl;
		closesocket(ClientSocket);
		WSACleanup();
		return -1;
	}

	cout << "连接建立成功!";


	//send发送数据
	if ((ret = send(ClientSocket, SendBuf, strlen(SendBuf), 0)) == SOCKET_ERROR){
		cout << "send failed with error " << WSAGetLastError() << endl;;
		closesocket(ClientSocket);
		WSACleanup();
		return -1;
	}

	//关闭套接字
	closesocket(ClientSocket);
	WSACleanup();
	return 0;

	
}