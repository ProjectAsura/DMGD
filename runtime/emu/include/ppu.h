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

private:
    uint8_t     m_Vram[8 * 1024] = {};
};