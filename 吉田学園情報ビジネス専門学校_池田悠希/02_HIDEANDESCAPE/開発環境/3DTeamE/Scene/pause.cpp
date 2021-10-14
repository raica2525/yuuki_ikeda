//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	pause.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "pause.h"

#include "continuebutton.h"
#include "object2d.h"
#include "retrybutton.h"
#include "returntitlebutton.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define PAUSE_BUTTON_SIZE D3DXVECTOR3(800.0f, 200.0f, 0.0f)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPause::CPause()
{
    m_pObject2d          = NULL;
    m_pReturnTitleButton = NULL;
    m_pRetryButton       = NULL;
    m_pContinueButton    = NULL;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPause::~CPause()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�����֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPause* CPause::Create(void)
{
    CPause* pPause = new CPause;
    pPause->Init();
    return pPause;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�������֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPause::Update(void)
{
    m_pObject2d->Update();
    m_pReturnTitleButton->Update();
    m_pRetryButton->Update();
    m_pContinueButton->Update();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPause::Draw(void)
{
}
