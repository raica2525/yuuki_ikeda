//=============================================================================
//
// �}�b�v01���� [map01.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "map01.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage01.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "goal.h"
#include "sound.h"
#include "light_enemy.h"
#include "uav.h"
#include "item.h"
#include "trap.h"
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMap01::CMap01()
{
	m_pCamera = NULL;
	m_pStage01 = NULL;
	m_pPlayer = NULL;
	bCollEnemy = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMap01::~CMap01()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMap01::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->StopSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_MAP);

											//�J�����I�u�W�F�N�g�̐���
	m_pCamera = new CCamera;
	//�J��������������
	m_pCamera->Init();
	//�J�����ʒu�Z�b�g
	SetCursorPos(((int)SCREEN_WIDTH / 2), ((int)SCREEN_HEIGHT / 2));
	//�v���C���[�Z�b�g
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(260.0f, 0.0f, -600.0f), D3DXVECTOR3(45, 180, 0), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	//�X�e�[�W�Z�b�g
	m_pStage01 = CStage01::Create(ZEROVECTOR3, ZEROVECTOR3, D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	//�S�[���Z�b�g
	CGoal::Create(D3DXVECTOR3(-100.0f, 50.0f, 650.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXCOLOR(255, 0, 0, 255), CManager::MODE_MAP02);

	//�g���b�v�Z�b�g
	CTrap::Create(D3DXVECTOR3(110.0f, 35.0f, -90.0f), D3DXVECTOR3(10.0f, 35.0f, -90.0f));
	CTrap::Create(D3DXVECTOR3(195.0f, 35.0f, 120.0f), D3DXVECTOR3(25.0f, 35.0f, 90.0f));
	CTrap::Create(D3DXVECTOR3(-120.0f, 35.0f, 580.0f), D3DXVECTOR3(-120.0f, 35.0f, 515.0f));

	//�A�C�e���Z�b�g
	CItem::Create(D3DXVECTOR3(-70.0f, 25.0f, 550.0f), ZEROVECTOR3);

	//�G�l�~�[�Z�b�g
	m_pLightEnemy[0] = CLightEnemy::Create(D3DXVECTOR3(180.0f,0.0f,-140.f), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	//����ʒu�Z�b�g
	if (m_pLightEnemy[0] != NULL)
	{
		m_pLightEnemy[0]->SetTour(1, D3DXVECTOR3(270.0f, 0.0f, -140.f));
		m_pLightEnemy[0]->SetTour(2, D3DXVECTOR3(270.0f, 0.0f, -30.f));
		m_pLightEnemy[0]->SetTour(3, D3DXVECTOR3(180.0f, 0.0f, -30.f));
	}
	//�G�l�~�[�Z�b�g
	m_pUav[0] = CUav::Create(D3DXVECTOR3(-190.0f, 0.0f, 480.f), ZEROVECTOR3);
	if (m_pUav[0] != NULL)
	{
		m_pUav[0]->SetTour(1, D3DXVECTOR3(-190.0f, 0.0f, 170.0f));
		m_pUav[0]->SetTour(2, D3DXVECTOR3(-85.0f, 0.0f, 170.0f));
		m_pUav[0]->SetTour(3, D3DXVECTOR3(-85.0f, 0.0f, 480.f));
	}

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CMap01::Update(void)
{
	//�J��������
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	if (m_pUav[0]->EnemyCall() == true)
	{
		//�G�̑��������Ă��邩
		if (bCollEnemy != true)
		{		
			//���Ă��Ȃ���Βǉ�
			m_pLightEnemy[1] = CLightEnemy::Create(D3DXVECTOR3(-30.0f, 0.0f, 650.f), ZEROVECTOR3);
			//����ʒu�Z�b�g
			if (m_pLightEnemy[1] != NULL)
			{
				m_pLightEnemy[1]->SetTour(0, D3DXVECTOR3(20.0f, 0.0f, 520.0f));

				m_pLightEnemy[1]->SetTour(1, D3DXVECTOR3(135.0f, 0.0f, 520.0f));
				m_pLightEnemy[1]->SetTour(2, D3DXVECTOR3(135.0f, 0.0f, 280.0f));

				m_pLightEnemy[1]->SetTour(3, D3DXVECTOR3(-20.0f, 0.0f, 280.f));

			}



			//���������Ă���
			bCollEnemy = true;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMap01::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// �I������
//=============================================================================
void CMap01::Uninit(void)
{
	CObject::ReleaseAll();
}
