//=============================================================================
//
// ��@�@���� [uav.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "renderer.h"
#include "manager.h"
#include "uav.h"
#include "enemy.h"
#include "exclamationmark.h"
#include "question.h"
#include "player.h"
#include "explosion.h"
#include "explosion2.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WARY_TIME 35	//�v���C���[�ɋC���t���܂ł̎���
#define MAX_LIFE 10

//*****************************************************************************
//�@�ÓI�����o�ϐ��̏�����
//*****************************************************************************
CModel::MODELDATA CUav::m_modeldata = {};
D3DXMATERIAL * CUav::m_pMat = NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CUav::CUav()
{
	m_pModel = NULL;
	SetMode(ENEMY_TOUR);	//�s�����[�h
	m_nLife = 0;		//���C�t
	m_fSpeed = 0.0f;		//�X�s�[�h
	m_bSearch = false;		//�{���Ă邩�ǂ���
	nWaryCoutn = 0;		//�x���J�E���g
	m_bWary = false;		//?
	m_bDiscovery = false;	//!
	bCall = false;
	m_nFly = 0;				//��Ԃ܂ł̃J�E���g
}

//=============================================================================
// �f�X�g�g���N�^
//=============================================================================
CUav::~CUav()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CUav::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXLoadMeshFromX("Data/Model/Enemy/Uav/Teisatuki.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);
	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CUav::Unload(void)
{
	if (m_modeldata.pBuffMat != NULL)
	{
		m_modeldata.pBuffMat->Release();
	}

	if (m_modeldata.pMesh != NULL)
	{
		m_modeldata.pMesh->Release();
	}

	for (int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
	{
		if (m_modeldata.pTexture[nCountTex] != NULL)
		{
			m_modeldata.pTexture[nCountTex]->Release();
		}
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CUav * CUav::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CUav* pUav = NULL;
	pUav = new CUav;
	pUav->SetPos(pos);
	pUav->SetRot(rot);
	pUav->SetSize(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	//���񃋁[�g�ݒ�
	pUav->SetTour(0, pos);

	pUav->Init();
	return pUav;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CUav::Init(void)
{
	CEnemy::Init();
	CEnemy::SetLife(MAX_LIFE);
	//���f������
	m_pModel = CModel::Create(CEnemy::GetWorld(), this, m_modeldata, D3DXVECTOR3(0,250.0f,0), ZEROVECTOR3, D3DXVECTOR3(1, 1, 1));

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CUav::Uninit(void)
{
	m_pModel->Uninit();
	CEnemy::Uninit();
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CUav::Update(void)
{
	//�G�l�~�[�A�b�v�f�[�g
	CEnemy::Update();
	//����
	float *fDistance=NULL;

	//�s��
	if (GetState() != STATE_DEATH)
	{
		switch (GetMode())
		{
		case ENEMY_TOUR:	//����
			
			Tour();		//����֐�
			
			if (Search(400.0f, 90.0f) == true && CManager::GetPlayer()->GetState() != CPlayer::STATE_DEATH)	//���G�֐�		
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

			//�����֐�
			if (Found() == true) 
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


			//���ԃJ�E���g
			m_nFly += 1;
			
			//�����֐�
			Direction(CManager::GetPlayer()->GetPos());

			bCall = true;

			//�v���C���[�����񂾂Ƃ�
			if (CManager::GetPlayer()->GetState() == CPlayer::STATE_DEATH)
			{
				SetMode(ENEMY_TOUR);
			}
			//���Ԃ܂ł̃J�E���g
			if (m_nFly>=30)
			{
				//NULL�`�F�b�N
				if (GetExclamation() != NULL)
				{
					GetExclamation()->Uninit();
					SetExclamation(NULL);
				}

				SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 1.0f, GetPos().z));
			}
			
			break;
		default:
			break;
		}

	}
	//���܂Œ��񂾂������
	if (GetPos().y>=60.0f)
	{
		Uninit();
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

		SetPos(D3DXVECTOR3(GetPos().x, GetPos().y-1.2f, GetPos().z));
		if (GetPos().y <= -20.0f)
		{
			//����

CExplosion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 30, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(100, 100, 100));
			//�I������
			Uninit();
		}

		break;
	default:
		break;
	}

}

//=============================================================================
// �`��֐�
//=============================================================================
void CUav::Draw(void)
{

}

//=============================================================================
// �������̃G�l�~�[���Ăԏ����֐�
//=============================================================================
bool CUav::EnemyCall(void)
{
	return bCall;
}

