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
bool Frame(void);

/* メインエントリーポイント. */
void main(void)
{
    DISPLAY_OFF;

    Init();
    SHOW_BKG;
    DISPLAY_ON;

    while(true)
    {
        if (Frame())
        { vsync(); }
    }
}

/* 初期化処理. */
void Init(void)
{

}

/* フレーム処理. 再描画が必要な場合は true を返却. */
bool Frame(void)
{
    return true;
}
