#pragma once

//Was too lazy to actually make everything clean
//So I stuffed it in here!!

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <future>
#include <sstream>
#include <sysinfoapi.h>
#include <thread>
#include <winternl.h>
#include <fstream>
#include <ctime>
#include <sddl.h>
#include <stdio.h>
#include <locale.h>
#include <tchar.h>
#include <Lmcons.h>
#include <VersionHelpers.h>
#include <psapi.h>
#include <strsafe.h>
#include <random>
#include <filesystem>
#include <urlmon.h>
#include <string>

#define getURL URLOpenBlockingStreamA
#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "ntdll.lib")
#include <d3d9.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_internal.h"
#include "imgui/font.h"

inline DWORD procpid(const std::string& process_name) {
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);
    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
        return 0;
    Process32First(processesSnapshot, &processInfo);
    if (!process_name.compare(processInfo.szExeFile)) {
        CloseHandle(processesSnapshot);

        return processInfo.th32ProcessID;
    }
    while (Process32Next(processesSnapshot, &processInfo)) {
        if (!process_name.compare(processInfo.szExeFile)) {
            CloseHandle(processesSnapshot);

            return processInfo.th32ProcessID;
        }
    }
    CloseHandle(processesSnapshot);
    return 0;
}

inline DWORD servpid(const char* service) {
    const auto h_scm = OpenSCManager(nullptr, nullptr, NULL);
    const auto h_sc = OpenService(h_scm, service, SERVICE_QUERY_STATUS);
    SERVICE_STATUS_PROCESS ssp = {};
    DWORD bytes_needed = 0;
    QueryServiceStatusEx(h_sc, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&ssp), sizeof(ssp), &bytes_needed);
    CloseServiceHandle(h_sc);
    CloseServiceHandle(h_scm);
    return ssp.dwProcessId;
}

inline void termproc(const char* process) {
    DWORD process_id = procpid(process);
    HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, false, process_id);
    TerminateProcess(process_handle, 1);
    CloseHandle(process_handle);
}

namespace iso {
	namespace gui {
		inline char sstate = 'A';
		inline HWND hwnd{};
		inline ImVec4 currentcol = ImColor(143, 105, 255);
		inline bool colorlogo = true;
		inline bool rainmode = false;
	}

	namespace auth {
		inline bool auth = true;
		inline std::string ver = "0.5 \n";
	}

	namespace tools {

	}

	namespace handles {
		inline HANDLE one{};
		inline HANDLE two{};
		inline HANDLE three{};
        inline HANDLE four{};
        inline HANDLE five{};
        inline HANDLE six{};
        inline HANDLE seven{};

    }
}
