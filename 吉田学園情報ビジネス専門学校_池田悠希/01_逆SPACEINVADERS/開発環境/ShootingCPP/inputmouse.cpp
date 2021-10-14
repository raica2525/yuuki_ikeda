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
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
bool CInputMouse::m_bPrevState[4];
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
	//入力デバイスの生成
    if(FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDeviceInput, NULL)))
    {
        return E_FAIL;
    }
	//データ・フォーマット生成
	if (FAILED(m_pDeviceInput->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}
	//協調レベル設定
	if (FAILED(m_pDeviceInput->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}
	//軸モード設定
    DIPROPDWORD diprop;
    diprop.diph.dwSize       = sizeof(diprop);
    diprop.diph.dwHeaderSize = sizeof(diprop.diph);
    diprop.diph.dwObj        = 0;
    diprop.diph.dwHow        = DIPH_DEVICE;
    diprop.dwData = DIPROPAXISMODE_REL;
    m_pDeviceInput->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	//アクセス権取得
    m_pDeviceInput->Acquire();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
    if(m_pDeviceInput != NULL)
    {
		//アクセス権開放
        m_pDeviceInput->Unacquire();
		m_pDeviceInput->Release();
        m_pDeviceInput = NULL;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CInputMouse::Update(void)
{
	//状態初期化
    for(int nCount = 0; nCount < sizeof(m_State.rgbButtons) / sizeof(m_State.rgbButtons[0]); nCount++)
    {
        m_State.rgbButtons[nCount] = 0;
    }
	//状態取得
    m_pDeviceInput->GetDeviceState(sizeof(DIMOUSESTATE2), &m_State);
	//アクセス権取得
	m_pDeviceInput->Acquire();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//状態取得処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
bool CInputMouse::GetKeyPress(int nkey)
{
    return (m_State.rgbButtons[nkey] & 0x80) ? true : false;
}

bool CInputMouse::GetKeyTrigger(int nkey)
{
	//現在の情報保存
    bool current = GetKeyPress(nkey);
	//前フレームと現在のマウスの状態が同じか違うか
    bool ret = current && !m_bPrevState[nkey];
	//現在のフレームの情報を保存
	m_bPrevState[nkey] = current;
    return ret;
}
