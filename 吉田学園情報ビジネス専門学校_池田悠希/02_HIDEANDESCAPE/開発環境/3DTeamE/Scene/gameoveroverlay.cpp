//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	gameoveroverlay.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "gameoveroverlay.h"

#include "manager.h"
#include "object2d.h"
#include "retrybutton.h"
#include "returntitlebutton.h"
#include "sound.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CGameoverOverlay::CGameoverOverlay()
{
    m_nBackgroundAlpha   = 0;
    m_pObject2d          = NULL;
    m_pReturnTitleButton = NULL;
    m_pRetryButton       = NULL;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CGameoverOverlay::~CGameoverOverlay()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//生成関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CGameoverOverlay* CGameoverOverlay::Create(void)
{
    CGameoverOverlay* pGameoverOverlay = new CGameoverOverlay;
    pGameoverOverlay->Init();
    return pGameoverOverlay;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CGameoverOverlay::Init(void)
{
    while(ShowCursor(true) < 0);
    m_pObject2d = CObject2D::Create(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0) / 2, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0), 3);
    m_pObject2d->SetCol(D3DCOLOR_RGBA(0, 0, 0, 0));
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CGameoverOverlay::Uninit(void)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CGameoverOverlay::Update(void)
{
    if(m_nBackgroundAlpha++ < 128)
    {
        m_pObject2d->SetCol(D3DCOLOR_RGBA(0, 0, 0, m_nBackgroundAlpha));
    }
    else if(m_pReturnTitleButton == NULL && m_pRetryButton == NULL)
    {
        //サウンドの取得
        CSound* pSound = CManager::GetSound();
        pSound->StopSound();
        pSound->PlaySound(CSound::SOUND_LABEL_BGM_CONTINUE);
        m_pReturnTitleButton = CReturnTitleButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4.0f * 3.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(800.0f, 200.0f, 0.0f));
        m_pRetryButton       = CRetryButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(800.0f, 200.0f, 0.0f));
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CGameoverOverlay::Draw(void)
{
}
