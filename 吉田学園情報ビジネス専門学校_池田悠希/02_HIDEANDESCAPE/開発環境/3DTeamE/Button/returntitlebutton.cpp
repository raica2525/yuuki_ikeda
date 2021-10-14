//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	returntitlebutton.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "returntitlebutton.h"

#include "fade.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CReturnTitleButton::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CReturnTitleButton::CReturnTitleButton() : CButton(3)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CReturnTitleButton::~CReturnTitleButton()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ読み込み関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CReturnTitleButton::Load(void)
{
    // テクスチャの生成
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Data/Texture/GiveUp.png", &m_pTexture);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ破棄関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CReturnTitleButton::Unload(void)
{
    // テクスチャの破棄
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//生成関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CReturnTitleButton* CReturnTitleButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
    CReturnTitleButton* pReturnTitleButton = new CReturnTitleButton;
    pReturnTitleButton->SetPos(pos);
    pReturnTitleButton->SetSize(size);
    pReturnTitleButton->Init();

    return pReturnTitleButton;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CReturnTitleButton::Init(void)
{
    BindTexture(m_pTexture);    //テクスチャの割り当て
    CButton::Init();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//押されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CReturnTitleButton::Push(void)
{
    //タイトル画面に移行
    CManager::GetFade()->SetFade(CManager::MODE_TITLE);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CReturnTitleButton::Select(void)
{
    //明るくする
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されていないときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CReturnTitleButton::Unselect(void)
{
    //暗くする
    SetCol(D3DCOLOR_RGBA(128, 128, 128, 255));
}
