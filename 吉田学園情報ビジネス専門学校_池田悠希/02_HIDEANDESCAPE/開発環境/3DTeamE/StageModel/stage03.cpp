//=============================================================================
//
// �X�e�[�W03���� [stage03.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "stage03.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
CModel::MODELDATA CStage03::m_modeldata = {};
D3DXMATERIAL * CStage03::m_pMat = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStage03::CStage03()
{
	m_pModel = NULL;
	m_pos = ZEROVECTOR3;
	m_rot = ZEROVECTOR3;
	m_size = ZEROVECTOR3;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStage03::~CStage03()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CStage03::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/befoe_stage_3.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

	m_pMat = (D3DXMATERIAL *)m_modeldata.pBuffMat->GetBufferPointer();

	for (int nCountMat = 0; nCountMat < (int)m_modeldata.nNumMat; nCountMat++)
	{
		D3DXCreateTextureFromFile(pDevice, m_pMat[nCountMat].pTextureFilename, &m_modeldata.pTexture[nCountMat]);
	}
	return S_OK;
}

//=============================================================================
// ���f���j���֐�
//=============================================================================
void CStage03::Unload(void)
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
CStage03 * CStage03::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CStage03* pStage03 = NULL;
	pStage03 = new CStage03;
	pStage03->m_pos = pos;
	pStage03->m_rot = rot;
	pStage03->m_size = size;
	pStage03->Init();
	CManager::SetStageModel(pStage03->m_pModel);
	return pStage03;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CStage03::Init(void)
{
	//���f������
	m_pModel = CModel::Create(NULL, this, m_modeldata, m_pos, m_rot, m_size);
	SetCollisionBullet(true);
	SetObjType(OBJTYPE_STAGE);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CStage03::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
	}
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CStage03::Update(void)
{
}

//=============================================================================
// �`��֐�
//=============================================================================
void CStage03::Draw(void)
{
}

CModel* CStage03::GetModel(void)
{
	return m_pModel;
}

