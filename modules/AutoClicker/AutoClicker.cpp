#include "../modules.h"

int random_int(int min, int max) {
    static auto device = std::random_device();
    static auto engine = std::mt19937(device());
    const auto gen = std::uniform_int_distribution<int>(min, max);
    return gen(engine);
}

int randomization(int cps, int& edited_cps, int& reset_value, int& clicks, int& counter,
    int& counter_reset_value, bool& drop, bool& spike, int& drop_reset_value, int& drop_counter,
    int& spike_reset_value, int& spike_counter) {
    if (clicks >= reset_value || clicks == 0) {
        reset_value = random_int(5, 15);
        edited_cps = cps + random_int(-3, 3);

        clicks = 0;
    }

    clicks++;
    counter++;

    if (counter >= counter_reset_value || counter == 0) {
        counter_reset_value = random_int(15, 25);

        counter = 0;

        // DROPS

        if (!drop && !spike && random_int(0, 100) <= 30) {
            drop = true;
            drop_reset_value = random_int(10, 25);
            drop_counter = 0;
        }

        // SPIKES

        if (!spike && !drop && random_int(0, 100) <= 20) {
            if (!modules::clicker::cps > 14) {
                spike = true;
                spike_reset_value = random_int(10, 25);
                spike_counter = 0;
            }
        }
    }

    if (drop && drop_counter <= drop_reset_value) {
        drop_counter++;
        if (modules::clicker::cps > 14) {
            return random_int(300, 600) / edited_cps;
        } else {
            return random_int(350, 500) / edited_cps;
        }
    }
    else if (drop && drop_counter >= drop_reset_value) {
        drop_counter = 0;
        drop = false;
    }

    if (spike && spike_counter <= spike_reset_value) {
        spike_counter++;
        if (modules::clicker::cps > 14) {
            return random_int(300, 600) / edited_cps;
        } else {
            return random_int(250, 450) / edited_cps;
        }
    }
    else if (spike && spike_counter >= spike_reset_value) {
        spike_counter = 0;
        spike = false;
    }

    return random_int(450, 550) / edited_cps;
}

//sa

int rrandomization(int ycps, int& edited_ycps, int& resett_value, int& rclicks, int& counterr,
                   int& counterr_resett_value, bool& drop, bool& spike, int& drop_resett_value, int& drop_counterr,
                   int& spike_resett_value, int& spike_counterr) {

    if (rclicks >= resett_value || rclicks == 0) {
        resett_value = random_int(5, 15);
        edited_ycps = ycps + random_int(-3, 3);

        rclicks = 0;
    }

    rclicks++;
    counterr++;

    if (counterr >= counterr_resett_value || counterr == 0) {
        counterr_resett_value = random_int(15, 25);

        counterr = 0;

        // DROPS

        if (!drop && !spike && random_int(0, 100) <= 30) {
            drop = true;
            drop_resett_value = random_int(10, 25);
            drop_counterr = 0;
        }

        // SPIKES

        if (!spike && !drop && random_int(0, 100) <= 20) {
            if (!modules::rclicker::rcps > 14) {
                spike = true;
                spike_resett_value = random_int(10, 25);
                spike_counterr = 0;
            }
        }
    }

    if (drop && drop_counterr <= drop_resett_value) {
        drop_counterr++;
        if (modules::rclicker::rcps > 14) {
            return random_int(300, 600) / edited_ycps;
        } else {
            return random_int(350, 500) / edited_ycps;
        }
    }
    else if (drop && drop_counterr >= drop_resett_value) {
        drop_counterr = 0;
        drop = false;
    }

    if (spike && spike_counterr <= spike_resett_value) {
        spike_counterr++;
        if (modules::rclicker::rcps > 14) {
            return random_int(300, 600) / edited_ycps;
        } else {
            return random_int(250, 450) / edited_ycps;
        }
    }
    else if (spike && spike_counterr >= spike_resett_value) {
        spike_counterr = 0;
        spike = false;
    }

    return random_int(450, 550) / edited_ycps;
}

float random_float(float min_value, float max_value) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(min_value, max_value);
    return dist(rng);
}

size_t random_delay(float current_cps) {
    static size_t last_delay = 0;

    float min_cps = current_cps - random_float(1, 4);
    size_t min_delay = (random_float(950, 1050) / min_cps);

    float max_cps = current_cps + random_float(1, 4);
    size_t max_delay = (random_float(950, 1050) / max_cps);

    size_t average_delay = (size_t)random_float(max_delay, min_delay);
    if (average_delay == last_delay) { average_delay++; }
    last_delay = average_delay;

    return average_delay;
}

