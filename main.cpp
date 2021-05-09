#include "main.h"

#include "modules/modules.h"
#include "auth/auth.h"

static LPDIRECT3D9 g_pD3D = nullptr;
static LPDIRECT3DDEVICE9 g_pd3dDevice = nullptr;
static D3DPRESENT_PARAMETERS g_d3dpp = {};
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void currentcol(float col[4]) {
    if (iso::gui::rainmode) {
        float add = 0.04f;
        static size_t turn = 0;

        if (turn == 0) {
            col[0] += add;

            if (col[0] >= 1.00f) {
                col[0] = 1.00f;
                turn++;
            }
        }
        if (turn == 1) {
            col[1] += add;

            if (col[1] >= 1.00f) {
                col[1] = 1.00f;
                turn++;
            }
        }
        if (turn == 2) {
            col[0] -= add;

            if (col[0] <= 0.00f) {
                col[0] = 0.00f;
                turn++;
            }
        }
        if (turn == 3) {
            col[2] += add;

            if (col[2] >= 1.00f) {
                col[2] = 1.00f;
                turn++;
            }
        }
        if (turn == 4) {
            col[1] -= add;

            if (col[1] <= 0.00f) {
                col[1] = 0.00f;
                turn++;
            }
        }
        if (turn == 5) {
            col[0] += add;

            if (col[0] >= 1.00f) {
                col[0] = 1.00f;
                turn++;
            }
        }
        if (turn == 6) {
            col[2] -= add;

            if (col[2] <= 0.00f) {
                col[2] = 0.00f;
                turn = 0;
            }
        }
        iso::gui::currentcol = ImVec4(col[0], col[1], col[2], 1);
    }
}
void slowtfdown() {
    while (true) {
        Sleep(42);
        currentcol((float*)&iso::gui::currentcol);
    }
}

