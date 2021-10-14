//=============================================================================
//
//  軽装武装機 [light_enemy.cpp]
// Author : 吉田悠人 二階堂汰一
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WARY_TIME 50	//プレイヤーに気が付くまでの時間
#define MAX_LIFE 100

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "renderer.h"
#include "manager.h"
#include "light_enemy.h"
#include "enemy.h"
#include "animation.h"
#include "player.h"
#include "input.h"
#include "inputkeyboard.h"
#include "exclamationmark.h"
#include "question.h"
#include "explosion.h"

//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************
CModel::MODELDATA CLightEnemy::m_modeldata[PARTS_MAX] = {};
CAnimation * CLightEnemy::m_pAnimaSave = NULL;
CLightEnemy::PARTS_DATA CLightEnemy::m_PartsData[PARTS_MAX]=
{
	{"Data/Model/Enemy/LightEnemy/00_mainhead,body,guns.x",-1 ,D3DXVECTOR3(0.0f,20.0f,0.0f), },
	{"Data/Model/Enemy/LightEnemy/01_Right_hutomomo.x",0 ,D3DXVECTOR3(-5.0f,0.0f,8.0f), },
	{ "Data/Model/Enemy/LightEnemy/02_Right_foot.x",1 ,D3DXVECTOR3(0.0f,-6.0f,-10.0f), },
	{ "Data/Model/Enemy/LightEnemy/03_left_hutomomo.x",0 ,D3DXVECTOR3(5.0f,0.0f,8.0f), },
	{"Data/Model/Enemy/LightEnemy/04_left_foot.x",3 ,D3DXVECTOR3(0.0f,-6.0f,-10.0f), }
};

//=============================================================================
// コンストラクタ
//=============================================================================
CLightEnemy::CLightEnemy()
{
	memset(m_apModel, NULL, sizeof(m_apModel));
	m_AnimaMotion = CAnimation::MOTION_LIGHT_ENEMY_NEUTRAL;
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
CLightEnemy::~CLightEnemy()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CLightEnemy::Load(void)
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
void CLightEnemy::Unload(void)
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

		for (int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
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
CLightEnemy * CLightEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CLightEnemy* pLightEnemy = NULL;
	pLightEnemy = new CLightEnemy;
	pLightEnemy->SetPos(pos);
	pLightEnemy->SetRot(rot);
	pLightEnemy->SetSize(D3DXVECTOR3(1.2f, 1.2f, 1.2f));
	//巡回ルート設定
	pLightEnemy->SetTour(0, pos);

	pLightEnemy->Init();

	return pLightEnemy;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CLightEnemy::Init(void)
{
	CEnemy::Init();
	//アニメーション生成
	m_pAnimaSave = CAnimation::Create(CAnimation::ANIMATION_LIGHT_ENEMY);
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
void CLightEnemy::Uninit(void)
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
void CLightEnemy::Update(void)
{
	//エネミーアップデート
	CEnemy::Update();
	//距離
	float *fDistance = NULL;


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
			if (Search(300.0f, 60.0f) == true&& CManager::GetPlayer()->GetState() != CPlayer::STATE_DEATH)	//索敵関数		
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
				SetQuestion(CQuestion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 50, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(10.0f, 10.0f, 10.0f)));
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
				SetExclamation(CExclamationMark::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 50, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(10.0f, 10.0f, 10.0f)));
				//使っている
				m_bDiscovery = true;
			}
			//攻撃アニメーション
			m_pAnime->SetAnimation(CAnimation::MOTION_LIGHT_ENEMY_ATTACK);

			//攻撃関数
			Attack(-1);

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

	if (GetMode()!= ENEMY_FOUND)
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
	case STATE_NORMAL:		//通常
		break;
	case STATE_DAMAGE:		//ダメージ
		//ダメージを食らうと警戒状態に移行
		if (GetMode() == ENEMY_TOUR)
		{
			SetMode(ENEMY_WARY);
		}
	
		SetState(STATE_NORMAL);		
		break;
	case STATE_DEATH:		//破壊
		if (m_pAnime->GetAnimeEnd() == false&& m_pAnime->GetAnimation()== CAnimation::MOTION_LIGHT_ENEMY_DEATH)
		{
			//爆発
			CExplosion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 30, GetPos().z), ZEROVECTOR3, D3DXVECTOR3(100, 100, 100));

			//終了処理
			Uninit();
		}

		if (m_pAnime->GetAnimation() != CAnimation::MOTION_LIGHT_ENEMY_DEATH)
		{
			m_pAnime->SetAnimation(CAnimation::MOTION_LIGHT_ENEMY_DEATH);
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
void CLightEnemy::Draw(void)
{

}

//=============================================================================
// パーツアップデート関数
//=============================================================================
void CLightEnemy::PartsUpdate(void)
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
