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

void Cpu::SetCarry(uint8_t lhs, uint8_t rhs)
{
    bool carryH = (lhs & 0x0F) + (rhs & 0x0F) > 0x0F;
    bool carryC = (lhs & 0xFF) + (rhs & 0xFF) > 0xFF;
    SetFlagH(carryH);
    SetFlagC(carryC); 
}

void Cpu::SetBorrow(uint8_t lhs, uint8_t rhs)
{
    bool borrowH = (lhs & 0xf) - (rhs & 0xf) < 0;
    bool borrowC = (lhs < rhs);
    SetFlagH(borrowH);
    SetFlagC(borrowC);
}

void Cpu::Add(uint8_t& lhs, uint8_t rhs)
{
    SetFlagN(false);
    SetCarry(lhs, rhs);
    lhs += rhs;
    SetFlagZ(lhs == 0);
}

void Cpu::Adc(uint8_t& lhs, uint8_t rhs)
{
    SetFlagN(false);
    SetCarry(lhs, rhs);
    lhs += rhs + m_Register.F.C;
    SetFlagZ(lhs == 0);
}

void Cpu::Sub(uint8_t& lhs, uint8_t rhs)
{
    SetFlagN(true);
    SetBorrow(lhs, rhs);
    lhs -= rhs;
    SetFlagZ(lhs == 0);
}

void Cpu::Sbc(uint8_t& lhs, uint8_t rhs)
{
    SetFlagN(true);
    SetBorrow(lhs, rhs);
    lhs -= rhs + m_Register.F.C;
    SetFlagZ(lhs == 0);
}

void Cpu::And(uint8_t val)
{
    SetFlagN(false);
    SetFlagH(true);
    SetFlagC(false);
    m_Register.A = m_Register.A & val;
    SetFlagZ(m_Register.A == 0);
}

void Cpu::Or(uint8_t val)
{
    SetFlagN(false);
    SetFlagH(false);
    SetFlagC(false);
    m_Register.A = m_Register.A | val;
    SetFlagZ(m_Register.A == 0);
}

void Cpu::Xor(uint8_t val)
{
    SetFlagN(false);
    SetFlagH(false);
    SetFlagC(false);
    m_Register.A = m_Register.A ^ val;
    SetFlagZ(m_Register.A == 0);
}

void Cpu::Cmp(uint8_t val)
{
    SetFlagZ(m_Register.A == val);
    SetFlagN(true);
    SetBorrow(m_Register.A, val);
}

void Cpu::Inc(uint8_t& val)
{
    SetFlagN(false);
    SetFlagH((val & 0xf) == 0xf);
    val++;
    SetFlagZ(val == 0);
}

void Cpu::Dec(uint8_t& val)
{
    SetFlagN(true);
    SetFlagH((val & 0xf) == 0);
    val--;
    SetFlagZ(val == 0);
}

void Cpu::AddHL(uint16_t val)
{
    SetFlagN(false);

}

void Cpu::Execute()
{
    // 低電力モードの場合は実行しない.
    if (m_EnablePowerSave)
    { return; }

    // 命令をフェッチ.
    uint8_t cmd = m_Memory->Read8(m_Register.PC);
    if (cmd != 0xCB)
    {
        ExecuteCommand(cmd);
    }
    else
    {
        cmd = m_Memory->Read8(m_Register.PC + 1);
        ExecutePrefixCommand(cmd);
    }
}

