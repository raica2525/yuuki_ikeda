//=============================================================================
//
// 布付き箱処理 [clothbox.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "clothbox.h"
#include "manager.h"
#include "renderer.h"
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
CModel::MODELDATA CClothBox::m_modeldata = {};
D3DXMATERIAL * CClothBox::m_pMat = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CClothBox::CClothBox()
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
CClothBox::~CClothBox()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CClothBox::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/clothbox.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

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
void CClothBox::Unload(void)
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
CClothBox * CClothBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CClothBox* pClothBox = NULL;
	pClothBox = new CClothBox;
	pClothBox->m_pos = pos;
	pClothBox->m_rot = rot;
	pClothBox->m_size = size;
	pClothBox->Init();

	return pClothBox;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CClothBox::Init(void)
{
	//モデル生成
	m_pModel = CModel::Create(NULL, this, m_modeldata, m_pos, m_rot, m_size);
	SetCollisionBullet(true);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CClothBox::Uninit(void)
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
void CClothBox::Update(void)
{
}

//=============================================================================
// 描画関数
//=============================================================================
void CClothBox::Draw(void)
{
}

//=============================================================================
// 位置取得関数
//=============================================================================
D3DXVECTOR3 CClothBox::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 向き取得関数
//=============================================================================
D3DXVECTOR3 CClothBox::GetRot(void)
{
	return m_rot;
}
