﻿#include "stdafx.h"
#include "wechatocr.h"

// dllmain
int APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#ifdef _DEBUG
// 定义这个函数仅方便使用regsvr32.exe调试本DLL, 使用环境变量WECHATOCR_EXE和WECHAT_DIR以及TEST_PNG传入调试参数
extern "C" __declspec(dllexport)
HRESULT WINAPI DllRegisterServer(void)
{
	if (AllocConsole()) {
		(void)freopen("CONOUT$", "w", stdout);
		(void)freopen("CONOUT$", "w", stderr);
		// disalbe stdout cache.
		setvbuf(stdout, NULL, _IONBF, 0);
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
	}
	CWeChatOCR wechat_ocr(_wgetenv(L"WECHATOCR_EXE"), _wgetenv(L"WECHAT_DIR"));
	if (!wechat_ocr.wait_connection(5000)) {
		return E_FAIL;
	}
	wechat_ocr.doOCR(getenv("TEST_PNG"), nullptr);
	// MessageBoxW(NULL, L"注册成功", L"提示", MB_OK);
	wechat_ocr.wait_done(-1);
	return S_OK;
}
#endif
