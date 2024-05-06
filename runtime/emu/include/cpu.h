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
#include <mem.h>


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
            uint8_t Reserved : 4;    // Unused.
            uint8_t C        : 1;    // Carry Flag.
            uint8_t H        : 1;    // Half Carry Flag.
            uint8_t N        : 1;    // Subtract Flag.
            uint8_t Z        : 1;    // Zero Flag.
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

    inline uint8_t GetA() const { return m_Register.A; }
    inline uint8_t GetF() const { return m_Register.F.Value; }
    inline uint8_t GetB() const { return m_Register.B; }
    inline uint8_t GetC() const { return m_Register.C; }
    inline uint8_t GetD() const { return m_Register.D; }
    inline uint8_t GetE() const { return m_Register.E; }
    inline uint8_t GetH() const { return m_Register.H; }
    inline uint8_t GetL() const { return m_Register.L; }
    inline uint16_t GetAF() const { return ToU16(m_Register.A, m_Register.F.Value); }
    inline uint16_t GetBC() const { return ToU16(m_Register.B, m_Register.C); }
    inline uint16_t GetDE() const { return ToU16(m_Register.D, m_Register.E); }
    inline uint16_t GetHL() const { return ToU16(m_Register.H, m_Register.L); }
    inline uint16_t GetSP() const { return m_Register.SP; }
    inline uint16_t GetPC() const { return m_Register.PC; }
    inline bool GetFlagZ() const { return !!m_Register.F.Z; }
    inline bool GetFlagN() const { return !!m_Register.F.N; }
    inline bool GetFlagH() const { return !!m_Register.F.H; }
    inline bool GetFlagC() const { return !!m_Register.F.C; }

    inline void SetA(uint8_t value) { m_Register.A = value; }
    inline void SetF(uint8_t value) { m_Register.F.Value = value; }
    inline void SetB(uint8_t value) { m_Register.B = value; }
    inline void SetC(uint8_t value) { m_Register.C = value; }
    inline void SetD(uint8_t value) { m_Register.D = value; }
    inline void SetE(uint8_t value) { m_Register.E = value; }
    inline void SetH(uint8_t value) { m_Register.H = value; }
    inline void SetL(uint8_t value) { m_Register.L = value; }
    inline void SetAF(uint16_t value) { FromU16(m_Register.A, m_Register.F.Value, value); }
    inline void SetBC(uint16_t value) { FromU16(m_Register.B, m_Register.C, value); }
    inline void SetDE(uint16_t value) { FromU16(m_Register.D, m_Register.E, value); }
    inline void SetHL(uint16_t value) { FromU16(m_Register.H, m_Register.L, value); }
    inline void SetSP(uint16_t value) { m_Register.SP = value; }
    inline void SetPC(uint16_t value) { m_Register.PC = value; }
    inline void SetFlagZ(bool value) { m_Register.F.Z = value ? 1 : 0; }
    inline void SetFlagN(bool value) { m_Register.F.N = value ? 1 : 0; }
    inline void SetFlagH(bool value) { m_Register.F.H = value ? 1 : 0; }
    inline void SetFlagC(bool value) { m_Register.F.C = value ? 1 : 0; }

    inline bool IsEnableColor() const { return m_EnableColor; }
    inline bool IsEnableSuper() const { return m_EnableSuper; }

    inline uint8_t GetConsumedCycles() const { return m_ConsumedCycles; }

    inline void SetMemory(Memory* memory) { m_Memory = memory; }

    void Execute(); // 命令を実行する.

private:
    Register    m_Register          = {};
    Timer       m_Timer             = {};
    bool        m_EnableColor       = false;
    bool        m_EnableSuper       = false;
    bool        m_EnablePowerSave   = false;
    bool        m_EnableInterrputs  = false;
    uint8_t     m_ConsumedCycles    = 0;
    Memory*     m_Memory            = nullptr;

    void ExecuteCommand(uint8_t opCode);
    void ExecutePrefixCommand(uint8_t opCode);
    void SetCarry(uint8_t lhs, uint8_t rhs);
    void SetBorrow(uint8_t lhs, uint8_t rhs);

    // 8-Bit Arithmetic
    void Add(uint8_t& lhs, uint8_t rhs);
    void Adc(uint8_t& lhs, uint8_t rhs);
    void Sub(uint8_t& lhs, uint8_t rhs);
    void Sbc(uint8_t& lhs, uint8_t rhs);
    void And(uint8_t val);
    void Or(uint8_t val);
    void Xor(uint8_t val);
    void Cmp(uint8_t val);
    void Inc(uint8_t& val);
    void Dec(uint8_t& val);

    // 16-Bit Arithmetic
    void AddHL(uint16_t val);
    void AddSP(int8_t val);
    // Inc.
    // Dec.

    // Miscellaneous
    void Swap(uint8_t& val);
    // Daa
    // Cpl
    // Ccf
    // Scf
};
