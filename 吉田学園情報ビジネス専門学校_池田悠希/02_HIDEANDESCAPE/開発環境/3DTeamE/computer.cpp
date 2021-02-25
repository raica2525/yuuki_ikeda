//=============================================================================
//
// コンピュータ処理 [computer.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "computer.h"
#include "manager.h"
#include "renderer.h"
#include "monitor.h"
#include "inputkeyboard.h"
#include "enemy.h"
#include "uav.h"
#include "tutorial.h"
#include "monitor.h"
#include "explosion.h"
#include "sound.h"
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
CModel::MODELDATA CComputer::m_modeldata = {};
D3DXMATERIAL * CComputer::m_pMat = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CComputer::CComputer()
{
	m_pModel = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CComputer::~CComputer()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CComputer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX("Data/Model/newpc.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);

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
void CComputer::Unload(void)
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
CComputer * CComputer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CComputer* pComputer = NULL;
	pComputer = new CComputer;
	pComputer->m_pos = pos;
	pComputer->m_rot = rot;
	pComputer->m_size = size;
	pComputer->Init();
	return pComputer;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CComputer::Init(void)
{
	//モデル生成
	m_pModel = CModel::Create(NULL,this, m_modeldata, m_pos, m_rot, m_size);
	SetObjType(OBJTYPE_STAGE);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CComputer::Uninit(void)
{
}

//=============================================================================
// 更新関数
//=============================================================================
void CComputer::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = (CInputKeyboard*)CManager::GetInputKey();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();

	//if (m_bUse == false)
	//{
	//	if (pInputKeyboard->GetKeyTrigger(DIK_T))
	//	{
	//		pSound->StopSound();
	//		CMonitor::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//		m_bUse = true;
	//	}
	//	if (pInputKeyboard->GetKeyTrigger(DIK_G))
	//	{
	//		CExplosion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//	}
	//}
}

//=============================================================================
// 描画関数
//=============================================================================
void CComputer::Draw(void)
{
}

D3DXVECTOR3 CComputer::GetPos(void)
{
	return D3DXVECTOR3();
}

D3DXVECTOR3 CComputer::GetRot(void)
{
	return D3DXVECTOR3();
}
