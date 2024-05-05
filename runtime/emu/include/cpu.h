//-----------------------------------------------------------------------------
// File   : cpu.h
// Desc   : CPU(Centrol Processing Unit) Emulation.
// Author : Pocol.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdint>
#include <array>
#include <mem.h>


class Cpu;
using CpuAction = void (Cpu::*)(uint8_t);


struct Command
{
    uint8_t     OpCode;
    uint8_t     Bytes;
    uint8_t     Cycles;
    CpuAction   Action;

    // 以下, デバッグ用途.
    const char* Instruction;
    const char* Operands;
};

inline uint16_t ToU16(uint8_t hiWord, uint8_t loWord)
{
    return uint16_t(hiWord << 8) | uint16_t(loWord); 
}

inline void FromU16(uint8_t& hiWord, uint8_t& loWord, uint16_t value)
{
    hiWord = value >> 8;
    loWord = value & 0xFF;
}


///////////////////////////////////////////////////////////////////////////////
// Cpu class
///////////////////////////////////////////////////////////////////////////////
class Cpu
{
public:
    union FlagRegister
    {
        struct
        {
            uint8_t Unused  : 4;    // Unused.
            uint8_t C       : 1;    // Carry Flag.
            uint8_t H       : 1;    // Half Carry Flag.
            uint8_t N       : 1;    // Subtract Flag.
            uint8_t Z       : 1;    // Zero Flag.
        };
        uint8_t Value;
    };

    struct Register
    {
        uint8_t         B     = 0;  //!< Bレジスタ.
        uint8_t         C     = 0;  //!< Cレジスタ.
        uint8_t         D     = 0;  //!< Dレジスタ.
        uint8_t         E     = 0;  //!< Eレジスタ.
        uint8_t         H     = 0;  //!< Hレジスタ.
        uint8_t         L     = 0;  //!< Lレジスタ.
        uint8_t         A     = 0;  //!< アキュムレータ.
        FlagRegister    F     = {}; //!< フラグレジスタ.
        uint16_t        SP    = 0;  //!< スタックポインタ.
        uint16_t        PC    = 0;  //!< プログラムカウンター.
    };

    struct Timer
    {
        uint8_t     DividerRegister = 0;    // DIV.
        uint8_t     TimerCounter    = 0;    // TIMA.
        uint8_t     TimerModulo     = 0;    // TMA.
        uint8_t     TimerControl    = 0;    // TAC.
    };

    Cpu() = default;

    uint8_t GetA() const { return m_Register.A; }
    uint8_t GetF() const { return m_Register.F.Value; }
    uint8_t GetB() const { return m_Register.B; }
    uint8_t GetC() const { return m_Register.C; }
    uint8_t GetD() const { return m_Register.D; }
    uint8_t GetE() const { return m_Register.E; }
    uint8_t GetH() const { return m_Register.H; }
    uint8_t GetL() const { return m_Register.L; }
    uint16_t GetAF() const { return ToU16(m_Register.A, m_Register.F.Value); }
    uint16_t GetBC() const { return ToU16(m_Register.B, m_Register.C); }
    uint16_t GetDE() const { return ToU16(m_Register.D, m_Register.E); }
    uint16_t GetHL() const { return ToU16(m_Register.H, m_Register.L); }
    bool GetFlagZ() const { return !!m_Register.F.Z; }
    bool GetFlagN() const { return !!m_Register.F.N; }
    bool GetFlagH() const { return !!m_Register.F.H; }
    bool GetFlagC() const { return !!m_Register.F.C; }

    void SetA(uint8_t value) { m_Register.A = value; }
    void SetF(uint8_t value) { m_Register.F.Value = value; }
    void SetB(uint8_t value) { m_Register.B = value; }
    void SetC(uint8_t value) { m_Register.C = value; }
    void SetD(uint8_t value) { m_Register.D = value; }
    void SetE(uint8_t value) { m_Register.E = value; }
    void SetH(uint8_t value) { m_Register.H = value; }
    void SetL(uint8_t value) { m_Register.L = value; }
    void SetAF(uint16_t value) { FromU16(m_Register.A, m_Register.F.Value, value); }
    void SetBC(uint16_t value) { FromU16(m_Register.B, m_Register.C, value); }
    void SetDE(uint16_t value) { FromU16(m_Register.D, m_Register.E, value); }
    void SetHL(uint16_t value) { FromU16(m_Register.H, m_Register.L, value); }
    void SetFlagZ(bool value) { m_Register.F.Z = value ? 1 : 0; }
    void SetFlagN(bool value) { m_Register.F.N = value ? 1 : 0; }
    void SetFlagH(bool value) { m_Register.F.H = value ? 1 : 0; }
    void SetFlagC(bool value) { m_Register.F.C = value ? 1 : 0; }

    bool IsEnableColor() const { return m_EnableColor; }
    bool IsEnableSuper() const { return m_EnableSuper; }

    void Execute(); // 命令を実行する.

    uint8_t GetConsumedCycles() const { return m_ConsumedCycles; }

    void SetMemory(Memory* memory) { m_Memory = memory; }

private:
    static std::array<Command, 256> s_Commands;
    static std::array<Command, 256> s_PrefixCommands;

    Register    m_Register          = {};
    Timer       m_Timer             = {};
    bool        m_EnableColor       = false;
    bool        m_EnableSuper       = false;
    bool        m_EnablePowerSave   = false;
    uint8_t     m_ConsumedCycles    = 0;
    Memory*     m_Memory            = nullptr;

    const Command& GetCommand(uint16_t address);
};
