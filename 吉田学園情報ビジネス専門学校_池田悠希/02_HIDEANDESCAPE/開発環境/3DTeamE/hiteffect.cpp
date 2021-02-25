//=============================================================================
//
// ヒットエフェクト処理 [hiteffect.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "hiteffect.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CHitEffect::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CHitEffect::CHitEffect()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_nLife = 30;
}

//=============================================================================
// デストラクタ
//=============================================================================
CHitEffect::~CHitEffect()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CHitEffect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		HITEFFECT_TEXTURE,								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CHitEffect::Unload(void)
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
CHitEffect * CHitEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CHitEffect* pHitEffect = NULL;
	pHitEffect = new CHitEffect;
	pHitEffect->m_pos = pos;
	pHitEffect->m_move = move;
	pHitEffect->m_rot = rot;
	pHitEffect->m_size = size;
	pHitEffect->m_col = col;
	pHitEffect->Init();

	return pHitEffect;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CHitEffect::Init(void)
{
	CBillboard::Init();
	SetPosition(m_pos);
	SetSize(m_size);
	SetColor(m_col);
	BindTexture(m_pTexture);
	SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CHitEffect::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CHitEffect::Update(void)
{
	CBillboard::Update();

	m_pos += m_move;
	SetPosition(m_pos);
	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
	}
	SetColor(m_col);
}

//=============================================================================
// 描画関数
//=============================================================================
void CHitEffect::Draw(void)
{
	//D3DMATERIAL9 material;
	//ZeroMemory(&material, sizeof(D3DMATERIAL9));
	//material.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//pDevice->SetMaterial(&material);
	//pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);
	CBillboard::Draw();
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void CHitEffect::HitEffectCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DCOLOR col)
{
	for (int nCount = 0; nCount < 10; nCount++)
	{
		float fRandRotX = float(rand() % 360 + -360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		float fRandSpeed = float(rand() % int(HITEFFECT_SPEED * 10));//十倍にしてランダムにする
		//元の値の倍率に戻す
		fRandSpeed = fRandSpeed / 10;
		CHitEffect::Create(pos, D3DXVECTOR3(cosf(D3DXToRadian(fRandRotX)) * fRandSpeed, sinf(D3DXToRadian(fRandRotY)) * -(fRandSpeed), cosf(D3DXToRadian(fRandRotZ))*fRandSpeed), D3DXVECTOR3(0.0f, 0.0f, 0.0f),size,col);
	}
}
