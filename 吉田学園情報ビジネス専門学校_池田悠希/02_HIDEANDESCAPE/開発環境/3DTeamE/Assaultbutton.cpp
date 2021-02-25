//=============================================================================
//
// アサルトボタン処理 [assaultbutton.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "assaultbutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
#include "sound.h"
//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CAssaultButton::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CAssaultButton::CAssaultButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CAssaultButton::~CAssaultButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CAssaultButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"Data/Texture/AR.png",								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CAssaultButton::Unload(void)
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
CAssaultButton * CAssaultButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CAssaultButton* pAssaultButton = NULL;
	pAssaultButton = new CAssaultButton;
	pAssaultButton->SetPos(pos);
	pAssaultButton->SetSize(size);
	pAssaultButton->Init();

	return pAssaultButton;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CAssaultButton::Init(void)
{

	BindTexture(m_pTexture);	//テクスチャの割り当て
	CButton::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CAssaultButton::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CAssaultButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// 描画関数
//=============================================================================
void CAssaultButton::Draw(void)
{
	CButton::Draw();
}

void CAssaultButton::Push(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
	CManager::SetWeaponsMode(CManager::WEAPONS_MODE_AR);
	CManager::GetFade()->SetFade(CManager::MODE_MAP01);
}

void CAssaultButton::Select(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
	SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
}

void CAssaultButton::Unselect(void)
{
	SetCol(D3DCOLOR_RGBA(255, 255, 255, 128));
}
