//=============================================================================
//
// �`���[�g���A���X�e�[�W���� [tutorialstage.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "tutorialstage.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
CModel::MODELDATA CTutorialStage::m_modeldata = {};
D3DXMATERIAL * CTutorialStage::m_pMat = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorialStage::CTutorialStage()
{
	m_pModel = NULL;
	m_pos = ZEROVECTOR3;
	m_rot = ZEROVECTOR3;
	m_size = ZEROVECTOR3;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorialStage::~CTutorialStage()
{
}

//=============================================================================
// ���f���ǂݍ��݊֐�
//=============================================================================
HRESULT CTutorialStage::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/TutorialStage.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

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
void CTutorialStage::Unload(void)
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
CTutorialStage * CTutorialStage::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CTutorialStage* pTutorialStage = NULL;
	pTutorialStage = new CTutorialStage;
	pTutorialStage->m_pos = pos;
	pTutorialStage->m_rot = rot;
	pTutorialStage->m_size = size;
	pTutorialStage->Init();
	CManager::SetStageModel(pTutorialStage->m_pModel);
	return pTutorialStage;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CTutorialStage::Init(void)
{
	//���f������
	m_pModel = CModel::Create(NULL,this, m_modeldata, m_pos, m_rot, m_size);
	SetCollisionBullet(true);
	SetObjType(OBJTYPE_STAGE);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CTutorialStage::Uninit(void)
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
void CTutorialStage::Update(void)
{
}

//=============================================================================
// �`��֐�
//=============================================================================
void CTutorialStage::Draw(void)
{
}

CModel* CTutorialStage::GetModel(void)
{
	return m_pModel;
}

