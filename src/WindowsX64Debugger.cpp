#include "WindowsX64Debugger.h"

#define DEBUG_PROCESS 0x00000001
#define DEBUG_ONLY_THIS_PROCESS 0x00000002

BOOL debugRelationship = TRUE;
DEBUG_EVENT debugEvent;
STARTUPINFO sInfo;
PROCESS_INFORMATION pInfo;
LPCSTR applicationPath;
HANDLE process_handle;
LPVOID base_address;
BYTE original_byte;
BYTE debug = 0xCC;
DWORD old_protection;

void printDebugEvent(DWORD debug_ec) {
	switch (debug_ec) {
	case EXCEPTION_DEBUG_EVENT:       std::cout << debug_ec << " - EXCEPTION_DEBUG_EVENT\n"; break;
	case CREATE_THREAD_DEBUG_EVENT:   std::cout << debug_ec << " - CREATE_THREAD_DEBUG_EVENT\n"; break;
	case CREATE_PROCESS_DEBUG_EVENT:  std::cout << debug_ec << " - CREATE_PROCESS_DEBUG_EVENT\n"; break;
	case EXIT_THREAD_DEBUG_EVENT:     std::cout << debug_ec << " - EXIT_THREAD_DEBUG_EVENT\n"; break;
	case EXIT_PROCESS_DEBUG_EVENT:    std::cout << debug_ec << " - EXIT_PROCESS_DEBUG_EVENT\n"; break;
	case LOAD_DLL_DEBUG_EVENT:        std::cout << debug_ec << " - LOAD_DLL_DEBUG_EVENT\n"; break;
	case UNLOAD_DLL_DEBUG_EVENT:      std::cout << debug_ec << " - UNLOAD_DLL_DEBUG_EVENT\n"; break;
	case OUTPUT_DEBUG_STRING_EVENT:   std::cout << debug_ec << " - OUTPUT_DEBUG_STRING_EVENT\n"; break;
	case RIP_EVENT:                   std::cout << debug_ec << " - RIP_EVENT\n"; break;
	default:                          std::cout << debug_ec << " - UNKNOWN_EVENT\n"; break;
	}
}

void installBreakPoint() {
	ReadProcessMemory(process_handle, base_address, &original_byte, 1, nullptr);
	VirtualProtectEx(process_handle, base_address, 1, PAGE_EXECUTE_READWRITE, &old_protection);
	WriteProcessMemory(process_handle, base_address, &debug, 1, nullptr);
	VirtualProtectEx(process_handle, base_address, 1, old_protection, &old_protection);
	FlushInstructionCache(process_handle, base_address, 1);
	
	std::cout << "[+] Software Breakpoint (0xCC) successfully installed at base address: " << base_address << "\n";
}

uintptr_t convertToAddress(char* hex) {
	return std::stoull(hex, nullptr, 0);
}

int main(int argc, char* argv[])
{	
	// exit if only one argument provided
	if (argc != 3) {
		std::cout << "Please provide the correct arguments!";
		return 1;
	}
	
	ZeroMemory(&sInfo, sizeof(sInfo));
	sInfo.cb = sizeof(sInfo);
	ZeroMemory(&pInfo, sizeof(pInfo));

	applicationPath = argv[1];
	if (!CreateProcessA(applicationPath, NULL, NULL, NULL, FALSE, DEBUG_ONLY_THIS_PROCESS, NULL, NULL, &sInfo, &pInfo)) {
		std::cout << "CreateProcess failed. Error: " << GetLastError() << "\n";
		return 1;
	};
	std::cout << "Debugger started\n";
	process_handle = pInfo.hProcess;

	while (debugRelationship) {
		if (!WaitForDebugEvent(&debugEvent, INFINITE)) {
			break;
		}
		switch (debugEvent.dwDebugEventCode)
		{
		case CREATE_PROCESS_DEBUG_EVENT:
			printDebugEvent(debugEvent.dwDebugEventCode);
			base_address = reinterpret_cast<LPVOID>(convertToAddress(argv[2]));
			installBreakPoint();
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
			printDebugEvent(debugEvent.dwDebugEventCode);
			debugRelationship = FALSE;
			break;
		default:
			printDebugEvent(debugEvent.dwDebugEventCode);
			break;
		}
		ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
	};
	if (pInfo.hThread) CloseHandle(pInfo.hThread);
	if (process_handle) CloseHandle(process_handle);
	return 0;
}
