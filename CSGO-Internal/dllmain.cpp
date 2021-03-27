#include "stdafx.h"
#include "csgohax.h"

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReasonCalls, LPVOID lpReversed)
{
	switch (dwReasonCalls)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)csgohax::main, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
