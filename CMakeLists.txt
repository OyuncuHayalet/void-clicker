cmake_minimum_required(VERSION 3.19)
project(isolation)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(auth)
include_directories(imgui)
include_directories(modules)

add_executable(isolation
        auth/auth.cpp
        auth/auth.h
        imgui/font.h
        imgui/iconhandler.h
        imgui/imconfig.h
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_draw.cpp
        imgui/imgui_impl_dx9.cpp
        imgui/imgui_impl_dx9.h
        imgui/imgui_impl_win32.cpp
        imgui/imgui_impl_win32.h
        imgui/imgui_internal.h
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        modules/AutoClicker/AutoClicker.cpp
        modules/Destruct/Destruct.cpp
        modules/bindsys.cpp
        modules/modules.h
        main.cpp
        main.h modules/rbindsys.cpp modules/AutoRod/AutoRod.cpp modules/rodbind.cpp xorstr.h)
