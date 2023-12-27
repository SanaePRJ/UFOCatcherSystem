/*--------------------------------------------------------------------------
* Name   : CommonDef.h
* Ver    : Beta
* Author : SanaePRJ
--------------------------------------------------------------------------*/


/*INCLUDE GUARD*/
#ifndef SANAE_COMMONDEF_H
#define SANAE_COMMONDEF_H


//Pin指定用
using Pin = uint8_t;

//ユーザ定義リテラル 秒->ミリ秒
unsigned long long operator"" s(unsigned long long msecond){
    return msecond * 1e3;
}


#endif