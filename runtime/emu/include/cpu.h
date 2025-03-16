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
{ return uint16_t(hiWord << 8) | uint16_t(loWord); }

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

    inline uint8_t  Read8 (uint16_t address) const { return m_pMemory->Read8 (address); }
    inline uint16_t Read16(uint16_t address) const { return m_pMemory->Read16(address); }

    inline void Write8 (uint16_t address, uint8_t  value) { m_pMemory->Write8 (address, value); }
    inline void Write16(uint16_t address, uint16_t value) { m_pMemory->Write16(address, value); }

    inline void Inc8 (uint16_t address) { m_pMemory->Inc8 (address); }
    inline void Inc16(uint16_t address) { m_pMemory->Inc16(address); }

    inline void Dec8 (uint16_t address) { m_pMemory->Dec8 (address); }
    inline void Dec16(uint16_t address) { m_pMemory->Dec16(address); }

    inline void SetMemory(Memory* memory) { m_pMemory = memory; }

    void Execute(); // 命令を実行する.

private:
    Register    m_Register          = {};
    Timer       m_Timer             = {};
    bool        m_EnableColor       = false;
    bool        m_EnableSuper       = false;
    bool        m_EnablePowerSave   = false;
    bool        m_EnableInterrputs  = false;
    uint8_t     m_ConsumedCycles    = 0;
    Memory*     m_pMemory           = nullptr;

    void ExecuteCommand(uint8_t opCode);
    void ExecutePrefixCommand(uint8_t opCode);

    uint8_t  n () const;
    uint16_t nn() const;


    // 8-Bit Loads
    void LD (uint8_t& lhs, uint8_t  rhs);

    // 16-Bit Loads
    void LD (uint16_t& lhs, uint16_t rhs);
    void LDHL(uint16_t addr);
    void PUSH(uint16_t value);
    void POP (uint16_t value);

    // 8-Bit ALU
    void ADD(uint8_t& lhs, uint8_t rhs);
    void ADC(uint8_t& lhs, uint8_t rhs);
    void SUB(uint8_t& lhs, uint8_t rhs);
    void SBC(uint8_t& lhs, uint8_t rhs);
    void AND(uint8_t& lhs, uint8_t rhs);
    void OR (uint8_t& lhs, uint8_t rhs);
    void XOR(uint8_t& lhs, uint8_t rhs);
    void CP (uint8_t& lhs, uint8_t rhs);
    void INC(uint8_t& val);
    void DEC(uint8_t& val);

    // 16-Bit Artithmetic
    void ADD(uint16_t& lhs, uint16_t rhs);
    void INC(uint16_t& val);
    void DEC(uint16_t& val);

    // Miscellaneous
    void SWAP(uint8_t& lhs, uint8_t& rhs);
    void DAA();
    void CPL();
    void CCF();
    void SCF();
    void NOP();
    void HALT();
    void STOP();
    void DI();
    void EI();

    // Rotates & Shifts
    void RLCA();
    void RLA();
    void RRCA();
    void RRA();
    void RLC(uint8_t& lhs, uint8_t rhs);
    void RL (uint8_t& lhs, uint8_t rhs);
    void RRC(uint8_t& lhs, uint8_t rhs);
    void RR (uint8_t& lhs, uint8_t rhs);
    void SLA(uint8_t& lhs, uint8_t rsh);
    void SAR(uint8_t& lhs, uint8_t rhs);
    void SRL(uint8_t& lhs, uint8_t rhs);

    // Bit OpCodes.
    void BIT(uint8_t& lhs, uint8_t rhs);
    void SET(uint8_t& lhs, uint8_t rhs);
    void RES(uint8_t& lhs, uint8_t rhs);

    // Jumps
    void JP(bool flag, uint8_t  addr);
    void JP(bool flag, uint16_t addr);

    // Calls
    void CALL(bool flag, uint16_t addr);

    // Restarts
    void RST(uint8_t addr);

    // Returns.
    void RET(bool flag);
    void RETI();
  
};
