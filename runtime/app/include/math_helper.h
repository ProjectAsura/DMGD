/*
    File   : math_helper.h
    Desc   : Math Helpers.
    Author : Pocol.
*/
#ifndef MATH_HELPER_H
#define MATH_HELPER_H

/*---------------------------------------------------------------------------*/
/* Includes                                                                  */
/*---------------------------------------------------------------------------*/
#include <typedef.h>

/* 最小値を求めます. */
#ifndef MIN
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#endif

/* 最大値を求めます. */
#ifndef MAX
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#endif

/* (a, b) の範囲に制限します. */
#ifndef CLAMP
#define CLAMP(x, a, b)  MAX(a, MIN(b, x))
#endif

/* ビットを付加します. */
#ifndef APPEND_BIT
#define APPEND_BIT(x, y)    ((x) |= (y))
#endif

/* ビットを削除します. */
#ifndef REMOVE_BIT
#define REMOVE_BIT(x, y)    ((x) &= ~(y))
#endif


#endif/* MAP_HELPER_H */