//=============================================================================
//
// 武器選択画面背景処理 [weaponselectscene.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "weaponselectscene.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWeaponSelectScene::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CWeaponSelectScene::CWeaponSelectScene()
{
	D3DXVECTOR3	m_pos = ZEROVECTOR3;
	D3DXVECTOR3	m_size = ZEROVECTOR3;
	D3DCOLOR	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_texpos[nCount] = D3DXVECTOR2(0.0f, 0.0f);
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CWeaponSelectScene::~CWeaponSelectScene()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CWeaponSelectScene::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"Data/Texture/selectscene.png",								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CWeaponSelectScene::Unload(void)
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
CWeaponSelectScene * CWeaponSelectScene::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CWeaponSelectScene* pWeaponSelectScene = NULL;
	pWeaponSelectScene = new CWeaponSelectScene;
	pWeaponSelectScene->m_pos = pos;
	pWeaponSelectScene->m_size = size;
	pWeaponSelectScene->Init();

	return pWeaponSelectScene;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CWeaponSelectScene::Init(void)
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
void CWeaponSelectScene::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CWeaponSelectScene::Update(void)
{
}

//=============================================================================
// 描画関数
//=============================================================================
void CWeaponSelectScene::Draw(void)
{
	CObject2D::Draw();
}
