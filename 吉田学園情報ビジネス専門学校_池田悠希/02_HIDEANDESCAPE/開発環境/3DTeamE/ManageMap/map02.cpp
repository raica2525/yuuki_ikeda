//=============================================================================
//
// �}�b�v02���� [map02.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "map02.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage02.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "goal.h"
#include "sound.h"
#include "trap.h"
#include "uav.h"
#include "light_enemy.h"
#include "item.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMap02::CMap02()
{
	bCollEnemy = false;
	m_pCamera = NULL;
	m_pStage02 = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMap02::~CMap02()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMap02::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_MAP);
	//��������p������
	bCollEnemy = false;
	//�J�����I�u�W�F�N�g�̐���
	m_pCamera = new CCamera;
	//�J��������������
	m_pCamera->Init();
	//�J�����ʒu�Z�b�g
	SetCursorPos(((int)SCREEN_WIDTH / 2), ((int)SCREEN_HEIGHT / 2));
	//�v���C���[�ʒu�Z�b�g
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-245.0f, 0.0f, 660.0f), D3DXVECTOR3(45, 180, 0), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	//�}�b�v���f���ʒu�Z�b�g
	m_pStage02 = CStage02::Create(ZEROVECTOR3, ZEROVECTOR3, D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	//�S�[���ʒu�Z�b�g
	CGoal::Create(D3DXVECTOR3(-170.0f, 50.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), D3DXCOLOR(255, 0, 0, 255), CManager::MODE_MAP03);
	//�񕜃A�C�e��
	CItem::Create(D3DXVECTOR3(0.0f, 25.0f, 155.0f), ZEROVECTOR3);
	CItem::Create(D3DXVECTOR3(-75.0f, 25.0f, -320.0f), ZEROVECTOR3);

	//�g���b�v�ʒu�Z�b�g
	CTrap::Create(D3DXVECTOR3(175.0f, 35.0f, 380.0f), D3DXVECTOR3(-30.0f, 35.0f, 380.0f));
	CTrap::Create(D3DXVECTOR3(80.0f,35.0f,270.0f), D3DXVECTOR3(-25.0f,35.0f,270.0f));
	
	CTrap::Create(D3DXVECTOR3(220.0f,35.0f,120.0f), D3DXVECTOR3(220.0f,35.0f,200.0f));
	CTrap::Create(D3DXVECTOR3(75.0f, 35.0f, -460.0f), D3DXVECTOR3(-5.0f, 35.0f, -460.0f));
	CTrap::Create(D3DXVECTOR3(-10.0f, 35.0f, -645.0f), D3DXVECTOR3(-10.0f, 35.0f, -600.0f));


	//��@�@�ʒu�Z�b�g
	//�}�b�v��
	m_pUav = CUav::Create(D3DXVECTOR3(240.0f, 0.0f, 200.f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pUav != NULL)
	{
		m_pUav->SetTour(1, D3DXVECTOR3(240.0f, 0.0f, 70.f));
		m_pUav->SetTour(2, D3DXVECTOR3(130.0f, 0.0f, 70.f));
		m_pUav->SetTour(3, D3DXVECTOR3(240.0f, 0.0f, 70.f));
	}

	//�}�b�v����
	m_pLightEnemy[0] = CLightEnemy::Create(D3DXVECTOR3(-160.0f, 0.0f, 470.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pLightEnemy[0] != NULL)
	{
		m_pLightEnemy[0]->SetTour(1, D3DXVECTOR3(-160.0f, 0.0f, 340.f));
		m_pLightEnemy[0]->SetTour(2, D3DXVECTOR3(-90.0f, 0.0f, 340.f));
		m_pLightEnemy[0]->SetTour(3, D3DXVECTOR3(-90.0f, 0.0f, 470.f));
	}

	//�}�b�v�^�񒆖ؔ����
	m_pLightEnemy[1] = CLightEnemy::Create(D3DXVECTOR3(-15.0f, 0.0f, -80.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pLightEnemy[1] != NULL)
	{
		m_pLightEnemy[1]->SetTour(1, D3DXVECTOR3(-100.0f, 0.0f, -80.f));
		m_pLightEnemy[1]->SetTour(2, D3DXVECTOR3(-100.0f, 0.0f, -195.f));
		m_pLightEnemy[1]->SetTour(3, D3DXVECTOR3(-15.0f, 0.0f, -195.f));
	}

	//�}�b�v�E���ؔ����
	m_pLightEnemy[2] = CLightEnemy::Create(D3DXVECTOR3(-60.0f, 0.0f, -450.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pLightEnemy[2] != NULL)
	{
		m_pLightEnemy[2]->SetTour(1, D3DXVECTOR3(-60.0f, 0.0f, -370.f));
		m_pLightEnemy[2]->SetTour(2, D3DXVECTOR3(-130.0f, 0.0f, -370.f));
		m_pLightEnemy[2]->SetTour(3, D3DXVECTOR3(-130.0f, 0.0f, -450.f));
	}

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CMap02::Update(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//��@�@���v���C���[�𔭌����Ă��邩
	if (m_pUav->EnemyCall() == true)
	{
		//�G�̑��������Ă��邩
		if (bCollEnemy!=true)
		{
			//���Ă��Ȃ���Βǉ�
			m_pLightEnemy[3] = CLightEnemy::Create(D3DXVECTOR3(-70.0f, 0.0f, -580.0f), ZEROVECTOR3);
			if (m_pLightEnemy[3] != NULL)
			{
				m_pLightEnemy[3]->SetTour(1, D3DXVECTOR3(-70.0f, 0.0f, -500.f));
				m_pLightEnemy[3]->SetTour(2, D3DXVECTOR3(-130.0f, 0.0f, -500.f));
				m_pLightEnemy[3]->SetTour(3, D3DXVECTOR3(-130.0f, 0.0f, -580.f));
			}
			//���������Ă���
			bCollEnemy = true;
		}

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMap02::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// �I������
//=============================================================================
void CMap02::Uninit(void)
{
	CObject::ReleaseAll();
}

