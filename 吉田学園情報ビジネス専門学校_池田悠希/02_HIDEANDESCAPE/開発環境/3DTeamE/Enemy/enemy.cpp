//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 二階堂汰一 吉田悠人
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "enemy.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "exclamationmark.h"
#include "explosion.h"
#include "hiteffect.h"
#include "input.h"
#include "inputkeyboard.h"
#include "manager.h"
#include "player.h"
#include "question.h"
#include "sound.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy()
{
    m_pos  = ZEROVECTOR3;        //位置
    m_move = ZEROVECTOR3;        //移動
    m_rot  = ZEROVECTOR3;        //向き
    m_size = ZEROVECTOR3;        //サイズ
    memset(m_TourPos, NULL, sizeof(m_TourPos));    //巡回位置
    m_nLife = 0;                                   //体力
    SetObjType(OBJTYPE_ENEMY);                     //オブジェクトタイプ設定
    m_TourCount    = 0;                            //巡回している位置
    m_TourMax      = 0;                            //巡回位置の最大値
    m_pQuestion    = NULL;
    m_pExclamation = NULL;
	m_nAttack_SE   = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CEnemy::Init(void)
{
    //ワールド座標取得用
    m_pModel = CModel::Create(NULL, this, {}, m_pos, m_rot, m_size);
    //エネミーの位置セット
    m_pModel->SetPos(m_pos);
    //エネミーの向きセット
    m_pModel->SetRot(m_rot);
    //オブジェクトタイプ設定
    m_pModel->SetObjType(OBJTYPE_NONE);
    //当たり判定
    SetCollisionBullet(true);
    return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CEnemy::Uninit(void)
{
    m_pModel->Uninit();
    Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CEnemy::Update(void)
{
    m_pModel->SetPos(m_pos);
    m_pModel->SetRot(m_rot);
}

//=============================================================================
// 描画関数
//=============================================================================
void CEnemy::Draw(void)
{
}

//=============================================================================
// 位置設定関数
//=============================================================================
void CEnemy::SetPos(D3DXVECTOR3(pos))
{
    m_pos = pos;
}

//=============================================================================
// 向き設定関数
//=============================================================================
void CEnemy::SetRot(D3DXVECTOR3(rot))
{
    m_rot = rot;
}

//=============================================================================
// サイズ設定関数
//=============================================================================
void CEnemy::SetSize(D3DXVECTOR3(size))
{
    m_size = size;
}

//=============================================================================
// 巡回位置設定関数
//=============================================================================
void CEnemy::SetTour(int nTour, D3DXVECTOR3(pos))
{
    m_TourPos[nTour] = pos;
    m_TourMax=nTour+1;
}

//=============================================================================
// モードチェンジ関数
//=============================================================================
void CEnemy::SetMode(ENEMY_MODE mode)
{
	m_Mode = mode;
}

//=============================================================================
//　ライフ設定関数
//=============================================================================
void CEnemy::SetLife(int nLife)
{
    m_nLife = nLife;
}

//=============================================================================
//　クエスチョン設定関数
//=============================================================================
void CEnemy::SetQuestion(CQuestion * pQuestion)
{
    CSound* pSound = CManager::GetSound();    //サウンドの取得
    pSound->PlaySoundA(CSound::SOUND_LABEL_SE_QUESTION);
    m_pQuestion = pQuestion;
}

//=============================================================================
//　！設定関数
//=============================================================================
void CEnemy::SetExclamation(CExclamationMark * pExclamation)
{
    CSound* pSound = CManager::GetSound();    //サウンドの取得
    pSound->PlaySoundA(CSound::SOUND_LABEL_SE_EXCLAMATIONMARK);
    m_pExclamation = pExclamation;
}

//=============================================================================
// ステータス設定関数
//=============================================================================
void CEnemy::SetState(ENEMY_STATE state)
{
    m_State = state;
}

//=============================================================================
// ライフ減算関数
//=============================================================================
void CEnemy::SubLife(int nSublife)
{
	m_nLife -= nSublife;
	CHitEffect::HitEffectCreate(D3DXVECTOR3(m_pos.x,m_pos.y + 20,m_pos.z), D3DXVECTOR3(2.0f, 2.0f, 2.0f ), D3DCOLOR_RGBA(255,255,0,255));
    //ライフ０のとき
    if(m_nLife <= 0)
    {
        //NULLチェック
        if(m_pQuestion != NULL)
        {
            m_pQuestion->Uninit();
            m_pQuestion = NULL;
        }

        if(m_pExclamation != NULL)
        {
            m_pExclamation->Uninit();
            m_pExclamation = NULL;
        }
        //終了処理
        m_State = STATE_DEATH;
    }
}

//=============================================================================
// HIT関数
//=============================================================================
void CEnemy::Hit(int nDamage)
{
	m_State = STATE_DAMAGE;
	SubLife(nDamage);

}

//=============================================================================
// 攻撃関数
//=============================================================================
void CEnemy::Attack(int nDamage)
{
    CSound* pSound = CManager::GetSound();    //サウンドの取得
	m_nAttack_SE += 1;
	if (m_nAttack_SE>=5)
	{
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ENEMYATTACK);
		m_nAttack_SE = 0;
	}

    //ランダム関数の初期化
    srand((unsigned)time(NULL));

	int nAttackHit = (rand() % +4);

    //10回に１回
    if(nAttackHit == 0)
    {
        //ヒット
        CManager::GetPlayer()->AddLife(nDamage);
    }
}

//=============================================================================
// 巡回関数
//=============================================================================
bool CEnemy::Tour(void)
{
    //目標の位置
    float fAngle;
	bool bTour=false;
	if (m_TourMax-1 != 0)
	{
		bTour = true;
		 //目標の位置についたとき
		 if(m_pos.x + 5 > m_TourPos[m_TourCount].x
		    && m_pos.x - 5 < m_TourPos[m_TourCount].x
		    && m_pos.y + 5 > m_TourPos[m_TourCount].y
		    && m_pos.y - 5 < m_TourPos[m_TourCount].y
		    && m_pos.z + 5 > m_TourPos[m_TourCount].z
		    && m_pos.z - 5 < m_TourPos[m_TourCount].z)
		 {
		     //次の巡回位置を設定
		     m_TourCount += 1;
		     //設定されている巡回位置を回り終えたら
		     if(m_TourCount == m_TourMax)
		     {
		         //最初の巡回位置に戻る
		         m_TourCount = 0;
		     }
		 }
		//目標の位置方向取得
		fAngle = atan2f((-m_pos.x + m_TourPos[m_TourCount].x), (-m_pos.z + m_TourPos[m_TourCount].z));

		//目標までの移動
		m_move.x = sinf(fAngle) * 1.0f;
		m_move.z = cosf(fAngle) * 1.0f;

		/*慣性*/
		m_move.x += (0.0f - m_move.x) * 0.5f;
		m_move.y += (0.0f - m_move.y) * 0.5f;
		m_move.z += (0.0f - m_move.z) * 0.5f;

		//位置更新
		m_pos += m_move;

		//移動方向に向く
		Direction(m_TourPos[m_TourCount]);

	}
	return bTour;
}

//=============================================================================
// 向き関数
//=============================================================================
void CEnemy::Direction(D3DXVECTOR3(pos))
{
    //目標の角度を取得
    float fRotDist = D3DXToDegree(atan2f((m_pos.x - pos.x), (m_pos.z - pos.z)));

    //方向処理
    if(fRotDist >= D3DXToDegree(m_rot.y) + (180))
    {    //-180度から180度になる処理
        m_rot.y  = D3DXToRadian(180);
        fRotDist = (180);
    }
    else if(fRotDist <= D3DXToDegree(m_rot.y) + (-180))
    {    //180度から-180度になる処理
        m_rot.y  = D3DXToRadian(-180);
        fRotDist = (-180);
    }

    //向き更新
    m_rot += D3DXToRadian((D3DXVECTOR3(0.0f, fRotDist, 0.0f) - D3DXToDegree(m_rot)) * 0.09f);
}

//=============================================================================
// 索敵関数
//=============================================================================
bool CEnemy::Search(const float fRangeDistance, const float fViewingAngle)
{
    CObject* pTop[PRIORITY_MAX] = {};
    CObject* pNext              = NULL;
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        //リストトップ取得
        pTop[nCount] = *(CObject::GetTop() + nCount);
    }

    //プレイヤーまでの距離
    float fDistancePlayer  = 0;
    float fClosestDistance = 999999999.9f;
    float fDistance        = 0;
    bool bSearch           = false;
    float fPlayerRotOld    = 0.0f;
    //NULLチェック
    for(int nCount = 0; nCount < PRIORITY_MAX; nCount++)
    {
        //NULLチェック
        if(pTop[nCount] != NULL)
        {
            pNext = pTop[nCount];
            while(pNext != NULL)
            {
                //オブジェクトタイプチェック
                if(pNext->GetObjType() == OBJTYPE_MODEL)
                {
                    //NULLチェック
                    if(((CModel*)pNext)->GetParentObject() != NULL)
                    {
                        if(((CModel*)pNext)->GetParentObject()->GetObjType() == OBJTYPE_PLAYER)
                        {
                            //索敵確認関数
							if (CheckSearch(((CModel*)pNext)->GetModelData(), &fDistancePlayer))
							{
								//距離確認
								if (fRangeDistance > fDistancePlayer)
								{
									//距離確認
									if (fRangeDistance > fDistancePlayer)
									{
										//プレイヤーの方向
										float fPlayerRot = D3DXToDegree(atan2f((m_pos.x - ((CPlayer*)((CModel*)pNext)->GetParentObject())->GetPos().x), (m_pos.z - ((CPlayer*)((CModel*)pNext)->GetParentObject())->GetPos().z)));
										//視野の右と左の最大数

										float fSearch_R = D3DXToDegree(m_rot.y) + (fViewingAngle / 2);
										float fSearch_L = D3DXToDegree(m_rot.y) - (fViewingAngle / 2);

										if (fSearch_R > 180)
										{
											fSearch_R -= 360;
										}
										if (fSearch_L < -180)
										{
											fSearch_L += 360;
										}
										if (fSearch_R > fSearch_L)
										{
											if (fSearch_R > fPlayerRot
												&& fSearch_L < fPlayerRot)
											{
												//見つかった時の処理
												bSearch = true;
											}
										}
										else
										{
											if (fSearch_R > fPlayerRot
												|| fSearch_L < fPlayerRot)
											{
												//見つかった時の処理
												bSearch = true;
											}
										}

									}
								}
							}
                        }
                        else if(((CModel*)pNext)->GetParentObject()->GetObjType() != OBJTYPE_ENEMY)
                        {
                            if(CheckSearch(((CModel*)pNext)->GetModelData(), &fDistance) == TRUE)
                            {
                                if(fClosestDistance == 0 || fClosestDistance > fDistance)
                                {
                                    fClosestDistance = fDistance;
                                }
                            }
                        }
                    }
                }
                //次の対象を読み込む
                pNext = pNext->GetNext();
            }
        }
    }
    if(fDistancePlayer > fClosestDistance)
    {
        bSearch = false;
    }
    //見つからなかったとき
    return bSearch;
}

//=============================================================================
// 発見関数
//=============================================================================
bool CEnemy::Found(void)
{
	CObject* pTop[PRIORITY_MAX] = {};
	CObject* pNext = NULL;
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//リストトップ取得
		pTop[nCount] = *(CObject::GetTop() + nCount);
	}
	float fDistancePlayer = 0;
	float fClosestDistance = 999999999.9f;
	float fDistance = 0;
	bool bFound = false;
	
	//NULLチェック
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULLチェック
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			while (pNext != NULL)
			{
				//オブジェクトタイプチェック
				if (pNext->GetObjType() == OBJTYPE_MODEL)
				{
					//NULLチェック
					if (((CModel *)pNext)->GetParentObject() != NULL)
					{
						if (((CModel*)pNext)->GetParentObject()->GetObjType() == OBJTYPE_PLAYER)
						{
							if (CheckSearch(((CModel*)pNext)->GetModelData(), &fDistancePlayer))
							{
								bFound = true;
							}
						}
						else if (((CModel*)pNext)->GetParentObject()->GetObjType() != OBJTYPE_ENEMY)
						{
							if (CheckSearch(((CModel*)pNext)->GetModelData(), &fDistance))
							{
								if (fClosestDistance == 0 || fClosestDistance>fDistance)
								{
									fClosestDistance = fDistance;
								}
							}
						}

					}
				}

				//次の対象を読み込む
				pNext = pNext->GetNext();
			}
		}
	}
	if (fDistancePlayer > fClosestDistance)
	{
		bFound = false;
	}

	return bFound;
}

