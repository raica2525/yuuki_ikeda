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
#include "sound.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CReturnTitleButton::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CReturnTitleButton::CReturnTitleButton()
  : CButton(3)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CReturnTitleButton::~CReturnTitleButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CReturnTitleButton::Load(void)
{
    CRenderer* pRenderer      = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    // テクスチャの生成
    D3DXCreateTextureFromFile(pDevice,                      // デバイスへのポインタ
                              "Data/Texture/GiveUp.png",    // ファイルの名前
                              &m_pTexture);                 // 読み込むメモリー
    return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CReturnTitleButton::Unload(void)
{
    // テクスチャの破棄
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//=============================================================================
// 生成関数
//=============================================================================
CReturnTitleButton* CReturnTitleButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CReturnTitleButton* pReturnTitleButton = NULL;
    pReturnTitleButton                     = new CReturnTitleButton;
    pReturnTitleButton->SetPos(pos);
    pReturnTitleButton->SetSize(size);
    pReturnTitleButton->Init();

    return pReturnTitleButton;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CReturnTitleButton::Init(void)
{
    BindTexture(m_pTexture);    //テクスチャの割り当て
    CButton::Init();
    return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CReturnTitleButton::Uninit(void)
{
    CButton::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CReturnTitleButton::Update(void)
{
    CButton::Update();
}

//=============================================================================
// 描画関数
//=============================================================================
void CReturnTitleButton::Draw(void)
{
    CButton::Draw();
}

void CReturnTitleButton::Push(void)
{
    //サウンドの取得
    CSound* pSound = CManager::GetSound();
    pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
    CManager::GetFade()->SetFade(CManager::MODE_TITLE);
}

void CReturnTitleButton::Select(void)
{
    //サウンドの取得
    CSound* pSound = CManager::GetSound();
    pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
}

void CReturnTitleButton::Unselect(void)
{
    SetCol(D3DCOLOR_RGBA(128, 128, 128, 255));
}
