//----------------------------------------------------------------------------
// File   : cpu.cpp
// Desc   : CPU(Centrol Processing Unit) Emulation.
// Author : Pocol.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cpu.h>

// Game Boy CPU Manual Page.75まで実装.


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
    case 0x01: {} break;
    // LD (BC),A
    case 0x02:
    {
        Write8(GetBC(), m_Register.A);
        m_ConsumedCycles += 8;
    } break;
    case 0x03: {} break;
    case 0x04: {} break;
    case 0x05: {} break;
    // LD B,n
    case 0x06: 
    {
        LD(m_Register.B, n());
        m_ConsumedCycles += 8;
    } break;
    case 0x07: {} break;
    case 0x08: {} break;
    case 0x09: {} break;
    // LD A,(BC)
    case 0x0A:
    {
        LD(m_Register.A, Read8(GetBC()));
        m_ConsumedCycles += 8;
    } break;
    case 0x0B: {} break;
    case 0x0C: {} break;
    case 0x0D: {} break;
    // LD C,n
    case 0x0E:
    {
        LD(m_Register.C, n());
        m_ConsumedCycles += 8;
    } break;
    case 0x0F: {} break;

    //-------------------------------------------------------------------------

    case 0x10: {} break;
    case 0x11: {} break;
    // LD (DE),A
    case 0x12:
    {
        Write8(GetDE(), m_Register.A);
        m_ConsumedCycles += 8;
    } break;
    case 0x13: {} break;
    case 0x14: {} break;
    case 0x15: {} break;
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
    case 0x1C: {} break;
    case 0x1D: {} break;
    // LD E,n
    case 0x1E:
    {
        LD(m_Register.E, n());
        m_ConsumedCycles += 8;
    } break;
    case 0x1F: {} break;

    case 0x20: {} break;
    case 0x21: {} break;
    // LDI (HL),A
    case 0x22:
    {
        Write8(GetHL(), m_Register.A);
        Inc8(GetHL());
        m_ConsumedCycles += 8;
    } break;
    case 0x23: {} break;
    case 0x24: {} break;
    case 0x25: {} break;
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
    case 0x2C: {} break;
    case 0x2D: {} break;
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
    case 0x34: {} break;
    case 0x35: {} break;
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
    case 0x3C: {} break;
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

    //-------------------------------------------------------------------------

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

    //-------------------------------------------------------------------------

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

    //-------------------------------------------------------------------------

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

    //-------------------------------------------------------------------------

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

    //-------------------------------------------------------------------------

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

    //-------------------------------------------------------------------------

    // LDH (n),A
    case 0xE0:
    {
        Write8(0xFF00 + n(), m_Register.A);
        m_ConsumedCycles +=12;
    } break;
    case 0xE1: {} break;
    // LD (C),A
    case 0xE2:
    {
        Write8(0xFF + m_Register.C, m_Register.A);
        m_ConsumedCycles += 8;
    } break;
    case 0xE3: {} break;
    case 0xE4: {} break;
    case 0xE5: {} break;
    case 0xE6: {} break;
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
    case 0xEE: {} break;
    case 0xEF: {} break;

    //-------------------------------------------------------------------------

    // LDH A,(n)
    case 0xF0:
    {
        LD(m_Register.A, Read8(0xFF00 + n()));
        m_ConsumedCycles += 12;
    } break;
    case 0xF1: {} break;
    // LD A,(C)
    case 0xF2:
    {
        LD(m_Register.A, Read8(m_Register.C));
        m_ConsumedCycles += 8;
    } break;
    case 0xF3: {} break;
    case 0xF4: {} break;
    case 0xF5: {} break;
    case 0xF6: {} break;
    case 0xF7: {} break;
    case 0xF8: {} break;
    case 0xF9: {} break;
    // LD A,(nn)
    case 0xFA:
    {
        LD(m_Register.A, Read8(nn()));
        m_ConsumedCycles += 16;
    } break;
    case 0xFB: {} break;
    case 0xFC: {} break;
    case 0xFD: {} break;
    case 0xFE: {} break;
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

void Cpu::LDHL(uint16_t addr)
{
}

void Cpu::PUSH(uint16_t value)
{
}

void Cpu::POP(uint16_t value)
{
}

//=============================================================================
// 8-Bit ALU.
//=============================================================================

void Cpu::ADD(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::ADC(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::SUB(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::SBC(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::AND(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::OR(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::XOR(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::CP(uint8_t& lhs, uint8_t rhs)
{
}

void Cpu::INC(uint8_t& val)
{
}

void Cpu::DEC(uint8_t& val)
{
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
