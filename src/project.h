/*
author          Oliver Blaser
date            27.07.2024
copyright       GPL-3.0 - Copyright (c) 2024 Oliver Blaser
*/

#ifndef IG_PROJECT_H
#define IG_PROJECT_H

#include <omw/defs.h>
#include <omw/version.h>


namespace prj {

const char* const appDirName = "hp54600-screen-capture";

const char* const appName = "HP54600 Screen Capture";
const char* const exeName = "hp54600-screen-capture"; // eq to the linker setting

const char* const website = "https://github.com/oblaser/HP54600-screen-capture";

const omw::Version version(0, 1, 0, "alpha");

}


#ifdef OMW_DEBUG
#define PRJ_DEBUG (1)
#else
#undef PRJ_DEBUG
#endif


#endif // IG_PROJECT_H
