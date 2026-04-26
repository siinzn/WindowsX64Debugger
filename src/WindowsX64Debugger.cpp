#include "WindowsX64Debugger.h"

#define DBG_CONTINUE ((DWORD)0x00010002L)
#define DEBUG_PROCESS 0x00000001

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
	if (!CreateProcessA(applicationName, NULL, NULL, NULL, FALSE, DEBUG_PROCESS, NULL, NULL, &si, &pi));
	while (running) {
		//std::cout << "Success! - " << pi.dwThreadId << " - " << pi.dwProcessId << "\n";
		WaitForDebugEvent(&de, INFINITE);
		std::cout << de.dwDebugEventCode << "\n";
		if (!EXIT_PROCESS_DEBUG_EVENT) running = FALSE;
		ContinueDebugEvent(de.dwProcessId, de.dwThreadId, DBG_CONTINUE);
	};
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}
