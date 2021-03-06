#include "stdafx.h"
#include "dllmain.h"

HMODULE WinhttpModule = NULL;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Initialize();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


void Initialize() {
	#ifdef LOG
	AllocConsole();
	#endif
	ConsoleWrite("Attached \n");
	LoadWinInet();
}


void LoadWinInet() {
	if (WinhttpModule != NULL)
		return;
	char buffer[MAX_PATH];
	GetSystemDirectoryA(buffer, MAX_PATH);
	strcat_s(buffer, "\\winhttp.dll");
	ConsoleWrite("Load original DLL at ");
	ConsoleWrite(buffer);
	ConsoleWrite("\n");
	if (WinhttpModule == NULL) {
		WinhttpModule = LoadLibraryA(buffer);
	}

	if (WinhttpModule == NULL)
	{
		ConsoleWrite("failed to load original winhttp.dll \n");
	}
}
