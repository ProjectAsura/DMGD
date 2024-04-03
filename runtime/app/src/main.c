/*---------------------------------------------------------------------------*/
/*  Includes                                                                 */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <typedef.h>
#include <gb/gb.h>



/*---------------------------------------------------------------------------*/
/*  Forward Declarations                                                     */
/*---------------------------------------------------------------------------*/
void Init(void);
void Frame(void);

/* メインエントリーポイント. */
void main(void)
{
    DISPLAY_OFF;

    Init();
    SHOW_BKG;
    DISPLAY_ON;

    while(true)
    {
        g_JoyPad = joypad();
        Frame();
        vsync();
    }
}

/* 初期化処理. */
void Init(void)
{

}

/* フレーム処理. */
void Frame(void)
{

}
