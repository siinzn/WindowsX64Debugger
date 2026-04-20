# CMakeList.txt : CMake project for WindowsX64Debugger, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("WindowsX64Debugger")

# Add source to this project's executable.
add_executable (WindowsX64Debugger "src/WindowsX64Debugger.cpp" "include/WindowsX64Debugger.h")
target_include_directories(WindowsX64Debugger PRIVATE "include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WindowsX64Debugger PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
