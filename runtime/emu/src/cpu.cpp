//-----------------------------------------------------------------------------
// File   : cpu.cpp
// Desc   : CPU(Centrol Processing Unit) Emulation.
// Author : Pocol.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cpu.h>


///////////////////////////////////////////////////////////////////////////////
// Cpu class.
///////////////////////////////////////////////////////////////////////////////

std::array<Command, 256> Cpu::s_Commands = {


};

std::array<Command, 256> Cpu::s_PrefixCommands = {

};


const Command& Cpu::GetCommand(uint16_t address)
{
    uint8_t idx = m_Memory->Read8(address);
    if (idx != 0xcb)
    { return s_Commands[idx]; }

    idx = m_Memory->Read8(address + 1);
    return s_PrefixCommands[idx];
}

void Cpu::Execute()
{
    // 低電力モードの場合は実行しない.
    if (m_EnablePowerSave)
    { return; }

    // 命令をフェッチ.
    const auto& cmd = GetCommand(m_Register.PC);

    // 命令を実行.
    if (cmd.Action != nullptr)
    { (*this.*(cmd.Action))(cmd.OpCode); }

    // 消費サイクル数を設定.
    m_ConsumedCycles = cmd.Cycles;

    // プログラムカウンターを進める.
    m_Register.PC += cmd.Bytes;
}