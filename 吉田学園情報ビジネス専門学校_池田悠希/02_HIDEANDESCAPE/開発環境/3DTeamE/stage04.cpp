//=============================================================================
//
// ステージ04処理 [stage04.cpp]
// Author : 吉田悠人
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "stage04.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
CModel::MODELDATA CStage04::m_modeldata = {};
D3DXMATERIAL * CStage04::m_pMat = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CStage04::CStage04()
{
	m_pModel = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// デストラクタ
//=============================================================================
CStage04::~CStage04()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CStage04::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/after_stage_3.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

	m_pMat = (D3DXMATERIAL *)m_modeldata.pBuffMat->GetBufferPointer();

	for (int nCountMat = 0; nCountMat < (int)m_modeldata.nNumMat; nCountMat++)
	{
		D3DXCreateTextureFromFile(pDevice, m_pMat[nCountMat].pTextureFilename, &m_modeldata.pTexture[nCountMat]);
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CStage04::Unload(void)
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
// 生成関数
//=============================================================================
CStage04 * CStage04::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CStage04* pStage04 = NULL;
	pStage04 = new CStage04;
	pStage04->m_pos = pos;
	pStage04->m_rot = rot;
	pStage04->m_size = size;
	pStage04->Init();
	CManager::SetStageModel(pStage04->m_pModel);
	return pStage04;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CStage04::Init(void)
{
	//モデル生成
	m_pModel = CModel::Create(NULL, this, m_modeldata, m_pos, m_rot, m_size);
	SetCollisionBullet(true);
	SetObjType(OBJTYPE_STAGE);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CStage04::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
	}
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CStage04::Update(void)
{
}

//=============================================================================
// 描画関数
//=============================================================================
void CStage04::Draw(void)
{
}

CModel* CStage04::GetModel(void)
{
	return m_pModel;
}

