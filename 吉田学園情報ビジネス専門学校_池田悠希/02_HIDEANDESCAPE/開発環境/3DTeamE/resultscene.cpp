//=============================================================================
//
// リザルト画面背景処理 [resultscene.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "resultscene.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"
#include "inputkeyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CResultScene::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CResultScene::CResultScene()
{
	D3DXVECTOR3	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DCOLOR	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_texpos[nCount] = D3DXVECTOR2(0.0f, 0.0f);
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CResultScene::~CResultScene()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CResultScene::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"Data/Texture/result.png",								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CResultScene::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CResultScene * CResultScene::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CResultScene* pResultScene = NULL;
	pResultScene = new CResultScene;
	pResultScene->m_pos = pos;
	pResultScene->m_size = size;
	pResultScene->Init();

	return pResultScene;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CResultScene::Init(void)
{
	SetPos(m_pos);
	SetSize(m_size);
	SetCol(m_col);
	BindTexture(m_pTexture);	//テクスチャの割り当て
	CObject2D::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CResultScene::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CResultScene::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = (CInputKeyboard*)CManager::GetInputKey();

	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CResultScene::Draw(void)
{
	CObject2D::Draw();
}
