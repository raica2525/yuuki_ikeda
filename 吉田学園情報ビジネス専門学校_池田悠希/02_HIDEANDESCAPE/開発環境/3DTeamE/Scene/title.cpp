//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "title.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage01.h"
#include "titlelogo.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "tutorialbutton.h"
#include "startbutton.h"
#include "sound.h"
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_pCamera = NULL;
	m_pStage01 = NULL;
	m_pTitleLogo = NULL;
	m_pTutorialButton = NULL;
	m_pStartButton = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_TITLESTART);
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
	while (ShowCursor(true)<0);
											//�J�����I�u�W�F�N�g�̐���
	m_pCamera = new CCamera;
	//�J��������������
	m_pCamera->Init();
	//�J�����ʒu�Z�b�g
	m_pStage01 = CStage01::Create(ZEROVECTOR3, ZEROVECTOR3, D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	m_pTitleLogo = CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200, 0.0f), D3DXVECTOR3(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 500, 0.0f));
	m_pTutorialButton = CTutorialButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT - (SCREEN_HEIGHT / 4), 0.0f), D3DXVECTOR3(700, 200, 0.0f));
	m_pStartButton = CStartButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT / 4), 0.0f), D3DXVECTOR3(700, 200, 0.0f));
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	CObject::ReleaseAll();
}
