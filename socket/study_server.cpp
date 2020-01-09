#include<winSock2.h>
#include<iostream>
#pragma comment(lib, "ws2_32.lib") //添加动态链接库

using namespace std;

int main(int argc, char * argv[]) {
	const int	BUFSIZE = 1024;
	SOCKET		ListeningSocket; //定义一个套接字变量
	SOCKET		NewConnection; //客户端的请求生成的新的套接字
	SOCKADDR_IN ClientAddr;
	SOCKADDR_IN ServerAddr;
	char		Message[BUFSIZE];
	int			ClientAddrLen;
	ZeroMemory(Message, BUFSIZE);
	
	if (argc <= 1)
	{
		cout << "USAGE: TcpServer <Listen Port>" << endl;
		return -1;
	}

	
	int ret; //用来检查初始化成功是否
	WSADATA wsaDATA; // 创建一个WSADATA 用来初始化套接字网络库
	
	if ( (ret = WSAStartup(MAKEWORD(2,2), &wsaDATA)) != 0) { // 初始化套接字网络库WinSock2.2版本
		cout << "WSAStartup初始化失败 with error " << ret << endl;
		return -1;
	}

	//创建套接字 AF_INET协议 SOCK_STREAM流 TCP协议
	if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR) {
		cout << "创建套接字失败 with error " << WSAGetLastError() << endl;
		WSACleanup();
		return -1; 
	}

	//绑定套接字
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(atoi(argv[1]));
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(ListeningSocket, (SOCKADDR *)&ServerAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "绑定套接字失败 with error " << WSAGetLastError() << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return -1;
	}
	 
	//监听套接字
	if((ret = listen(ListeningSocket, 1)) == SOCKET_ERROR) {
		cout << "监听套接字失败 with error " << WSAGetLastError() << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return -1;
	}
	cout << "正在监听端口"<< argv[1] << "中..." << endl;


	//接收客户端数据

	ClientAddrLen = sizeof(SOCKADDR);

	if((NewConnection = accept(ListeningSocket,(SOCKADDR*)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET){//创建一个当前客户端和服务端的套接字
		cout << "创建NewConnection失败 with error " << WSAGetLastError() << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return -1;
	}

	//关闭套接字
	closesocket(ListeningSocket);

	recv(NewConnection, Message, sizeof(Message), 0);
	cout << "接收到的数据为:" << Message << endl;


	closesocket(NewConnection);
	WSACleanup();
	

	return 0;
}