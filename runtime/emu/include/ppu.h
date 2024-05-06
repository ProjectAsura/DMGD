//-----------------------------------------------------------------------------
// File   : ppu.h
// Desc   : PPU(Picture Processing Unit) Emulation.
// Author : Pocol.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdint>
#include <mem.h>


///////////////////////////////////////////////////////////////////////////////
// Ppu class
///////////////////////////////////////////////////////////////////////////////
class Ppu
{
public:
    static constexpr uint8_t    DisplayWidth  = 160;    //!< 表示横幅.
    static constexpr uint8_t    DisplayHeight = 144;    //!< 表示縦幅.
    static constexpr uint16_t   BufferWidth   = 256;    //!< バッファ横幅.
    static constexpr uint16_t   BufferHeight  = 256;    //!< バッファ縦幅.

    Ppu() = default;

    void Execute() {}
    void SetMemory(Memory* value) { m_Memory = value; }

private:
    Memory*     m_Memory = nullptr;
};