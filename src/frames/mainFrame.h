/*
author          Oliver Blaser
date            27.07.2024
copyright       GPL-3.0 - Copyright (c) 2024 Oliver Blaser
*/

#ifndef IG_FRAMES_MAINFRAME_H
#define IG_FRAMES_MAINFRAME_H

#include <cstddef>
#include <cstdint>

#include <olcPixelGameEngine.h>


namespace frames {

class MainFrame final : public olc::PixelGameEngine
{
public:
    static const olc::vi2d pgeWindowSize;
    static constexpr int32_t pgePixelSize = 1;

    static constexpr size_t scopeScreenWidth = 500;
    static constexpr size_t scopeScreenHeight = 255;

public:
    MainFrame();
    virtual ~MainFrame() {}

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float tElapsed) override;
    bool OnUserDestroy() override;

private:
    uint8_t m_screenData[scopeScreenWidth][scopeScreenHeight]; // [x][y]

private:
    MainFrame(const MainFrame& other) = delete;
    MainFrame(const MainFrame&& other) = delete;
    const MainFrame& operator=(const MainFrame& b) { return b; }
};

} // namespace frames


#endif // IG_FRAMES_MAINFRAME_H
