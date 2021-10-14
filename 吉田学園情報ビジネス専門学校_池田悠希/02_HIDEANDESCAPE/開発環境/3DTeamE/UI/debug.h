//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	debug.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _DEBUG_H_
#define _DEBUG_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CDebug
{
public:
    CDebug();
    ~CDebug();

    static HRESULT Init(void);            //初期化処理
    static void Uninit(void);             //終了処理
    static void Print(char* fmt, ...);    //表示内容変更
    static void Draw(void);               //描画処理

private:
    static LPD3DXFONT m_pFont;    // フォントへのポインタ
    static char m_str[512];       //表示する文字列
};

#endif
