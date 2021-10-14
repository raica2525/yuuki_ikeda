//=============================================================================
//
// �d�����@ [heavy_enemy.cpp]
// Author : �g�c�I�l ��K������
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WARY_TIME 30	//�v���C���[�ɋC���t���܂ł̎���
#define MAX_LIFE 200

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "renderer.h"
#include "manager.h"
#include "heavy_enemy.h"
#include "enemy.h"
#include "animation.h"
#include "manager.h"
#include "player.h"
#include "exclamationmark.h"
#include "explosion.h"
#include "question.h"
//*****************************************************************************
//�@�ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODELDATA CHeavyEnemy::m_modeldata[PARTS_MAX] = {};
CAnimation * CHeavyEnemy::m_pAnimaSave = NULL;
CHeavyEnemy::PARTS_DATA CHeavyEnemy::m_PartsData[PARTS_MAX] =
{
	{ "Data/Model/Enemy/HeavyEnemy/00_MainHead,Body,Gun.x",-1 ,D3DXVECTOR3(0.0f,280.0f,0.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/04_LeftHutomomo.x",0 ,D3DXVECTOR3(-45.0f,0.0f,0.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/02_RightHukurahagi.x",1 ,D3DXVECTOR3(0.0f,-110.0f,-20.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/03_RightFoot.x",2 ,D3DXVECTOR3(0.0f,-130.0f,20.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/04_LeftHutomomo.x",0 ,D3DXVECTOR3(45.0f,0.0f,0.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/02_RightHukurahagi.x",4 ,D3DXVECTOR3(0.0f,-110.0f,-25.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/06_LeftFoot.x",5 ,D3DXVECTOR3(5.0f,-130.0f,25.0f), }


};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CHeavyEnemy::CHeavyEnemy()
{
	memset(m_apModel, NULL, sizeof(m_apModel));
	m_AnimaMotion = CAnimation::MOTION_HEAVY_ENEMY_NEUTRAL;
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
CHeavyEnemy::~CHeavyEnemy()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CHeavyEnemy::Load(void)
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
void CHeavyEnemy::Unload(void)
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

		for (int nCountTex = 0; nCountTex < PARTS_MAX; nCountTex++)
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
CHeavyEnemy * CHeavyEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CHeavyEnemy* pLightEnemy = NULL;
	pLightEnemy = new CHeavyEnemy;
	pLightEnemy->SetPos(pos);
	pLightEnemy->SetRot(rot);
	pLightEnemy->SetSize(D3DXVECTOR3(0.2f,0.2f,0.2f));
	//���񃋁[�g�ݒ�
	pLightEnemy->SetTour(0, pos);

	pLightEnemy->Init();

	return pLightEnemy;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CHeavyEnemy::Init(void)
{
	CEnemy::Init();
	//�A�j���[�V��������
	m_pAnimaSave = CAnimation::Create(CAnimation::ANIMATION_HEAVY_ENEMY);
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
void CHeavyEnemy::Uninit(void)
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
void CHeavyEnemy::Update(void)
{
	//�G�l�~�[�A�b�v�f�[�g
	CEnemy::Update();
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
			if (Search(300.0f, 70.0f) == true && CManager::GetPlayer()->GetState() != CPlayer::STATE_DEATH)	//���G�֐�		
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
				SetQuestion(CQuestion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 85, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(10.0f, 10.0f, 10.0f)));
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
				//�J�E���g������
				nWaryCoutn = 0;
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
				SetExclamation(CExclamationMark::Create(D3DXVECTOR3(GetPos().x, GetPos().y +85, GetPos().z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f)));
				//�g���Ă���
				m_bDiscovery = true;
			}
			//�U���A�j���[�V����
			m_pAnime->SetAnimation(CAnimation::MOTION_HEAVY_ENEMY_ATTACK);

			//�U���֐�
			Attack(-3);

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


	if (GetMode() != ENEMY_FOUND)
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
		//�ʏ�
	case STATE_NORMAL:		
		break;
		//�_���[�W
	case STATE_DAMAGE:		
							//�_���[�W��H�炤�ƌx����ԂɈڍs
		if (GetMode() == ENEMY_TOUR)
		{
			SetMode(ENEMY_WARY);
		}

		SetState(STATE_NORMAL);
		break;
	case STATE_DEATH:		//�j��

		if (m_pAnime->GetAnimeEnd() == false && m_pAnime->GetAnimation() == CAnimation::MOTION_HEAVY_ENEMY_DEATH)
		{
			//����
			CExplosion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 30, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(100, 100, 100));

			//�I������
			Uninit();
		}
		//�A�j���[�V�����Đ�
		if (m_pAnime->GetAnimation() != CAnimation::MOTION_HEAVY_ENEMY_DEATH)
		{
			m_pAnime->SetAnimation(CAnimation::MOTION_HEAVY_ENEMY_DEATH);
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
void CHeavyEnemy::Draw(void)
{

}

//=============================================================================
// �p�[�c�A�b�v�f�[�g�֐�
//=============================================================================
void CHeavyEnemy::PartsUpdate(void)
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
