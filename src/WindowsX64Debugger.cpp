#include "WindowsX64Debugger.h"

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
		switch (de.dwDebugEventCode) {
		case EXCEPTION_DEBUG_EVENT: 
			std::cout << de.dwDebugEventCode << " - EXCEPTION_DEBUG_EVENT\n";
			break;
		case CREATE_THREAD_DEBUG_EVENT:
			std::cout << de.dwDebugEventCode << " - CREATE_THREAD_DEBUG_EVENT\n";
			break;
		case CREATE_PROCESS_DEBUG_EVENT: 
			std::cout << de.dwDebugEventCode << " - CREATE_PROCESS_DEBUG_EVENT\n";
			break;
		case EXIT_THREAD_DEBUG_EVENT: 
			std::cout << de.dwDebugEventCode << " - EXIT_THREAD_DEBUG_EVENT\n";
			break;
		case EXIT_PROCESS_DEBUG_EVENT: 
			std::cout << de.dwDebugEventCode << " - EXIT_PROCESS_DEBUG_EVENT\n";
			running = FALSE;
			break;
		case LOAD_DLL_DEBUG_EVENT: 
			std::cout << de.dwDebugEventCode << " - LOAD_DLL_DEBUG_EVENT\n";
			break;
		case UNLOAD_DLL_DEBUG_EVENT: 
			std::cout << de.dwDebugEventCode << " - UNLOAD_DLL_DEBUG_EVENT\n";
			break;
		case OUTPUT_DEBUG_STRING_EVENT: 
			std::cout << de.dwDebugEventCode << " - OUTPUT_DEBUG_STRING_EVENT\n";
			break;
		case RIP_EVENT: 
			std::cout << de.dwDebugEventCode << " - RIP_EVENT\n";
			break;
		}
		ContinueDebugEvent(de.dwProcessId, de.dwThreadId, DBG_CONTINUE);
	};
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}
