//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	inputkeyboard.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "input.h"
#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define NUM_KEY_MAX (256)    //キーボードの最大数

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CInputKeyboard : public CInput
{
public:
    CInputKeyboard();
    ~CInputKeyboard();

    HRESULT Init(HINSTANCE hInstance, HWND hWnd);    //初期化処理
    void Uninit(void);                               //終了処理
    void Update(void);                               //更新処理

    //キー状態取得関数
    bool GetKeyPress(int nkey);
    bool GetKeyTrigger(int nkey);
    bool GetKeyRelease(int nkey);

private:
    //キー状態保存用
    BYTE m_aState[NUM_KEY_MAX];
    BYTE m_aStateTrigger[NUM_KEY_MAX];
    BYTE m_aStateRelease[NUM_KEY_MAX];
};

#endif
