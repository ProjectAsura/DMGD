//----------------------------------------------------------------------------
// File   : cpu.cpp
// Desc   : CPU(Centrol Processing Unit) Emulation.
// Author : Pocol.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cpu.h>

// Game Boy CPU Manual Page.89まで実装.


///////////////////////////////////////////////////////////////////////////////
// Cpu class.
///////////////////////////////////////////////////////////////////////////////


void Cpu::Execute()
{
    // 低電力モードの場合は実行しない.
    if (m_EnablePowerSave)
    { return; }

    // 命令をフェッチ.
    auto cmd = Read8(m_Register.PC);
    if (cmd != 0xCB)
    {
        ExecuteCommand(cmd);
    }
    else
    {
        cmd = Read8(m_Register.PC + 1);
        ExecutePrefixCommand(cmd);
    }
}

void Cpu::ExecuteCommand(uint8_t opCode)
{
    switch(opCode)
    {
    case 0x00: {} break;
    // LD BC,nn
    case 0x01:
    {
        LD(m_Register.BC, nn());
        m_ConsumedCycles += 12;
    } break;
    // LD (BC),A
    case 0x02:
    {
        Write8(GetBC(), m_Register.A);
        m_ConsumedCycles += 8;
    } break;
    case 0x03: {} break;
    // INC B
    case 0x04: 
    {
        INC(m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // DEC B
    case 0x05:
    {
        DEC(m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // LD B,n
    case 0x06: 
    {
        LD(m_Register.B, n());
        m_ConsumedCycles += 8;
    } break;
    case 0x07: {} break;
    // LD (nn),SP
    case 0x08:
    {
        Write16(nn(), m_Register.SP);
        m_ConsumedCycles += 20;
    } break;
    case 0x09: {} break;
    // LD A,(BC)
    case 0x0A:
    {
        LD(m_Register.A, Read8(GetBC()));
        m_ConsumedCycles += 8;
    } break;
    case 0x0B: {} break;
    // INC C
    case 0x0C:
    {
        INC(m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // DEC C
    case 0x0D:
    {
        DEC(m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // LD C,n
    case 0x0E:
    {
        LD(m_Register.C, n());
        m_ConsumedCycles += 8;
    } break;
    case 0x0F: {} break;

    //-------------------------------------------------------------------------

    case 0x10: {} break;
    // LD DE,nn
    case 0x11:
    {
        LD(m_Register.DE, nn());
        m_ConsumedCycles += 12;
    } break;
    // LD (DE),A
    case 0x12:
    {
        Write8(GetDE(), m_Register.A);
        m_ConsumedCycles += 8;
    } break;
    case 0x13: {} break;
    // INC D
    case 0x14:
    {
        INC(m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // DEC D
    case 0x15:
    {
        DEC(m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // LD D,n
    case 0x16:
    {
        LD(m_Register.D, n());
       m_ConsumedCycles += 8;
    } break;
    case 0x17: {} break;
    case 0x18: {} break;
    case 0x19: {} break;
    // LD A,(DE)
    case 0x1A:
    {
        LD(m_Register.A, Read8(GetDE()));
        m_ConsumedCycles += 8;
    } break;
    case 0x1B: {} break;
    // INC E
    case 0x1C:
    {
        INC(m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // DEC E
    case 0x1D:
    {
        DEC(m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // LD E,n
    case 0x1E:
    {
        LD(m_Register.E, n());
        m_ConsumedCycles += 8;
    } break;
    case 0x1F: {} break;

    case 0x20: {} break;
    // LD HL,nn
    case 0x21:
    {
        LD(m_Register.HL, nn());
        m_ConsumedCycles += 12;
    } break;
    // LDI (HL),A
    case 0x22:
    {
        Write8(GetHL(), m_Register.A);
        Inc8(GetHL());
        m_ConsumedCycles += 8;
    } break;
    case 0x23: {} break;
    // INC H
    case 0x24:
    {
        INC(m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // DEC H
    case 0x25:
    {
        DEC(m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // LD H,n
    case 0x26:
    {
        LD(m_Register.H, n());
        m_ConsumedCycles += 8;
    } break;
    case 0x27: {} break;
    case 0x28: {} break;
    case 0x29: {} break;
    // LDI A,(HL)
    case 0x2A:
    {
        LD(m_Register.A, Read8(GetHL()));
        Inc8(GetHL());
        m_ConsumedCycles +=8;
    } break;
    case 0x2B: {} break;
    // INC L
    case 0x2C:
    {
        INC(m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // DEC L
    case 0x2D:
    {
        DEC(m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // LD L,n
    case 0x2E:
    {
        LD(m_Register.L, n());
        m_ConsumedCycles += 8;
    } break;
    case 0x2F: {} break;

    //-------------------------------------------------------------------------

    case 0x30: {} break;
    case 0x31: {} break;
    // LDD (HL),A
    case 0x32: 
    {
        Write8(GetHL(), m_Register.A);
        Dec8(GetHL());
        m_ConsumedCycles += 8;
    } break;
    case 0x33: {} break;
    // INC (HL).
    case 0x34:
    {
        auto hl = Read8(m_Register.HL);
        INC(hl);
        Write8(m_Register.HL, hl);
        m_ConsumedCycles += 12;
    } break;
    // DEC (HL).
    case 0x35:
    {
        auto hl = Read8(m_Register.HL);
        DEC(hl);
        Write8(m_Register.HL, hl);
        m_ConsumedCycles += 12;
    } break;
    // LD (HL),n
    case 0x36:
    {
        Write8(GetHL(), n());
        m_ConsumedCycles += 12;
    } break;
    case 0x37: {} break;
    case 0x38: {} break;
    case 0x39: {} break;
    // LDD A,(HL)
    case 0x3A:
    {
        LD(m_Register.A, Read8(GetHL()));
        Dec8(GetHL());
        m_ConsumedCycles += 8;
    } break;
    case 0x3B: {} break;
    // INC A
    case 0x3C:
    {
        INC(m_Register.A);
        m_ConsumedCycles += 4;
    } break;
    case 0x3D: {} break;
    // LD A,#
    case 0x3E:
    {
    } break;
    case 0x3F: {} break;

    //-------------------------------------------------------------------------


    // LD B,B
    case 0x40:
    {
        LD(m_Register.B, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // LD B,C
    case 0x41:
    {
        LD(m_Register.B, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // LD B,D
    case 0x42:
    {
        LD(m_Register.B, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // LD B,E
    case 0x43:
    {
        LD(m_Register.B, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // LD B,H
    case 0x44:
    {
        LD(m_Register.B, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // LD B,L
    case 0x45:
    {
        LD(m_Register.B, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // LD B,(HL)
    case 0x46:
    {
        LD(m_Register.B, Read8(GetHL()));
        m_ConsumedCycles += 8;
    } break;
    // LD B,A
    case 0x47: 
    {
        LD(m_Register.B, m_Register.A);
        m_ConsumedCycles += 4;
    } break;
    // LD C,B
    case 0x48:
    {
        LD(m_Register.C, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // LD C,C
    case 0x49:
    {
        LD(m_Register.C, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // LD C,D
    case 0x4A:
    {
        LD(m_Register.C, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // LD C,E
    case 0x4B:
    {
        LD(m_Register.C, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // LD C,H
    case 0x4C:
    {
        LD(m_Register.C, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // LD C,L
    case 0x4D:
    {
        LD(m_Register.C, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // LD C,(HL)
    case 0x4E:
    {
        LD(m_Register.C, Read8(GetHL()));
        m_ConsumedCycles += 8;
    } break;
    // LD C,A
    case 0x4F:
    {
        LD(m_Register.C, m_Register.A);
        m_ConsumedCycles += 4;
    } break;

    //-------------------------------------------------------------------------

    // LD D,B
    case 0x50:
    {
        LD(m_Register.D, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // LD D,C
    case 0x51:
    {
        LD(m_Register.D, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // LD D,D
    case 0x52: 
    {
        LD(m_Register.D, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // LD D,E
    case 0x53:
    {
        LD(m_Register.D, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // LD D,H
    case 0x54:
    {
        LD(m_Register.D, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // LD D,L
    case 0x55:
    {
        LD(m_Register.D, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // LD D, (HL)
    case 0x56:
    {
        LD(m_Register.D, Read8(GetHL()));
        m_ConsumedCycles += 8;
    } break;
    // LD D,A
    case 0x57:
    {
        LD(m_Register.D, m_Register.A);
        m_ConsumedCycles += 4;
    } break;
    // LD E,B
    case 0x58:
    {
        LD(m_Register.E, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // LD E,C
    case 0x59:
    {
        LD(m_Register.E, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // LD E,D
    case 0x5A:
    {
        LD(m_Register.E, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // LD E,E
    case 0x5B: 
    {
        LD(m_Register.E, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // LD E,H
    case 0x5C:
    {
        LD(m_Register.E, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // LD E,L
    case 0x5D:
    {
        LD(m_Register.E, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // LD E, (HL)
    case 0x5E:
    {
        LD(m_Register.E, Read8(GetHL()));
        m_ConsumedCycles += 8;
    } break;
    // LD E,A
    case 0x5F:
    {
        LD(m_Register.E, m_Register.A);
        m_ConsumedCycles += 4;
    } break;

    //-------------------------------------------------------------------------

    // LD H,B
    case 0x60:
    {
        LD(m_Register.H, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // LD H,C
    case 0x61:
    {
        LD(m_Register.H, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // LD H,D
    case 0x62:
    {
        LD(m_Register.H, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // LD H,E
    case 0x63: 
    {
        LD(m_Register.H, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // LD H,H
    case 0x64:
    {
        LD(m_Register.H, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // LD H,L
    case 0x65:
    {
        LD(m_Register.H, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // LD H,(HL)
    case 0x66:
    {
        LD(m_Register.H, Read8(GetHL()));
        m_ConsumedCycles += 8;
    } break;
    // LD H,A
    case 0x67:
    {
        LD(m_Register.H, m_Register.A);
        m_ConsumedCycles += 4;
    } break;
    // LD L,B
    case 0x68:
    {
        LD(m_Register.L, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // LD L,C
    case 0x69:
    {
        LD(m_Register.L, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // LD L,D
    case 0x6A:
    {
        LD(m_Register.L, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // LD L,E
    case 0x6B:
    {
        LD(m_Register.L, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // LD L, H
    case 0x6C:
    {
        LD(m_Register.L, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // LD L,L
    case 0x6D:
    {
        LD(m_Register.L, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // LD L,(HL)
    case 0x6E:
    {
        LD(m_Register.L, Read8(GetHL()));
        m_ConsumedCycles += 8;
    } break;
    // LD L,A
    case 0x6F: 
    {
        LD(m_Register.L, m_Register.A);
        m_ConsumedCycles += 4;
    } break;

    //-------------------------------------------------------------------------

    // LD (HL),B
    case 0x70:
    {
        Write8(GetHL(), m_Register.B);
        m_ConsumedCycles += 8;
    } break;
    // LD (HL),C
    case 0x71:
    {
        Write8(GetHL(), m_Register.C);
        m_ConsumedCycles += 8;
    } break;
    // LD (HL),D
    case 0x72:
    {
        Write8(GetHL(), m_Register.D);
        m_ConsumedCycles += 8;
    } break;
    // LD (HL),E
    case 0x73:
    {
        Write8(GetHL(), m_Register.E);
        m_ConsumedCycles += 8;
    } break;
    // LD (HL),H
    case 0x74:
    {
        Write8(GetHL(), m_Register.H);
        m_ConsumedCycles += 8;
    } break;
    // LD (HL),L
    case 0x75:
    {
        Write8(GetHL(), m_Register.L);
        m_ConsumedCycles += 8;
    } break;
    case 0x76: {} break;
    // LD (HL),A
    case 0x77:
    {
        Write8(GetHL(), m_Register.A);
        m_ConsumedCycles += 8;
    } break;
    // LD A,B
    case 0x78:
    {
        LD(m_Register.A, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // LD A,C
    case 0x79:
    {
        LD(m_Register.A, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // LD A,D
    case 0x7A:
    {
        LD(m_Register.A, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // LD A,E
    case 0x7B:
    {
        LD(m_Register.A, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // LD A,H
    case 0x7C:
    {
        LD(m_Register.A, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // LD A,L
    case 0x7D:
    {
        LD(m_Register.A, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // LD A,(HL)
    case 0x7E:
    {
        LD(m_Register.A, Read8(GetHL()));
        m_ConsumedCycles += 8;
    } break;
    // LD A,A
    case 0x7F:
    {
        LD(m_Register.A, m_Register.A);
        m_ConsumedCycles += 4;
    } break;

    //-------------------------------------------------------------------------

    // ADD A,B
    case 0x80:
    {
        ADD(m_Register.A, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // ADD A,C
    case 0x81:
    {
        ADD(m_Register.A, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // ADD A,D
    case 0x82:
    {
        ADD(m_Register.A, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // ADD A,E
    case 0x83:
    {
        ADD(m_Register.A, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // ADD A,H
    case 0x84:
    {
        ADD(m_Register.A, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // ADD A,L
    case 0x85:
    {
        ADD(m_Register.A, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // ADD A,(HL)
    case 0x86:
    {
        ADD(m_Register.A, Read8(m_Register.HL));
        m_ConsumedCycles += 8;
    } break;
    // ADD A,A
    case 0x87:
    {
        ADD(m_Register.A, m_Register.A);
        m_ConsumedCycles += 4;
    } break;
    // ADC A,B
    case 0x88:
    {
        ADC(m_Register.A, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // ADC A,C
    case 0x89:
    {
        ADC(m_Register.A, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // ADC A,D
    case 0x8A:
    {
        ADC(m_Register.A, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // ADC A,E
    case 0x8B:
    {
        ADC(m_Register.A, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // ADC A,H
    case 0x8C:
    {
        ADC(m_Register.A, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // ADC A, L
    case 0x8D:
    {
        ADC(m_Register.A, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // ADC A,(HL)
    case 0x8E:
    {
        ADC(m_Register.A, Read8(m_Register.HL));
        m_ConsumedCycles += 8;
    } break;
    // ADC A,A
    case 0x8F:
    {
        ADC(m_Register.A, m_Register.A);
        m_ConsumedCycles += 4;
    } break;

    //-------------------------------------------------------------------------

    // SUB A,B
    case 0x90:
    {
        SUB(m_Register.A, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // SUB A,C
    case 0x91:
    {
        SUB(m_Register.A, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // SUB A,D
    case 0x92:
    {
        SUB(m_Register.A, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // SUB A,E
    case 0x93:
    {
        SUB(m_Register.A, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // SUB A,H
    case 0x94:
    {
        SUB(m_Register.A, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // SUB A,L
    case 0x95:
    {
        SUB(m_Register.A, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // SUB A,(HL)
    case 0x96:
    {
        SUB(m_Register.A, Read8(m_Register.HL));
        m_ConsumedCycles += 8;
    } break;
    // SUB A,A
    case 0x97:
    {
        SUB(m_Register.A, m_Register.A);
        m_ConsumedCycles += 4;
    } break;
    // SBC A,B
    case 0x98:
    {
        SBC(m_Register.A, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // SBC A,C
    case 0x99:
    {
        SBC(m_Register.A, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // SBC A,D
    case 0x9A:
    {
        SBC(m_Register.A, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // SBC A,E
    case 0x9B: 
    {
        SBC(m_Register.A, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // SBC A,H
    case 0x9C:
    {
        SBC(m_Register.A, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // SBC A,L
    case 0x9D:
    {
        SBC(m_Register.A, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // SBC A,(HL)
    case 0x9E:
    {
        SBC(m_Register.A, Read8(m_Register.HL));
        m_ConsumedCycles += 8;
    } break;
    // SBC A,A
    case 0x9F:
    {
        SBC(m_Register.A, m_Register.A);
        m_ConsumedCycles += 4;
    } break;

    //-------------------------------------------------------------------------

    // AND A,B
    case 0xA0:
    {
        AND(m_Register.A, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // AND A,C
    case 0xA1:
    {
        AND(m_Register.A, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // AND A,D
    case 0xA2:
    {
        AND(m_Register.A, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // AND A,E
    case 0xA3:
    {
        AND(m_Register.A, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // AND A,H
    case 0xA4:
    {
        AND(m_Register.A, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // AND A,L
    case 0xA5:
    {
        AND(m_Register.A, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // AND A,(HL)
    case 0xA6:
    {
        AND(m_Register.A, Read8(m_Register.HL));
        m_ConsumedCycles += 8;
    } break;
    // AND A,A
    case 0xA7:
    {
        AND(m_Register.A, m_Register.A);
        m_ConsumedCycles += 4;
    } break;
    // XOR A,B
    case 0xA8:
    {
        XOR(m_Register.A, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // XOR A,C
    case 0xA9:
    {
        XOR(m_Register.A, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // XOR A,D
    case 0xAA:
    {
        XOR(m_Register.A, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // XOR A,E
    case 0xAB:
    {
        XOR(m_Register.A, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // XOR A,H
    case 0xAC:
    {
        XOR(m_Register.A, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // XOR A,L
    case 0xAD:
    {
        XOR(m_Register.A, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // XOR A,(HL)
    case 0xAE:
    {
        XOR(m_Register.A, Read8(m_Register.HL));
        m_ConsumedCycles += 8;
    } break;
    case 0xAF: {} break;

    //-------------------------------------------------------------------------

    // OR A,B
    case 0xB0:
    {
        OR(m_Register.A, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // OR A,C
    case 0xB1:
    {
        OR(m_Register.A, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // OR A,D
    case 0xB2:
    {
        OR(m_Register.A, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // OR A,E
    case 0xB3:
    {
        OR(m_Register.A, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // OR A,H
    case 0xB4:
    {
        OR(m_Register.A, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // OR A,L
    case 0xB5:
    {
        OR(m_Register.A, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // OR A,(HL)
    case 0xB6:
    {
        OR(m_Register.A, Read8(m_Register.HL));
        m_ConsumedCycles += 8;
    } break;
    // OR A,A
    case 0xB7:
    {
        OR(m_Register.A, m_Register.A);
        m_ConsumedCycles += 4;
    } break;
    // CP A,B
    case 0xB8:
    {
        CP(m_Register.A, m_Register.B);
        m_ConsumedCycles += 4;
    } break;
    // CP A,C
    case 0xB9:
    {
        CP(m_Register.A, m_Register.C);
        m_ConsumedCycles += 4;
    } break;
    // CP A,D
    case 0xBA:
    {
        CP(m_Register.A, m_Register.D);
        m_ConsumedCycles += 4;
    } break;
    // CP A,E
    case 0xBB:
    {
        CP(m_Register.A, m_Register.E);
        m_ConsumedCycles += 4;
    } break;
    // CP A,H
    case 0xBC:
    {
        CP(m_Register.A, m_Register.H);
        m_ConsumedCycles += 4;
    } break;
    // CP A,L
    case 0xBD:
    {
        CP(m_Register.A, m_Register.L);
        m_ConsumedCycles += 4;
    } break;
    // CP A,(HL)
    case 0xBE:
    {
        CP(m_Register.A, Read8(m_Register.HL));
        m_ConsumedCycles += 8;
    } break;
    // CP A,A
    case 0xBF:
    {
        CP(m_Register.A, m_Register.A);
        m_ConsumedCycles += 4;
    } break;

    //-------------------------------------------------------------------------

    case 0xC0: {} break;
    // POP BC
    case 0xC1:
    {
        POP(m_Register.BC);
        m_ConsumedCycles += 12;
    } break;
    case 0xC2: {} break;
    case 0xC3: {} break;
    case 0xC4: {} break;
    // PUSH BC
    case 0xC5:
    {
        PUSH(m_Register.BC);
        m_ConsumedCycles += 16;
    } break;
    // ADD A,#
    case 0xC6:
    {
        ADD(m_Register.A, n());
        m_ConsumedCycles += 8;
    } break;
    case 0xC7: {} break;
    case 0xC8: {} break;
    case 0xC9: {} break;
    case 0xCA: {} break;
    case 0xCB: {} break;
    case 0xCC: {} break;
    case 0xCD: {} break;
    // ADC A,#
    case 0xCE:
    {
        ADC(m_Register.A, n());
        m_ConsumedCycles += 8;
    } break;
    case 0xCF: {} break;

    //-------------------------------------------------------------------------

    case 0xD0: {} break;
    // POP DE
    case 0xD1:
    {
        POP(m_Register.DE);
        m_ConsumedCycles += 12;
    } break;
    case 0xD2: {} break;
    case 0xD3: {} break;
    case 0xD4: {} break;
    // PUSH DE
    case 0xD5:
    {
        PUSH(m_Register.DE);
        m_ConsumedCycles += 16;    
    } break;
    // SUB A,#
    case 0xD6:
    {
        SUB(m_Register.A, n());
        m_ConsumedCycles += 8;
    } break;
    case 0xD7: {} break;
    case 0xD8: {} break;
    case 0xD9: {} break;
    case 0xDA: {} break;
    case 0xDB: {} break;
    case 0xDC: {} break;
    case 0xDD: {} break;
    // SBC A,#
    case 0xDE:
    {
        SBC(m_Register.A, n());
        m_ConsumedCycles += 8;
    } break;
    case 0xDF: {} break;

    //-------------------------------------------------------------------------

    // LDH (n),A
    case 0xE0:
    {
        Write8(0xFF00 + n(), m_Register.A);
        m_ConsumedCycles += 12;
    } break;
    // POP HL
    case 0xE1:
    {
        POP(m_Register.HL);
        m_ConsumedCycles += 12;
    } break;
    // LD (C),A
    case 0xE2:
    {
        Write8(0xFF + m_Register.C, m_Register.A);
        m_ConsumedCycles += 8;
    } break;
    case 0xE3: {} break;
    case 0xE4: {} break;
    // PUSH HL
    case 0xE5:
    {
        PUSH(m_Register.HL);
        m_ConsumedCycles += 16;
    } break;
    // AND A,#
    case 0xE6:
    {
        AND(m_Register.A, n());
        m_ConsumedCycles += 8;
    } break;
    case 0xE7: {} break;
    case 0xE8: {} break;
    case 0xE9: {} break;
    // LD (nn), A
    case 0xEA:
    {
        Write16(nn(), m_Register.A);
        m_ConsumedCycles += 16;
    } break;
    case 0xEB: {} break;
    case 0xEC: {} break;
    case 0xED: {} break;
    // XOR A,#
    case 0xEE:
    {
        XOR(m_Register.A, n());
        m_ConsumedCycles += 8;
    } break;
    case 0xEF: {} break;

    //-------------------------------------------------------------------------

    // LDH A,(n)
    case 0xF0:
    {
        LD(m_Register.A, Read8(0xFF00 + n()));
        m_ConsumedCycles += 12;
    } break;
    case 0xF1:
    {
        POP(m_Register.AF);
        m_ConsumedCycles += 12;
    } break;
    // LD A,(C)
    case 0xF2:
    {
        LD(m_Register.A, Read8(m_Register.C));
        m_ConsumedCycles += 8;
    } break;
    case 0xF3: {} break;
    case 0xF4: {} break;
    // PUSH AF
    case 0xF5:
    {
        PUSH(m_Register.AF);
        m_ConsumedCycles += 16;
    } break;
    // OR A,#
    case 0xF6:
    {
        OR(m_Register.A, n());
        m_ConsumedCycles += 8;
    } break;
    case 0xF7: {} break;
    // LDHL SP,n
    case 0xF8:
    {
        LDHL(m_Register.SP, n());
        m_ConsumedCycles += 12;
    } break;
    // LD SP,HL
    case 0xF9:
    {
        LD(m_Register.SP, m_Register.HL);
        m_ConsumedCycles += 8;
    } break;
    // LD A,(nn)
    case 0xFA:
    {
        LD(m_Register.A, Read8(nn()));
        m_ConsumedCycles += 16;
    } break;
    case 0xFB: {} break;
    case 0xFC: {} break;
    case 0xFD: {} break;
    // CP A,#
    case 0xFE:
    {
        CP(m_Register.A, n());
        m_ConsumedCycles += 8;
    } break;
    case 0xFF: {} break;

    //-------------------------------------------------------------------------


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

uint8_t Cpu::n() const
{ return Read8(m_Register.PC + 1); }

uint16_t Cpu::nn() const
{ return Read16(m_Register.PC + 1); }

void Cpu::Carry(uint8_t lhs, uint8_t rhs)
{
    bool carryH = (lhs & 0x0F) + (rhs & 0x0F) > 0x0F;
    bool carryC = (lhs & 0xFF) + (rhs & 0xFF) > 0xFF;
    m_Register.H = carryH;
    m_Register.C = carryC;
}

void Cpu::Borrow(uint8_t lhs, uint8_t rhs)
{
    bool borrowH = int(lhs & 0xf) - int(rhs & 0xf) < 0;
    bool borrowC = (lhs < rhs);
    m_Register.H = borrowH;
    m_Register.C = borrowC;
}

//=============================================================================
// 8-Bit Load.
//=============================================================================
void Cpu::LD(uint8_t& lhs, uint8_t rhs)
{ lhs = rhs; }

//=============================================================================
// 16-Bit Load.
//=============================================================================
void Cpu::LD(uint16_t& lhs, uint16_t rhs)
{ lhs = rhs; }

void Cpu::LDHL(uint16_t lhs, uint8_t rhs)
{
    uint16_t addr = lhs + rhs;
    SetHL(addr);
    m_Register.F.Z = 0;
    m_Register.F.N = 0;
    Carry(uint8_t(lhs), rhs);
}

void Cpu::PUSH(uint16_t value)
{
    Write16(m_Register.SP, value);
    m_Register.SP -= 2;
}

void Cpu::POP(uint16_t& value)
{
    value = Read16(m_Register.SP);
    m_Register.SP += 2;
}

//=============================================================================
// 8-Bit ALU.
//=============================================================================

void Cpu::ADD(uint8_t& lhs, uint8_t rhs)
{
    lhs += rhs;
    CheckZero(lhs);
    m_Register.F.N = 0;
    Carry(lhs, rhs);
}

void Cpu::ADC(uint8_t& lhs, uint8_t rhs)
{
    lhs += (rhs + m_Register.C);
    CheckZero(lhs);
    m_Register.F.N = 0;
    Carry(lhs, rhs + m_Register.C);
}

void Cpu::SUB(uint8_t& lhs, uint8_t rhs)
{
    lhs -= rhs;
    CheckZero(lhs);
    m_Register.F.N = 0;
    Borrow(lhs, rhs);
}

void Cpu::SBC(uint8_t& lhs, uint8_t rhs)
{
    lhs -= (rhs + m_Register.F.C);
    CheckZero(lhs);
    m_Register.F.N = 0;
    Borrow(lhs, rhs);
}

void Cpu::AND(uint8_t& lhs, uint8_t rhs)
{
    lhs = lhs & rhs;
    CheckZero(lhs);
    m_Register.F.N = 0;
    m_Register.F.H = 1;
    m_Register.F.C = 0;
}

void Cpu::OR(uint8_t& lhs, uint8_t rhs)
{
    lhs = lhs | rhs;
    CheckZero(lhs);
    m_Register.F.N = 0;
    m_Register.F.H = 0;
    m_Register.F.C = 0;
}

void Cpu::XOR(uint8_t& lhs, uint8_t rhs)
{
    lhs = lhs ^ rhs;
    CheckZero(lhs);
    m_Register.F.N = 0;
    m_Register.F.H = 0;
    m_Register.F.C = 0;
}

void Cpu::CP(uint8_t lhs, uint8_t rhs)
{
    auto ret = (lhs == rhs);
    SetFlagZ(ret);
    m_Register.F.N = 1;
    Borrow(lhs, rhs);
}

void Cpu::INC(uint8_t& val)
{
    Carry(val, 1);
    val++;
    CheckZero(val);
    m_Register.F.N = 0;
}

void Cpu::DEC(uint8_t& val)
{
    Borrow(val, 1);
    val--;
    CheckZero(val);
    m_Register.F.N = 0;
}

//=============================================================================
// 16-Bit Arithmetic.
//=============================================================================
void Cpu::ADD(uint16_t& lhs, uint16_t rhs)
{
}

void Cpu::INC(uint16_t& val)
{
}

void Cpu::DEC(uint16_t& val)
{
}


//=============================================================================
// Miscellaneous.
//=============================================================================
void Cpu::SWAP(uint8_t& lhs, uint8_t& rhs)
{
}

void Cpu::DAA()
{
}

void Cpu::CPL()
{
}

void Cpu::CCF()
{
}

void Cpu::SCF()
{
}

void Cpu::NOP()
{
}

void Cpu::HALT()
{
}

void Cpu::STOP()
{
}

void Cpu::DI()
{
}

void Cpu::EI()
{
}

//=============================================================================
// Rotates & Shifts.
//=============================================================================

void Cpu::RLCA()
{
}

void Cpu::RLA()
{
}

void Cpu::RRCA()
{
}

void Cpu::RRA()
{
}

void Cpu::RLC(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::RL(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::RRC(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::RR(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::SLA(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::SAR(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::SRL(uint8_t& lhs, uint8_t rhs)
{
}


//=============================================================================
// Bit OpCodes.
//=============================================================================
void Cpu::BIT(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::SET(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::RES(uint8_t& lhs, uint8_t rhs)
{
}

//=============================================================================
// Jumps.
//=============================================================================
void Cpu::JP(bool flag, uint8_t addr)
{
}

void Cpu::JP(bool flag, uint16_t addr)
{
}

//=============================================================================
// Calls.
//=============================================================================
void Cpu::CALL(bool flag, uint16_t addr)
{
}

//=============================================================================
// Restarts.
//=============================================================================
void Cpu::RST(uint8_t addr)
{
}

//=============================================================================
// Returns.
//=============================================================================
void Cpu::RET(bool flag)
{
}

void Cpu::RETI()
{
}