float random_cps(float current_cps) {
    if ((size_t)random_float(1, 4) ==
        (size_t)random_float(1, 4))
        current_cps -= random_float(0.4, 1.00);

    else if ((size_t)random_float(1, 6) ==
        (size_t)random_float(1, 4))
        current_cps += random_float(0.4, 1.00);

    return current_cps;
}

void modules::clicker::thread() {
    bool first_click = true;
    while (!iso::auth::auth) {
        Sleep(1);

        while (modules::clicker::enabled && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            if (modules::clicker::rmblock && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
                // Ignore
            }
            else {
                POINT clickerpos;
                GetCursorPos(&clickerpos);
                HWND window = WindowFromPoint(clickerpos);
                if (modules::clicker::mconly) {
                    if (modules::clicker::fcprot) {
                        if (!first_click) {
                            if (FindWindow(("LWJGL"), nullptr) == GetForegroundWindow()) {
                                if (ScreenToClient(window, &clickerpos)) {
                                    if (clickerpos.y > 20) {
                                        if (random_int(0, 100) <= 2)
                                            std::this_thread::sleep_for(std::chrono::milliseconds(
                                                randomization(modules::clicker::cps,
                                                    clicker::random::left_edited_cps,
                                                    clicker::random::left_reset_value,
                                                    clicker::random::left_clicks,
                                                    clicker::random::left_counter,
                                                    clicker::random::left_counter_reset_value,
                                                    clicker::random::left_drop, clicker::random::left_spike,
                                                    clicker::random::left_drop_reset_value,
                                                    clicker::random::left_drop_counter,
                                                    clicker::random::left_spike_reset_value,
                                                    clicker::random::left_spike_counter) * 3));

                                        if (!first_click) {
                                            PostMessageW(window, WM_LBUTTONDOWN, MK_LBUTTON,
                                                MAKELPARAM(clickerpos.x, clickerpos.y));
                                        }

                                        std::this_thread::sleep_for(std::chrono::milliseconds(
                                            randomization(modules::clicker::cps,
                                                clicker::random::left_edited_cps,
                                                clicker::random::left_reset_value,
                                                clicker::random::left_clicks,
                                                clicker::random::left_counter,
                                                clicker::random::left_counter_reset_value,
                                                clicker::random::left_drop, clicker::random::left_spike,
                                                clicker::random::left_drop_reset_value,
                                                clicker::random::left_drop_counter,
                                                clicker::random::left_spike_reset_value,
                                                clicker::random::left_spike_counter)));

                                        PostMessageW(window, WM_LBUTTONUP, MK_LBUTTON,
                                            MAKELPARAM(clickerpos.x, clickerpos.y));

                                        std::this_thread::sleep_for(std::chrono::milliseconds(
                                            randomization(modules::clicker::cps,
                                                clicker::random::left_edited_cps,
                                                clicker::random::left_reset_value,
                                                clicker::random::left_clicks,
                                                clicker::random::left_counter,
                                                clicker::random::left_counter_reset_value,
                                                clicker::random::left_drop, clicker::random::left_spike,
                                                clicker::random::left_drop_reset_value,
                                                clicker::random::left_drop_counter,
                                                clicker::random::left_spike_reset_value,
                                                clicker::random::left_spike_counter)));
                                    }
                                }
                            }
                        }
                    }
                    else {
                        if (FindWindow(("LWJGL"), nullptr) == GetForegroundWindow()) {
                            if (ScreenToClient(window, &clickerpos)) {
                                if (clickerpos.y > 20) {
                                    if (random_int(0, 100) <= 2)
                                        std::this_thread::sleep_for(std::chrono::milliseconds(
                                            randomization(modules::clicker::cps,
                                                clicker::random::left_edited_cps,
                                                clicker::random::left_reset_value,
                                                clicker::random::left_clicks,
                                                clicker::random::left_counter,
                                                clicker::random::left_counter_reset_value,
                                                clicker::random::left_drop, clicker::random::left_spike,
                                                clicker::random::left_drop_reset_value,
                                                clicker::random::left_drop_counter,
                                                clicker::random::left_spike_reset_value,
                                                clicker::random::left_spike_counter) * 3));

                                    if (!first_click) {
                                        PostMessageW(window, WM_LBUTTONDOWN, MK_LBUTTON,
                                            MAKELPARAM(clickerpos.x, clickerpos.y));
                                    }

                                    std::this_thread::sleep_for(std::chrono::milliseconds(
                                        randomization(modules::clicker::cps,
                                            clicker::random::left_edited_cps,
                                            clicker::random::left_reset_value,
                                            clicker::random::left_clicks,
                                            clicker::random::left_counter,
                                            clicker::random::left_counter_reset_value,
                                            clicker::random::left_drop, clicker::random::left_spike,
                                            clicker::random::left_drop_reset_value,
                                            clicker::random::left_drop_counter,
                                            clicker::random::left_spike_reset_value,
                                            clicker::random::left_spike_counter)));

                                    PostMessageW(window, WM_LBUTTONUP, MK_LBUTTON,
                                        MAKELPARAM(clickerpos.x, clickerpos.y));

                                    std::this_thread::sleep_for(std::chrono::milliseconds(
                                        randomization(modules::clicker::cps,
                                            clicker::random::left_edited_cps,
                                            clicker::random::left_reset_value,
                                            clicker::random::left_clicks,
                                            clicker::random::left_counter,
                                            clicker::random::left_counter_reset_value,
                                            clicker::random::left_drop, clicker::random::left_spike,
                                            clicker::random::left_drop_reset_value,
                                            clicker::random::left_drop_counter,
                                            clicker::random::left_spike_reset_value,
                                            clicker::random::left_spike_counter)));
                                }
                            }
                        }
                    }
                }
                else {
                    if (ScreenToClient(window, &clickerpos)) {
                        if (clickerpos.y > 20) {
                            if (random_int(0, 100) <= 2)
                                std::this_thread::sleep_for(std::chrono::milliseconds(
                                    randomization(modules::clicker::cps,
                                        clicker::random::left_edited_cps,
                                        clicker::random::left_reset_value,
                                        clicker::random::left_clicks,
                                        clicker::random::left_counter,
                                        clicker::random::left_counter_reset_value,
                                        clicker::random::left_drop, clicker::random::left_spike,
                                        clicker::random::left_drop_reset_value,
                                        clicker::random::left_drop_counter,
                                        clicker::random::left_spike_reset_value,
                                        clicker::random::left_spike_counter) * 3));

                            if (!first_click) {
                                PostMessageW(window, WM_LBUTTONDOWN, MK_LBUTTON,
                                    MAKELPARAM(clickerpos.x, clickerpos.y));
                            }

                            std::this_thread::sleep_for(std::chrono::milliseconds(
                                randomization(modules::clicker::cps,
                                    clicker::random::left_edited_cps,
                                    clicker::random::left_reset_value,
                                    clicker::random::left_clicks,
                                    clicker::random::left_counter,
                                    clicker::random::left_counter_reset_value,
                                    clicker::random::left_drop, clicker::random::left_spike,
                                    clicker::random::left_drop_reset_value,
                                    clicker::random::left_drop_counter,
                                    clicker::random::left_spike_reset_value,
                                    clicker::random::left_spike_counter)));

                            PostMessageW(window, WM_LBUTTONUP, MK_LBUTTON,
                                MAKELPARAM(clickerpos.x, clickerpos.y));

                            std::this_thread::sleep_for(std::chrono::milliseconds(
                                randomization(modules::clicker::cps,
                                    clicker::random::left_edited_cps,
                                    clicker::random::left_reset_value,
                                    clicker::random::left_clicks,
                                    clicker::random::left_counter,
                                    clicker::random::left_counter_reset_value,
                                    clicker::random::left_drop, clicker::random::left_spike,
                                    clicker::random::left_drop_reset_value,
                                    clicker::random::left_drop_counter,
                                    clicker::random::left_spike_reset_value,
                                    clicker::random::left_spike_counter)));
                        }
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

void modules::rclicker::rthread() {
    bool rfirst_click = true;
    while (!iso::auth::auth) {
        Sleep(1);

        while (modules::rclicker::renabled && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
            if (modules::rclicker::rrmblock && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
                // Ignore
            }
            else {
                POINT rclickerpos;
                GetCursorPos(&rclickerpos);
                HWND window = WindowFromPoint(rclickerpos);
                int delay = 500 / modules::rclicker::rcps;
                if (modules::rclicker::rmconly) {
                    if (modules::rclicker::rfcprot) {
                        if (!rfirst_click) {
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
                    }
                    else {
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
            }

            if (rfirst_click) {
                rfirst_click = false;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}