#include<stdio.h>
#include<windows.h>


/*
 * 实现递归遍历目录的操作
 * 使用的API有以下三个：
 * FindFirstFile
 * FindNextFile
 * WIN32_FIND_DATA
*/
DWORD EnumerateFileInDirectory(LPCWSTR szPath){
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile; //定义一个实例句柄 来接收FindFirstFile api函数返回的对象
	wchar_t szFilePath[MAX_PATH];
	wchar_t szFullPath[MAX_PATH]; //绝对路径

	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, L"\\*");

	hListFile = FindFirstFile(szFilePath, &FindFileData); //FindFirstFile会把szFilePath
	if(hListFile == INVALID_HANDLE_VALUE){
		printf("错误：%d \n", GetLastError());
		return 1;
	}else {
		do {
			if (lstrcmp(FindFileData.cFileName, L".") == 0 || lstrcmp(FindFileData.cFileName, L"..") == 0){
				continue;
			}


			wsprintf(szFullPath, L"%ls\\%ls", szPath, FindFileData.cFileName);
			//printf("%ls\\%ls", szPath, FindFileData.cFileName);
			printf("\n%ls\t", szFullPath);
			//if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) { //判断文件的属性是否为隐藏，如果是的话 输出个前缀为HIDDEN
			//	printf("<HIDDEN> ");
			//}
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { //判断是否是目录，如果是的话 输出个前缀为DIR
				printf("\t<DIR>");
				EnumerateFileInDirectory(szFullPath);
			}
			
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
				printf("\t<FILE>");
			}

			//printf("\n");

		} while (FindNextFile(hListFile, &FindFileData));
	}
	printf("\n");
	return 0;
}



int main() {

	EnumerateFileInDirectory(L"C:\\Users\\dell\\source\\repos\\msgboxtest");
	system("pause");
	return 0;
}