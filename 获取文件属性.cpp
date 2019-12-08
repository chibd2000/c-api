#include <stdio.h>
#include <Windows.h>

/*
WIN32_FILE_ATTRIBUTE_DATA  文件属性的结构体 
GetFileAttributesEx   这个是GetFileAttributes的加强版哇
*/

DWORD ShowFileSize(DWORD nFileSizeHigh, DWORD nFileSizeLow)
{                       //32位相当于4G，如果小的话 没必要
    ULONGLONG FileSize; //64位无符号的整数来存储文件大小，因为    DWORD nFileSizeHigh   DWORD nFileSizeLow
    FileSize = nFileSizeHigh;
    FileSize <<= 32;
    FileSize += nFileSizeLow;
    printf("文件大小为:%I64d\n", FileSize);
    return 0;
}

DWORD ShowFileAttribute(DWORD dwFileAttributes)
{
    printf("文件信息\t");
    if (dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
    { //进行与运算
        printf("<ARCHIVE>\n");
    }
    if (dwFileAttributes & FILE_ATTRIBUTE_READONLY)
    { //进行与运算
        printf("<READ_ONLY>\n");
    }
    if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    { //进行与运算
        printf("<DIRECTORY>\n");
    }
    return 0;
}

DWORD ShowFileTime(LPFILETIME init_time)
{ //FileTimeToLocalFileTime接收的是指针类型 所以这里定义PFILETIME，
    FILETIME lpf1;
    SYSTEMTIME st;
    FileTimeToLocalFileTime(init_time, &lpf1);
    FileTimeToSystemTime(&lpf1, &st);
    printf("%4d年%02d月%02d日,%02d:%02d:%02d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    return 0;
}

DWORD ShowFileAttribute(LPCWSTR FilePath)
{
    WIN32_FILE_ATTRIBUTE_DATA wfad; //定义一个结构体 ，保存GetFileAttributesEx获取到的文件属性
    if (!GetFileAttributesEx(FilePath, GetFileExInfoStandard, &wfad))
    { // GetFileExInfoStandard枚举常量，&wfad 指向接收属性信息的缓冲区的指针
        printf("获取文件属性失败: %d\n", GetLastError());
        return 0; //如果失败 返回0
    }
    //得到wfad结构中的原始时间 还需要转换，先转换为本地时间，然后转换为系统时间
    printf("创建时间:\t");
    ShowFileTime(&(wfad.ftCreationTime));
    printf("修改时间:\t");
    ShowFileTime(&(wfad.ftLastWriteTime));
    printf("访问时间:\t");
    ShowFileTime(&(wfad.ftLastAccessTime));
    ShowFileSize(wfad.nFileSizeHigh, wfad.nFileSizeLow);
    ShowFileAttribute(wfad.dwFileAttributes);
}

int main()
{
    ShowFileAttribute(L"C:\\Users\\dell\\source\\repos\\msgboxtest\\AbleWrite.txt");
    system("pause");
    return 0;
}