#include <windows.h>
#include <stdio.h>

int wmain(int argc, wchar_t *argv[])
{
    /*
		删除文件 api.exe -d 文件路径
		复制文件 api.exe -c 路径1 路径2
		移动/重命名文件 api.exe -m 路径1 路径2
	*/

    if (argc == 3 && 0 == lstrcmp(L"-d", argv[1]))
    { // 满足条件是否是 第二个参数为-d 并且 命令行参数的个数为3  该函数结束的两个值都是为LPCWSTR

        if (!DeleteFile(argv[2]))
        { //unicode的时候 接收的值为 LPCWSTR
            printf("删除失败 \n");
        }
        else
        {
            printf("删除成功 \n");
        }
    }
    else if (argc == 4 && 0 == lstrcmp(L"-c", argv[1]))
    {
        if (!CopyFile(argv[2], argv[3], true))
        { //第三个参数为true那么文件如果已经存在则不进行覆盖
            //复制失败，其中一种可能是存在文件同名,copyfile 返回值为0x50
            if (getchar() == 'y')
            {
                if (!CopyFile(argv[2], argv[3], false))
                { //第三个参数为false那么文件如果已经存在则直接覆盖
                    printf("文件复制失败");
                }
                else
                {
                    printf("文件复制成功");
                }
            }
        }
        else
            printf("文件复制成功! \n");
    }
    else if (argc == 4 && 0 == lstrcmp(L"-m", argv[1]))
    {
        //进行移动/重命名文件的操作
        if (!MoveFile(argv[2], argv[3]))
        { //movefile 和 copyfile api 参数的数据类型一样，用法也类似
            printf("文件移动失败! \n");
        }
        else
        {
            printf("文件移动成功! \n");
        }
    }
    else
    {
        printf("参数错误! 请重新输入");
    }

    system("pause");
    return 0;
}