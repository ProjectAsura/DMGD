//-----------------------------------------------------------------------------
// File   : mem.cpp
// Desc   : Memory Interface.
// Author : Pocol.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <mem.h>


///////////////////////////////////////////////////////////////////////////////
// Memory class
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//      初期化処理を行います.
//-----------------------------------------------------------------------------
bool Memory::Init()
{
    if (m_Buffer != nullptr)
    { Term(); }

    m_Buffer = static_cast<uint8_t*>(malloc(0xFFFF));
    if (m_Buffer == nullptr)
    { return false; }

    m_SizeInBytes = 0xFFFF;
    memset(m_Buffer, 0, m_SizeInBytes);
    return true;
}

//-----------------------------------------------------------------------------
//      終了処理を行います.
//-----------------------------------------------------------------------------
void Memory::Term()
{
    if (m_Buffer != nullptr)
    {
        free(m_Buffer);
        m_Buffer = nullptr;
    }

    m_SizeInBytes = 0;
}

//-----------------------------------------------------------------------------
//      指定アドレスの8bitデータを読み取ります.
//-----------------------------------------------------------------------------
uint8_t Memory::Read8(uint16_t address) const
{
    assert(m_Buffer != nullptr);
    assert(address < m_SizeInBytes);
    return m_Buffer[address];
}

//-----------------------------------------------------------------------------
//      指定アドレスの16bitデータを読み取ります.
//-----------------------------------------------------------------------------
uint16_t Memory::Read16(uint16_t address) const
{
    assert(m_Buffer != nullptr);
    assert(address < m_SizeInBytes);
    uint16_t result = 0;
    memcpy(&result, m_Buffer + address, sizeof(result));
    return result;
}

//-----------------------------------------------------------------------------
//      指定アドレスに8bitデータを書き込みます.
//-----------------------------------------------------------------------------
void Memory::Write8(uint16_t address, uint8_t value)
{
    assert(m_Buffer != nullptr);
    assert(address < m_SizeInBytes);
    assert(address >= 0x8000);  // ROM領域を除く.
    m_Buffer[address] = value;
}

//-----------------------------------------------------------------------------
//      指定アドレスに16bitデータを書き込みます.
//-----------------------------------------------------------------------------
void Memory::Write16(uint16_t address, uint16_t value)
{
    assert(m_Buffer != nullptr);
    assert(address < m_SizeInBytes);
    assert(address >= 0x8000); // ROM領域を除く.
    memcpy(m_Buffer + address, &value, sizeof(value));
}

//-----------------------------------------------------------------------------
//      ROMバンク0にマウントします.
//-----------------------------------------------------------------------------
void Memory::MountRomBank0(const uint8_t* data, uint32_t sizeInBytes)
{
    assert(data != nullptr);
    assert(sizeInBytes <= 0x4000);
    memcpy(m_Buffer, data, sizeInBytes);
}

//-----------------------------------------------------------------------------
//      切り替え可能なROMバンクにマウントします.
//-----------------------------------------------------------------------------
void Memory::MountRomBank1(const uint8_t* data, uint32_t sizeInBytes)
{
    if (data == nullptr)
    { return; }

    assert(sizeInBytes <= 0x4000);
    memcpy(m_Buffer + 0x4000, data, sizeInBytes);
}