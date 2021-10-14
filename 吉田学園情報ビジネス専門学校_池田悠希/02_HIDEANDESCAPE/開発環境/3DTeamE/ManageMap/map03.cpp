//=============================================================================
//
// �}�b�v03���� [map03.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "map03.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage03.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "goal.h"
#include "sound.h"
#include "item.h"
#include "handgunbutton.h"
#include "light_enemy.h"
#include "uav.h"
#include "trap.h"
#include "heavy_enemy.h"
//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMap03::CMap03()
{
	m_pCamera = NULL;
	m_pStage03 = NULL;
	m_pObstacle = NULL;


	m_pUav[3] = {};
	m_pLightEnemy[6] = {}; 
	m_pHeavyEnemy[1] = {};
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMap03::~CMap03()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMap03::Init(void)
{
	//�T�E���h�̎擾
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_MAP);
	for (int nCount = 0; nCount < 3; nCount++)
	{
		bCollEnemy[nCount] = false;
	}

	//�J�����I�u�W�F�N�g�̐���
	m_pCamera = new CCamera;
	//�J��������������
	m_pCamera->Init();
	//�J�����ʒu�Z�b�g
	SetCursorPos(((int)SCREEN_WIDTH / 2), ((int)SCREEN_HEIGHT / 2));
	//�v���C���[�̈ʒu�Z�b�g
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-700.0f, 0.0f, -425.0f), D3DXVECTOR3(45, 180, 0), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	//�X�e�[�W���f���ݒu

	m_pStage03 = CStage03::Create(ZEROVECTOR3, ZEROVECTOR3, D3DXVECTOR3(1.7f, 1.7f, 1.7f));

	//�S�[���ݒu
	CGoal::Create(D3DXVECTOR3(635.0f, 50.0f, 435.0f), D3DXVECTOR3(0.0f, 10.0f, -1.0f), D3DXVECTOR3(85.0f, 100.0f, 85.0f), D3DXCOLOR(255, 0, 0, 255), CManager::MODE_MAP04);
	
	//�A�C�e���ݒu
	CItem::Create(D3DXVECTOR3(280.0f, 25.0f, -320.0f), ZEROVECTOR3);
	CItem::Create(D3DXVECTOR3(-10.0f, 25.0f, -20.0f), ZEROVECTOR3);

	//�g���b�v�ݒu
	CTrap::Create(D3DXVECTOR3(-615.0f, 35.0f, -240.0f), D3DXVECTOR3(-500.0f, 35.0f, -240.0f));
	CTrap::Create(D3DXVECTOR3(-400.0f, 35.0f, -135.0f), D3DXVECTOR3(-400.0f, 35.0f, -55.0f));
	CTrap::Create(D3DXVECTOR3(-520.0f, 35.0f, 135.0f), D3DXVECTOR3(-520.0f, 35.0f, 200.0f));
	CTrap::Create(D3DXVECTOR3(-390.0f, 35.0f, 135.0f), D3DXVECTOR3(-390.0f, 35.0f, 200.0f));
	CTrap::Create(D3DXVECTOR3(80.0f, 35.0f, -10.0f), D3DXVECTOR3(80.0f, 35.0f, 80.0f));

	//��@�@�ݒu�i�@�j
	m_pUav[0] = CUav::Create(D3DXVECTOR3(-500.0f, 0.0f, -115.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pUav != NULL)
	{
		m_pUav[0]->SetTour(1, D3DXVECTOR3(-500.0f, 0.0f, -200.0f));
		m_pUav[0]->SetTour(2, D3DXVECTOR3(-430.0f, 0.0f, -200.0f));
		m_pUav[0]->SetTour(3, D3DXVECTOR3(-430.0f, 0.0f, -115.0f));
	}
	//��@�@�ݒu�i�A�j
	m_pUav[1] = CUav::Create(D3DXVECTOR3(-180.0f, 0.0f, 120.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pUav != NULL)
	{
		m_pUav[1]->SetTour(1, D3DXVECTOR3(-240.0f, 0.0f, 120.0f));
		m_pUav[1]->SetTour(2, D3DXVECTOR3(-240.0f, 0.0f, 60.0f));
		m_pUav[1]->SetTour(3, D3DXVECTOR3(-180.0f, 0.0f, 60.0f));
	}
	//��@�@�ݒu�i�B�j
	m_pUav[2] = CUav::Create(D3DXVECTOR3(-180.0f, 0.0f, -430.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pUav != NULL)
	{
		m_pUav[2]->SetTour(1, D3DXVECTOR3(-110.0f, 0.0f, -430.0f));
		m_pUav[2]->SetTour(2, D3DXVECTOR3(-110.0f, 0.0f, -360.0f));
		m_pUav[2]->SetTour(3, D3DXVECTOR3(-180.0f, 0.0f, -360.0f));
	}

	//�y���G�l�~�[�ݒu(���̃S�[���t��)
	m_pLightEnemy[0] = CLightEnemy::Create(D3DXVECTOR3(-320.0f, 0.0f, -430.0f) , ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pLightEnemy[0] != NULL)
	{
		m_pLightEnemy[0]->SetTour(1, D3DXVECTOR3(-250.0f, 0.0f, -430.0f));
		m_pLightEnemy[0]->SetTour(2, D3DXVECTOR3(-250.0f, 0.0f, -370.0f));
		m_pLightEnemy[0]->SetTour(3, D3DXVECTOR3(-320.0f, 0.0f, -370.0f));
	}

	//�y���G�l�~�[�ݒu(���̒����)
	m_pLightEnemy[1] = CLightEnemy::Create(D3DXVECTOR3(-20.0f, 0.0f, -290.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pLightEnemy[1] != NULL)
	{
		m_pLightEnemy[1]->SetTour(1, D3DXVECTOR3(-20.0f, 0.0f, -350.0f));
		m_pLightEnemy[1]->SetTour(2, D3DXVECTOR3(45.0f, 0.0f, -350.0f));
		m_pLightEnemy[1]->SetTour(3, D3DXVECTOR3(45.0f, 0.0f, -290.0f));
	}

	//�y���G�l�~�[�ݒu(��̓S�����)
	m_pLightEnemy[2] = CLightEnemy::Create(D3DXVECTOR3(-345.0f, 0.0f, 95.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pLightEnemy[2] != NULL)
	{
		m_pLightEnemy[2]->SetTour(1, D3DXVECTOR3(-410.0f, 0.0f, 95.0f));
		m_pLightEnemy[2]->SetTour(2, D3DXVECTOR3(-410.0f, 0.0f, 5.0f));
		m_pLightEnemy[2]->SetTour(3, D3DXVECTOR3(-345.0f, 0.0f, 5.0f));
	}

	//�d���G�l�~�[�ݒu
	m_pHeavyEnemy[0] = CHeavyEnemy::Create(D3DXVECTOR3(270.0f, 0.0f, -145.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pHeavyEnemy[0] != NULL)
	{
		m_pHeavyEnemy[0]->SetTour(1, D3DXVECTOR3(165.0f, 0.0f, -145.0f));
		m_pHeavyEnemy[0]->SetTour(2, D3DXVECTOR3(165.0f, 0.0f, -205.0f));
		m_pHeavyEnemy[0]->SetTour(3, D3DXVECTOR3(270.0f, 0.0f, -205.0f));
	}

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CMap03::Update(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//��@�@(1)���v���C���[�𔭌����Ă��邩
	if (m_pUav[0]->EnemyCall() == true)
	{
		//�G�̑��������Ă��邩
		if (bCollEnemy[0] != true)
		{
			//���Ă��Ȃ���Βǉ�
			m_pLightEnemy[3] = CLightEnemy::Create(D3DXVECTOR3(280.0f, 0.0f, 50.0f), ZEROVECTOR3);
			if (m_pLightEnemy[3] != NULL)
			{
				m_pLightEnemy[3]->SetTour(0, D3DXVECTOR3(-50.0f, 0.0f, 30.0f));
				m_pLightEnemy[3]->SetTour(1, D3DXVECTOR3(-50.0f, 0.0f, -20.0f));
				m_pLightEnemy[3]->SetTour(2, D3DXVECTOR3(-125.0f, 0.0f, -20.0f));
				m_pLightEnemy[3]->SetTour(3, D3DXVECTOR3(-125.0f, 0.0f, 30.0f));
			}
			//���������Ă���
			bCollEnemy[0] = true;
		}

	}
	//��@�@(2)���v���C���[�𔭌����Ă��邩
	if (m_pUav[1]->EnemyCall() == true)
	{
		//�G�̑��������Ă��邩
		if (bCollEnemy[1] != true)
		{
			//���Ă��Ȃ���Βǉ�
			m_pLightEnemy[4] = CLightEnemy::Create(D3DXVECTOR3(280.0f, 0.0f, 50.0f), ZEROVECTOR3);
			if (m_pLightEnemy[4] != NULL)
			{
				m_pLightEnemy[4]->SetTour(0, D3DXVECTOR3(220.0f, 0.0f, 40.0f));
				m_pLightEnemy[4]->SetTour(1, D3DXVECTOR3(140.0f, 0.0f, 40.0f));
				m_pLightEnemy[4]->SetTour(2, D3DXVECTOR3(140.0f, 0.0f, -20.0f));
				m_pLightEnemy[4]->SetTour(3, D3DXVECTOR3(220.0f, 0.0f, -20.0f));
			}
			//���������Ă���
			bCollEnemy[1] = true;
		}

	}
	//��@�@(3)���v���C���[�𔭌����Ă��邩
	if (m_pUav[2]->EnemyCall() == true)
	{
		//�G�̑��������Ă��邩
		if (bCollEnemy[2] != true)
		{
			//���Ă��Ȃ���Βǉ�
			m_pLightEnemy[5] = CLightEnemy::Create(D3DXVECTOR3(380.0f, 0.0f, -80.0f), ZEROVECTOR3);
			if (m_pLightEnemy[5] != NULL)
			{
				m_pLightEnemy[5]->SetTour(0, D3DXVECTOR3(360.0f, 0.0f, -270.0f));
				m_pLightEnemy[5]->SetTour(1, D3DXVECTOR3(120.0f, 0.0f, -270.0f));
				m_pLightEnemy[5]->SetTour(2, D3DXVECTOR3(120.0f, 0.0f, -440.0f));
				m_pLightEnemy[5]->SetTour(3, D3DXVECTOR3(360.0f, 0.0f, -440.0f));
			}
			//���������Ă���
			bCollEnemy[2] = true;
		}

	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void CMap03::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// �I������
//=============================================================================
void CMap03::Uninit(void)
{
	CObject::ReleaseAll();
}

