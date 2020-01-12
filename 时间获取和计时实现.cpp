//#include<Windows.h>
//#include<iostream>
//#define NUMSIZE 100000
//
//using namespace std;
//
//int compare_func(const void *a, const void *b) { //接收两个任意类型的指针
//	return *(int *)a - *(int *)b; // 比较的是int值 所以需要转换为int类型的指针 然后再取值进行比较
//}
//
//int main(int argc, char * argv[]) {
//
//	SYSTEMTIME st;
//	GetLocalTime(&st); //获取当前机器的时间赋值给结构体st
//	cout << "[" << st.wYear << "-" << st.wMonth << "-" << st.wDay << " " << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒]" << endl;
//
//	st.wHour--;
//	SetLocalTime(&st); //设置时间
//	cout << "[" << st.wYear << "-" << st.wMonth << "-" << st.wDay << " " << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒]" << endl;
//
//	int arr[NUMSIZE];
//
//	srand(GetTickCount());
//
//	for (int i = 0; i < NUMSIZE; i++) {
//		arr[i] = rand() % 1000;
//	}
//	/*
//	qsort用法
//	base -- 指向要排序的数组的第一个元素的指针。
//	nitems -- 由 base 指向的数组中元素的个数。
//	size -- 数组中每个元素的大小，以字节为单位。
//	compare -- 用来比较两个元素的函数。
//	*/
//	int startTime = GetTickCount(); //取开始排序的时间
//	qsort(arr, NUMSIZE, sizeof(arr[0]), compare_func);
//	int endTime = GetTickCount(); //取开始排序的时间
//	cout << "总耗时 " << endTime - startTime << "毫秒" << endl;
//
//
//	//for (int i = 0; i < NUMSIZE; i++)
//	//	cout << arr[i] << endl;
//
//	system("pause");
//	return 0;
//}