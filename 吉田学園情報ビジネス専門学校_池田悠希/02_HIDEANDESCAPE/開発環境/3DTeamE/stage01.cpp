//=============================================================================
//
// ステージ01処理 [stage01.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "stage01.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
CModel::MODELDATA CStage01::m_modeldata = {};
D3DXMATERIAL * CStage01::m_pMat = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CStage01::CStage01()
{
	m_pModel = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// デストラクタ
//=============================================================================
CStage01::~CStage01()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CStage01::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/Stage_1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

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
void CStage01::Unload(void)
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
CStage01 * CStage01::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CStage01* pStage01 = NULL;
	pStage01 = new CStage01;
	pStage01->m_pos = pos;
	pStage01->m_rot = rot;
	pStage01->m_size = size;
	pStage01->Init();
	CManager::SetStageModel(pStage01->m_pModel);
	return pStage01;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CStage01::Init(void)
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
void CStage01::Uninit(void)
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
void CStage01::Update(void)
{
}

//=============================================================================
// 描画関数
//=============================================================================
void CStage01::Draw(void)
{
}

CModel* CStage01::GetModel(void)
{
	return m_pModel;
}

