#include<windows.h>
#include<string>
#include<stdio.h>


int main() {
	char a[] = "这是多字符转宽字符";
	setlocale(LC_ALL, "");
	//先获取其a的大小
	DWORD Mnum; //用来保存大小
	Mnum = MultiByteToWideChar(CP_ACP, 0, a, -1, NULL, 0); //计算a的大小 , 第三个参数为被转换的字符，第四个取最后\0之前的，第五个参数为接收转换之后的数据，由于我们这里先计算大小所以参数为NULL,第六个参数为被转换的大小
	wchar_t * b = new wchar_t[Mnum];
	if (!b) {
		delete[] b;
		return 1;
	}

	MultiByteToWideChar(CP_ACP, 0, a, -1, b, Mnum);
	wprintf(L"L->M %s\n", b);


	DWORD Mnum2;
	wchar_t c[] = L"这是宽字符转多字符";
	Mnum2 = WideCharToMultiByte(CP_OEMCP, 0, c, -1, NULL, 0,NULL,NULL);

	char * d = new char[Mnum2];
	if (!d) {
		delete[] d;
		return 1;
	}
	WideCharToMultiByte(CP_OEMCP, 0, c, -1, d, Mnum2,NULL,NULL);
	printf("M->L %s\n", d);



	system("pause");
	return 0;
}