//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	continuebutton.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "continuebutton.h"

#include "fade.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CContinueButton::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CContinueButton::CContinueButton()
  : CButton(3)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CContinueButton::~CContinueButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CContinueButton::Load(void)
{
    CRenderer* pRenderer      = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    // テクスチャの生成
    D3DXCreateTextureFromFile(pDevice,                        // デバイスへのポインタ
                              "Data/Texture/continue.png",    // ファイルの名前
                              &m_pTexture);                   // 読み込むメモリー
    return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CContinueButton::Unload(void)
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
CContinueButton* CContinueButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CContinueButton* pRetryButton = NULL;
    pRetryButton                  = new CContinueButton;
    pRetryButton->SetPos(pos);
    pRetryButton->SetSize(size);
    pRetryButton->Init();
    return pRetryButton;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CContinueButton::Init(void)
{
    BindTexture(m_pTexture);    //テクスチャの割り当て
    CButton::Init();
    return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CContinueButton::Uninit(void)
{
    CButton::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CContinueButton::Update(void)
{
    CButton::Update();
}

//=============================================================================
// 描画関数
//=============================================================================
void CContinueButton::Draw(void)
{
    CButton::Draw();
}

void CContinueButton::Push(void)
{
    //サウンドの取得
    CSound* pSound = CManager::GetSound();
    pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
    SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	while(ShowCursor(false)>=0);
    CManager::EndPause();
}

void CContinueButton::Select(void)
{
    //サウンドの取得
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
    CSound* pSound = CManager::GetSound();
    pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
}

void CContinueButton::Unselect(void)
{
    SetCol(D3DCOLOR_RGBA(128, 128, 128, 255));
}
