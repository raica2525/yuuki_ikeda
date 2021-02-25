//=============================================================================
//
// スタートボタン処理 [startbutton.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "startbutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
#include "sound.h"
//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CStartButton::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CStartButton::CStartButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CStartButton::~CStartButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CStartButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"Data/Texture/gamestart.png",								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CStartButton::Unload(void)
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
CStartButton * CStartButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CStartButton* pStartButton = NULL;
	pStartButton = new CStartButton;
	pStartButton->SetPos(pos);
	pStartButton->m_DefaultSize = size;
	pStartButton->SetSize(size);
	pStartButton->Init();

	return pStartButton;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CStartButton::Init(void)
{
	BindTexture(m_pTexture);	//テクスチャの割り当て
	CButton::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CStartButton::Uninit(void)
{
	CButton::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CStartButton::Update(void)
{

	CButton::Update();
}

//=============================================================================
// 描画関数
//=============================================================================
void CStartButton::Draw(void)
{
	CButton::Draw();
}

void CStartButton::Push(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
	CManager::GetFade()->SetFade(CManager::MODE_WEAPONSELECT);
}

void CStartButton::Select(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
	SetSize(m_DefaultSize * 1.1f);
}

void CStartButton::Unselect(void)
{
	SetSize(m_DefaultSize);
}