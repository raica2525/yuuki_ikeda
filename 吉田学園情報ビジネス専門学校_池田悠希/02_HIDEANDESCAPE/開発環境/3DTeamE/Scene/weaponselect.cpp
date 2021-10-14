//=============================================================================
//
// 武器選択処理 [weaponselect.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "weaponselect.h"
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
#include "assaultbutton.h"
#include "handgunbutton.h"
#include "weaponselectscene.h"
#include "sound.h"
#include "returntitlebutton.h"
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CWeaponSelect::CWeaponSelect()
{
	m_pCamera = NULL;
	m_pStage01 = NULL;
	m_pTitleLogo = NULL;
	m_pTutorialButton = NULL;
	m_pStartButton = NULL;
	m_pAssaultButton = NULL;
	m_pHandgunButton = NULL;
	m_pWeaponSelectScene = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CWeaponSelect::~CWeaponSelect()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWeaponSelect::Init(void)
{
											//カメラオブジェクトの生成
	m_pCamera = new CCamera;
	//カメラ初期化処理
	m_pCamera->Init();
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->StopSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_WEAPONSELECT);
	//カメラ位置セット
	m_pWeaponSelectScene = CWeaponSelectScene::Create(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pAssaultButton = CAssaultButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT - (SCREEN_HEIGHT / 4) - 100, 0.0f), D3DXVECTOR3(700, 600, 0.0f));
	m_pHandgunButton = CHandgunButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT - (SCREEN_HEIGHT / 4) - 100, 0.0f), D3DXVECTOR3(700, 600, 0.0f));
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CWeaponSelect::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CWeaponSelect::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CWeaponSelect::Uninit(void)
{
	CObject::ReleaseAll();
}