int gui() {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr,
                     nullptr, nullptr, _T(" "), nullptr };
    ::RegisterClassEx(&wc);
    iso::gui::hwnd = ::CreateWindow(wc.lpszClassName, _T(" "), (WS_POPUP | WS_EX_TOPMOST), 100, 100, 650, 350, nullptr, nullptr, wc.hInstance, nullptr);

    if (!CreateDeviceD3D(iso::gui::hwnd)) {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        MessageBox(0, "error when creating d3d device (report to staff)", " ", MB_OK | MB_ICONINFORMATION);
        exit(1);
    }

    ::ShowWindow(iso::gui::hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(iso::gui::hwnd);

    iso::handles::one = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&modules::clicker::thread, nullptr, 0, nullptr);
    iso::handles::four = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&modules::rclicker::rthread, nullptr, 0, nullptr);
    iso::handles::two = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&modules::bind::thread, nullptr, 0, nullptr);
    iso::handles::five = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&modules::rbind::rthread, nullptr, 0, nullptr);
    iso::handles::six = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&modules::autorod::rodthread, nullptr, 0, nullptr);
    iso::handles::six = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&modules::rodbind::rodthread, nullptr, 0, nullptr);
    iso::handles::three = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&slowtfdown, nullptr, 0, nullptr);



    system("cls");
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(iso::gui::hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    /*Starting icons*/
    const auto icons = io.Fonts->AddFontFromMemoryCompressedBase85TTF(icons_compressed_data_base85, 35);
    const auto logo = io.Fonts->AddFontFromMemoryCompressedBase85TTF(logo_compressed_data_base85, 80);

    /*Starting fonts*/
    const auto default_font = io.Fonts->AddFontDefault();
    const auto semibold_font = io.Fonts->AddFontFromMemoryCompressedTTF(semibold_compressed_data, semibold_compressed_size, 15);
    const auto big_semibold_font = io.Fonts->AddFontFromMemoryCompressedTTF(semibold_compressed_data, semibold_compressed_size, 20);

    io.IniFilename = nullptr;
    ImFontConfig config;
    config.MergeMode = true;
    config.PixelSnapH = true;
    static const ImWchar ranges[] =
    {
            0xf000,
            0xf976,
            NULL
    };
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    static int menu_movement_x = 0;
    static int menu_movement_y = 0;
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE) != 0) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ImGuiStyle* style = &ImGui::GetStyle();
        style->WindowBorderSize = 0.0f;
        style->Alpha = 1.0f;
        style->ChildBorderSize = 1.0f;
        style->FrameBorderSize = 1.0f;
        style->WindowPadding = ImVec2(0, 0);
        style->WindowRounding = 0.0f;
        style->FramePadding = ImVec2(5, 5);
        style->FrameRounding = 3.0f;
        style->ItemSpacing = ImVec2(5, 5);
        style->ItemInnerSpacing = ImVec2(5, 5);
        style->IndentSpacing = 6.0f;
        style->TouchExtraPadding = ImVec2(5, 5);
        style->ScrollbarSize = 6.0f;
        style->ScrollbarRounding = 15.0f;
        style->GrabMinSize = 10.0f;
        style->GrabRounding = 2.0f;
        style->ColumnsMinSpacing = 10.0f;
        style->ButtonTextAlign = ImVec2(0.5, 0.5);
        style->WindowTitleAlign = ImVec2(0.5, 0.5);
        style->AntiAliasedLines = true;
        style->AntiAliasedFill = true;

        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = ImColor(240, 240, 240);
        colors[ImGuiCol_WindowBg] = ImColor(20, 20, 20);
        colors[ImGuiCol_Border] = ImColor(45, 45, 45);
        colors[ImGuiCol_Separator] = ImColor(45, 45, 45);
        colors[ImGuiCol_FrameBg] = ImColor(35, 35, 35);
        colors[ImGuiCol_FrameBgHovered] = ImColor(28, 28, 28);
        colors[ImGuiCol_FrameBgActive] = ImColor(28, 28, 28);
        colors[ImGuiCol_CheckMark] = ImVec4(iso::gui::currentcol);
        colors[ImGuiCol_SliderGrab] = ImVec4(iso::gui::currentcol);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(iso::gui::currentcol);
        colors[ImGuiCol_Button] = ImColor(35, 35, 35);
        colors[ImGuiCol_ButtonHovered] = ImColor(28, 28, 28);
        colors[ImGuiCol_ButtonActive] = ImColor(28, 28, 28);

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::PushFont(semibold_font);
            ImGui::Begin(("##ImGui"), nullptr,
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollWithMouse |
                ImGuiWindowFlags_NoScrollbar);
            ImGui::SetWindowPos(ImVec2(0, 0));
            ImGui::SetWindowSize(ImVec2(650, 350));
            ImGui::SetCursorPos(ImVec2(0, 0));
            if (!iso::auth::auth) {
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 p = ImGui::GetCursorScreenPos();
                draw_list->AddRectFilled(p, ImVec2(p.x + 75, p.y + 350), IM_COL32(30, 30, 30, 255)); //26, 29, 35
                if (!iso::gui::colorlogo) {
                    ImGui::SetCursorPos(ImVec2(-10, 0));
                    ImGui::PushFont(logo);
                    ImGui::Text("A");
                    ImGui::PopFont();
                } else {
                    ImVec4 logocol = ImVec4(iso::gui::currentcol);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(logocol));
                    //ImGui::SetCursorPos(ImVec2(-10, 0));
                    ImGui::SetCursorPos(ImVec2(22, 30));
                    ImGui::PushFont(semibold_font);
                    //ImGui::PushFont(logo);
                    //ImGui::Text("A");

                    ImGui::Text("VOID");
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                }
                ImGui::SetCursorPos(ImVec2(622, 4));
                if (ImGui::Button((" "), ImVec2(24, 24))) {
                    CloseHandle(iso::handles::one);
                    CloseHandle(iso::handles::two);
                    CloseHandle(iso::handles::three);
                    CloseHandle(iso::handles::four);
                    CloseHandle(iso::handles::five);
                    CloseHandle(iso::handles::six);
                    CloseHandle(iso::handles::seven);
                    ImGui_ImplDX9_Shutdown();
                    ImGui_ImplWin32_Shutdown();
                    ImGui::DestroyContext();
                    CleanupDeviceD3D();
                    ::DestroyWindow(iso::gui::hwnd);
                    ::UnregisterClass(wc.lpszClassName, wc.hInstance);
                    exit(0);
                }
                ImGui::SetCursorPos(ImVec2(630, 7));
                ImGui::Text(("X"));
                if (ImGui::IsMouseClicked(0)) {
                    POINT CursorPosition;
                    RECT MenuPosition;
                    GetCursorPos(&CursorPosition);
                    GetWindowRect(iso::gui::hwnd, &MenuPosition);
                    menu_movement_x = CursorPosition.x - MenuPosition.left;
                    menu_movement_y = CursorPosition.y - MenuPosition.top;
                }
                if ((menu_movement_y >= 0 && menu_movement_y <= 65 && menu_movement_x <= 150) && ImGui::IsMouseDragging(0)) {
                    POINT cursor_position;
                    GetCursorPos(&cursor_position);
                    SetWindowPos(iso::gui::hwnd, nullptr, cursor_position.x - menu_movement_x,
                        cursor_position.y - menu_movement_y, 0,
                        0, SWP_NOSIZE);
                }
                /*-----------------------------------------------------*/
                ImGui::SetCursorPos(ImVec2(65, 138));
                ImGui::PushFont(semibold_font);
                ImGui::Text((""));
                if (ImGui::IsItemClicked()) {
                    iso::gui::sstate = 'A';
                }
                ImGui::PopFont();
                if (iso::gui::sstate != 'A') {
                    ImGui::SetCursorPos(ImVec2(20, 130));
                    ImGui::PushFont(icons);
                    ImGui::Text(("A"));
                    if (ImGui::IsItemClicked()) {
                        iso::gui::sstate = 'A';
                    }
                    ImGui::PopFont();
                }
                ImGui::SetCursorPos(ImVec2(65, 198));
                ImGui::PushFont(semibold_font);
                ImGui::Text((""));
                if (ImGui::IsItemClicked()) {
                    iso::gui::sstate = 'B';
                }
                ImGui::PopFont();
                if (iso::gui::sstate != 'B') {
                    ImGui::SetCursorPos(ImVec2(20, 190));
                    ImGui::PushFont(icons);
                    ImGui::Text(("B"));
                    if (ImGui::IsItemClicked()) {
                        iso::gui::sstate = 'B';
                    }
                    ImGui::PopFont();
                }
                /*-----------------------------------------------------*/
                ImGui::SetCursorPos(ImVec2(5, 316));
                if (ImGui::Button(("Destruct"), ImVec2(68, 26))) {
                    exit(0);
                    //modules::destruct::go();
                }
                switch (iso::gui::sstate) {
                case 'A': {
                    ImVec4 logocol = ImVec4(iso::gui::currentcol);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(logocol));
                    ImGui::SetCursorPos(ImVec2(20, 130));
                    ImGui::PushFont(icons);
                    ImGui::Text("A");
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                    /*------------------------*/

                    float maxcps = 20.f;
                    float rmaxcps = 22.f;
                    static const char* sword[]{"1","2","3","4","5","6","7","8","9"};
                    static const char* rod[]{"1","2","3","4","5","6","7","8","9"};

                    ImGui::SetCursorPos(ImVec2(90, 20));
                    ImGui::BeginChild(("Clicker"), ImVec2(250, 130), true);
                    {
                        ImGui::SetCursorPos(ImVec2(20, 20));
                        ImGui::Checkbox(("Toggle"), &modules::clicker::enabled);

                        ImGui::SameLine();
                        ImGui::TextDisabled(modules::clicker::bind.c_str());

                        if (ImGui::IsItemClicked()) {
                            modules::clicker::bind_pressed = true;
                            modules::clicker::bind = "[click a key]";
                        }


                        ImGui::SetCursorPos(ImVec2(20, 76));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(20, 88));
                        ImGui::Checkbox(("Blatant"), &modules::clicker::blatant);

                        if(modules::clicker::blatant){
                            maxcps = 100.f;
                            ImGui::SetCursorPos(ImVec2(20, 58));
                            ImGui::SliderFloat(("CPS"), &modules::clicker::cps, 20.f, maxcps, "%.1f");
                        }
                        else{
                            maxcps = 20.f;
                            ImGui::SetCursorPos(ImVec2(20, 58));
                            ImGui::SliderFloat(("CPS"), &modules::clicker::cps, 10.f, maxcps, "%.1f");
                        }

                        ImGui::SetCursorPos(ImVec2(120, 88));
                        ImGui::Checkbox(("MC Only"), &modules::clicker::mconly);

                    }
                    ImGui::EndChild();
                    ImGui::SetCursorPos(ImVec2(175, 12));
                    ImGui::Text(("left clicker"));

                    //
                    ImGui::SetCursorPos(ImVec2(90, 150));
                    ImGui::BeginChild(("RClicker"), ImVec2(250, 130), true);
                    {
                        ImGui::SetCursorPos(ImVec2(20, 20));
                        ImGui::Checkbox(("Toggle"), &modules::rclicker::renabled);

                        ImGui::SameLine();
                        ImGui::TextDisabled(modules::rclicker::rbind.c_str());

                        if (ImGui::IsItemClicked()) {
                            modules::rclicker::rbind_pressed = true;
                            modules::rclicker::rbind = "[click a key]";
                        }


                        ImGui::SetCursorPos(ImVec2(20, 76));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(20, 88));
                        ImGui::Checkbox(("Blatant"), &modules::rclicker::rblatant);

                        if(modules::rclicker::rblatant){
                            rmaxcps = 100.f;
                            ImGui::SetCursorPos(ImVec2(20, 58));
                            ImGui::SliderFloat(("CPS"), &modules::rclicker::rcps, 20.f, rmaxcps, "%.1f");
                        }
                        else{
                            rmaxcps = 20.f;
                            ImGui::SetCursorPos(ImVec2(20, 58));
                            ImGui::SliderFloat(("CPS"), &modules::rclicker::rcps, 10.f, rmaxcps, "%.1f");
                        }

                        ImGui::SetCursorPos(ImVec2(120, 88));
                        ImGui::Checkbox(("MC Only"), &modules::rclicker::rmconly);
                    }
                    ImGui::EndChild();
                    ImGui::SetCursorPos(ImVec2(175, 140));
                    ImGui::Text(("right clicker"));

                    // rod

                    ImGui::SetCursorPos(ImVec2(340, 20));
                    ImGui::BeginChild(("AutoRod"), ImVec2(250, 260), true);
                    {
                        ImGui::SetCursorPos(ImVec2(20, 20));
                        ImGui::Checkbox(("Toggle"), &modules::autorod::enabled);

                        ImGui::SameLine();
                        ImGui::TextDisabled(modules::autorod::bind.c_str());

                        if (ImGui::IsItemClicked()) {
                            modules::autorod::bind_pressed = true;
                            modules::autorod::bind = "[click a key]";
                        }

                        ImGui::SetCursorPos(ImVec2(20, 58));
                        ImGui::SliderFloat(("delay"), &modules::autorod::delay, 40.f, 200.f, "%.f");

                        ImGui::SetCursorPos(ImVec2(20, 76));
                        ImGui::Separator();

                        ImGui::SetCursorPos(ImVec2(20, 88));
                        //ImGui::Checkbox(("Blatant"), &modules::rclicker::rblatant);
                        ImGui::Combo("sword", &modules::autorod::sword, sword, 9);


                        ImGui::SetCursorPos(ImVec2(20, 120));
                        //ImGui::Checkbox(("MC Only"), &modules::rclicker::rmconly);
                        ImGui::Combo("rod", &modules::autorod::rod, rod, 9);

                        ImGui::SetCursorPos(ImVec2(20, 158));
                        ImGui::Separator();
                    }
                    ImGui::EndChild();
                    ImGui::SetCursorPos(ImVec2(425, 12));
                    ImGui::Text(("autorod"));

                }



                        break;
                case 'B': {
                    ImVec4 logocol = ImVec4(iso::gui::currentcol);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(logocol));
                    ImGui::SetCursorPos(ImVec2(20, 190));
                    ImGui::PushFont(icons);
                    ImGui::Text("B");
                    ImGui::PopFont();
                    ImGui::PopStyleColor();
                    /*------------------------*/

                    ImGui::SetCursorPos(ImVec2(90, 20));
                    ImGui::BeginChild(("GUI"), ImVec2(250, 120), true);
                    {
                        ImGui::SetCursorPos(ImVec2(10, 10));
                        ImGui::PushItemWidth(130);
                        ImGui::ColorPicker4(("##picker"), (float*)&iso::gui::currentcol,
                            ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview |
                            ImGuiColorEditFlags_NoInputs);

                        ImGui::SetCursorPos(ImVec2(155, 10));
                        ImGui::Checkbox(("Rainbow"), &iso::gui::rainmode);


                        //ImGui::Checkbox(("Logo"), &iso::gui::colorlogo);

                        ImGui::SetCursorPos(ImVec2(155, 45));
                        if (ImGui::Button(("Reset"), ImVec2(68, 26))) {
                            iso::gui::rainmode = false;
                            iso::gui::colorlogo = true;
                            iso::gui::currentcol = ImColor(143, 105, 255);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::SetCursorPos(ImVec2(200, 12));
                    ImGui::Text(("GUI"));
                }
                        break;
                }
            } else {
                exit(0);
            }
            ImGui::End();
            ImGui::PopFont();
        }
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f),
            (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0) {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();

        /*DO NOT REMOVE*/
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanupDeviceD3D();
    ::DestroyWindow(iso::gui::hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

int main() {
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tkp;
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
    LookupPrivilegeValue(nullptr, ("SeDebugPrivilege"), &luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = luid;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), nullptr, nullptr);
    CloseHandle(hToken);

    SetConsoleTitleA(" ");
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    std::cout << "[+] Authenticating your license" << std::endl;

    //Run authentication

    //If authed
    iso::auth::auth = false;

    //else if not
    //iso::auth::auth = true;

    if (!iso::auth::auth) {
        gui();
    } else {
        exit(1);
    }

    return 0;
}

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}