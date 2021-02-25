//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	gameoveroverlay.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "gameoveroverlay.h"

#include "manager.h"
#include "object2d.h"
#include "retrybutton.h"
#include "returntitlebutton.h"
#include "sound.h"

CGameoverOverlay::CGameoverOverlay()
{
    m_nBackgroundAlpha   = 0;
    m_pObject2d          = NULL;
    m_pReturnTitleButton = NULL;
    m_pRetryButton       = NULL;
}
CGameoverOverlay::~CGameoverOverlay()
{
}

CGameoverOverlay* CGameoverOverlay::Create(void)
{
    CGameoverOverlay* pGameoverOverlay = NULL;
    pGameoverOverlay                   = new CGameoverOverlay;
    pGameoverOverlay->Init();
    return pGameoverOverlay;
}
HRESULT CGameoverOverlay::Init(void)
{
    while(ShowCursor(true)<0);
    m_pObject2d = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0) / 2, D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0), 3);
    m_pObject2d->SetCol(D3DCOLOR_RGBA(0, 0, 0, 0));
    return S_OK;
}
void CGameoverOverlay::Uninit(void)
{
}
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
        m_pReturnTitleButton = CReturnTitleButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 2, 0), D3DXVECTOR3(800, 200, 0));
        m_pRetryButton       = CRetryButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0), D3DXVECTOR3(800, 200, 0));
    }
}
void CGameoverOverlay::Draw(void)
{
}
