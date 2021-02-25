//=============================================================================
//
// 血処理 [blood.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "blood.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBlood::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CBlood::CBlood()
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
CBlood::~CBlood()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CBlood::Load(void)
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
void CBlood::Unload(void)
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
CBlood * CBlood::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CBlood* pBlood = NULL;
	pBlood = new CBlood;
	pBlood->m_pos = pos;
	pBlood->m_move = move;
	pBlood->m_rot = rot;
	pBlood->m_size = size;
	pBlood->m_col = col;
	pBlood->Init();

	return pBlood;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBlood::Init(void)
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
void CBlood::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CBlood::Update(void)
{
	CBillboard::Update();

	m_move.y -= 0.1f;

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
void CBlood::Draw(void)
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

void CBlood::BloodCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DCOLOR col)
{
	//for (int nCount = 0; nCount < BLOOD_VALUE; nCount++)
	//{
	//	float fRandRot = float(rand() % 360 + -360);
	//	float fRandRotY = float(rand() % 360);
	//	float fRandRotZ = float(rand() % 360);
	//	float fRandSize = float(rand() % SPLACH_BLOOD_SIZE_X);
	//	float fRandSpeed = float(rand() % int(BLOOD_SPEED * 10));//十倍にしてランダムにする
	//															 //元の値の倍率に戻す
	//	fRandSpeed = fRandSpeed / 10;
	//	CBlood::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*fRandSpeed, sinf(D3DXToRadian(fRandRotY))*-(fRandSpeed + BLOOD_UP_VALUE), cosf(D3DXToRadian(fRandRotZ))*fRandSpeed), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 0, 0, 255));
	//}
	//for (int nCount = 0; nCount < BLOOD_VALUE; nCount++)
	//{
	//	float fRandRot = float(rand() % 360 + -360);
	//	float fRandRotY = float(rand() % 360);
	//	float fRandRotZ = float(rand() % 360);
	//	float fRandSize = float(rand() % SPLACH_BLOOD_SIZE_X);
	//	float fRandSpeed = float(rand() % int(BLOOD_SPEED * 10));//十倍にしてランダムにする
	//															 //元の値の倍率に戻す
	//	fRandSpeed = (fRandSpeed / 10) / 2;
	//	CBlood::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(cosf(D3DXToRadian(fRandRot))*fRandSpeed, sinf(D3DXToRadian(fRandRotY))*-(fRandSpeed + BLOOD_UP_VALUE), cosf(D3DXToRadian(fRandRotZ))*fRandSpeed), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 0, 0, 255));
	//}

	int nRandSeed = 0;//ランダムシード値（時間毎変更ではなくクリック毎変更にするため）
	nRandSeed = rand() % 255;
	srand((unsigned int)time(NULL)*nRandSeed);

	for (int nCount = 0; nCount < 10; nCount++)
	{
		float fRandRotX = float(rand() % 360 + -360);
		float fRandRotY = float(rand() % 360);
		float fRandRotZ = float(rand() % 360);
		float fRandSize = float(rand() % SPLACH_BLOOD_SIZE_X);
		float fRandSpeed = float(rand() % int(BLOOD_SPEED * 10));//十倍にしてランダムにする
																	 //元の値の倍率に戻す
		fRandSpeed = fRandSpeed / 10;
		CBlood::Create(pos, D3DXVECTOR3(cosf(D3DXToRadian(fRandRotX)) * fRandSpeed, sinf(D3DXToRadian(fRandRotY)) * -(fRandSpeed), cosf(D3DXToRadian(fRandRotZ))*fRandSpeed), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(fRandSize, fRandSize, 0.0f), D3DCOLOR_RGBA(255, 0, 0, 255));
	}
}
