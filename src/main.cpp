/*
author          Oliver Blaser
date            27.07.2024
copyright       GPL-3.0 - Copyright (c) 2024 Oliver Blaser
*/

#include <cstddef>
#include <cstdint>

#include "project.h"


namespace {}



#include <olcPixelGameEngine.h>
namespace frames {

class MainFrame final : public olc::PixelGameEngine
{
public:
    static const olc::vi2d pgeWindowSize;
    static constexpr int32_t pgePixelSize = 1;

public:
    MainFrame();
    virtual ~MainFrame() {}

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float tElapsed) override;
    bool OnUserDestroy() override;

private:
    MainFrame(const MainFrame& other) = delete;
    MainFrame(const MainFrame&& other) = delete;
    const MainFrame& operator=(const MainFrame& b) { return b; }
};

} // namespace frames

#include <omw/defs.h>

#ifdef OMW_PLAT_WIN
#include <Windows.h>
#endif

using olc::vi2d;

namespace frames {

const vi2d MainFrame::pgeWindowSize = vi2d(1120, 700);

MainFrame::MainFrame() { sAppName = prj::appName; }

bool MainFrame::OnUserCreate()
{
#ifdef OMW_PLAT_WIN
    {
        RECT desktop, pge;
        HWND hwnd_pge = FindWindowExW(nullptr, nullptr, L"OLC_PIXEL_GAME_ENGINE", nullptr);

        GetClientRect(GetDesktopWindow(), &desktop);
        GetClientRect(hwnd_pge, &pge);

        int x = ((desktop.right - desktop.left) / 2) - ((pge.right - pge.left) / 2);
        int y = ((desktop.bottom - desktop.top) * 1 / 3) - ((pge.bottom - pge.top) / 2);
        // const int y = 10;

        if (x < 1) x = 1;
        if (y < 1) y = 1;

        SetWindowPos(hwnd_pge, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }
#endif

    return true;
}

bool MainFrame::OnUserUpdate(float tElapsed)
{
    Clear(olc::VERY_DARK_BLUE);

    FillRect(vi2d(50, 50), vi2d(500, 255), olc::BLACK);

    return true;
}

bool MainFrame::OnUserDestroy() { return true; }

} // namespace frames



int main(int argc, char** argv)
{
    int r = 0;

#ifdef OMW_PLAT_WIN
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

    frames::MainFrame mainFrame;

#ifdef PRJ_DEBUG
    constexpr bool vSync = false;
#else
    constexpr bool vSync = true;
#endif

    if (mainFrame.Construct(frames::MainFrame::pgeWindowSize.x, frames::MainFrame::pgeWindowSize.y, frames::MainFrame::pgePixelSize,
                            frames::MainFrame::pgePixelSize, false, vSync))
    {
        mainFrame.Start();
    }

    return r;
}
