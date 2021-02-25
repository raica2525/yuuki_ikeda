//=============================================================================
//
// マップ02処理 [map02.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "map02.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage02.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "goal.h"
#include "sound.h"
#include "trap.h"
#include "uav.h"
#include "light_enemy.h"
#include "item.h"

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CMap02::CMap02()
{
	bCollEnemy = false;
	m_pCamera = NULL;
	m_pStage02 = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMap02::~CMap02()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMap02::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_MAP);
	//増援判定用初期化
	bCollEnemy = false;
	//ベクトル定義
	D3DXVECTOR3 vec = D3DXVECTOR3(0, 0, 0); 
	//カメラオブジェクトの生成
	m_pCamera = new CCamera;
	//カメラ初期化処理
	m_pCamera->Init();
	//カメラ位置セット
	SetCursorPos(((int)SCREEN_WIDTH / 2), ((int)SCREEN_HEIGHT / 2));
	//プレイヤー位置セット
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-245.0f, 0.0f, 660.0f), D3DXVECTOR3(45, 180, 0), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	//マップモデル位置セット
	m_pStage02 = CStage02::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), vec, D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	//ゴール位置セット
	CGoal::Create(D3DXVECTOR3(-170.0f, 50.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR3(50.0f, 100.0f, 50.0f), D3DXCOLOR(255, 0, 0, 255), CManager::MODE_MAP03);
	//回復アイテム
	CItem::Create(D3DXVECTOR3(0.0f, 25.0f, 155.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CItem::Create(D3DXVECTOR3(-75.0f, 25.0f, -320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//トラップ位置セット
	CTrap::Create(D3DXVECTOR3(175.0f, 35.0f, 380.0f), D3DXVECTOR3(-30.0f, 35.0f, 380.0f));
	CTrap::Create(D3DXVECTOR3(80.0f,35.0f,270.0f), D3DXVECTOR3(-25.0f,35.0f,270.0f));
	
	CTrap::Create(D3DXVECTOR3(220.0f,35.0f,120.0f), D3DXVECTOR3(220.0f,35.0f,200.0f));
	CTrap::Create(D3DXVECTOR3(75.0f, 35.0f, -460.0f), D3DXVECTOR3(-5.0f, 35.0f, -460.0f));
	CTrap::Create(D3DXVECTOR3(-10.0f, 35.0f, -645.0f), D3DXVECTOR3(-10.0f, 35.0f, -600.0f));


	//偵察機位置セット
	//マップ上
	m_pUav = CUav::Create(D3DXVECTOR3(240.0f, 0.0f, 200.f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pUav != NULL)
	{
		m_pUav->SetTour(1, D3DXVECTOR3(240.0f, 0.0f, 70.f));
		m_pUav->SetTour(2, D3DXVECTOR3(130.0f, 0.0f, 70.f));
		m_pUav->SetTour(3, D3DXVECTOR3(240.0f, 0.0f, 70.f));
	}

	//マップ左柱
	m_pLightEnemy[0] = CLightEnemy::Create(D3DXVECTOR3(-160.0f, 0.0f, 470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pLightEnemy[0] != NULL)
	{
		m_pLightEnemy[0]->SetTour(1, D3DXVECTOR3(-160.0f, 0.0f, 340.f));
		m_pLightEnemy[0]->SetTour(2, D3DXVECTOR3(-90.0f, 0.0f, 340.f));
		m_pLightEnemy[0]->SetTour(3, D3DXVECTOR3(-90.0f, 0.0f, 470.f));
	}

	//マップ真ん中木箱回り
	m_pLightEnemy[1] = CLightEnemy::Create(D3DXVECTOR3(-15.0f, 0.0f, -80.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pLightEnemy[1] != NULL)
	{
		m_pLightEnemy[1]->SetTour(1, D3DXVECTOR3(-100.0f, 0.0f, -80.f));
		m_pLightEnemy[1]->SetTour(2, D3DXVECTOR3(-100.0f, 0.0f, -195.f));
		m_pLightEnemy[1]->SetTour(3, D3DXVECTOR3(-15.0f, 0.0f, -195.f));
	}

	//マップ右下木箱回り
	m_pLightEnemy[2] = CLightEnemy::Create(D3DXVECTOR3(-60.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pLightEnemy[2] != NULL)
	{
		m_pLightEnemy[2]->SetTour(1, D3DXVECTOR3(-60.0f, 0.0f, -370.f));
		m_pLightEnemy[2]->SetTour(2, D3DXVECTOR3(-130.0f, 0.0f, -370.f));
		m_pLightEnemy[2]->SetTour(3, D3DXVECTOR3(-130.0f, 0.0f, -450.f));
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CMap02::Update(void)
{
	//デバッグ用
	//=============================================================================
#ifdef _DEBUG
	if (((CInputKeyboard*)CManager::GetInputKey())->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_MAP03);
	}
#endif
	//=============================================================================

	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//偵察機がプレイヤーを発見しているか
	if (m_pUav->EnemyCall() == true)
	{
		//敵の増援が来ているか
		if (bCollEnemy!=true)
		{
			//来ていなければ追加
			m_pLightEnemy[3] = CLightEnemy::Create(D3DXVECTOR3(-70.0f, 0.0f, -580.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			if (m_pLightEnemy[3] != NULL)
			{
				m_pLightEnemy[3]->SetTour(1, D3DXVECTOR3(-70.0f, 0.0f, -500.f));
				m_pLightEnemy[3]->SetTour(2, D3DXVECTOR3(-130.0f, 0.0f, -500.f));
				m_pLightEnemy[3]->SetTour(3, D3DXVECTOR3(-130.0f, 0.0f, -580.f));
			}
			//増援が来ている
			bCollEnemy = true;
		}

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CMap02::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CMap02::Uninit(void)
{
	CObject::ReleaseAll();
}

