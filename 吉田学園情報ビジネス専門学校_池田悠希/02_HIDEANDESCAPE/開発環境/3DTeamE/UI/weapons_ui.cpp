//=============================================================================
//
// 武装UI処理 [weapons_ui.cpp]
// Author : 吉田悠人
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "weapons_ui.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "manager.h"
//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CWeapons_ui::m_pTexture[WEAPONS_TEXTURE_MAX] = {};
char *CWeapons_ui::m_cFileName[WEAPONS_TEXTURE_MAX]=
{
	WEAPONS_UI_AR_TEXTURE,
	WEAPONS_UI_HG_TEXTURE
};
//=============================================================================
// コンストラクタ
//=============================================================================
CWeapons_ui::CWeapons_ui() : CObject2D(2)
{
	m_pos = ZEROVECTOR3;
	m_frot = 0.0f;
	m_size = ZEROVECTOR3;
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	nCountCol = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CWeapons_ui::~CWeapons_ui()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CWeapons_ui::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	for (int nTexture=0;nTexture<WEAPONS_TEXTURE_MAX;nTexture++)
	{
		D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
			m_cFileName[nTexture],						// ファイルの名前
			&m_pTexture[nTexture]);								// 読み込むメモリー

	}
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CWeapons_ui::Unload(void)
{
	// テクスチャの破棄
	for (int nTexture = 0; nTexture < WEAPONS_TEXTURE_MAX; nTexture++)
	{
		if (m_pTexture[nTexture] != NULL)
		{
			m_pTexture[nTexture]->Release();
			m_pTexture[nTexture] = NULL;
		}

	}
}

//=============================================================================
// 生成関数
//=============================================================================
CWeapons_ui * CWeapons_ui::Create(void)
{
	CWeapons_ui* pWeaponsUi = NULL;
	pWeaponsUi = new CWeapons_ui;

	pWeaponsUi->Init();

	return pWeaponsUi;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWeapons_ui::Init(void)
{
	//オブジェクト2D初期化
	CObject2D::Init();
	//サイズ生成
	m_size = D3DXVECTOR3(250, 150, 0);
	//位置設定
	m_pos = D3DXVECTOR3(SCREEN_WIDTH - (m_size.x/2), SCREEN_HEIGHT - (m_size.y+25), 0);

	//セット
	SetPos(m_pos);
	SetRot(m_frot);
	SetSize(m_size);
	SetCol(m_col);
	//SetCol(D3DCOLOR_RGBA(255, 255, 0, 255));

	//テクスチャ設定
	BindTexture(m_pTexture[CManager::GetWeaponsMode()]);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CWeapons_ui::Uninit(void)
{
	CObject2D::Uninit();
	
}

//=============================================================================
// 更新処理
//=============================================================================
void CWeapons_ui::Update(void)
{
	CObject2D::Update();
	if (nCountCol >= 0)
	{
		nCountCol--;
	}
	if (nCountCol == 0)
	{
		SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CWeapons_ui::Draw(void)
{
	CObject2D::Draw();
}

//=============================================================================
// 光る関数
//=============================================================================
void CWeapons_ui::Gleams(void)
{
	nCountCol = 5;
	SetCol(D3DCOLOR_RGBA(255, 241, 86, 255));

}
