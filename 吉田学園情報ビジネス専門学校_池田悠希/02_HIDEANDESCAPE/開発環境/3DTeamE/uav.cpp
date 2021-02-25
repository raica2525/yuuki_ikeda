//=============================================================================
//
// 偵察機処理 [uav.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "renderer.h"
#include "manager.h"
#include "uav.h"
#include "enemy.h"
#include "exclamationmark.h"
#include "question.h"
#include "player.h"
#include "explosion.h"
#include "explosion2.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WARY_TIME 35	//プレイヤーに気が付くまでの時間
#define MAX_LIFE 10

//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************
CModel::MODELDATA CUav::m_modeldata = {};
D3DXMATERIAL * CUav::m_pMat = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CUav::CUav()
{
	m_pModel = NULL;
	SetMode(ENEMY_TOUR);	//行動モード
	m_nLife = 0;		//ライフ
	m_fSpeed = 0.0f;		//スピード
	m_bSearch = false;		//捜してるかどうか
	nWaryCoutn = 0;		//警戒カウント
	m_bWary = false;		//?
	m_bDiscovery = false;	//!
	bCall = false;
	m_nFly = 0;				//飛ぶまでのカウント
}

//=============================================================================
// デストトラクタ
//=============================================================================
CUav::~CUav()
{
}

//=============================================================================
// モデル読み込み関数
//=============================================================================
HRESULT CUav::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXLoadMeshFromX("Data/Model/Enemy/Uav/Teisatuki.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modeldata.pBuffMat, NULL, &m_modeldata.nNumMat, &m_modeldata.pMesh);
	return S_OK;
}

//=============================================================================
// モデル破棄関数
//=============================================================================
void CUav::Unload(void)
{
	if (m_modeldata.pBuffMat != NULL)
	{
		m_modeldata.pBuffMat->Release();
	}

	if (m_modeldata.pMesh != NULL)
	{
		m_modeldata.pMesh->Release();
	}

	for (int nCountTex = 0; nCountTex < MAX_MATERIAL; nCountTex++)
	{
		if (m_modeldata.pTexture[nCountTex] != NULL)
		{
			m_modeldata.pTexture[nCountTex]->Release();
		}
	}
}

//=============================================================================
// 生成関数
//=============================================================================
CUav * CUav::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CUav* pUav = NULL;
	pUav = new CUav;
	pUav->SetPos(pos);
	pUav->SetRot(rot);
	pUav->SetSize(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	//巡回ルート設定
	pUav->SetTour(0, pos);

	pUav->Init();
	return pUav;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CUav::Init(void)
{
	CEnemy::Init();
	CEnemy::SetLife(MAX_LIFE);
	//モデル生成
	m_pModel = CModel::Create(CEnemy::GetWorld(), this, m_modeldata, D3DXVECTOR3(0,250.0f,0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1));

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CUav::Uninit(void)
{
	m_pModel->Uninit();
	CEnemy::Uninit();
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CUav::Update(void)
{
	//エネミーアップデート
	CEnemy::Update();
	//距離
	float *fDistance=NULL;

	//行動
	if (GetState() != STATE_DEATH)
	{
		switch (GetMode())
		{
		case ENEMY_TOUR:	//巡回
			
			Tour();		//巡回関数
			
			if (Search(400.0f, 90.0f) == true && CManager::GetPlayer()->GetState() != CPlayer::STATE_DEATH)	//索敵関数		
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
				SetQuestion(CQuestion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 50, GetPos().z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f)));
				//使っている処理
				m_bWary = true;
			}

			//発見関数
			if (Found() == true) 
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
				SetExclamation(CExclamationMark::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 50, GetPos().z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 10.0f)));
				//使っている
				m_bDiscovery = true;
			}


			//跳ぶカウント
			m_nFly += 1;
			
			//向き関数
			Direction(CManager::GetPlayer()->GetPos());

			bCall = true;

			//プレイヤーが死んだとき
			if (CManager::GetPlayer()->GetState() == CPlayer::STATE_DEATH)
			{
				SetMode(ENEMY_TOUR);
			}
			//跳ぶまでのカウント
			if (m_nFly>=30)
			{
				//NULLチェック
				if (GetExclamation() != NULL)
				{
					GetExclamation()->Uninit();
					SetExclamation(NULL);
				}

				SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 1.0f, GetPos().z));
			}
			
			break;
		default:
			break;
		}

	}
	//一定まで跳んだら消える
	if (GetPos().y>=60.0f)
	{
		Uninit();
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

		SetPos(D3DXVECTOR3(GetPos().x, GetPos().y-1.2f, GetPos().z));
		if (GetPos().y <= -20.0f)
		{
			//爆発

CExplosion::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 30, GetPos().z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100, 100, 100));
			//終了処理
			Uninit();
		}

		break;
	default:
		break;
	}

}

//=============================================================================
// 描画関数
//=============================================================================
void CUav::Draw(void)
{

}

//=============================================================================
// 発見時のエネミーを呼ぶ処理関数
//=============================================================================
bool CUav::EnemyCall(void)
{
	return bCall;
}

