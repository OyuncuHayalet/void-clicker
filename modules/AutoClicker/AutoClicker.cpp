#include "../modules.h"

void modules::clicker::thread() {
    bool first_click = true;
            while (!iso::auth::auth) {
                Sleep(1);
                    while (modules::clicker::enabled && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                        int ldelay = 500 / modules::clicker::cps;
                        POINT clickerpos;
                        GetCursorPos(&clickerpos);
                        HWND window = WindowFromPoint(clickerpos);
                        if (modules::clicker::mconly) {
                            if (FindWindow(("LWJGL"), nullptr) == GetForegroundWindow()) {
                                if (ScreenToClient(window, &clickerpos)) {
                                    if (clickerpos.y > 20) {

                                        SendMessage(window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(clickerpos.x, clickerpos.y));
                                        Sleep(ldelay);
                                        SendMessage(window, WM_LBUTTONUP, 0, MAKELPARAM(clickerpos.x, clickerpos.y));
                                        Sleep(ldelay);
                                    }
                                }
                            }

                        } else {
                            if (ScreenToClient(window, &clickerpos)) {
                                if (clickerpos.y > 20) {
                                    SendMessage(window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(clickerpos.x, clickerpos.y));
                                    Sleep(ldelay);
                                    SendMessage(window, WM_LBUTTONUP, 0, MAKELPARAM(clickerpos.x, clickerpos.y));
                                    Sleep(ldelay);
                                }
                            }
                        }


                        if (first_click) {
                            first_click = false;
                        }

                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    }
            }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

//

void modules::rclicker::rthread() {
    bool rfirst_click = true;
    while (!iso::auth::auth) {
        Sleep(1);
        while (modules::rclicker::renabled && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
                POINT rclickerpos;
                GetCursorPos(&rclickerpos);
                HWND window = WindowFromPoint(rclickerpos);
                int delay = 500 / modules::rclicker::rcps;
                if (modules::rclicker::rmconly) {
                        if (FindWindow(("LWJGL"), nullptr) == GetForegroundWindow()) {
                            if (ScreenToClient(window, &rclickerpos)) {
                                if (rclickerpos.y > 20) {
                                    SendMessage(window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(rclickerpos.x, rclickerpos.y));
                                    Sleep(delay);
                                    SendMessage(window, WM_RBUTTONUP, 0, MAKELPARAM(rclickerpos.x, rclickerpos.y));
                                    Sleep(delay);
                                }
                            }
                        }
                }
                else {
                    if (ScreenToClient(window, &rclickerpos)) {
                        if (rclickerpos.y > 20) {
                            SendMessage(window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(rclickerpos.x, rclickerpos.y));
                            Sleep(delay);
                            SendMessage(window, WM_RBUTTONUP, 0, MAKELPARAM(rclickerpos.x, rclickerpos.y));
                            Sleep(delay);
                        }
                    }
                }
            if (rfirst_click) {
                rfirst_click = false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}