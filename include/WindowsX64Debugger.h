// WindowsX64Debugger.h : Include file for standard system include files,
// or project specific include files.
// TODO: Reference additional headers your program requires here.

#pragma once

#include <iostream>
#include <Windows.h>
#include <minwinbase.h>
#include <debugapi.h>
#include <string>

//declarations
bool debugRelationship = TRUE;
DEBUG_EVENT debugEvent;
DWORD uprocessId;
HANDLE processHandle;
