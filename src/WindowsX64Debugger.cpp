#include "WindowsX64Debugger.h"

#define DEBUG_PROCESS 0x00000001
#define DEBUG_ONLY_THIS_PROCESS 0x00000002

using namespace std;

int main()
{
	bool running = TRUE;
	LPCSTR applicationName = R"(C:\Windows\System32\notepad.exe)";
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DEBUG_EVENT de;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcessA(applicationName, NULL, NULL, NULL, FALSE, DEBUG_ONLY_THIS_PROCESS, NULL, NULL, &si, &pi)) return 1;
	while (running) {
		WaitForDebugEvent(&de, INFINITE);
		std::cout << de.dwDebugEventCode << "\n";
		if (de.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) running = FALSE;
		ContinueDebugEvent(de.dwProcessId, de.dwThreadId, DBG_CONTINUE);
	};
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}
