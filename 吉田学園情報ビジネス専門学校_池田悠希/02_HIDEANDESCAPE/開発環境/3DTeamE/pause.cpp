//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	pause.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "pause.h"

#include "continuebutton.h"
#include "object2d.h"
#include "retrybutton.h"
#include "returntitlebutton.h"
CPause::CPause()
{
    m_pObject2d          = NULL;
    m_pReturnTitleButton = NULL;
    m_pRetryButton       = NULL;
    m_pContinueButton    = NULL;
}
CPause::~CPause()
{
}

CPause* CPause::Create(void)
{
    CPause* pPause = NULL;
    pPause         = new CPause;
    pPause->Init();
    return pPause;
}
HRESULT CPause::Init(void)
{
    while(ShowCursor(true) <0);
    m_pObject2d = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0) / 2, D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0), 3);
    m_pObject2d->SetCol(D3DCOLOR_RGBA(0, 0, 0, 128));
    m_pContinueButton    = CContinueButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0), D3DXVECTOR3(800, 200, 0));
    m_pReturnTitleButton = CReturnTitleButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 2, 0), D3DXVECTOR3(800, 200, 0));
    m_pRetryButton       = CRetryButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3, 0), D3DXVECTOR3(800, 200, 0));

    return S_OK;
}
void CPause::Uninit(void)
{
    if(m_pObject2d != NULL)
    {
        m_pObject2d->Uninit();
    }
    if(m_pReturnTitleButton != NULL)
    {
        m_pReturnTitleButton->Uninit();
    }
    if(m_pRetryButton != NULL)
    {
        m_pRetryButton->Uninit();
    }
    if(m_pContinueButton != NULL)
    {
        m_pContinueButton->Uninit();
    }
}
void CPause::Update(void)
{
    m_pObject2d->Update();
    m_pReturnTitleButton->Update();
    m_pRetryButton->Update();
    m_pContinueButton->Update();
}
void CPause::Draw(void)
{
}
