//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	pause.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "pause.h"

#include "continuebutton.h"
#include "object2d.h"
#include "retrybutton.h"
#include "returntitlebutton.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define PAUSE_BUTTON_SIZE D3DXVECTOR3(800.0f, 200.0f, 0.0f)

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPause::CPause()
{
    m_pObject2d          = NULL;
    m_pReturnTitleButton = NULL;
    m_pRetryButton       = NULL;
    m_pContinueButton    = NULL;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPause::~CPause()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//生成関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPause* CPause::Create(void)
{
    CPause* pPause = new CPause;
    pPause->Init();
    return pPause;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CPause::Init(void)
{
    while(ShowCursor(true) < 0)
        ;
    m_pObject2d = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f) / 2.0f, D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), 3);
    m_pObject2d->SetCol(D3DCOLOR_RGBA(0, 0, 0, 128));
    m_pContinueButton    = CContinueButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f, 0), PAUSE_BUTTON_SIZE);
    m_pReturnTitleButton = CReturnTitleButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f * 2.0f, 0), PAUSE_BUTTON_SIZE);
    m_pRetryButton       = CRetryButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f * 3.0f, 0), PAUSE_BUTTON_SIZE);

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPause::Uninit(void)
{
    if(m_pObject2d != NULL)
    {
        m_pObject2d->Uninit();
		m_pObject2d = NULL;
    }
    if(m_pReturnTitleButton != NULL)
    {
        m_pReturnTitleButton->Uninit();
		m_pReturnTitleButton = NULL;
    }
    if(m_pRetryButton != NULL)
    {
        m_pRetryButton->Uninit();
		m_pRetryButton = NULL;
    }
    if(m_pContinueButton != NULL)
    {
        m_pContinueButton->Uninit();
		m_pContinueButton = NULL;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPause::Update(void)
{
    m_pObject2d->Update();
    m_pReturnTitleButton->Update();
    m_pRetryButton->Update();
    m_pContinueButton->Update();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPause::Draw(void)
{
}
