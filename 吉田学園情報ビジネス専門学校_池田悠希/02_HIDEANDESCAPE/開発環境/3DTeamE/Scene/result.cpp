//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "result.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage03.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "goal.h"
#include "resultscene.h"
#include "sound.h"
#include "mission.h"
#include "clear.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	m_pResultScene = NULL;
	m_pMission = NULL;
	m_pClear = NULL;
	m_nCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);
	while (ShowCursor(true)<0);
	m_pMission = CMission::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -100, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 100, 0.0f));
	m_pClear = CClear::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0.0f));
	m_nCount = 0;
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	m_nCount++;

	if (m_nCount == 600)
	{
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	
}

