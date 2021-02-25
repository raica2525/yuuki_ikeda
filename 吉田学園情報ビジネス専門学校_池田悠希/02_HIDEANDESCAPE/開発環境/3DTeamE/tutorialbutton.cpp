//=============================================================================
//
// チュートリアルボタン処理 [tutorialbutton.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "tutorialbutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
#include "sound.h"
//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTutorialButton::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorialButton::CTutorialButton()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorialButton::~CTutorialButton()
{
}

//=============================================================================
// テクスチャ読み込み関数
//=============================================================================
HRESULT CTutorialButton::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		"Data/Texture/tutorial.png",								// ファイルの名前
		&m_pTexture);								// 読み込むメモリー
	return S_OK;
}

//=============================================================================
// テクスチャ破棄関数
//=============================================================================
void CTutorialButton::Unload(void)
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
CTutorialButton * CTutorialButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTutorialButton* pTutorialButton = NULL;
	pTutorialButton = new CTutorialButton;
	pTutorialButton->SetPos(pos);
	pTutorialButton->m_DefaultSize = size;
	pTutorialButton->SetSize(size);
	pTutorialButton->Init();

	return pTutorialButton;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CTutorialButton::Init(void)
{
	BindTexture(m_pTexture);	//テクスチャの割り当て
	CButton::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CTutorialButton::Uninit(void)
{
	CObject2D::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CTutorialButton::Update(void)
{
	CButton::Update();
}

//=============================================================================
// 描画関数
//=============================================================================
void CTutorialButton::Draw(void)
{
	CButton::Draw();
}

void CTutorialButton::Push(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
	CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
}

void CTutorialButton::Select(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
	SetSize(m_DefaultSize * 1.1f);
}

void CTutorialButton::Unselect(void)
{
	SetSize(m_DefaultSize);
}
