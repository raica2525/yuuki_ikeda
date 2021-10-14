//=============================================================================
//
// ����I������ [weaponselect.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "weaponselect.h"
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
#include "assaultbutton.h"
#include "handgunbutton.h"
#include "weaponselectscene.h"
#include "sound.h"
#include "returntitlebutton.h"
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWeaponSelect::CWeaponSelect()
{
	m_pCamera = NULL;
	m_pStage01 = NULL;
	m_pTitleLogo = NULL;
	m_pTutorialButton = NULL;
	m_pStartButton = NULL;
	m_pAssaultButton = NULL;
	m_pHandgunButton = NULL;
	m_pWeaponSelectScene = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWeaponSelect::~CWeaponSelect()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWeaponSelect::Init(void)
{
											//�J�����I�u�W�F�N�g�̐���
	m_pCamera = new CCamera;
	//�J��������������
	m_pCamera->Init();
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->StopSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_WEAPONSELECT);
	//�J�����ʒu�Z�b�g
	m_pWeaponSelectScene = CWeaponSelectScene::Create(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pAssaultButton = CAssaultButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT - (SCREEN_HEIGHT / 4) - 100, 0.0f), D3DXVECTOR3(700, 600, 0.0f));
	m_pHandgunButton = CHandgunButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT / 4) - 100, 0.0f), D3DXVECTOR3(700, 600, 0.0f));
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CWeaponSelect::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CWeaponSelect::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// �I������
//=============================================================================
void CWeaponSelect::Uninit(void)
{
	CObject::ReleaseAll();
}
