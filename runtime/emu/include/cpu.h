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

///////////////////////////////////////////////////////////////////////////////
// FLAG_MASK enum
///////////////////////////////////////////////////////////////////////////////
enum FLAG_MASK
{
    FLAG_MASK_ZERO         = 0x1 << 7,
    FLAG_MASK_SUBSTRACTION = 0x1 << 6,
    FLAG_MASK_HALF_CARRY   = 0x1 << 5,
    FLAG_MASK_CARRY        = 0x1 << 4,
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
    Cpu() = default;

    uint8_t GetA() const { return m_Register.A; }
    uint8_t GetF() const { return m_Register.F; }
    uint8_t GetB() const { return m_Register.B; }
    uint8_t GetC() const { return m_Register.C; }
    uint8_t GetD() const { return m_Register.D; }
    uint8_t GetE() const { return m_Register.E; }
    uint8_t GetH() const { return m_Register.H; }
    uint8_t GetL() const { return m_Register.L; }
    uint16_t GetAF() const { return ToU16(m_Register.A, m_Register.F); }
    uint16_t GetBC() const { return ToU16(m_Register.B, m_Register.C); }
    uint16_t GetDE() const { return ToU16(m_Register.D, m_Register.E); }
    uint16_t GetHL() const { return ToU16(m_Register.H, m_Register.L); }

    void SetA(uint8_t value) { m_Register.A = value; }
    void SetF(uint8_t value) { m_Register.F = value; }
    void SetB(uint8_t value) { m_Register.B = value; }
    void SetC(uint8_t value) { m_Register.C = value; }
    void SetD(uint8_t value) { m_Register.D = value; }
    void SetE(uint8_t value) { m_Register.E = value; }
    void SetH(uint8_t value) { m_Register.H = value; }
    void SetL(uint8_t value) { m_Register.L = value; }
    void SetAF(uint16_t value) { FromU16(m_Register.A, m_Register.F, value); }
    void SetBC(uint16_t value) { FromU16(m_Register.B, m_Register.C, value); }
    void SetDE(uint16_t value) { FromU16(m_Register.D, m_Register.E, value); }
    void SetHL(uint16_t value) { FromU16(m_Register.H, m_Register.L, value); }

    bool IsEnableColor() const { return m_EnableColor; }
    bool IsEnableSuper() const { return m_EnableSuper; }

private:
    struct Register
    {
        uint8_t     B     = 0;  //!< Bレジスタ.
        uint8_t     C     = 0;  //!< Cレジスタ.
        uint8_t     D     = 0;  //!< Dレジスタ.
        uint8_t     E     = 0;  //!< Eレジスタ.
        uint8_t     H     = 0;  //!< Hレジスタ.
        uint8_t     L     = 0;  //!< Lレジスタ.
        uint8_t     A     = 0;  //!< アキュムレータ.
        uint8_t     F     = 0;  //!< フラグレジスタ.
        uint16_t    SP    = 0;  //!< スタックポインタ.
        uint16_t    PC    = 0;  //!< プログラムカウンター.
    };
    struct Timer
    {
        uint8_t     DividerRegister = 0;    // DIV.
        uint8_t     TimerCounter    = 0;    // TIMA.
        uint8_t     TimerModulo     = 0;    // TMA.
        uint8_t     TimerControl    = 0;    // TAC.
    };

    Register    m_Register      = {};
    Timer       m_Timer         = {};
    bool        m_EnableColor   = false;
    bool        m_EnableSuper   = false;



};
