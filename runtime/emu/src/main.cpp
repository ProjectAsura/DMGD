//-----------------------------------------------------------------------------
// File   : main.cpp
// Desc   : Main Entry Point.
// Author : Pocol.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <emu.h>
#include <cartridge.h>

void test()
{
    Cartridge* cartridge = nullptr;
    if (!LoadCartridge("../res/rom/sample.gb", &cartridge))
    {
        return;
    }


}


int main(int argc, char** argv)
{
    test();

    Emulator().Run();

    return 0;
}