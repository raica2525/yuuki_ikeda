//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "title.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage01.h"
#include "titlelogo.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "tutorialbutton.h"
#include "startbutton.h"
#include "sound.h"
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_pCamera = NULL;
	m_pStage01 = NULL;
	m_pTitleLogo = NULL;
	m_pTutorialButton = NULL;
	m_pStartButton = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_TITLESTART);
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
	while (ShowCursor(true)<0);
	D3DXVECTOR3 vec = D3DXVECTOR3(0, 0, 0); //ベクトル定義
											//カメラオブジェクトの生成
	m_pCamera = new CCamera;
	//カメラ初期化処理
	m_pCamera->Init();
	//カメラ位置セット
	m_pStage01 = CStage01::Create(D3DXVECTOR3(0, 0, 0), vec, D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	m_pTitleLogo = CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200, 0.0f), D3DXVECTOR3(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 500, 0.0f));
	m_pTutorialButton = CTutorialButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT - (SCREEN_HEIGHT / 4), 0.0f), D3DXVECTOR3(700, 200, 0.0f));
	m_pStartButton = CStartButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT / 4), 0.0f), D3DXVECTOR3(700, 200, 0.0f));
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = (CInputKeyboard*)CManager::GetInputKey();

	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	CObject::ReleaseAll();
}
