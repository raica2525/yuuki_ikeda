//=============================================================================
//
// ハンドガンボタン処理 [handgunbutton.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "handgunbutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
#include "sound.h"
//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CHandgunButton::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CHandgunButton::CHandgunButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CHandgunButton::~CHandgunButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CHandgunButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"Data/Texture/HG.png",								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CHandgunButton::Unload(void)
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
CHandgunButton * CHandgunButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CHandgunButton* pHandgunButton = NULL;
	pHandgunButton = new CHandgunButton;
	pHandgunButton->SetPos(pos);
	pHandgunButton->SetSize(size);
	pHandgunButton->Init();

	return pHandgunButton;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CHandgunButton::Init(void)
{
	BindTexture(m_pTexture);	//テクスチャの割り当て
	CButton::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CHandgunButton::Uninit(void)
{
	CButton::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CHandgunButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// 描画関数
//=============================================================================
void CHandgunButton::Draw(void)
{
	CButton::Draw();
}

void CHandgunButton::Push(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
	CManager::SetWeaponsMode(CManager::WEAPONS_MODE_HG);
	CManager::GetFade()->SetFade(CManager::MODE_MAP01);
}

void CHandgunButton::Select(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
	SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
}

void CHandgunButton::Unselect(void)
{
	SetCol(D3DCOLOR_RGBA(255, 255, 255, 128));
}