// WindowsX64Debugger.h : Include file for standard system include files,
// or project specific include files.
// TODO: Reference additional headers your program requires here.

#pragma once

#include <iostream>
#include <cstdint>
#include <Windows.h>
#include <minwinbase.h>
#include <debugapi.h>
#include <string>
#include <vector>

void printDebugEvent(DWORD debug_ec);
void installBreakPoint();
uintptr_t convertToAddress(char* hex);
