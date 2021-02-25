//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	retrybutton.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "retrybutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
#include "sound.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CRetryButton::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CRetryButton::CRetryButton() :CButton(3)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRetryButton::~CRetryButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CRetryButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"Data/Texture/retry.png",								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CRetryButton::Unload(void)
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
CRetryButton * CRetryButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CRetryButton* pRetryButton = NULL;
	pRetryButton = new CRetryButton;
	pRetryButton->SetPos(pos);
	pRetryButton->SetSize(size);
	pRetryButton->Init();
	return pRetryButton;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CRetryButton::Init(void)
{
	BindTexture(m_pTexture);	//テクスチャの割り当て
	CButton::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CRetryButton::Uninit(void)
{
	CButton::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CRetryButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// 描画関数
//=============================================================================
void CRetryButton::Draw(void)
{
	CButton::Draw();
}

void CRetryButton::Push(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
	CManager::GetFade()->SetFade(CManager::GetMode());
}

void CRetryButton::Select(void)
{
	//サウンドの取得
	SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
}

void CRetryButton::Unselect(void)
{
	SetCol(D3DCOLOR_RGBA(128, 128, 128, 255));
}
