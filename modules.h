#pragma once

#include "../main.h"
#include "../xorstr.h"
namespace modules {
    namespace clicker {
        namespace random {
            inline int left_edited_cps = 0;
            inline int left_reset_value = 0;
            inline int left_clicks = 0;

            inline int left_drop_reset_value = 0;
            inline int left_drop_counter = 0;
            inline bool left_drop = false;

            inline int left_spike_reset_value = 0;
            inline int left_spike_counter = 0;
            inline bool left_spike = false;

            inline int left_counter = 0;
            inline int left_counter_reset_value = 0;
        }

        inline bool enabled = false;
        inline float cps = 12.f;
        inline bool bind_pressed = false;
        inline std::string bind = "[null]";
        inline size_t sel_bind = 0;


        inline bool blatant = false;
        inline bool mconly = true;


        extern void thread();
    }
    namespace rclicker{

        namespace random{
            inline int right_edited_cps = 0;
            inline int right_reset_value = 0;
            inline int right_clicks = 0;

            inline int right_drop_reset_value = 0;
            inline int right_drop_counter = 0;
            inline bool right_drop = false;

            inline int right_spike_reset_value = 0;
            inline int right_spike_counter = 0;
            inline bool right_spike = false;

            inline int right_counter = 0;
            inline int right_counter_reset_value = 0;
        }
        inline bool renabled = false;
        inline float rcps = 12.f;
        inline bool rbind_pressed = false;
        inline std::string rbind = "[null]";
        inline size_t rsel_bind = 0;


        inline bool rblatant = false;
        inline bool rmconly = true;

        extern void rthread();
    }
    namespace destruct {
        //extern void go();
    }
    namespace bind {
        extern void thread();
    }
    namespace rbind {
        extern void rthread();
    }
    namespace rodbind {
        extern void rodthread();
    }

    namespace autorod{
        inline float delay = 120.f;
        inline bool enabled = false;
        inline bool bind_pressed = false;
        inline std::string bind = "[null]";
        inline size_t sel_bind = 0;
        inline int sword = 0;
        inline int rod = 2;

        inline int state = 0;
        extern void rodthread();

    }

    namespace utils {
        inline int random_int(int min, int max) {
            static auto device = std::random_device();
            static auto engine = std::mt19937(device());
            const auto gen = std::uniform_int_distribution<int>(min, max);
            return gen(engine);
        }

        inline float random_float(float min, float max) {
            static auto device = std::random_device();
            static auto engine = std::mt19937(device());
            const auto gen = std::uniform_real_distribution<float>(min, max);
            return gen(engine);
        }

        inline DWORD get_pid(const std::string &process_name) {
            PROCESSENTRY32 process_info;
            process_info.dwSize = sizeof(process_info);

            HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
            if (snapshot == INVALID_HANDLE_VALUE)
                return 0;

            Process32First(snapshot, &process_info);
            if (!process_name.compare(process_info.szExeFile)) {
                CloseHandle(snapshot);
                return process_info.th32ProcessID;
            }

            while (Process32Next(snapshot, &process_info)) {
                if (!process_name.compare(process_info.szExeFile)) {
                    CloseHandle(snapshot);
                    return process_info.th32ProcessID;
                }
            }

            CloseHandle(snapshot);

            return 0;
        }

        inline DWORD get_service_pid(const std::string &service_name) {
            SC_HANDLE scm = OpenSCManager(nullptr, nullptr, NULL);
            SC_HANDLE sc = OpenService(scm, service_name.c_str(), SERVICE_QUERY_STATUS);

            SERVICE_STATUS_PROCESS ssp = {0};
            DWORD bytes_needed = 0;
            QueryServiceStatusEx(sc, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&ssp), sizeof(ssp),
                                 &bytes_needed);

            CloseServiceHandle(sc);
            CloseServiceHandle(scm);

            return ssp.dwProcessId;
        }
        inline void suspend_process(DWORD pid) {
            if (HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pid)) {
                BOOL result = SuspendThread(hProcess);
                CloseHandle(hProcess);
            }
        }

        inline void resume_process(DWORD pid) {
            if (HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pid)) {
                BOOL result = ResumeThread(hProcess);
                CloseHandle(hProcess);
            }
        }

        inline void terminate_process(DWORD pid) {
            if (HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pid)) {
                BOOL result = TerminateProcess(hProcess, 1);
                CloseHandle(hProcess);
            }
        }

        inline std::string get_hwid() {
            std::string drive_name = (std::string)getenv(xorstr("SystemDrive"));
            drive_name.append(xorstr("\\"));

            DWORD drive_serial = 0;
            GetVolumeInformationA(drive_name.c_str(), nullptr, NULL, &drive_serial,
                                  nullptr, nullptr, nullptr, NULL);

            std::ostringstream o;
            o << std::hex << HIWORD(drive_serial) << LOWORD(drive_serial);
            return o.str();
        }

        inline std::string random_string(std::size_t size) {

            const std::string chars = xorstr("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

            std::random_device random_device;
            std::mt19937 generator(random_device());
            std::uniform_int_distribution<> distribution(0, chars.size() - 1);

            std::string random_string;

            for (std::size_t i = 0; i < size; ++i)
                random_string += chars[distribution(generator)];

            return random_string;
        }

        inline void copy_to_clipboard(HWND hwnd, const std::string& s) {

            OpenClipboard(hwnd);
            EmptyClipboard();
            HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
            if (!hg) {

                CloseClipboard();
                return;
            }
            memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
            GlobalUnlock(hg);
            SetClipboardData(CF_TEXT, hg);
            CloseClipboard();
            GlobalFree(hg);
        }
    }
}