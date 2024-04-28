//-----------------------------------------------------------------------------
// File   : cartridge.cpp
// Desc   : Cartridge Data.
// Author : Pocol.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cartridge.h>


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define CARTRIDGE_HEADER_OFFSET  0x100 // ヘッダーまでのオフセット.


namespace {

//-----------------------------------------------------------------------------
// Constant Values.
//-----------------------------------------------------------------------------
static constexpr uint8_t kNintendoLogo[48] = {
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
};

//=== サイズチェック ===.
static_assert(sizeof(CartridgeHeader) == 0x50); // 0x100 - 0x14F.

} // namespace

//-----------------------------------------------------------------------------
//      カートリッジを読み込みます.
//-----------------------------------------------------------------------------
bool LoadCartridge(const char* path, Cartridge** cartridge)
{
    assert(path != nullptr);
    assert(*cartridge != nullptr);

    FILE* fp = nullptr;
    auto err = fopen_s(&fp, path, "rb");
    if (err != 0)
    {
        printf_s("Error : Load Cartridge Failed. path = %s\n", path);
        return false;
    }

    fseek(fp, CARTRIDGE_HEADER_OFFSET, SEEK_SET);
    auto cur = ftell(fp);
    fseek(fp, 0, SEEK_END);
    auto end = ftell(fp);
    fseek(fp, CARTRIDGE_HEADER_OFFSET, SEEK_SET);

    auto size = end - cur;
    assert(size > 0);

    auto buf = static_cast<uint8_t*>(malloc(size));
    if (buf == nullptr)
    {
        fclose(fp);
        printf_s("Error : Out of Memory.\n");
        return false;
    }

    auto rom = reinterpret_cast<Cartridge*>(buf);
    assert(rom != nullptr);

    fread(rom, size, 1, fp);
    fclose(fp);

    // ロゴチェック.
    if (memcmp(rom->Header.Logo, kNintendoLogo, sizeof(kNintendoLogo) != 0))
    {
        printf_s("Error : Invalid Cartridge Data.");
        UnloadCartridge(rom);
        return false;
    }

    // チェックサム.
    {
        uint8_t checkSum = 0;
        for(uint8_t i=0x34; i<=0x4C; ++i)
        { checkSum = checkSum - buf[i] - 1; }

        if (checkSum != rom->Header.HeaderCheckSum)
        {
            printf_s("Error : Invalid Header Check Sum.\n");
            UnloadCartridge(rom);
            return false;
        }
    }

    // ROMサイズをチェック.
    auto romSize = GetRomSize(rom);
    if (romSize != (size + CARTRIDGE_HEADER_OFFSET))
    {
        printf_s("Error : Rom Size Not Match.\n");
        UnloadCartridge(rom);
        return false;
    }

    // 読み取りデータを格納.
    (*cartridge) = rom;

    // 正常終了.
    return true;
}

//-----------------------------------------------------------------------------
//      カートリッジデータを解放します.
//-----------------------------------------------------------------------------
void UnloadCartridge(Cartridge*& cartridge)
{
    if (cartridge == nullptr)
        return;

    free(cartridge);
    cartridge = nullptr;
}

//-----------------------------------------------------------------------------
//      ROMサイズを取得します.
//-----------------------------------------------------------------------------
uint32_t GetRomSize(const Cartridge* cartridge)
{
    assert(cartridge != nullptr);
    return 32 * 1024 * (1 << cartridge->Header.RomSize);
}

