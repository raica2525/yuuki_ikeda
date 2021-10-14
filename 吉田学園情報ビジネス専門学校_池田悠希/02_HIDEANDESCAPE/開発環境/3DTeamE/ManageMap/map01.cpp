//=============================================================================
//
// マップ01処理 [map01.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "map01.h"
#include "manager.h"
#include "camera.h"
#include "object.h"
#include "stage01.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "goal.h"
#include "sound.h"
#include "light_enemy.h"
#include "uav.h"
#include "item.h"
#include "trap.h"
//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CMap01::CMap01()
{
	m_pCamera = NULL;
	m_pStage01 = NULL;
	m_pPlayer = NULL;
	bCollEnemy = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMap01::~CMap01()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMap01::Init(void)
{
	//サウンドの取得
	CSound * pSound = CManager::GetSound();
	pSound->StopSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM_MAP);

											//カメラオブジェクトの生成
	m_pCamera = new CCamera;
	//カメラ初期化処理
	m_pCamera->Init();
	//カメラ位置セット
	SetCursorPos(((int)SCREEN_WIDTH / 2), ((int)SCREEN_HEIGHT / 2));
	//プレイヤーセット
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(260.0f, 0.0f, -600.0f), D3DXVECTOR3(45, 180, 0), D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	//ステージセット
	m_pStage01 = CStage01::Create(ZEROVECTOR3, ZEROVECTOR3, D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	//ゴールセット
	CGoal::Create(D3DXVECTOR3(-100.0f, 50.0f, 650.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXCOLOR(255, 0, 0, 255), CManager::MODE_MAP02);

	//トラップセット
	CTrap::Create(D3DXVECTOR3(110.0f, 35.0f, -90.0f), D3DXVECTOR3(10.0f, 35.0f, -90.0f));
	CTrap::Create(D3DXVECTOR3(195.0f, 35.0f, 120.0f), D3DXVECTOR3(25.0f, 35.0f, 90.0f));
	CTrap::Create(D3DXVECTOR3(-120.0f, 35.0f, 580.0f), D3DXVECTOR3(-120.0f, 35.0f, 515.0f));

	//アイテムセット
	CItem::Create(D3DXVECTOR3(-70.0f, 25.0f, 550.0f), ZEROVECTOR3);

	//エネミーセット
	m_pLightEnemy[0] = CLightEnemy::Create(D3DXVECTOR3(180.0f,0.0f,-140.f), D3DXVECTOR3(0.0f, 90.0f, 0.0f));
	//巡回位置セット
	if (m_pLightEnemy[0] != NULL)
	{
		m_pLightEnemy[0]->SetTour(1, D3DXVECTOR3(270.0f, 0.0f, -140.f));
		m_pLightEnemy[0]->SetTour(2, D3DXVECTOR3(270.0f, 0.0f, -30.f));
		m_pLightEnemy[0]->SetTour(3, D3DXVECTOR3(180.0f, 0.0f, -30.f));
	}
	//エネミーセット
	m_pUav[0] = CUav::Create(D3DXVECTOR3(-190.0f, 0.0f, 480.f), ZEROVECTOR3);
	if (m_pUav[0] != NULL)
	{
		m_pUav[0]->SetTour(1, D3DXVECTOR3(-190.0f, 0.0f, 170.0f));
		m_pUav[0]->SetTour(2, D3DXVECTOR3(-85.0f, 0.0f, 170.0f));
		m_pUav[0]->SetTour(3, D3DXVECTOR3(-85.0f, 0.0f, 480.f));
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CMap01::Update(void)
{
	//カメラ処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	if (m_pUav[0]->EnemyCall() == true)
	{
		//敵の増援が来ているか
		if (bCollEnemy != true)
		{		
			//来ていなければ追加
			m_pLightEnemy[1] = CLightEnemy::Create(D3DXVECTOR3(-30.0f, 0.0f, 650.f), ZEROVECTOR3);
			//巡回位置セット
			if (m_pLightEnemy[1] != NULL)
			{
				m_pLightEnemy[1]->SetTour(0, D3DXVECTOR3(20.0f, 0.0f, 520.0f));

				m_pLightEnemy[1]->SetTour(1, D3DXVECTOR3(135.0f, 0.0f, 520.0f));
				m_pLightEnemy[1]->SetTour(2, D3DXVECTOR3(135.0f, 0.0f, 280.0f));

				m_pLightEnemy[1]->SetTour(3, D3DXVECTOR3(-20.0f, 0.0f, 280.f));

			}



			//増援が来ている
			bCollEnemy = true;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CMap01::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CMap01::Uninit(void)
{
	CObject::ReleaseAll();
}