//=============================================================================
// 索敵確認関数
//=============================================================================
BOOL CEnemy::CheckSearch(CModel::MODELDATA modeldata, float* fDistance)
{
	BOOL bSearch = false;					//見つかっているか
	D3DXMATRIX InversedWorldMatrix;	//逆列用マトリックス
	D3DXVECTOR3 TransformedPos, NormalizedVec , TranceformedVec;
	//単位ベクトルに変換
	D3DXVec3Normalize(&NormalizedVec, &((CManager::GetPlayer()->GetCenter()) - (m_pos + D3DXVECTOR3(0.0f, 33.0f, 0.0f))));
	//逆行列生成
	D3DXMatrixInverse(&InversedWorldMatrix, NULL, &modeldata.mtxWorld);
	//逆行列で変換
	D3DXVec3TransformCoord(&TransformedPos, &(m_pos + D3DXVECTOR3(0.0f, 33.0f, 0.0f)), &InversedWorldMatrix);
	D3DXVec3TransformNormal(&TranceformedVec, &NormalizedVec, &InversedWorldMatrix);
	//当たり判定を確認
	D3DXIntersect(modeldata.pMesh, &TransformedPos, &TranceformedVec, &bSearch, NULL, NULL, NULL, fDistance, NULL, NULL);

	return bSearch;
}

