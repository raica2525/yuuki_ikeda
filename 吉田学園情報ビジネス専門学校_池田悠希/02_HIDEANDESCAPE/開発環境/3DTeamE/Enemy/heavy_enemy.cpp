//=============================================================================
//
// 重武装機 [heavy_enemy.cpp]
// Author : 吉田悠人 二階堂汰一
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WARY_TIME 30	//プレイヤーに気が付くまでの時間
#define MAX_LIFE 200

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "renderer.h"
#include "manager.h"
#include "heavy_enemy.h"
#include "enemy.h"
#include "animation.h"
#include "manager.h"
#include "player.h"
#include "exclamationmark.h"
#include "explosion.h"
#include "question.h"
//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************
CModel::MODELDATA CHeavyEnemy::m_modeldata[PARTS_MAX] = {};
CAnimation * CHeavyEnemy::m_pAnimaSave = NULL;
CHeavyEnemy::PARTS_DATA CHeavyEnemy::m_PartsData[PARTS_MAX] =
{
	{ "Data/Model/Enemy/HeavyEnemy/00_MainHead,Body,Gun.x",-1 ,D3DXVECTOR3(0.0f,280.0f,0.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/04_LeftHutomomo.x",0 ,D3DXVECTOR3(-45.0f,0.0f,0.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/02_RightHukurahagi.x",1 ,D3DXVECTOR3(0.0f,-110.0f,-20.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/03_RightFoot.x",2 ,D3DXVECTOR3(0.0f,-130.0f,20.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/04_LeftHutomomo.x",0 ,D3DXVECTOR3(45.0f,0.0f,0.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/02_RightHukurahagi.x",4 ,D3DXVECTOR3(0.0f,-110.0f,-25.0f), },
	{ "Data/Model/Enemy/HeavyEnemy/06_LeftFoot.x",5 ,D3DXVECTOR3(5.0f,-130.0f,25.0f), }


};

//=============================================================================
// コンストラクタ
//=============================================================================
CHeavyEnemy::CHeavyEnemy()
{
	memset(m_apModel, NULL, sizeof(m_apModel));
	m_AnimaMotion = CAnimation::MOTION_HEAVY_ENEMY_NEUTRAL;
	for (int nCount = 0; nCount < PARTS_MAX/*(読み込んだモデル数分)*/; nCount++)
	{
		m_Partsrot[nCount] = ZEROVECTOR3;		//パーツrot情報
		m_Partspos[nCount] = ZEROVECTOR3;		//パーツpos情報
	}
	SetMode(ENEMY_TOUR);	//行動モード
	m_fSpeed = 0.0f;		//スピード
	m_bSearch = false;		//捜しているかどうか
	m_pAnime = NULL;		//アニメーションポインタ
	nWaryCoutn = 0;			//警戒カウント
	m_bWary = false;		//?
	m_bDiscovery = false;	//!
}

//=============================================================================
// デストトラクタ
//=============================================================================
CHeavyEnemy::~CHeavyEnemy()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CHeavyEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	for (int nCount = 0; nCount < PARTS_MAX/*(txtから読み込んだモデル数分)*/; nCount++)
	{
		D3DXLoadMeshFromX(m_PartsData[nCount].FileName, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata[nCount].pBuffMat, NULL, &m_modeldata[nCount].nNumMat, &m_modeldata[nCount].pMesh);
	}
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CHeavyEnemy::Unload(void)
{
	for (int nCount = 0; nCount < PARTS_MAX; nCount++)
	{
		if (m_modeldata[nCount].pBuffMat != NULL)
		{
			m_modeldata[nCount].pBuffMat->Release();
		}

		if (m_modeldata[nCount].pMesh != NULL)
		{
			m_modeldata[nCount].pMesh->Release();
		}

		for (int nCountTex = 0; nCountTex < PARTS_MAX; nCountTex++)
		{
			if (m_modeldata[nCount].pTexture[nCountTex] != NULL)
			{
				m_modeldata[nCount].pTexture[nCountTex]->Release();
			}
		}
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CHeavyEnemy * CHeavyEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CHeavyEnemy* pLightEnemy = NULL;
	pLightEnemy = new CHeavyEnemy;
	pLightEnemy->SetPos(pos);
	pLightEnemy->SetRot(rot);
	pLightEnemy->SetSize(D3DXVECTOR3(0.2f,0.2f,0.2f));
	//巡回ルート設定
	pLightEnemy->SetTour(0, pos);

	pLightEnemy->Init();

	return pLightEnemy;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CHeavyEnemy::Init(void)
{
	CEnemy::Init();
	//アニメーション生成
	m_pAnimaSave = CAnimation::Create(CAnimation::ANIMATION_HEAVY_ENEMY);
	CEnemy::SetLife(MAX_LIFE);
	//モデル生成
	for (int nCount = 0; nCount < PARTS_MAX/*(読み込んだモデル数分)*/; nCount++)
	{
		if (m_PartsData[nCount].nParent == -1)
		{
			m_apModel[nCount] = CModel::Create(CEnemy::GetWorld(), this, m_modeldata[nCount], m_PartsData[nCount].Partspos, m_Partsrot[nCount], D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_apModel[nCount] = CModel::Create(m_apModel[m_PartsData[nCount].nParent], this, m_modeldata[nCount], m_PartsData[nCount].Partspos, m_Partsrot[nCount], D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		}
	}
	m_pAnime = m_pAnimaSave;	//アニメ保存
	m_pAnime->SetAnimation(CAnimation::MOTION_LIGHT_ENEMY_NEUTRAL);

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CHeavyEnemy::Uninit(void)
{
	for (int nCount = 0; nCount < PARTS_MAX/*(読み込んだモデル数分)*/; nCount++)
	{
		m_apModel[nCount]->Uninit();
	}
	CEnemy::Uninit();
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CHeavyEnemy::Update(void)
{
	//エネミーアップデート
	CEnemy::Update();
	//行動
	if (GetState() != STATE_DEATH)
	{
		switch (GetMode())
		{
		case ENEMY_TOUR:
			//巡回関数
			if (Tour() == true)
			{
				//歩くアニメーションセット
				m_pAnime->SetAnimation(CAnimation::MOTION_LIGHT_ENEMY_MOVE);

			}
			if (Search(300.0f, 70.0f) == true && CManager::GetPlayer()->GetState() != CPlayer::STATE_DEATH)	//索敵関数		
			{
				//発見したとき
				SetMode(ENEMY_WARY);
			}

			break;
		case ENEMY_WARY:
			//クエスチョンマーク処理
			if (m_bWary == false)
			{
				//クエスチョンマーク生成
				SetQuestion(CQuestion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 85, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(10.0f, 10.0f, 10.0f)));
				//使っている処理
				m_bWary = true;
			}
			//アニメーション立ち止まる
			m_pAnime->SetAnimation(CAnimation::MOTION_LIGHT_ENEMY_NEUTRAL);

			//発見関数
			if (Found())
			{
				//向き関数
				Direction(CManager::GetPlayer()->GetPos());

				//視界に入っている
				nWaryCoutn++;
			}
			else
			{
				//視界に入っていない
				nWaryCoutn--;
			}
			//一定時間見つかっていると
			if (nWaryCoutn>WARY_TIME)
			{
				//カウント初期化
				nWaryCoutn = 0;
				//攻撃開始
				SetMode(ENEMY_FOUND);
			}

			//一定時間見つからないと
			if (nWaryCoutn<0)
			{
				//巡回状態
				SetMode(ENEMY_TOUR);
				nWaryCoutn = 0;
			}
			break;
		case ENEMY_FOUND:	//プレイヤー発見

							//発見マーク処理
			if (m_bDiscovery == false)
			{
				//発見マーク生成
				SetExclamation(CExclamationMark::Create(D3DXVECTOR3(GetPos().x, GetPos().y +85, GetPos().z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f)));
				//使っている
				m_bDiscovery = true;
			}
			//攻撃アニメーション
			m_pAnime->SetAnimation(CAnimation::MOTION_HEAVY_ENEMY_ATTACK);

			//攻撃関数
			Attack(-3);

			//向き関数
			Direction(CManager::GetPlayer()->GetPos());

			//発見関数
			if (!Found())
			{
				//見失ったとき
				SetMode(ENEMY_WARY);
			}
			//プレイヤーが死んだとき
			if (CManager::GetPlayer()->GetState() == CPlayer::STATE_DEATH)
			{
				SetMode(ENEMY_TOUR);

			}
			break;
		default:
			break;
		}
	}


	if (GetMode() != ENEMY_FOUND)
	{
		//NULLチェック
		if (GetExclamation() != NULL)
		{
			GetExclamation()->Uninit();
			SetExclamation(NULL);
		}
		m_bDiscovery = false;
	}

	if (GetMode() != ENEMY_WARY)
	{
		//NULLチェック
		if (GetQuestion() != NULL)
		{
			GetQuestion()->Uninit();
			SetQuestion(NULL);
		}
		m_bWary = false;
	}


	switch (GetState())		
	{
		//通常
	case STATE_NORMAL:		
		break;
		//ダメージ
	case STATE_DAMAGE:		
							//ダメージを食らうと警戒状態に移行
		if (GetMode() == ENEMY_TOUR)
		{
			SetMode(ENEMY_WARY);
		}

		SetState(STATE_NORMAL);
		break;
	case STATE_DEATH:		//破壊

		if (m_pAnime->GetAnimeEnd() == false && m_pAnime->GetAnimation() == CAnimation::MOTION_HEAVY_ENEMY_DEATH)
		{
			//爆発
			CExplosion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 30, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(100, 100, 100));

			//終了処理
			Uninit();
		}
		//アニメーション再生
		if (m_pAnime->GetAnimation() != CAnimation::MOTION_HEAVY_ENEMY_DEATH)
		{
			m_pAnime->SetAnimation(CAnimation::MOTION_HEAVY_ENEMY_DEATH);
		}
		break;
	default:
		break;
	}
	//パーツアニメーション
	PartsUpdate();

}

//=============================================================================
// 描画関数
//=============================================================================
void CHeavyEnemy::Draw(void)
{

}

//=============================================================================
// パーツアップデート関数
//=============================================================================
void CHeavyEnemy::PartsUpdate(void)
{
	if (m_pAnime != NULL)
	{
		for (int nCount = 0; nCount < PARTS_MAX/*(読み込んだモデル数分)*/; nCount++)
		{
			m_apModel[nCount]->SetAnimationRot(m_Partsrot[nCount]);
			m_apModel[nCount]->SetAnimationPos(m_Partspos[nCount]);
		}
		m_pAnime->Update();
		for (int nCount = 0; nCount < PARTS_MAX/*(読み込んだモデル数分)*/; nCount++)
		{
			m_Partsrot[nCount] = m_pAnime->GetAnimeRot(nCount);
			m_Partspos[nCount] = m_pAnime->GetAnimePos(nCount);
			m_pAnime->SetAnimeRot(nCount, m_Partsrot[nCount]);
			m_pAnime->SetAnimePos(nCount, m_Partspos[nCount]);
		}
	}
}
