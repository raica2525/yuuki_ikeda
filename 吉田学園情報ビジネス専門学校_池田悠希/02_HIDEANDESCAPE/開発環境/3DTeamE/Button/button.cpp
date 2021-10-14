//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	button.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "button.h"

#include "fade.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CButton::CButton(int nPriority) : CObject2D(nPriority)
{
    m_bSelect = false;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CButton::~CButton()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CButton::Init(void)
{
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
    CObject2D::Init();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CButton::Uninit(void)
{
    CObject2D::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CButton::Update(void)
{
    D3DXVECTOR3 pos  = GetPos();
    D3DXVECTOR3 size = GetSize();
    POINT point;
    //マウスカーソル位置取得
    GetCursorPos(&point);
    //マウスカーソル位置をクライアントの相対位置に変換
    ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
    //マウスカーソルがボタンに触れていれば
    if(point.x > pos.x - size.x / 2.0f && point.x < pos.x + size.x / 2.0f && point.y > pos.y - size.y / 2.0f && point.y < pos.y + size.y / 2.0f)
    {
        CSound* pSound = CManager::GetSound();
        //選択したときの処理
        Select();
        //前フレームで選択されていなければ
        if(!m_bSelect)
        {
            //サウンド再生
            pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
            m_bSelect = true;
        }
        //その状態でクリックされた場合の処理
        if(((CInputMouse*)CManager::GetInputMou())->GetKeyTrigger(CInputMouse::MOUSE_BUTTON_LEFT))
        {
            pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
            Push();
        }
    }
    else
    {
        //前フレームで選択されていれば
        if(m_bSelect)
        {
            //選択されていないときの処理
            m_bSelect = false;
            Unselect();
        }
    }
	CObject2D::Update();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CButton::Draw(void)
{
    CObject2D::Draw();
}
