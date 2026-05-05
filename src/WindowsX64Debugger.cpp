#include "WindowsX64Debugger.h"

using namespace std;

void printDebugEvent(DWORD debug_ec) {
	switch (debug_ec) {
	case EXCEPTION_DEBUG_EVENT:
		std::cout << debug_ec << " - EXCEPTION_DEBUG_EVENT\n";
		break;
	case CREATE_THREAD_DEBUG_EVENT:
		std::cout << debug_ec << " - CREATE_THREAD_DEBUG_EVENT\n";
		break;
	case CREATE_PROCESS_DEBUG_EVENT:
		std::cout << debug_ec << " - CREATE_PROCESS_DEBUG_EVENT\n";
		break;
	case EXIT_THREAD_DEBUG_EVENT:
		std::cout << debug_ec << " - EXIT_THREAD_DEBUG_EVENT\n";
		break;
	case EXIT_PROCESS_DEBUG_EVENT:
		std::cout << debug_ec << " - EXIT_PROCESS_DEBUG_EVENT\n";
		debugRelationship = FALSE;
		break;
	case LOAD_DLL_DEBUG_EVENT:
		std::cout << debug_ec << " - LOAD_DLL_DEBUG_EVENT\n";
		break;
	case UNLOAD_DLL_DEBUG_EVENT:
		std::cout << debug_ec << " - UNLOAD_DLL_DEBUG_EVENT\n";
		break;
	case OUTPUT_DEBUG_STRING_EVENT:
		std::cout << debug_ec << " - OUTPUT_DEBUG_STRING_EVENT\n";
		break;
	case RIP_EVENT:
		std::cout << debug_ec << " - RIP_EVENT\n";
		break;
	}
}

int main(int argc, char* argv[])
{	
	// exit if only one argument provided
	if (argc != 2) {
		std::cout << "Only one argument provided.\n";
		return 1;
	}
	//takes the string -> convert to DWORD
	uprocessId = std::stoul(argv[1]);

	if (!DebugActiveProcess(uprocessId)) return GetLastError();
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, uprocessId);

	while (debugRelationship) {
		WaitForDebugEvent(&debugEvent, INFINITE);
		printDebugEvent(debugEvent.dwDebugEventCode);
		ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
	};

	DebugActiveProcessStop(uprocessId);
	CloseHandle(processHandle);
	return 0;
}
