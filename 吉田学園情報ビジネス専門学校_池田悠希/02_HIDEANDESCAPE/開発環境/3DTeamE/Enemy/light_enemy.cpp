//=============================================================================
//
//  �y�������@ [light_enemy.cpp]
// Author : �g�c�I�l ��K������
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WARY_TIME 50	//�v���C���[�ɋC���t���܂ł̎���
#define MAX_LIFE 100

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "renderer.h"
#include "manager.h"
#include "light_enemy.h"
#include "enemy.h"
#include "animation.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "exclamationmark.h"
#include "question.h"
#include "explosion.h"

//*****************************************************************************
//�@�ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODELDATA CLightEnemy::m_modeldata[PARTS_MAX] = {};
CAnimation * CLightEnemy::m_pAnimaSave = NULL;
CLightEnemy::PARTS_DATA CLightEnemy::m_PartsData[PARTS_MAX]=
{
	{"Data/Model/Enemy/LightEnemy/00_mainhead,body,guns.x",-1 ,D3DXVECTOR3(0.0f,20.0f,0.0f), },
	{"Data/Model/Enemy/LightEnemy/01_Right_hutomomo.x",0 ,D3DXVECTOR3(-5.0f,0.0f,8.0f), },
	{ "Data/Model/Enemy/LightEnemy/02_Right_foot.x",1 ,D3DXVECTOR3(0.0f,-6.0f,-10.0f), },
	{ "Data/Model/Enemy/LightEnemy/03_left_hutomomo.x",0 ,D3DXVECTOR3(5.0f,0.0f,8.0f), },
	{"Data/Model/Enemy/LightEnemy/04_left_foot.x",3 ,D3DXVECTOR3(0.0f,-6.0f,-10.0f), }
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLightEnemy::CLightEnemy()
{
	memset(m_apModel, NULL, sizeof(m_apModel));
	m_AnimaMotion = CAnimation::MOTION_LIGHT_ENEMY_NEUTRAL;
	for (int nCount = 0; nCount < PARTS_MAX/*(�ǂݍ��񂾃��f������)*/; nCount++)
	{
		m_Partsrot[nCount] = ZEROVECTOR3;		//�p�[�crot���
		m_Partspos[nCount] = ZEROVECTOR3;		//�p�[�cpos���
	}
	SetMode(ENEMY_TOUR);	//�s�����[�h

	m_fSpeed = 0.0f;		//�X�s�[�h
	m_bSearch = false;		//�{���Ă��邩�ǂ���
	m_pAnime = NULL;		//�A�j���[�V�����|�C���^
	nWaryCoutn = 0;			//�x���J�E���g
	m_bWary = false;		//?
	m_bDiscovery = false;	//!
}

//=============================================================================
// �f�X�g�g���N�^
//=============================================================================
CLightEnemy::~CLightEnemy()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CLightEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	for (int nCount = 0; nCount < PARTS_MAX/*(txt����ǂݍ��񂾃��f������)*/; nCount++)
	{
		D3DXLoadMeshFromX(m_PartsData[nCount].FileName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata[nCount].pBuffMat, NULL, &m_modeldata[nCount].nNumMat, &m_modeldata[nCount].pMesh);
	}

	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CLightEnemy::Unload(void)
{
	for (int nCount = 0; nCount < PARTS_MAX; nCount++)
	{
		if (m_modeldata[nCount].pBuffMat != NULL)
		{
			m_modeldata[nCount].pBuffMat->Release();
		}

		if (m_modeldata[nCount].pMesh != NULL)
		{
		m_modeldata[nCount].pMesh->Release();
		}

		for (int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
		{
			if (m_modeldata[nCount].pTexture[nCountTex] != NULL)
			{
				m_modeldata[nCount].pTexture[nCountTex]->Release();
			}
		}
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CLightEnemy * CLightEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CLightEnemy* pLightEnemy = NULL;
	pLightEnemy = new CLightEnemy;
	pLightEnemy->SetPos(pos);
	pLightEnemy->SetRot(rot);
	pLightEnemy->SetSize(D3DXVECTOR3(1.2f, 1.2f, 1.2f));
	//���񃋁[�g�ݒ�
	pLightEnemy->SetTour(0, pos);

	pLightEnemy->Init();

	return pLightEnemy;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CLightEnemy::Init(void)
{
	CEnemy::Init();
	//�A�j���[�V��������
	m_pAnimaSave = CAnimation::Create(CAnimation::ANIMATION_LIGHT_ENEMY);
	CEnemy::SetLife(MAX_LIFE);
	//���f������
	for (int nCount = 0; nCount < PARTS_MAX/*(�ǂݍ��񂾃��f������)*/; nCount++)
	{
		if (m_PartsData[nCount].nParent == -1)
		{			
			m_apModel[nCount] = CModel::Create(CEnemy::GetWorld(), this, m_modeldata[nCount], m_PartsData[nCount].Partspos, m_Partsrot[nCount], D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		}
		else
		{

			m_apModel[nCount] = CModel::Create(m_apModel[m_PartsData[nCount].nParent], this, m_modeldata[nCount], m_PartsData[nCount].Partspos, m_Partsrot[nCount], D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		}
	}
	m_pAnime = m_pAnimaSave;	//�A�j���ۑ�
	m_pAnime->SetAnimation(CAnimation::MOTION_LIGHT_ENEMY_NEUTRAL);

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CLightEnemy::Uninit(void)
{
	for (int nCount = 0; nCount < PARTS_MAX/*(�ǂݍ��񂾃��f������)*/; nCount++)
	{
		m_apModel[nCount]->Uninit();
	}
	CEnemy::Uninit();
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CLightEnemy::Update(void)
{
	//�G�l�~�[�A�b�v�f�[�g
	CEnemy::Update();
	//����
	float *fDistance = NULL;


	//�s��
	if (GetState() != STATE_DEATH)
	{
		switch (GetMode())
		{
		case ENEMY_TOUR:
			
			//����֐�
			if (Tour() == true)
			{
				//�����A�j���[�V�����Z�b�g
				m_pAnime->SetAnimation(CAnimation::MOTION_LIGHT_ENEMY_MOVE);

			}
			if (Search(300.0f, 60.0f) == true&& CManager::GetPlayer()->GetState() != CPlayer::STATE_DEATH)	//���G�֐�		
			{
				//���������Ƃ�
				SetMode(ENEMY_WARY);
			}
			break;
		case ENEMY_WARY:
			//�N�G�X�`�����}�[�N����
			if (m_bWary == false)
			{
				//�N�G�X�`�����}�[�N����
				SetQuestion(CQuestion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 50, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(10.0f, 10.0f, 10.0f)));
				//�g���Ă��鏈��
				m_bWary = true;
			}
			//�A�j���[�V���������~�܂�
			m_pAnime->SetAnimation(CAnimation::MOTION_LIGHT_ENEMY_NEUTRAL);

			//�����֐�
			if (Found())
			{
				//�����֐�
				Direction(CManager::GetPlayer()->GetPos());

				//���E�ɓ����Ă���
				nWaryCoutn++;
			}
			else
			{
				//���E�ɓ����Ă��Ȃ�
				nWaryCoutn--;
			}
			//��莞�Ԍ������Ă����
			if (nWaryCoutn>WARY_TIME)
			{
				//�U���J�n
				SetMode(ENEMY_FOUND);
			}

			//��莞�Ԍ�����Ȃ���
			if (nWaryCoutn<0)
			{
				//������
				SetMode(ENEMY_TOUR);
				nWaryCoutn = 0;
			}
			break;
		case ENEMY_FOUND:	//�v���C���[����

			//�����}�[�N����
			if (m_bDiscovery == false)
			{
				//�����}�[�N����
				SetExclamation(CExclamationMark::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 50, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(10.0f, 10.0f, 10.0f)));
				//�g���Ă���
				m_bDiscovery = true;
			}
			//�U���A�j���[�V����
			m_pAnime->SetAnimation(CAnimation::MOTION_LIGHT_ENEMY_ATTACK);

			//�U���֐�
			Attack(-1);

			//�����֐�
			Direction(CManager::GetPlayer()->GetPos());

			//�����֐�
			if (!Found())
			{
				//���������Ƃ�
				SetMode(ENEMY_WARY);
			}
			//�v���C���[�����񂾂Ƃ�
			if (CManager::GetPlayer()->GetState() == CPlayer::STATE_DEATH)
			{
				SetMode(ENEMY_TOUR);

			}
			break;
		default:
			break;
		}
	}

	if (GetMode()!= ENEMY_FOUND)
	{
		//NULL�`�F�b�N
			if (GetExclamation() != NULL)
			{
				GetExclamation()->Uninit();
				SetExclamation(NULL);
		}
				m_bDiscovery = false;
			}

	if (GetMode() != ENEMY_WARY)
	{
			//NULL�`�F�b�N
			if (GetQuestion() != NULL)
			{
				GetQuestion()->Uninit();
				SetQuestion(NULL);
		}
				m_bWary = false;
			}

	switch (GetState())	
	{
	case STATE_NORMAL:		//�ʏ�
		break;
	case STATE_DAMAGE:		//�_���[�W
		//�_���[�W��H�炤�ƌx����ԂɈڍs
		if (GetMode() == ENEMY_TOUR)
		{
			SetMode(ENEMY_WARY);
		}
	
		SetState(STATE_NORMAL);		
		break;
	case STATE_DEATH:		//�j��
		if (m_pAnime->GetAnimeEnd() == false&& m_pAnime->GetAnimation()== CAnimation::MOTION_LIGHT_ENEMY_DEATH)
		{
			//����
			CExplosion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 30, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(100, 100, 100));

			//�I������
			Uninit();
		}

		if (m_pAnime->GetAnimation() != CAnimation::MOTION_LIGHT_ENEMY_DEATH)
		{
			m_pAnime->SetAnimation(CAnimation::MOTION_LIGHT_ENEMY_DEATH);
		}
		break;
	default:
		break;
	}
	//�p�[�c�A�j���[�V����
	PartsUpdate();

}

//=============================================================================
// �`��֐�
//=============================================================================
void CLightEnemy::Draw(void)
{

}

//=============================================================================
// �p�[�c�A�b�v�f�[�g�֐�
//=============================================================================
void CLightEnemy::PartsUpdate(void)
{
	if (m_pAnime != NULL)
	{
		for (int nCount = 0; nCount < PARTS_MAX/*(�ǂݍ��񂾃��f������)*/; nCount++)
		{
			m_apModel[nCount]->SetAnimationRot(m_Partsrot[nCount]);
			m_apModel[nCount]->SetAnimationPos(m_Partspos[nCount]);
		}
		m_pAnime->Update();
		for (int nCount = 0; nCount < PARTS_MAX/*(�ǂݍ��񂾃��f������)*/; nCount++)
		{
			m_Partsrot[nCount] = m_pAnime->GetAnimeRot(nCount);
			m_Partspos[nCount] = m_pAnime->GetAnimePos(nCount);
			m_pAnime->SetAnimeRot(nCount, m_Partsrot[nCount]);
			m_pAnime->SetAnimePos(nCount, m_Partspos[nCount]);
		}

	}
}
