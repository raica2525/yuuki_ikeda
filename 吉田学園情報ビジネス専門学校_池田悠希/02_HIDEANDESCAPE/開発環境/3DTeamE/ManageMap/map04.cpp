//=============================================================================
//
// �}�b�v04���� [map04.cpp]
// Author : ��K������ �E�g�c�I�l
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "map04.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage04.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "goal.h"
#include "sound.h"
#include "trap.h"
#include "heavy_enemy.h"
#include "light_enemy.h"
#include "item.h"
#include "monitor.h"


//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMap04::CMap04()
{
	m_pCamera = NULL;
	m_pStage04 = NULL;
	m_pObstacle = NULL;
	m_pLightEnemy[6] = {};
	m_pHeavyEnemy[1] = {};
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMap04::~CMap04()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMap04::Init(void)
{
	//�T�E���h�̎擾
	CMonitor::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	CSound * pSound = CManager::GetSound();
											//�J�����I�u�W�F�N�g�̐���
	m_pCamera = new CCamera;
	//�J��������������
	m_pCamera->Init();
	//�J�����ʒu�Z�b�g
	SetCursorPos(((int)SCREEN_WIDTH / 2), ((int)SCREEN_HEIGHT / 2));
	//�v���C���[�̈ʒu�Z�b�g
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(635.0f, 0.0f, 430.0f), D3DXVECTOR3(45, 180, 0), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	//�}�b�v���f���̃Z�b�g
	m_pStage04 = CStage04::Create(ZEROVECTOR3, ZEROVECTOR3, D3DXVECTOR3(1.7f, 1.6f, 1.7f));
	//�S�[���̐ݒu
	CGoal::Create(D3DXVECTOR3(-380.0f, 50.0f, -530.0f), D3DXVECTOR3(0.0f, 10.0f, -1.0f), D3DXVECTOR3(65.0f, 100.0f, 65.0f), D3DXCOLOR(255, 0, 0, 255), CManager::MODE_RESULT);
	//�A�C�e���ݒu
	CItem::Create(D3DXVECTOR3(-10.0f, 25.0f, -20.0f), ZEROVECTOR3);
	CItem::Create(D3DXVECTOR3(-230.0f, 25.0f, -190.0f), ZEROVECTOR3);

	//�g���b�v�ݒu
	CTrap::Create(D3DXVECTOR3(80.0f, 35.0f, -10.0f), D3DXVECTOR3(80.0f, 35.0f, 80.0f));
	CTrap::Create(D3DXVECTOR3(-285.0f, 35.0f, -35.0f), D3DXVECTOR3(-180.0f, 35.0f, -35.0f));

	//�y���G�l�~�[�ݒu
	m_pLightEnemy[1] = CLightEnemy::Create(D3DXVECTOR3(-50.0f, 0.0f, 30.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pLightEnemy[1] != NULL)
	{
		m_pLightEnemy[1]->SetTour(1, D3DXVECTOR3(-50.0f, 0.0f, -20.0f));
		m_pLightEnemy[1]->SetTour(2, D3DXVECTOR3(-125.0f, 0.0f, -20.0f));
		m_pLightEnemy[1]->SetTour(3, D3DXVECTOR3(-125.0f, 0.0f, 30.0f));
	}

	//�y���G�l�~�[�ݒu
	m_pLightEnemy[2] = CLightEnemy::Create(D3DXVECTOR3(-10.0f, 0.0f, -110.0f), D3DXVECTOR3(0.0f, D3DXToDegree(90.0f), 0.0f));
	//����ʒu�Z�b�g
	if (m_pLightEnemy[2] != NULL)
	{
		m_pLightEnemy[2]->SetTour(1, D3DXVECTOR3(-230.0f, 0.0f, -110.0f));
	}


	//�y���G�l�~�[�ݒu
	m_pLightEnemy[3] = CLightEnemy::Create(D3DXVECTOR3(-20.0f, 0.0f, -290.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pLightEnemy[3] != NULL)
	{
		m_pLightEnemy[3]->SetTour(1, D3DXVECTOR3(-20.0f, 0.0f, -350.0f));
		m_pLightEnemy[3]->SetTour(2, D3DXVECTOR3(45.0f, 0.0f, -350.0f));
		m_pLightEnemy[3]->SetTour(3, D3DXVECTOR3(45.0f, 0.0f, -290.0f));
	}

	//�y���G�l�~�[�ݒu
	m_pLightEnemy[4] = CLightEnemy::Create(D3DXVECTOR3(-250.0f, 0.0f, -370.0f), ZEROVECTOR3);
	//����ʒu�Z�b�g
	if (m_pLightEnemy[4] != NULL)
	{
		m_pLightEnemy[4]->SetTour(1, D3DXVECTOR3(-250.0f, 0.0f, -430.0f));
		m_pLightEnemy[4]->SetTour(2, D3DXVECTOR3(-320.0f, 0.0f, -430.0f));
		m_pLightEnemy[4]->SetTour(3, D3DXVECTOR3(-320.0f, 0.0f, -370.0f));
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
void CMap04::Update(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMap04::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// �I������
//=============================================================================
void CMap04::Uninit(void)
{
	CObject::ReleaseAll();
}

