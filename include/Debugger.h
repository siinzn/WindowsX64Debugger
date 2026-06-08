
#include <iostream>
#include <cstdint>
#include <Windows.h>
#include <minwinbase.h>
#include <debugapi.h>
#include <string>
#include <vector>

class Debugger {
public:
	int run(int argc, char* argv[]);

private:
    void printDebugEvent(DWORD debug_ec);
    void installBreakPoint();
    uintptr_t convertToAddress(char* hex);
    void printRegisters(CONTEXT context);

    BOOL running = TRUE;
    DEBUG_EVENT debugEvent;
    STARTUPINFO sInfo;
    PROCESS_INFORMATION pInfo;
    LPCSTR applicationPath;
    HANDLE process_handle;
    LPVOID baseAddress;
    BYTE originalByte;
    BYTE breakpoint = 0xCC;
    DWORD oldProtection;
    CONTEXT context;
};