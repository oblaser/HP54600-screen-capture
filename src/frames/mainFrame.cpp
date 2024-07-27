/*
author          Oliver Blaser
date            27.07.2024
copyright       GPL-3.0 - Copyright (c) 2024 Oliver Blaser
*/

#include <array>
#include <cstddef>
#include <cstdint>

#include "mainFrame.h"
#include "project.h"

#include <olcPixelGameEngine.h>
#include <omw/defs.h>

#ifdef OMW_PLAT_WIN
#include <Windows.h>
#endif


using olc::vi2d;

namespace {

class Colour
{
public:
    Colour()
        : r(0), g(0), b(0)
    {}

    constexpr Colour(uint8_t _r, uint8_t _g, uint8_t _b)
        : r(_r), g(_g), b(_b)
    {}

    constexpr Colour(uint32_t c)
        : r((c >> 16) & 0xFF), g((c >> 8) & 0xFF), b(c & 0xFF)
    {}

    virtual ~Colour() {}

    operator olc::Pixel() const { return olc::Pixel(r, g, b); }

    uint8_t r, g, b;
};

class ColourProfile
{
public:
    ColourProfile() = delete;

    constexpr ColourProfile(const Colour& bg, const Colour& h, const Colour& f)
        : background(bg), half(h), full(f)
    {}

    virtual ~ColourProfile() {}

    olc::Pixel get(size_t idx) const
    {
        if (idx == 1) { return half; }
        else if (idx == 2) { return full; }
        return background;
    }

    olc::Pixel operator[](size_t idx) const { return this->get(idx); }

    Colour background, half, full;
};

const auto colourProfile_crt = ColourProfile(Colour(0), Colour(/*0x3d993d*/ 0x4d994d), Colour(0x009900));
const auto colourProfile_bw = ColourProfile(Colour(0xFFFFFF), Colour(0x7F7F7F), Colour(0));

const ColourProfile* colProf = &colourProfile_crt;

} // namespace



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

    // clear screen data
    for (size_t x = 0; x < scopeScreenWidth; ++x)
    {
        for (size_t y = 0; y < scopeScreenHeight; ++y)
        {
#if defined(PRJ_DEBUG) && 1
            m_screenData[x][y] = (x * 3 / 500);
#else
            m_screenData[x][y] = 0;
#endif
        }
    }

    return true;
}

bool MainFrame::OnUserUpdate(float tElapsed)
{
    Clear(olc::GREY);

    const vi2d scopeScreenPos(10, 10);

    for (size_t x = 0; x < scopeScreenWidth; ++x)
    {
        for (size_t y = 0; y < scopeScreenHeight; ++y) { FillRect(scopeScreenPos + (vi2d(x, y) * 2), vi2d(2, 2), colProf->get(m_screenData[x][y])); }
    }

    return true;
}

bool MainFrame::OnUserDestroy() { return true; }

} // namespace frames
