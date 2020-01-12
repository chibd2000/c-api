//#include<Windows.h>
//#include<iostream>
//#pragma warning(disable:4996)
//
//using namespace std;
//
//int main(int argc, char * argv[]) {
//	OSVERSIONINFO	osver;
//	//char			RecordInfor[1024];
//	//ZeroMemory(RecordInfor, 1024);
//
//	osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); //获取OSVERSIONINFO结构体的大小
//
//	if (!GetVersionEx(&osver)) { // 是否获取成功
//		cout << "获取系统版本失败" << endl;
//		return -1;
//	}
//
//	if (osver.dwMajorVersion == 5) {  //获取成功那么就继续下面的判断
//		if (osver.dwMinorVersion == 0) {
//			cout << "系统版本为WIN 2000" << endl;
//		}
//		else if (osver.dwMinorVersion == 1) {
//			cout << "系统版本为WIN XP" << endl;
//		}
//		else if (osver.dwMinorVersion == 2) {
//			cout << "系统版本为WIN 2003" << endl;
//		}
//	}
//	else if (osver.dwMajorVersion == 6) {
//		if (osver.dwMinorVersion == 0) {
//			cout << "系统版本为WIN Vista" << endl;
//		}
//		else if (osver.dwMinorVersion == 1) {
//			cout << "系统版本为WIN 7 或者 Windows Server 2008 R2" << endl;
//		}
//		else if (osver.dwMinorVersion == 2) {
//			cout << "系统版本为WIN 8 或者 Windows Server 2012" << endl;
//		}
//		else if (osver.dwMinorVersion == 3) {
//			cout << "系统版本为WIN 8.1 或者 Windows Server 2012 R2" << endl;
//		}
//	}
//	else if (osver.dwMajorVersion == 10) {
//		if (osver.dwMinorVersion == 0) {
//			cout << "系统版本为WIN 10 或者 Windows Server 2016 Technical Preview " << endl;
//		}
//	}
//	else {
//		cout << "无法识别" << endl;
//	}
//
//	cout << "高版本号：" << osver.dwMajorVersion << "，次版本号：" << osver.dwMinorVersion << "，build版本号" << osver.dwBuildNumber << endl;
//	
//	DWORD	dwComputerLen = MAX_COMPUTERNAME_LENGTH + 1;
//	wchar_t	ComputerName[MAX_COMPUTERNAME_LENGTH + 1];
//	
//	GetComputerName(ComputerName, &dwComputerLen); //获得计算机名
//	cout << ComputerName << endl;
//
//	DWORD dwComputerUserLen = 64;
//	wchar_t ComputerUserName[64];
//	GetUserName(ComputerUserName, &dwComputerUserLen);//获得当前登陆机器的用户名
//	cout << ComputerUserName << endl;
//
//	
//
//
//
//	cout << "--------------------------------------------------------------------" << endl;
//	cout << "------------------------------硬件信息------------------------------" << endl;
//	cout << "--------------------------------------------------------------------" << endl;
//	
//	SYSTEM_INFO sys_info;  //创建一个SYSTEM_INFO结构体
//
//	GetSystemInfo(&sys_info); //检索有关当前系统的信息
//	cout << "处理器个数："<<  sys_info.dwNumberOfProcessors << endl; // 处理器个数
//	cout << "内存分页大小："<< sys_info.dwPageSize << endl; //内存分页大小
//	cout << "可用内存起始大小：" << sys_info.lpMinimumApplicationAddress << endl; //可用内存起始大小
//	cout << "可用内存结束大小：" <<sys_info.lpMaximumApplicationAddress << endl; //可用内存结束大小
//	cout << "处理器类型：" << sys_info.dwProcessorType << endl; //处理器类型
//	cout << "处理器架构：" << sys_info.wProcessorArchitecture << endl; //处理器架构
//	system("pause");
//	return 0;
//
//}