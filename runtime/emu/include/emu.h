//-----------------------------------------------------------------------------
// File   : emu.h
// Desc   : Game-Boy Emulator.
// Author : Pocol.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdint>
#include <cpu.h>
#include <ppu.h>
#include <apu.h>
#include <mem.h>
#include <cartridge.h>


///////////////////////////////////////////////////////////////////////////////
// Emulator class
///////////////////////////////////////////////////////////////////////////////
class Emulator
{
public:
    Emulator () = default;
    ~Emulator() = default;

    bool Init();
    void Term();
    void Update();

    const Memory& GetMemory() const { return m_Memory; }
    void SetRom(const Cartridge* rom);
    void SetJoyPad(uint8_t value);

private:
    Cpu                 m_CPU       = {};
    Ppu                 m_PPU       = {};
    Apu                 m_APU       = {};
    Memory              m_Memory    = {};
    const Cartridge*    m_ROM       = nullptr;
};

