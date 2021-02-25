//=============================================================================
//
// !マーク処理 [exclamationmark.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "exclamationmark.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExclamationMark::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CExclamationMark::CExclamationMark()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//=============================================================================
// デストラクタ
//=============================================================================
CExclamationMark::~CExclamationMark()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CExclamationMark::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		EXCLAMATIONMARK_TEXTURE,								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CExclamationMark::Unload(void)
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
CExclamationMark * CExclamationMark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CExclamationMark* pExclamationMark = NULL;
	pExclamationMark = new CExclamationMark;
	pExclamationMark->m_pos = pos;
	pExclamationMark->m_rot = rot;
	pExclamationMark->m_size = size;
	pExclamationMark->Init();

	return pExclamationMark;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CExclamationMark::Init(void)
{
	CBillboard::Init();
	SetPosition(m_pos);
	SetSize(m_size);
	SetColor(m_col);
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CExclamationMark::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CExclamationMark::Update(void)
{
	CBillboard::Update();

	//テクスチャのセット
	SetTex(
		0.0f,
		0.0f,
		1.0f,
		1.0f);
}

//=============================================================================
// 描画関数
//=============================================================================
void CExclamationMark::Draw(void)
{
	CBillboard::Draw();
}
