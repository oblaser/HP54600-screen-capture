/*
author          Oliver Blaser
date            27.07.2024
copyright       GPL-3.0 - Copyright (c) 2024 Oliver Blaser
*/

#include <cstddef>
#include <cstdint>

#include "frames/mainFrame.h"
#include "project.h"



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
