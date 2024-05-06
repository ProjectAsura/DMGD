//-----------------------------------------------------------------------------
// File   : emu.cpp
// Desc   : Game-Boy Emulator.
// Author : Pocol.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <emu.h>


///////////////////////////////////////////////////////////////////////////////
// Emulator class
///////////////////////////////////////////////////////////////////////////////

bool Emulator::Init()
{
    if (!m_Memory.Init())
    { return false; }

    m_CPU.SetMemory(&m_Memory);
    m_PPU.SetMemory(&m_Memory);

    m_ROM = nullptr;

    return true;
}

void Emulator::Term()
{
    m_CPU.SetMemory(nullptr);
    m_PPU.SetMemory(nullptr);

    m_Memory.Term();
}

void Emulator::Update()
{
    // GameBoy更新.
    m_CPU.Execute();
    m_PPU.Execute();
    m_APU.Execute();
}

void Emulator::SetRom(const Cartridge* rom)
{
}

void Emulator::SetJoyPad(uint8_t value)
{
}
