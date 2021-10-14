//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	input.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _INPUT_H_
#define _INPUT_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CInput
{
public:
    CInput();
    virtual ~CInput();

    virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);    //初期化関数
    virtual void Uninit(void);                               //終了関数
    virtual void Update(void) = 0;                           //更新処理

protected:
    static LPDIRECTINPUT8 m_pInput;         // DirectInputオブジェクト
    LPDIRECTINPUTDEVICE8 m_pDeviceInput;    //インプットデバイスへのポインタ
};

#endif
