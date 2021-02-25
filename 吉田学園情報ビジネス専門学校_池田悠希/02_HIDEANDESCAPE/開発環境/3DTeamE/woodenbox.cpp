//=============================================================================
//
// 木箱 [woodenbox.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "woodenbox.h"
#include "manager.h"
#include "renderer.h"
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
CModel::MODELDATA CWoodenBox::m_modeldata = {};
D3DXMATERIAL * CWoodenBox::m_pMat = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CWoodenBox::CWoodenBox()
{
	m_pModel = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetObjType(OBJTYPE_OBSTACLE);					//オブジェクトタイプ設定
}

//=============================================================================
// デストラクタ
//=============================================================================
CWoodenBox::~CWoodenBox()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CWoodenBox::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/woodenbox.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

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
void CWoodenBox::Unload(void)
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
CWoodenBox * CWoodenBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CWoodenBox* pWoodenBox = NULL;
	pWoodenBox = new CWoodenBox;
	pWoodenBox->m_pos = pos;
	pWoodenBox->m_rot = rot;
	pWoodenBox->m_size = size;
	pWoodenBox->Init();

	return pWoodenBox;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CWoodenBox::Init(void)
{
	//モデル生成
	m_pModel = CModel::Create(NULL, this, m_modeldata, m_pos, m_rot, m_size);
	SetCollisionBullet(true);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CWoodenBox::Uninit(void)
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
void CWoodenBox::Update(void)
{
}

//=============================================================================
// 描画関数
//=============================================================================
void CWoodenBox::Draw(void)
{
}

//=============================================================================
// 位置取得関数
//=============================================================================
D3DXVECTOR3 CWoodenBox::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 向き取得関数
//=============================================================================
D3DXVECTOR3 CWoodenBox::GetRot(void)
{
	return m_rot;
}
