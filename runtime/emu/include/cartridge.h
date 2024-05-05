//-----------------------------------------------------------------------------
// File   : cartridge.h
// Desc   : Cartridge Data.
// Author : Pocol.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdint>


///////////////////////////////////////////////////////////////////////////////
// GBC_FLAG enum
///////////////////////////////////////////////////////////////////////////////
enum GBC_FLAG
{
    GBC_FLAG_MONOCHROME = 0x80,   //!< 無印ゲームボーイ.
    GBC_FLAG_COLOR      = 0xc0    //!< ゲームボーイカラー.
};

///////////////////////////////////////////////////////////////////////////////
// SGB_FLAG enum
///////////////////////////////////////////////////////////////////////////////
enum SGB_FLAG
{
    SGB_FLAG_GAMEBOY        = 0x00, //!< ゲームボーイ.
    SGB_FLAG_SUPER_GAME_BOY = 0x03, //!< スーパーゲームボーイ.
};

///////////////////////////////////////////////////////////////////////////////
// CARTRIDGE_TYPE enum
///////////////////////////////////////////////////////////////////////////////
enum CARTRIDGE_TYPE
{
    CARTRIDGE_ROM_ONLY                          = 0x00,
    CARTRIDGE_MBC1                              = 0x01,
    CARTRIDGE_MBC1_RAM                          = 0x02,
    CARTRIDGE_MBC1_RAM_BATTERY                  = 0x03,
    CARTRIDGE_MBC2                              = 0x05,
    CARTRIDGE_MBC2_BATTERY                      = 0x06,
    CARTRIDGE_ROM_RAM                           = 0x08,
    CARTRIDGE_ROM_RAM_BATTERY                   = 0x09,
    CARTRIDGE_MMM01                             = 0x0B,
    CARTRIDGE_MMM01_RAM                         = 0x0C,
    CARTRIDGE_MMM01_RAM_BATTERY                 = 0x0D,
    CARTRIDGE_MBC3_TIMER_BATTERY                = 0x0F,
    CARTRIDGE_MBC3_TIMER_RAM_BATTERY            = 0x10,
    CARTRIDGE_MBC3                              = 0x11,
    CARTRIDGE_MBC3_RAM                          = 0x12,
    CARTRIDGE_MBC3_RAM_BATTERY                  = 0x13,
    CARTRIDGE_MBC5                              = 0x19,
    CARTRIDGE_MBC5_RAM                          = 0x1A,
    CARTRIDGE_MBC5_RAM_BATTERY                  = 0x1B,
    CARTRIDGE_MBC5_RUMBLE                       = 0x1C,
    CARTRIDGE_MBC5_RUMBLE_RAM                   = 0x1D,
    CARTRIDGE_MBC5_RUMBLE_RAM_BATTERY           = 0x1E,
    CARTRIDGE_MBC6                              = 0x20,
    CARTRIDGE_MBC7_SENSOR_RUMBLE_RAM_BATTERY    = 0x22,
    CARTRIDGE_POCKET_CAMERA                     = 0xFC,
    CARTRIDGE_BANDAI_TAM5                       = 0xFD,
    CARTRIDGE_HUC3                              = 0xFE,
    CARTRIDGE_HUC1_RAM_BATTERY                  = 0xFF,
};

///////////////////////////////////////////////////////////////////////////////
// RAM_SIZE enum
///////////////////////////////////////////////////////////////////////////////
enum RAM_SIZE
{
    NO_RAM          = 0x00,     //!< RAM無し.
    RAM_SIZE_2KB    = 0x01,     //!< 2KB.
    RAM_SIZE_8KB    = 0x02,     //!< 8KB * 1  bank.
    RAM_SIZE_32KB   = 0x03,     //!< 8KB * 4  bank.
    RAM_SIZE_128KB  = 0x04,     //!< 8KB * 16 bank.
};

///////////////////////////////////////////////////////////////////////////////
// DESTINATION_CODE enum
///////////////////////////////////////////////////////////////////////////////
enum DESTINATION_CODE
{
    DESTINATION_JAPANESE        = 0x00, //!< 日本.
    DESTINATION_OVERSEAS_ONLY   = 0x01, //!< 海外限定.
};

///////////////////////////////////////////////////////////////////////////////
// CartridgeHeader structure
///////////////////////////////////////////////////////////////////////////////
struct CartridgeHeader
{
    uint8_t     EntryPoint[4];          //!< エントリーポイント.
    uint8_t     Logo[48];               //!< 任天堂ロゴ.
    uint8_t     Title[15];              //!< タイトル名.
    uint8_t     GBCFlag;                //!< ゲームボーイカラーフラグ.
    uint8_t     NewLicenseeCode[2];     //!< ライセンシーコード(新).
    uint8_t     SGBFlag;                //!< スーパーゲームボーイフラグ.
    uint8_t     CartridgeType;          //!< カートリッジタイプ.
    uint8_t     RomSize;                //!< ROMサイズ.
    uint8_t     RamSize;                //!< RAMサイズ.
    uint8_t     DestinationCode;        //!< リージョンコード.
    uint8_t     OldLicenseeCode;        //!< ライセンシーコード(旧).
    uint8_t     MaskRomVersion;         //!< ROMバージョン.
    uint8_t     HeaderCheckSum;         //!< ヘッダーチェックサム.
    uint8_t     GlobalCheckSum[2];      //!< グローバルチェックサム.
};

///////////////////////////////////////////////////////////////////////////////
// Cartridge structure
///////////////////////////////////////////////////////////////////////////////
struct Cartridge
{
    CartridgeHeader Header;     //!< カートリッジヘッダー.
    uint8_t         Data[1];    //!< カートリッジデータ.
};

//-----------------------------------------------------------------------------
//! @brief      カートリッジをロードします.
//! 
//! @param[in]      path        ファイルパス.
//! @param[out]     cartridge   カートリッジデータの格納先.
//! @retval true    ロードに成功.
//! @retval false   ロードに失敗.
//-----------------------------------------------------------------------------
bool LoadCartridge(const char* path, Cartridge** cartridge);

//-----------------------------------------------------------------------------
//! @brief      カートリッジデータを解放します.
//! 
//! @param[in]      cartridge   カートリッジデータ.
//-----------------------------------------------------------------------------
void UnloadCartridge(Cartridge*& cartridge);

//-----------------------------------------------------------------------------
//! @brief      ROMサイズを取得します.
//! 
//! @param[in]      cartridge   カートリッジデータ.
//! @return     ROMサイズを返却します.
//-----------------------------------------------------------------------------
uint32_t GetRomSize(const Cartridge* cartridge);

