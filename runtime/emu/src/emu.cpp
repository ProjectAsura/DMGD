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

    if (!InitWnd())
    { return false; }

    return true;
}

void Emulator::Term()
{
    TermWnd();

    m_CPU.SetMemory(nullptr);
    m_PPU.SetMemory(nullptr);

    m_Memory.Term();
}

void Emulator::Update()
{
    // GameBoy更新処理.
    m_CPU.Execute();
    m_PPU.Execute();
    m_APU.Execute();

    // フレームバッファを描画.
}

void Emulator::SetRom(const Cartridge* rom)
{
}

void Emulator::SetJoyPad(uint8_t value)
{
}

void Emulator::Run()
{
    if (Init())
    { MainLoop(); }

    Term();
}

#if PLATFORM_WIN64
bool Emulator::InitWnd()
{
    return false;
}

void Emulator::TermWnd()
{
}

void Emulator::MainLoop()
{

}
#endif
