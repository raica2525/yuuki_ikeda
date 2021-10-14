//=============================================================================
//
// �X�e�[�W02���� [stage02.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "stage02.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
CModel::MODELDATA CStage02::m_modeldata = {};
D3DXMATERIAL * CStage02::m_pMat = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStage02::CStage02()
{
	m_pModel = NULL;
	m_pos = ZEROVECTOR3;
	m_rot = ZEROVECTOR3;
	m_size = ZEROVECTOR3;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStage02::~CStage02()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CStage02::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/Stage_02.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

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
void CStage02::Unload(void)
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
CStage02 * CStage02::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CStage02* pStage02 = NULL;
	pStage02 = new CStage02;
	pStage02->m_pos = pos;
	pStage02->m_rot = rot;
	pStage02->m_size = size;
	pStage02->Init();
	CManager::SetStageModel(pStage02->m_pModel);
	return pStage02;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CStage02::Init(void)
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
void CStage02::Uninit(void)
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
void CStage02::Update(void)
{
}

//=============================================================================
// �`��֐�
//=============================================================================
void CStage02::Draw(void)
{
}

CModel* CStage02::GetModel(void)
{
	return m_pModel;
}

