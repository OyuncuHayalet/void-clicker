#include "../modules.h"

void modules::autorod::rodthread() {

    while (!iso::auth::auth) {
        Sleep(1);
        while(modules::autorod::enabled){
            POINT clickerpos;
            GetCursorPos(&clickerpos);
            HWND window = WindowFromPoint(clickerpos);

                if (ScreenToClient(window, &clickerpos)) {
                    if (clickerpos.y > 20) {
                        if(modules::autorod::state >= 1){
                            int rod = 0x33;
                            int sword = 0x31;
                            switch (modules::autorod::rod)  {
                                case 0:
                                    rod = 0x31;
                                    break;

                                case 1:
                                    rod = 0x32;
                                    break;

                                case 2:
                                    rod = 0x33;
                                    break;

                                case 3:
                                    rod = 0x34;
                                    break;

                                case 4:
                                    rod = 0x35;
                                    break;

                                case 5:
                                    rod = 0x36;
                                    break;

                                case 6:
                                    rod = 0x37;
                                    break;

                                case 7:
                                    rod = 0x38;
                                    break;

                                case 8:
                                    rod = 0x39;
                                    break;
                                default:
                                    rod = 0x31;
                                    break;
                            }
//
                            switch (modules::autorod::sword)  {
                                case 0:
                                    sword = 0x31;
                                    break;

                                case 1:
                                    sword = 0x32;
                                    break;

                                case 2:
                                    sword = 0x33;
                                    break;

                                case 3:
                                    sword = 0x34;
                                    break;

                                case 4:
                                    sword = 0x35;
                                    break;

                                case 5:
                                    sword = 0x36;
                                    break;

                                case 6:
                                    sword = 0x37;
                                    break;

                                case 7:
                                    sword = 0x38;
                                    break;

                                case 8:
                                    sword = 0x39;
                                    break;
                                default:
                                    sword = 0x31;
                                    break;
                            }


                            POINT pos1;
                            GetCursorPos(&pos1);
                            HWND window = WindowFromPoint(pos1);

                            if (ScreenToClient(window, &pos1)) {

                                keybd_event(rod, 0, 0, 0);
                                Sleep(5);
                                keybd_event(rod, 0, KEYEVENTF_KEYUP, 0);
                                //InputSimulator.SimulateKeyPress(VirtualKeyCode.VK_1);


                                SendMessage(window, WM_RBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos1.x, pos1.y));
                                Sleep(5);
                                SendMessage(window, WM_RBUTTONUP, MK_LBUTTON, MAKELPARAM(pos1.x, pos1.y));

                                Sleep(modules::autorod::delay);

                                keybd_event(sword, 0, 0, 0);
                                Sleep(5);
                                keybd_event(sword, 0, KEYEVENTF_KEYUP, 0);

                            }


                            modules::autorod::state -= 1;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    }
                }


        }

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}




