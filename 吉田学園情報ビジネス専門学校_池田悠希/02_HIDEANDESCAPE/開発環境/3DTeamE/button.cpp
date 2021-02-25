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
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CButton::CButton(int nPriority)
  : CObject2D(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CButton::~CButton()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CButton::Init(void)
{
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
    CObject2D::Init();
    return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CButton::Uninit(void)
{
    CObject2D::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CButton::Update(void)
{
    D3DXVECTOR3 pos  = GetPos();
    D3DXVECTOR3 size = GetSize();
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
    CObject2D::Update();
    if(point.x > pos.x - size.x / 2 && point.x < pos.x + size.x / 2 && point.y > pos.y - size.y / 2 && point.y < pos.y + size.y / 2)
    {
        //大きくする処理
        Select();
        if(((CInputMouse*)CManager::GetInputMou())->GetKeyTrigger(CInputMouse::MOUSE_LEFT))
        {
            Push();
        }
    }
    else
    {
        Unselect();
    }
}

//=============================================================================
// 描画関数
//=============================================================================
void CButton::Draw(void)
{
    CObject2D::Draw();
}
