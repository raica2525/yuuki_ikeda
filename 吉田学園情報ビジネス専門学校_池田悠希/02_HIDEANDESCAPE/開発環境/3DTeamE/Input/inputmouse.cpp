//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	inputmouse.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "inputmouse.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CInputMouse::CInputMouse()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CInputMouse::~CInputMouse()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
    CInput::Init(hInstance, hWnd);
    if(FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDeviceInput, NULL)))
    {
        return E_FAIL;
    }

    m_pDeviceInput->SetDataFormat(&c_dfDIMouse2);    //データフォーマット設定
    m_pDeviceInput->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

    DIPROPDWORD diprop;
    diprop.diph.dwSize       = sizeof(diprop);
    diprop.diph.dwHeaderSize = sizeof(diprop.diph);
    diprop.diph.dwObj        = 0;
    diprop.diph.dwHow        = DIPH_DEVICE;
    diprop.dwData            = DIPROPAXISMODE_REL;    // 相対値モードで設定
    m_pDeviceInput->SetProperty(DIPROP_AXISMODE, &diprop.diph);

    m_pDeviceInput->Acquire();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CInputMouse::Uninit(void)
{
    //入力デバイス開放
    if(m_pDeviceInput != NULL)
    {
        //キーボードのアクセス権開放
        m_pDeviceInput->Unacquire();
        m_pDeviceInput = NULL;
    }
    CInput::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CInputMouse::Update(void)
{
    for(int nCount = 0; nCount < MOUSE_BUTTON_MAX; nCount++)
    {
        m_State.rgbButtons[nCount] = 0;
    }
    m_pDeviceInput->GetDeviceState(sizeof(DIMOUSESTATE2), &m_State);

    m_pDeviceInput->Acquire();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マウスボタンの状態取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
bool CInputMouse::GetKeyPress(const int Mouse)
{
    return (m_State.rgbButtons[Mouse] & 0x80) ? true : false;
}

bool CInputMouse::GetKeyTrigger(const int nkey)
{
    //前のフレームと今のフレームが違うならtrue;
    static bool prevState[sizeof(m_State.rgbButtons) / sizeof(m_State.rgbButtons[0])];
    bool current    = GetKeyPress(nkey);
    bool ret        = current && !prevState[nkey];
    prevState[nkey] = current;
    return ret;
}
