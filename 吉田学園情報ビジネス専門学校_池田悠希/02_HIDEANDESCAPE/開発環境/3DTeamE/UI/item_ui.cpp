//=============================================================================
//
// アイテムUI処理 [item_ui.cpp]
// Author : 若山　言稀
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "item_ui.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "manager.h"
//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CItem_ui::m_pTexture = NULL;
char *CItem_ui::m_cFileName = ITEM_UI_TEXTURE;
//=============================================================================
// コンストラクタ
//=============================================================================
CItem_ui::CItem_ui() :CObject2D(2)
{
	m_pos = ZEROVECTOR3;
	m_frot = 0.0f;
	m_size = ZEROVECTOR3;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem_ui::~CItem_ui()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CItem_ui::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	for (int nTexture = 0; nTexture<TEXTURE_MAX; nTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
			m_cFileName,						// ファイルの名前
			&m_pTexture);						// 読み込むメモリー

	}
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CItem_ui::Unload(void)
{
	// テクスチャの破棄
	for (int nTexture = 0; nTexture < TEXTURE_MAX; nTexture++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}

	}
}

//=============================================================================
// 生成関数
//=============================================================================
CItem_ui * CItem_ui::Create(D3DXVECTOR3 pos)
{
	CItem_ui* pItemUi = NULL;
	pItemUi = new CItem_ui;
	pItemUi->m_pos = pos;
	pItemUi->Init();

	return pItemUi;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItem_ui::Init(void)
{
	//サイズ生成
	m_size = D3DXVECTOR3(100, 100, 0);
	//セット
	SetPos(m_pos);
	SetRot(m_frot);
	SetSize(m_size);
	SetCol(m_col);

	//テクスチャ設定
	BindTexture(m_pTexture);
	//オブジェクト2D初期化
	CObject2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItem_ui::Uninit(void)
{
	CObject2D::Uninit();

}

//=============================================================================
// 更新処理
//=============================================================================
void CItem_ui::Update(void)
{
	CObject2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CItem_ui::Draw(void)
{
	CObject2D::Draw();
}