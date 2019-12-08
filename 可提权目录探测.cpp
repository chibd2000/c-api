#include <Windows.h>
#include <stdio.h>
//用多字节编码来写的

DWORD ToCreateFile(const char *FilePath)
{
    HANDLE hFile; //用来接收CreateFile返回来的句柄，用这个句柄来进行写入的操作
    DWORD dwWritten;
    char szFullPath[MAX_PATH];
    int len = strlen(FilePath);
    if (FilePath[len - 1] == '\\')
    {
        wsprintf(szFullPath, "%s\%s", FilePath, "AbleWrite.txt"); //拼接字符串，成为一个完整的路径
        hFile = CreateFile(szFullPath,
                           GENERIC_WRITE,
                           0,
                           NULL,
                           CREATE_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
                           NULL); //创建文件AbleWrite.txt

        if (hFile != INVALID_HANDLE_VALUE)
        {
            if (!WriteFile(hFile, NULL, NULL, &dwWritten, NULL)) //将系统目录，系统信息写入文件中
            {
                return GetLastError(); //如果写入失败 返回错误信息
            }

            //打印当前能写入文件的路径
            printf("可写入路径有：%s \n", FilePath);
        }
        CloseHandle(hFile); //关闭文件句柄

        //如果能写入的话 然后进行删除文件的操作
        DeleteFile(szFullPath); //接收类型的数据为LPCSTR
    }
    else
    {
        //首先判断当前路径是否存在
        WIN32_FIND_DATA FindFileData;
        HANDLE hListFile;
        hListFile = FindFirstFile(FilePath, &FindFileData);
        if (hListFile == INVALID_HANDLE_VALUE)
        {
            return 1;
        }
        else
        {
            printf("当前路径文件能进行提权操作：%s \n", FilePath);
        }
    }

    return 0;
}

int main()
{
    const char *FileDictory[] = {
        "C:\\RECYCLER\\",
        "c:\\programdata\\",
        "C:\\windows\\temp\\",
        "e:\\recycler\\",
        "f:\\recycler\\",
        "C:\\php\\PEAR\\",
        "C:\\WINDOWS\\7i24.com\\FreeHost\\",
        "C:\\php\\dev\\",
        "C:\\System Volume Information\\",
        "C:\\7i24.com\\serverdoctor\\log\\",
        "c:\\windows\\hchiblis.ibl",
        "C:\\7i24.com\\iissafe\\log\\",
        "C:\\7i24.com\\LinkGate\\log\\",
        "C:\\Program Files\\Thunder Network\\Thunder7\\",
        "C:\\Program Files\\Thunder Network\\Thunder\\",
        "C:\\Program Files\\Symantec AntiVirus\\SAVRT\\",
        "C:\\windows\\DriverPacks\\C\\AM2\\",
        "C:\\Program Files\\FlashFXP\\",
        "C:\\Program Files\\Microsoft SQL Server\\90\\Shared\\ErrorDumps\\",
        "C:\\Program Files\\Zend\\ZendOptimizer-3.3.0\\",
        "C:\\Program Files\\Common Files\\",
        "C:\\Documents and Settings\\All Users\\Application Data\\Hagel Technologies\\DU Meter\\log.csv",
        "C:\\Program Files\\360\\360Safe\\deepscan\\Section\\mutex.db",
        "C:\\Program Files\\Helicon\\ISAPI_Rewrite3\\error.log",
        "C:\\Program Files\\Helicon\\ISAPI_Rewrite3\\Rewrite.log",
        "C:\\Program Files\\Helicon\\ISAPI_Rewrite3\\httpd.conf",
        "C:\\Program Files\\Common Files\\Symantec Shared\\Persist.bak",
        "C:\\Program Files\\Common Files\\Symantec Shared\\Validate.dat",
        "C:\\Program Files\\Common Files\\Symantec Shared\\Validate.dat",
        "C:\\Program Files\\Zend\\ZendOptimizer-3.3.0\\docs\\",
        "C:\\Documents and Settings\\All Users\\DRM\\",
        "C:\\Documents and Settings\\All Users\\Application Data\\McAfee\\DesktopProtection\\",
        "C:\\Documents and Settings\\All Users\\Application Data\\360safe\\softmgr\\",
        "C:\\Program Files\\Zend\\ZendOptimizer-3.3.0\\lib\\Optimizer-3.3.0\\php-5.2.x\\ZendOptimizer.dll",
        "C:\\Documents and Settings\\All Users\\Application Data\\Microsoft\\Media Index\\",
    };

    int len = sizeof(FileDictory) / sizeof(FileDictory[0]);
    printf("#author:zpchcbd\n");
    printf("#result:寻找常见的可读写目录\n");
    for (int i = 0; i < len; i++)
    {
        ToCreateFile(FileDictory[i]);
    }
    system("pause");
    return 0;
}