void Cpu::ExecuteCommand(uint8_t opCode)
{
    switch(opCode)
    {
    case 0x00:
        {
            // NOP
            m_ConsumedCycles = 4;
        }
        break;
    case 0x01:
        {
            // LD BC,nn
            auto nn = m_Memory->Read16(m_Register.PC + 1);
            SetBC(nn);
            m_ConsumedCycles = 12;
        }
        break;
    case 0x02:
        {
            // LD (BC),A
            m_Memory->Write8(GetBC(), GetA());
            m_ConsumedCycles = 8;
        }
        break;
    case 0x03: {} break;
    case 0x04:
        {
            // INC B
            Inc(m_Register.B);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x05:
        {
            // DEC B
            Dec(m_Register.B);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x06:
        {
            // LD B,n
            auto n = m_Memory->Read8(m_Register.PC + 1);
            SetB(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x07: {} break;
    case 0x08:
        {
            // LD (nn),SP
            auto nn = m_Memory->Read16(m_Register.PC + 1);
            m_Memory->Write16(nn, GetSP());
            m_ConsumedCycles = 20;
        }
        break;
    case 0x09: {} break;
    case 0x0A:
        {
            // LD A,(BC)
            auto n = m_Memory->Read8(GetBC());
            SetA(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x0B: {} break;
    case 0x0C:
        {
            // INC C
            Inc(m_Register.C);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x0D:
        {
            // DEC C
            Dec(m_Register.C);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x0E:
        {
            // LD C,n
            auto n = m_Memory->Read8(m_Register.PC + 1);
            SetC(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x0F: {} break;

    case 0x10: {} break;
    case 0x11:
        {
            // LD DE,nn
            auto nn = m_Memory->Read16(m_Register.PC + 1);
            SetDE(nn);
            m_ConsumedCycles = 12;
        }
        break;
    case 0x12:
        {
            // LD (DE),A
            m_Memory->Write8(GetDE(), GetA());
            m_ConsumedCycles = 8;
        }
        break;
    case 0x13: {} break;
    case 0x14:
        {
            // INC D
            Inc(m_Register.D);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x15:
        {
            // DEC D
            Dec(m_Register.D);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x16:
        {
            // LD D,n
            auto n = m_Memory->Read8(m_Register.PC + 1);
            SetD(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x17: {} break;
    case 0x18: {} break;
    case 0x19: {} break;
    case 0x1A:
        {
            // LD A,(DE)
            auto n = m_Memory->Read8(GetDE());
            SetA(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x1B: {} break;
    case 0x1C:
        {
            // INC E
            Inc(m_Register.E);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x1D:
        {
            // DEC E
            Dec(m_Register.E);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x1E:
        {
            // LD E,n
            auto n = m_Memory->Read8(m_Register.PC + 1);
            SetE(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x1F: {} break;

    case 0x20: {} break;
    case 0x21:
        {
            // LD HL,nn
            auto nn = m_Memory->Read16(m_Register.PC + 1);
            SetHL(nn);
            m_ConsumedCycles = 12;
        }
        break;
    case 0x22:
        {
            // LDI (HL),A
            auto hl = GetHL();
            m_Memory->Write8(hl, GetA());
            hl++;
            SetHL(hl);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x23: {} break;
    case 0x24:
        {
            // INC H
            Inc(m_Register.H);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x25:
        {
            // DEC H
            Dec(m_Register.H);
            m_ConsumedCycles = 4;
        } break;
    case 0x26:
        {
            // LD H,n
            auto n = m_Memory->Read8(m_Register.PC + 1);
            SetH(n);
            m_ConsumedCycles = 8;
         }
        break;
    case 0x27: {} break;
    case 0x28: {} break;
    case 0x29: {} break;
    case 0x2A:
        {
            // LDI A,(HL)
            auto hl = GetHL();
            auto n = m_Memory->Read8(hl);
            SetA(n);
            hl++;
            SetHL(hl);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x2B: {} break;
    case 0x2C:
        {
            // INC L
            Inc(m_Register.L);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x2D:
        {
            // DEC L
            Dec(m_Register.L);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x2E:
        {
            // LD L,n
            auto n = m_Memory->Read8(m_Register.PC + 1);
            SetL(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x2F: {} break;

    case 0x30: {} break;
    case 0x31:
        {
            // LD SP,nn
            auto nn = m_Memory->Read16(m_Register.PC + 1);
            SetSP(nn);
            m_ConsumedCycles = 12;
        }
        break;
    case 0x32:
        {
            // LDD (HL),A
            auto hl = GetHL();
            m_Memory->Write8(hl, GetA());
            hl--;
            SetHL(hl);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x33: {} break;
    case 0x34:
        {
            // INC (HL)
            auto n = m_Memory->Read8(GetHL());
            Inc(n);
            m_Memory->Write8(GetHL(), n);
            m_ConsumedCycles = 12;
        }
        break;
    case 0x35:
        {
            // DEC (HL)
            auto n = m_Memory->Read8(GetHL());
            Dec(n);
            m_Memory->Write8(GetHL(), n);
            m_ConsumedCycles = 12;
        }
        break;
    case 0x36: {} break;
    case 0x37: {} break;
    case 0x38: {} break;
    case 0x39: {} break;
    case 0x3A:
        {
            // LDD A,(HL)
            auto hl = GetHL();
            auto n = m_Memory->Read8(hl);
            SetA(n);
            hl--;
            SetHL(hl);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x3B: {} break;
    case 0x3C:
        {
            // INC A
            Inc(m_Register.A);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x3D:
        {
            // DEC A
            Dec(m_Register.A);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x3E:
        {
            // LD A,#
            auto n = m_Memory->Read8(m_Register.PC + 1);
            SetA(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x3F: {} break;

    case 0x40:
        {
            // LD B,B
            SetB(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x41:
        {
            // LD B,C
            SetB(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x42:
        {
            // LD B,D
            SetB(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x43:
        {
            // LD B,E
            SetB(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x44:
        {
            // LD B,H
            SetB(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x45:
        {
            // LD B,L
            SetB(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x46:
        {
            // LD B,(HL)
            auto n = m_Memory->Read8(GetHL());
            SetB(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x47:
        {
            // LD B,A
            SetB(GetA());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x48:
        {
            // LD C,B
            SetC(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x49:
        {
            // LD C,C
            SetC(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x4A:
        {
            // LD C,D
            SetC(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x4B:
        {
            // LD C,E
            SetC(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x4C: 
        {
            // LD C,H
            SetC(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x4D:
        {
            // LD C,L
            SetC(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x4E:
        {
            // LD C,(HL)
            auto n = m_Memory->Read8(GetHL());
            SetC(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x4F:
        {
            // LD C,A
            SetC(GetA());
            m_ConsumedCycles = 4;
        }
        break;

    case 0x50:
        {
            // LD D,B
            SetD(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x51:
        {
            // LD D,C
            SetD(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x52:
        {
            // LD D,D
            SetD(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x53:
        {
            // LD D,E
            SetD(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x54:
        {
            // LD D,H
            SetD(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x55:
        {
            // LD D,L
            SetD(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x56:
        {
            // LD D,(HL)
            auto n = m_Memory->Read8(GetHL());
            SetD(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x57:
        {
            // LD D,A
            SetD(GetA());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x58:
        {
            // LD E,B
            SetE(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x59:
        {
            // LD E,C
            SetE(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x5A:
        {
            // LD E,D
            SetE(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x5B:
        {
            // LD E,E
            SetE(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x5C:
        {
            // LD E,H
            SetE(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x5D:
        {
            // LD E,L
            SetE(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x5E:
        {
            // LD E,(HL)
            auto n = m_Memory->Read8(GetHL());
            SetE(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x5F:
        {
            // LD E,A
            SetE(GetA());
            m_ConsumedCycles = 4;
        }
        break;

    case 0x60:
        {
            // LD H,B
            SetH(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x61:
        {
            // LD H,C
            SetH(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x62:
        {
            // LD H,D
            SetH(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x63:
        {
            // LD H,E
            SetH(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x64:
        {
            // LD H,H
            SetH(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x65:
        {
            // LD H,L
            SetH(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x66:
        {
            // LD H,(HL)
            auto n = m_Memory->Read8(GetHL());
            SetH(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x67:
        {
            // LD H,A
            SetH(GetA());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x68:
        {
            // LD L,B
            SetL(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x69:
        {
            // LD L,C
            SetL(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x6A:
        {
            // LD L,D
            SetL(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x6B:
        {
            // LD L,E
            SetL(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x6C:
        {
            // LD L,H
            SetL(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x6D:
        {
            // LD L,L
            SetL(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x6E:
        {
            // LD L,(HL)
            auto n = m_Memory->Read8(GetHL());
            SetL(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x6F:
        {
            // LD L,A
            SetL(GetA());
            m_ConsumedCycles = 4;
        }
        break;

    case 0x70:
        {
            // LD (HL),B
            m_Memory->Write8(GetHL(), GetB());
            m_ConsumedCycles = 8;
        }
        break;
    case 0x71:
        {
            // LD (HL),C
            m_Memory->Write8(GetHL(), GetC());
            m_ConsumedCycles = 8;
        }
        break;
    case 0x72:
        {
            // LD (HL),D
            m_Memory->Write8(GetHL(), GetD());
            m_ConsumedCycles = 8;
        }
        break;
    case 0x73:
        {
            // LD (HL),E
            m_Memory->Write8(GetHL(), GetE());
            m_ConsumedCycles = 8;
        }
        break;
    case 0x74:
        {
            // LD (HL),H
            m_Memory->Write8(GetHL(), GetH());
            m_ConsumedCycles = 8;
        }
        break;
    case 0x75:
        {
            // LD (HL),L
            m_Memory->Write8(GetHL(), GetL());
            m_ConsumedCycles = 8;
        }
        break;
    case 0x76:
        {
            // HALT.
            m_ConsumedCycles = 4;
        }
        break;
    case 0x77:
        {
            // LD (HL),A
            m_Memory->Write8(GetHL(), GetA());
            m_ConsumedCycles = 8;
        }
        break;
    case 0x78:
        {
            // LD A,B
            SetA(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x79:
        {
            // LD A,C
            SetA(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x7A:
        {
            // LD A,D
            SetA(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x7B:
        {
            // LD A,E
            SetA(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x7C:
        {
            // LD A,H
            SetA(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x7D:
        {
            // LD A,L
            SetA(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0x7E:
        {
            // LD A,(HL)
            auto n = m_Memory->Read8(GetHL());
            SetA(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x7F:
        {
            // LD A,A
            SetA(GetA());
            m_ConsumedCycles = 4;
        }
        break;

    case 0x80:
        {
            // ADD A,B
            Add(m_Register.A, m_Register.B);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x81:
        {
            // ADD A,C
            Add(m_Register.A, m_Register.C);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x82:
        {
            // ADD A,D
            Add(m_Register.A, m_Register.D);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x83:
        {
            // ADD A,E
            Add(m_Register.A, m_Register.E);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x84:
        {
            // ADD A,H
            Add(m_Register.A, m_Register.H);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x85:
        {
            // ADD A,L
            Add(m_Register.A, m_Register.L);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x86:
        {
            // ADD A,(HL)
            auto n = m_Memory->Read8(GetHL());
            Add(m_Register.A, n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x87:
        {
            // ADD A,A
            Add(m_Register.A, m_Register.A);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x88:
        {
            // ADC A,B
            Adc(m_Register.A, m_Register.B);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x89:
        {
            // ADC A,C
            Adc(m_Register.A, m_Register.C);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x8A:
        {
            // ADC A,D
            Adc(m_Register.A, m_Register.D);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x8B:
        {
            // ADC A,E
            Adc(m_Register.A, m_Register.E);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x8C:
        {
            // ADC A,H
            Adc(m_Register.A, m_Register.H);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x8D:
        {
            // ADC A,L
            Adc(m_Register.A, m_Register.L);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x8E:
        {
            // ADC A,(HL)
            auto n = m_Memory->Read8(GetHL());
            Adc(m_Register.A, n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x8F:
        {
            // ADC A,A
            Adc(m_Register.A, m_Register.A);
            m_ConsumedCycles = 4;
        }
        break;

    case 0x90:
        {
            // SUB B
            Sub(m_Register.A, m_Register.B);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x91:
        {
            // SUB C
            Sub(m_Register.A, m_Register.C);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x92:
        {
            // SUB D
            Sub(m_Register.A, m_Register.D);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x93:
        {
            // SUB E
            Sub(m_Register.A, m_Register.E);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x94:
        {
            // SUB H
            Sub(m_Register.A, m_Register.H);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x95:
        {
            // SUB L
            Sub(m_Register.A, m_Register.L);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x96:
        {
            // SUB (HL)
            auto n = m_Memory->Read8(GetHL());
            Sub(m_Register.A, n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0x97:
        {
            // SUB A
            Sub(m_Register.A, m_Register.A);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x98:
        {
            // SBC A,B
            Sbc(m_Register.A, m_Register.B);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x99:
        {
            // SBC A,C
            Sbc(m_Register.A, m_Register.C);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x9A:
        {
            // SBC A,D
            Sbc(m_Register.A, m_Register.D);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x9B:
        {
            // SBC A,E
            Sbc(m_Register.A, m_Register.E);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x9C:
        {
            // SBC A,H
            Sbc(m_Register.A, m_Register.H);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x9D: 
        {
            // SBC A,L
            Sbc(m_Register.A, m_Register.L);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x9E:
        {
            // SBC A,(HL)
            auto n = m_Memory->Read8(GetHL());
            Sbc(m_Register.A, n);
            m_ConsumedCycles = 4;
        }
        break;
    case 0x9F:
        {
            // SBC A,A
            Sbc(m_Register.A, m_Register.A);
            m_ConsumedCycles = 4;
        }
        break;

    case 0xA0:
        {
            // AND B
            And(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xA1:
        {
            // AND C
            And(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xA2:
        {
            // AND D
            And(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xA3:
        {
            // AND E
            And(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xA4:
        {
            // AND H
            And(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xA5:
        {
            // AND L
            And(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xA6:
        {
            // AND (HL)
            auto n = m_Memory->Read8(GetHL());
            And(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xA7:
        {
            // AND A
            And(GetA());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xA8:
        {
            // XOR B
            Xor(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xA9:
        {
            // XOR C
            Xor(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xAA:
        {
            // XOR D
            Xor(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xAB:
        {
            // XOR E
            Xor(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xAC:
        {
            // XOR H
            Xor(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xAD:
        {
            // XOR L
            Xor(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xAE:
        {
            // XOR (HL)
            auto n = m_Memory->Read8(GetHL());
            Xor(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xAF:
        {
            // XOR A
            Xor(GetA());
            m_ConsumedCycles = 4;
        }
        break;

    case 0xB0:
        {
            // OR B
            Or(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xB1:
        {
            // OR C
            Or(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xB2:
        {
            // OR D
            Or(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xB3:
        {
            // OR E
            Or(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xB4:
        {
            // OR H
            Or(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xB5:
        {
            // OR L
            Or(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xB6:
        {
            // OR (HL)
            auto n = m_Memory->Read8(GetHL());
            Or(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xB7:
        {
            // OR A
            Or(GetA());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xB8:
        {
            // CP B
            Cmp(GetB());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xB9:
        {
            // CP C
            Cmp(GetC());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xBA:
        {
            // CP D
            Cmp(GetD());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xBB:
        {
            // CP E
            Cmp(GetE());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xBC:
        {
            // CP H
            Cmp(GetH());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xBD:
        {
            // CP L
            Cmp(GetL());
            m_ConsumedCycles = 4;
        }
        break;
    case 0xBE:
        {
            // CP (HL)
            auto n = m_Memory->Read8(GetHL());
            Cmp(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xBF:
        {
            // CP A
            Cmp(GetA());
            m_ConsumedCycles = 4;
        }
        break;

    case 0xC0: {} break;
    case 0xC1:
        {
            // POP BC
            auto sp = GetSP();
            auto nn = m_Memory->Read16(sp);
            SetBC(nn);
            sp += 2;
            SetSP(sp);
            m_ConsumedCycles = 12;
        }
        break;
    case 0xC2: {} break;
    case 0xC3: {} break;
    case 0xC4: {} break;
    case 0xC5:
        {
            // PUSH BC
            auto sp = GetSP();
            m_Memory->Write16(sp, GetBC());
            sp -= 2;
            SetSP(sp);
            m_ConsumedCycles = 16;
        }
        break;
    case 0xC6:
        {
            // ADD A,#
            auto n = m_Memory->Read8(m_Register.PC + 1);
            Add(m_Register.A, n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xC7: {} break;
    case 0xC8: {} break;
    case 0xC9: {} break;
    case 0xCA: {} break;
    case 0xCB: {} break;
    case 0xCC: {} break;
    case 0xCD: {} break;
    case 0xCE:
        {
            // ADC A,#
            auto n = m_Memory->Read8(m_Register.PC + 1);
            Adc(m_Register.A, n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xCF: {} break;

    case 0xD0: {} break;
    case 0xD1:
        {
            // POP DE
            auto sp = GetSP();
            auto nn = m_Memory->Read16(sp);
            SetDE(nn);
            sp += 2;
            SetSP(sp);
            m_ConsumedCycles = 12;
        }
        break;
    case 0xD2: {} break;
    //case 0xD3: {} break;
    case 0xD4: {} break;
    case 0xD5:
        {
            // PUSH DE
            auto sp = GetSP();
            m_Memory->Write16(sp, GetDE());
            sp -= 2;
            SetSP(sp);
            m_ConsumedCycles = 16;
        }
        break;
    case 0xD6:
        {
            // SUB #
            auto n = m_Memory->Read8(m_Register.PC + 1);
            Sub(m_Register.A, n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xD7: {} break;
    case 0xD8: {} break;
    case 0xD9: {} break;
    case 0xDA: {} break;
    //case 0xDB: {} break;
    case 0xDC: {} break;
    //case 0xDD: {} break;
    case 0xDE: {} break;
    case 0xDF: {} break;

    case 0xE0:
        {
            // LDH (n),A
            auto addr = 0xFF00 + m_Memory->Read8(m_Register.PC + 1);
            m_Memory->Write8(addr, GetA());
            m_ConsumedCycles = 12;
        }
        break;
    case 0xE1:
        {
            // POP HL
            auto sp = GetSP();
            auto nn = m_Memory->Read16(sp);
            SetHL(nn);
            sp += 2;
            SetSP(sp);
            m_ConsumedCycles = 12;
        }
        break;
    case 0xE2:
        {
            // LD ($FF00 + C),A
            uint16_t addr = 0xFF00 + GetC();
            m_Memory->Write8(addr, GetA());
            m_ConsumedCycles = 8;
        }
        break;
    //case 0xE3: {} break;
    //case 0xE4: {} break;
    case 0xE5:
        {
            // PUSH HL
            auto sp = GetSP();
            m_Memory->Write16(sp, GetHL());
            sp -= 2;
            SetSP(sp);
            m_ConsumedCycles = 16;
        }
        break;
    case 0xE6:
        {
            // AND #
            auto n = m_Memory->Read8(m_Register.PC + 1);
            And(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xE7: {} break;
    case 0xE8: {} break;
    case 0xE9: {} break;
    case 0xEA:
        {
            // LD (nn),A
            auto nn = m_Memory->Read16(m_Register.PC + 1);
            m_Memory->Write8(nn, GetA());
            m_ConsumedCycles = 16;
        }
        break;
    //case 0xEB: {} break;
    //case 0xEC: {} break;
    //case 0xED: {} break;
    case 0xEE: {} break;
    case 0xEF: {} break;

    case 0xF0:
        {
            // LDH A,(n)
            uint16_t addr = 0xFF00 + m_Memory->Read8(m_Register.PC + 1);
            auto n = m_Memory->Read8(addr);
            SetA(n);
            m_ConsumedCycles = 12;
        }
        break;
    case 0xF1:
        {
            // POP AF
            auto sp = GetSP();
            auto nn = m_Memory->Read16(sp);
            SetAF(nn);
            sp += 2;
            SetSP(sp);
            m_ConsumedCycles = 12;
        }
        break;
    case 0xF2:
        {
            // LD A,($FF00+C)
            uint16_t addr = 0xFF00 + GetC();
            auto n = m_Memory->Read8(addr);
            SetA(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xF3:
        {
            // DI.
            m_EnableInterrputs = false;
            m_ConsumedCycles = 4;
        }
        break;
    //case 0xF4: {} break;
    case 0xF5:
        {
            // PUSH AF
            auto sp = GetSP();
            m_Memory->Write16(sp, GetAF());
            sp -= 2;
            SetSP(sp);
            m_ConsumedCycles = 16;
        }
        break;
    case 0xF6:
        {
            // OR #
            auto n = m_Memory->Read8(m_Register.PC + 1);
            Or(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xF7: {} break;
    case 0xF8:
        {
            // LDHL SP,n
            SetFlagZ(false);
            SetFlagN(false);
            auto sp = GetSP();
            auto n = static_cast<int8_t>(m_Memory->Read8(m_Register.PC + 1));
            SetFlagH((sp & 0xf) + (n & 0xf) > 0xf);
            SetFlagC((sp & 0xff) + (n & 0xff) > 0xff);
            SetHL(sp + n);
            m_ConsumedCycles = 12;
        }
        break;
    case 0xF9:
        {
            // LD SP,HL
            SetSP(GetHL());
            m_ConsumedCycles = 8;
        }
        break;
    case 0xFA:
        {
            // LD A,(nn)
            auto nn = m_Memory->Read16(m_Register.PC + 1);
            auto n = m_Memory->Read8(nn);
            SetA(n);
            m_ConsumedCycles = 16;
        }
        break;
    case 0xFB:
        {
            // EI
            m_EnableInterrputs = true;
            m_ConsumedCycles = 4;
        }
        break;
    //case 0xFC: {} break;
    //case 0xFD: {} break;
    case 0xFE:
        {
            // CP #
            auto n = m_Memory->Read8(m_Register.PC + 1);
            Cmp(n);
            m_ConsumedCycles = 8;
        }
        break;
    case 0xFF: {} break;

    default:
        break;
    }
}

void Cpu::ExecutePrefixCommand(uint8_t opCode)
{
    switch(opCode)
    {
    case 0x00: {} break;
    case 0x01: {} break;
    case 0x02: {} break;
    case 0x03: {} break;
    case 0x04: {} break;
    case 0x05: {} break;
    case 0x06: {} break;
    case 0x07: {} break;
    case 0x08: {} break;
    case 0x09: {} break;
    case 0x0A: {} break;
    case 0x0B: {} break;
    case 0x0C: {} break;
    case 0x0D: {} break;
    case 0x0E: {} break;
    case 0x0F: {} break;

    case 0x10: {} break;
    case 0x11: {} break;
    case 0x12: {} break;
    case 0x13: {} break;
    case 0x14: {} break;
    case 0x15: {} break;
    case 0x16: {} break;
    case 0x17: {} break;
    case 0x18: {} break;
    case 0x19: {} break;
    case 0x1A: {} break;
    case 0x1B: {} break;
    case 0x1C: {} break;
    case 0x1D: {} break;
    case 0x1E: {} break;
    case 0x1F: {} break;

    case 0x20: {} break;
    case 0x21: {} break;
    case 0x22: {} break;
    case 0x23: {} break;
    case 0x24: {} break;
    case 0x25: {} break;
    case 0x26: {} break;
    case 0x27: {} break;
    case 0x28: {} break;
    case 0x29: {} break;
    case 0x2A: {} break;
    case 0x2B: {} break;
    case 0x2C: {} break;
    case 0x2D: {} break;
    case 0x2E: {} break;
    case 0x2F: {} break;

    case 0x30: {} break;
    case 0x31: {} break;
    case 0x32: {} break;
    case 0x33: {} break;
    case 0x34: {} break;
    case 0x35: {} break;
    case 0x36: {} break;
    case 0x37: {} break;
    case 0x38: {} break;
    case 0x39: {} break;
    case 0x3A: {} break;
    case 0x3B: {} break;
    case 0x3C: {} break;
    case 0x3D: {} break;
    case 0x3E: {} break;
    case 0x3F: {} break;

    case 0x40: {} break;
    case 0x41: {} break;
    case 0x42: {} break;
    case 0x43: {} break;
    case 0x44: {} break;
    case 0x45: {} break;
    case 0x46: {} break;
    case 0x47: {} break;
    case 0x48: {} break;
    case 0x49: {} break;
    case 0x4A: {} break;
    case 0x4B: {} break;
    case 0x4C: {} break;
    case 0x4D: {} break;
    case 0x4E: {} break;
    case 0x4F: {} break;

    case 0x50: {} break;
    case 0x51: {} break;
    case 0x52: {} break;
    case 0x53: {} break;
    case 0x54: {} break;
    case 0x55: {} break;
    case 0x56: {} break;
    case 0x57: {} break;
    case 0x58: {} break;
    case 0x59: {} break;
    case 0x5A: {} break;
    case 0x5B: {} break;
    case 0x5C: {} break;
    case 0x5D: {} break;
    case 0x5E: {} break;
    case 0x5F: {} break;

    case 0x60: {} break;
    case 0x61: {} break;
    case 0x62: {} break;
    case 0x63: {} break;
    case 0x64: {} break;
    case 0x65: {} break;
    case 0x66: {} break;
    case 0x67: {} break;
    case 0x68: {} break;
    case 0x69: {} break;
    case 0x6A: {} break;
    case 0x6B: {} break;
    case 0x6C: {} break;
    case 0x6D: {} break;
    case 0x6E: {} break;
    case 0x6F: {} break;

    case 0x70: {} break;
    case 0x71: {} break;
    case 0x72: {} break;
    case 0x73: {} break;
    case 0x74: {} break;
    case 0x75: {} break;
    case 0x76: {} break;
    case 0x77: {} break;
    case 0x78: {} break;
    case 0x79: {} break;
    case 0x7A: {} break;
    case 0x7B: {} break;
    case 0x7C: {} break;
    case 0x7D: {} break;
    case 0x7E: {} break;
    case 0x7F: {} break;

    case 0x80: {} break;
    case 0x81: {} break;
    case 0x82: {} break;
    case 0x83: {} break;
    case 0x84: {} break;
    case 0x85: {} break;
    case 0x86: {} break;
    case 0x87: {} break;
    case 0x88: {} break;
    case 0x89: {} break;
    case 0x8A: {} break;
    case 0x8B: {} break;
    case 0x8C: {} break;
    case 0x8D: {} break;
    case 0x8E: {} break;
    case 0x8F: {} break;

    case 0x90: {} break;
    case 0x91: {} break;
    case 0x92: {} break;
    case 0x93: {} break;
    case 0x94: {} break;
    case 0x95: {} break;
    case 0x96: {} break;
    case 0x97: {} break;
    case 0x98: {} break;
    case 0x99: {} break;
    case 0x9A: {} break;
    case 0x9B: {} break;
    case 0x9C: {} break;
    case 0x9D: {} break;
    case 0x9E: {} break;
    case 0x9F: {} break;

    case 0xA0: {} break;
    case 0xA1: {} break;
    case 0xA2: {} break;
    case 0xA3: {} break;
    case 0xA4: {} break;
    case 0xA5: {} break;
    case 0xA6: {} break;
    case 0xA7: {} break;
    case 0xA8: {} break;
    case 0xA9: {} break;
    case 0xAA: {} break;
    case 0xAB: {} break;
    case 0xAC: {} break;
    case 0xAD: {} break;
    case 0xAE: {} break;
    case 0xAF: {} break;

    case 0xB0: {} break;
    case 0xB1: {} break;
    case 0xB2: {} break;
    case 0xB3: {} break;
    case 0xB4: {} break;
    case 0xB5: {} break;
    case 0xB6: {} break;
    case 0xB7: {} break;
    case 0xB8: {} break;
    case 0xB9: {} break;
    case 0xBA: {} break;
    case 0xBB: {} break;
    case 0xBC: {} break;
    case 0xBD: {} break;
    case 0xBE: {} break;
    case 0xBF: {} break;

    case 0xC0: {} break;
    case 0xC1: {} break;
    case 0xC2: {} break;
    case 0xC3: {} break;
    case 0xC4: {} break;
    case 0xC5: {} break;
    case 0xC6: {} break;
    case 0xC7: {} break;
    case 0xC8: {} break;
    case 0xC9: {} break;
    case 0xCA: {} break;
    case 0xCB: {} break;
    case 0xCC: {} break;
    case 0xCD: {} break;
    case 0xCE: {} break;
    case 0xCF: {} break;

    case 0xD0: {} break;
    case 0xD1: {} break;
    case 0xD2: {} break;
    case 0xD3: {} break;
    case 0xD4: {} break;
    case 0xD5: {} break;
    case 0xD6: {} break;
    case 0xD7: {} break;
    case 0xD8: {} break;
    case 0xD9: {} break;
    case 0xDA: {} break;
    case 0xDB: {} break;
    case 0xDC: {} break;
    case 0xDD: {} break;
    case 0xDE: {} break;
    case 0xDF: {} break;

    case 0xE0: {} break;
    case 0xE1: {} break;
    case 0xE2: {} break;
    case 0xE3: {} break;
    case 0xE4: {} break;
    case 0xE5: {} break;
    case 0xE6: {} break;
    case 0xE7: {} break;
    case 0xE8: {} break;
    case 0xE9: {} break;
    case 0xEA: {} break;
    case 0xEB: {} break;
    case 0xEC: {} break;
    case 0xED: {} break;
    case 0xEE: {} break;
    case 0xEF: {} break;

    case 0xF0: {} break;
    case 0xF1: {} break;
    case 0xF2: {} break;
    case 0xF3: {} break;
    case 0xF4: {} break;
    case 0xF5: {} break;
    case 0xF6: {} break;
    case 0xF7: {} break;
    case 0xF8: {} break;
    case 0xF9: {} break;
    case 0xFA: {} break;
    case 0xFB: {} break;
    case 0xFC: {} break;
    case 0xFD: {} break;
    case 0xFE: {} break;
    case 0xFF: {} break;

    default:
        break;
    }
}