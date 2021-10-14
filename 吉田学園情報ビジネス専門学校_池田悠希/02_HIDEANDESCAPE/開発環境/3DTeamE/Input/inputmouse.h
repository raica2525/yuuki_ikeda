//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	inputmouse.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "input.h"
#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CInputMouse : public CInput
{
public:
    typedef enum
    {
        MOUSE_BUTTON_LEFT = 0,
        MOUSE_BUTTON_RIGHT,
        MOUSE_BUTTON_CENTER,
        MOUSE_BUTTON_MAX
    } MOUSE_BUTTON;

    CInputMouse();
    ~CInputMouse();

    HRESULT Init(HINSTANCE hInstance, HWND hWnd);    //初期化処理
    void Uninit(void);                               //終了処理
    void Update(void);                               //更新処理

    //状態取得用関数
    bool GetKeyPress(int nkey);
    bool GetKeyTrigger(int nkey);

private:
    DIMOUSESTATE2 m_State;    //マウスステート
};

#endif
