//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	gameoveroverlay.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "gameoveroverlay.h"

#include "manager.h"
#include "object2d.h"
#include "retrybutton.h"
#include "returntitlebutton.h"
#include "sound.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CGameoverOverlay::CGameoverOverlay()
{
    m_nBackgroundAlpha   = 0;
    m_pObject2d          = NULL;
    m_pReturnTitleButton = NULL;
    m_pRetryButton       = NULL;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CGameoverOverlay::~CGameoverOverlay()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�����֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CGameoverOverlay* CGameoverOverlay::Create(void)
{
    CGameoverOverlay* pGameoverOverlay = new CGameoverOverlay;
    pGameoverOverlay->Init();
    return pGameoverOverlay;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�������֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CGameoverOverlay::Init(void)
{
    while(ShowCursor(true) < 0);
    m_pObject2d = CObject2D::Create(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0) / 2, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0), 3);
    m_pObject2d->SetCol(D3DCOLOR_RGBA(0, 0, 0, 0));
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CGameoverOverlay::Uninit(void)
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CGameoverOverlay::Update(void)
{
    if(m_nBackgroundAlpha++ < 128)
    {
        m_pObject2d->SetCol(D3DCOLOR_RGBA(0, 0, 0, m_nBackgroundAlpha));
    }
    else if(m_pReturnTitleButton == NULL && m_pRetryButton == NULL)
    {
        //�T�E���h�̎擾
        CSound* pSound = CManager::GetSound();
        pSound->StopSound();
        pSound->PlaySound(CSound::SOUND_LABEL_BGM_CONTINUE);
        m_pReturnTitleButton = CReturnTitleButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4.0f * 3.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(800.0f, 200.0f, 0.0f));
        m_pRetryButton       = CRetryButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(800.0f, 200.0f, 0.0f));
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CGameoverOverlay::Draw(void)
{
}
