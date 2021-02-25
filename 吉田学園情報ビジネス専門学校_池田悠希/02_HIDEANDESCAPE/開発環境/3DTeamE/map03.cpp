//=============================================================================
//
// マップ03処理 [map03.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "map03.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage03.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "goal.h"
#include "Obstacle.h"
#include "sound.h"
#include "woodenbox.h"
#include "item.h"
#include "handgunbutton.h"
#include "light_enemy.h"
#include "uav.h"
#include "trap.h"
#include "heavy_enemy.h"
#include "computer.h"
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CMap03::CMap03()
{
	m_pCamera = NULL;
	m_pStage03 = NULL;
	m_pObstacle = NULL;


	m_pUav[3] = {};
	m_pLightEnemy[6] = {}; 
	m_pHeavyEnemy[1] = {};
	m_pComputer = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMap03::~CMap03()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMap03::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_MAP);
	D3DXVECTOR3 vec = D3DXVECTOR3(0, 0, 0); //ベクトル定義
	for (int nCount = 0; nCount < 3; nCount++)
	{
		bCollEnemy[nCount] = false;
	}

	//カメラオブジェクトの生成
	m_pCamera = new CCamera;
	//カメラ初期化処理
	m_pCamera->Init();
	//カメラ位置セット
	SetCursorPos(((int)SCREEN_WIDTH / 2), ((int)SCREEN_HEIGHT / 2));
	//プレイヤーの位置セット
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-700.0f, 0.0f, -425.0f), D3DXVECTOR3(45, 180, 0), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	//ステージモデル設置

	m_pStage03 = CStage03::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.7f, 1.7f, 1.7f));
	//コンピュータ生成
	//m_pComputer = CComputer::Create(D3DXVECTOR3(635, 0, 550), D3DXVECTOR3(0, D3DXToRadian(90.0f), 0), D3DXVECTOR3(3.0f, 3.0f, 2.2f));
	//ゴール設置


	CGoal::Create(D3DXVECTOR3(635.0f, 50.0f, 435.0f), D3DXVECTOR3(0.0f, 10.0f, -1.0f), D3DXVECTOR3(85.0f, 100.0f, 85.0f), D3DXCOLOR(255, 0, 0, 255), CManager::MODE_MAP04);
	
	//アイテム設置
	CItem::Create(D3DXVECTOR3(280.0f, 25.0f, -320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CItem::Create(D3DXVECTOR3(-10.0f, 25.0f, -20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//トラップ設置
	CTrap::Create(D3DXVECTOR3(-615.0f, 35.0f, -240.0f), D3DXVECTOR3(-500.0f, 35.0f, -240.0f));
	CTrap::Create(D3DXVECTOR3(-400.0f, 35.0f, -135.0f), D3DXVECTOR3(-400.0f, 35.0f, -55.0f));
	CTrap::Create(D3DXVECTOR3(-520.0f, 35.0f, 135.0f), D3DXVECTOR3(-520.0f, 35.0f, 200.0f));
	CTrap::Create(D3DXVECTOR3(-390.0f, 35.0f, 135.0f), D3DXVECTOR3(-390.0f, 35.0f, 200.0f));
	CTrap::Create(D3DXVECTOR3(80.0f, 35.0f, -10.0f), D3DXVECTOR3(80.0f, 35.0f, 80.0f));

	//偵察機設置（①）
	m_pUav[0] = CUav::Create(D3DXVECTOR3(-500.0f, 0.0f, -115.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pUav != NULL)
	{
		m_pUav[0]->SetTour(1, D3DXVECTOR3(-500.0f, 0.0f, -200.0f));
		m_pUav[0]->SetTour(2, D3DXVECTOR3(-430.0f, 0.0f, -200.0f));
		m_pUav[0]->SetTour(3, D3DXVECTOR3(-430.0f, 0.0f, -115.0f));
	}
	//偵察機設置（②）
	m_pUav[1] = CUav::Create(D3DXVECTOR3(-180.0f, 0.0f, 120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pUav != NULL)
	{
		m_pUav[1]->SetTour(1, D3DXVECTOR3(-240.0f, 0.0f, 120.0f));
		m_pUav[1]->SetTour(2, D3DXVECTOR3(-240.0f, 0.0f, 60.0f));
		m_pUav[1]->SetTour(3, D3DXVECTOR3(-180.0f, 0.0f, 60.0f));
	}
	//偵察機設置（③）
	m_pUav[2] = CUav::Create(D3DXVECTOR3(-180.0f, 0.0f, -430.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pUav != NULL)
	{
		m_pUav[2]->SetTour(1, D3DXVECTOR3(-110.0f, 0.0f, -430.0f));
		m_pUav[2]->SetTour(2, D3DXVECTOR3(-110.0f, 0.0f, -360.0f));
		m_pUav[2]->SetTour(3, D3DXVECTOR3(-180.0f, 0.0f, -360.0f));
	}

	//軽装エネミー設置(下のゴール付近)
	m_pLightEnemy[0] = CLightEnemy::Create(D3DXVECTOR3(-320.0f, 0.0f, -430.0f) , D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pLightEnemy[0] != NULL)
	{
		m_pLightEnemy[0]->SetTour(1, D3DXVECTOR3(-250.0f, 0.0f, -430.0f));
		m_pLightEnemy[0]->SetTour(2, D3DXVECTOR3(-250.0f, 0.0f, -370.0f));
		m_pLightEnemy[0]->SetTour(3, D3DXVECTOR3(-320.0f, 0.0f, -370.0f));
	}

	//軽装エネミー設置(下の柱回り)
	m_pLightEnemy[1] = CLightEnemy::Create(D3DXVECTOR3(-20.0f, 0.0f, -290.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pLightEnemy[1] != NULL)
	{
		m_pLightEnemy[1]->SetTour(1, D3DXVECTOR3(-20.0f, 0.0f, -350.0f));
		m_pLightEnemy[1]->SetTour(2, D3DXVECTOR3(45.0f, 0.0f, -350.0f));
		m_pLightEnemy[1]->SetTour(3, D3DXVECTOR3(45.0f, 0.0f, -290.0f));
	}

	//軽装エネミー設置(上の鉄箱回り)
	m_pLightEnemy[2] = CLightEnemy::Create(D3DXVECTOR3(-345.0f, 0.0f, 95.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pLightEnemy[2] != NULL)
	{
		m_pLightEnemy[2]->SetTour(1, D3DXVECTOR3(-410.0f, 0.0f, 95.0f));
		m_pLightEnemy[2]->SetTour(2, D3DXVECTOR3(-410.0f, 0.0f, 5.0f));
		m_pLightEnemy[2]->SetTour(3, D3DXVECTOR3(-345.0f, 0.0f, 5.0f));
	}

	//重装エネミー設置
	m_pHeavyEnemy[0] = CHeavyEnemy::Create(D3DXVECTOR3(270.0f, 0.0f, -145.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//巡回位置セット
	if (m_pHeavyEnemy[0] != NULL)
	{
		m_pHeavyEnemy[0]->SetTour(1, D3DXVECTOR3(165.0f, 0.0f, -145.0f));
		m_pHeavyEnemy[0]->SetTour(2, D3DXVECTOR3(165.0f, 0.0f, -205.0f));
		m_pHeavyEnemy[0]->SetTour(3, D3DXVECTOR3(270.0f, 0.0f, -205.0f));
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CMap03::Update(void)
{
	//デバッグ用
	//=============================================================================
#ifdef _DEBUG

	if (((CInputKeyboard*)CManager::GetInputKey())->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_MAP04);
	}
#endif
	//=============================================================================

	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//偵察機(1)がプレイヤーを発見しているか
	if (m_pUav[0]->EnemyCall() == true)
	{
		//敵の増援が来ているか
		if (bCollEnemy[0] != true)
		{
			//来ていなければ追加
			m_pLightEnemy[3] = CLightEnemy::Create(D3DXVECTOR3(280.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			if (m_pLightEnemy[3] != NULL)
			{
				m_pLightEnemy[3]->SetTour(0, D3DXVECTOR3(-50.0f, 0.0f, 30.0f));
				m_pLightEnemy[3]->SetTour(1, D3DXVECTOR3(-50.0f, 0.0f, -20.0f));
				m_pLightEnemy[3]->SetTour(2, D3DXVECTOR3(-125.0f, 0.0f, -20.0f));
				m_pLightEnemy[3]->SetTour(3, D3DXVECTOR3(-125.0f, 0.0f, 30.0f));
			}
			//増援が来ている
			bCollEnemy[0] = true;
		}

	}
	//偵察機(2)がプレイヤーを発見しているか
	if (m_pUav[1]->EnemyCall() == true)
	{
		//敵の増援が来ているか
		if (bCollEnemy[1] != true)
		{
			//来ていなければ追加
			m_pLightEnemy[4] = CLightEnemy::Create(D3DXVECTOR3(280.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			if (m_pLightEnemy[4] != NULL)
			{
				m_pLightEnemy[4]->SetTour(0, D3DXVECTOR3(220.0f, 0.0f, 40.0f));
				m_pLightEnemy[4]->SetTour(1, D3DXVECTOR3(140.0f, 0.0f, 40.0f));
				m_pLightEnemy[4]->SetTour(2, D3DXVECTOR3(140.0f, 0.0f, -20.0f));
				m_pLightEnemy[4]->SetTour(3, D3DXVECTOR3(220.0f, 0.0f, -20.0f));
			}
			//増援が来ている
			bCollEnemy[1] = true;
		}

	}
	//偵察機(3)がプレイヤーを発見しているか
	if (m_pUav[2]->EnemyCall() == true)
	{
		//敵の増援が来ているか
		if (bCollEnemy[2] != true)
		{
			//来ていなければ追加
			m_pLightEnemy[5] = CLightEnemy::Create(D3DXVECTOR3(380.0f, 0.0f, -80.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			if (m_pLightEnemy[5] != NULL)
			{
				m_pLightEnemy[5]->SetTour(0, D3DXVECTOR3(360.0f, 0.0f, -270.0f));
				m_pLightEnemy[5]->SetTour(1, D3DXVECTOR3(120.0f, 0.0f, -270.0f));
				m_pLightEnemy[5]->SetTour(2, D3DXVECTOR3(120.0f, 0.0f, -440.0f));
				m_pLightEnemy[5]->SetTour(3, D3DXVECTOR3(360.0f, 0.0f, -440.0f));
			}
			//増援が来ている
			bCollEnemy[2] = true;
		}

	}


}

//=============================================================================
// 描画処理
//=============================================================================
void CMap03::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CMap03::Uninit(void)
{
	CObject::ReleaseAll();
}

