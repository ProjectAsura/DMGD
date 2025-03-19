//-----------------------------------------------------------------------------
// File   : emu.h
// Desc   : Game-Boy Emulator.
// Author : Pocol.
//-----------------------------------------------------------------------------
#pragma once

#define PLATFORM_WIN64 (1)

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdint>
#include <cpu.h>
#include <ppu.h>
#include <apu.h>
#include <mem.h>
#include <cartridge.h>

#if PLATFORM_WIN64
#include <Windows.h>
#endif//PLATFORM_WIN64


///////////////////////////////////////////////////////////////////////////////
// Emulator class
///////////////////////////////////////////////////////////////////////////////
class Emulator
{
    //=========================================================================
    // list of friend classes and methods.
    //=========================================================================
    /* NOTHING */

public:
    //=========================================================================
    // public variables.
    //=========================================================================
    /* NOTHING */

    //=========================================================================
    // public methods.
    //=========================================================================
    Emulator () = default;
    ~Emulator() = default;

    void Run();

    const Memory& GetMemory() const { return m_Memory; }
    void SetRom(const Cartridge* rom);
    void SetJoyPad(uint8_t value);

private:
    //=========================================================================
    // private variables.
    //=========================================================================
    Cpu                 m_CPU       = {};
    Ppu                 m_PPU       = {};
    Apu                 m_APU       = {};
    Memory              m_Memory    = {};
    const Cartridge*    m_ROM       = nullptr;

#if PLATFORM_WIN64
    HINSTANCE m_hInst = nullptr;
    HWND      m_hWnd  = nullptr;
#endif

    //=========================================================================
    // private methods.
    //=========================================================================
    bool InitWnd (uint32_t w, uint32_t h);
    void TermWnd ();
    void MainLoop();

    bool Init();
    void Term();
    void Update();

#if PLATFORM_WIN64
    static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
#endif

};

