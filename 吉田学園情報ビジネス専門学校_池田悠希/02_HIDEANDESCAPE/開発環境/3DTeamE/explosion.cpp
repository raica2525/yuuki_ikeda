//=============================================================================
//
// 爆発処理 [explosion.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "sound.h"
//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosion::CExplosion()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		EXPLOSION_TEXTURE,								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CExplosion::Unload(void)
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
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CExplosion* pExplosion = NULL;
	pExplosion = new CExplosion;
	pExplosion->m_pos = pos;
	pExplosion->m_rot = rot;
	pExplosion->m_size = size;
	pExplosion->Init();

	return pExplosion;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CExplosion::Init(void)
{
	CSound* pSound = CManager::GetSound();
	CBillboard::Init();
	pSound->PlaySoundA(CSound::SOUND_LABEL_SE_TRAP);
	SetPosition(m_pos);
	SetSize(m_size);
	SetColor(m_col);
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CExplosion::Update(void)
{
	CBillboard::Update();
	//カウントインクリメント
	m_nCounterAnim++;
	//カウントが4以上になった場合
	if (m_nCounterAnim > 4)
	{
		//カウントを0にする
		m_nCounterAnim = 0;

		//パターンのインクリメント
		m_nPatternAnim++;
		//パターンが8になった場合
		if (m_nPatternAnim > 8)
		{
			//終了
			Uninit();
			return;
		}
	}
	//テクスチャセット
	SetTex(m_nPatternAnim * 0.125f,
		0.0f,
		m_nPatternAnim * 0.125f + 0.125f,
		1.0f);
}

//=============================================================================
// 描画関数
//=============================================================================
void CExplosion::Draw(void)
{
	CBillboard::Draw();
}
