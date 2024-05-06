//-----------------------------------------------------------------------------
// File   : mem.h
// Desc   : Memory Interface.
// Author : Pocol.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdint>


///////////////////////////////////////////////////////////////////////////////
// Memory class
///////////////////////////////////////////////////////////////////////////////
class Memory
{
public:
    Memory() = default;
    ~Memory() = default;

    bool Init();
    void Term();

    uint8_t  Read8 (uint16_t address) const;
    uint16_t Read16(uint16_t address) const;

    void Write8 (uint16_t address, uint8_t  value);
    void Write16(uint16_t address, uint16_t value);

    void MountRomBank0(const uint8_t* data, uint32_t sizeInBytes);
    void MountRomBank1(const uint8_t* data, uint32_t sizeInBytes);

    const uint8_t* GetBuffer() const { return m_Buffer; }

private:
    uint8_t*    m_Buffer        = nullptr;
    uint32_t    m_SizeInBytes   = 0;
};

