//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	laser.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "laser.h"
#include "laserlayer.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define WHITE D3DCOLOR_RGBA(255, 255, 255, 255)
#define RED D3DCOLOR_RGBA(255, 0, 0, 255)
#define FRAME_BLOCK_BRAKE (51)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CLaser::CLaser() : CScene(1)
{
    m_nDamage    = 0;
    m_fRot       = 0;
    m_nWidth     = 0;
    m_bHit       = false;
    m_bPenetrate = false;
    memset(m_vtxPos, 0, sizeof(m_vtxPos));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CLaser::~CLaser()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CLaser::Init(void)
{
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaser::Uninit(void)
{
    m_pPolygon->Uninit();
	delete m_pPolygon;
	m_pPolygon = NULL;

    m_pLaserLayer->Uninit();
	delete m_pLaserLayer;
	m_pPolygon = NULL;

    CScene::Release();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaser::Update(void)
{
    CEnemy* pClosestEnemy         = NULL;          //レーザーが当たった中で一番近い敵
    CEnemy* apHitEnemy[MAX_SCENE] = {};            //レーザーが当たった敵のリスト
    int nHitEnemyCount            = 0;             //レーザーが当たった敵の数
    CScene2d* pClosestTile        = NULL;          //レーザーが当たった中で一番近いマップタイル
    CScene** pScene               = GetScene();    //シーンポインタを取得
    CScore* pScore                = NULL;          //スコアのポインタ

    //配列をゼロクリア
    ZeroMemory(apHitEnemy, sizeof(apHitEnemy));
    //スコアのオブジェクト探索
    for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
    {
        if((*(pScene + nCount)) != NULL)
        {
            if((*(pScene + nCount))->GetObjType() == OBJTYPE_SCORE)
            {
                pScore = (CScore*)(*(pScene + nCount));
            }
        }
    }
    //レーザーが当たるオブジェクトを探索
    GetHittedObject(pScene, apHitEnemy, &nHitEnemyCount, &pClosestEnemy, &pClosestTile);
    //敵とマップタイル両方に当たる場合
    if(pClosestEnemy != NULL && pClosestTile != NULL)
    {
        //レーザーが貫通属性を持っている場合
        if(m_bPenetrate)
        {
            for(int nCount = 0; nCount < nHitEnemyCount; nCount++)
            {
                D3DXVECTOR3 EnemyPos = apHitEnemy[nCount]->GetPos();
                //一番近いタイルよりも近い敵がレーザーに当たる
                if(D3DXVec3Length(&(EnemyPos - m_pos)) < D3DXVec3Length(&(pClosestTile->GetPos() - m_pos)))
                {
                    apHitEnemy[nCount]->HitLaser(m_nDamage);
                }
                HitTile(pClosestTile, pScore);
            }
        }
        else
        {
            D3DXVECTOR3 EnemyPos = pClosestEnemy->GetPos();
            //一番近い敵が一番近いタイルよりも近かった場合
            if(D3DXVec3Length(&(EnemyPos - m_pos)) < D3DXVec3Length(&(pClosestTile->GetPos() - m_pos)))
            {
                pClosestEnemy->HitLaser(m_nDamage);
                SetLaserSize(D3DXVECTOR3(D3DXVec3Length(&(EnemyPos - m_pos)), (float)m_nWidth, 0.0f));
            }
            else
            {
                HitTile(pClosestTile, pScore);
            }
        }
    }
    else if(pClosestEnemy != NULL)
    {    //敵にだけ当たる場合
         //レーザーが貫通属性を持っている場合
        if(m_bPenetrate)
        {
            for(int nCount = 0; nCount < nHitEnemyCount; nCount++)
            {
                D3DXVECTOR3 EnemyPos = apHitEnemy[nCount]->GetPos();
                apHitEnemy[nCount]->HitLaser(m_nDamage);
            }
        }
        else
        {
            D3DXVECTOR3 EnemyPos = pClosestEnemy->GetPos();
            pClosestEnemy->HitLaser(m_nDamage);
            SetLaserSize(D3DXVECTOR3(D3DXVec3Length(&(EnemyPos - m_pos)), (float)m_nWidth, 0.0f));
        }
    }
    else if(pClosestTile != NULL)
    {    //マップタイルにだけ当たる場合
        HitTile(pClosestTile, pScore);
    }
    m_pPolygon->SetPos(m_pos);
    m_pLaserLayer->SetPos(m_pos);

    m_pPolygon->Update();
    m_pLaserLayer->Update();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaser::Draw(void)
{
    m_pPolygon->Draw();
    m_pLaserLayer->Draw();
    Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaser::Create(D3DXVECTOR3 pos, D3DCOLOR col, int nWidth, float fRot, int nDamage, bool bPenetrate)
{
	float fDefaultLaserLength = D3DXVec3Length(&D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	//メモリ確保
    CLaser* pLaser       = new CLaser();
	//各変数初期化
    pLaser->m_pos        = pos;
    pLaser->m_col        = col;
    pLaser->m_nWidth     = nWidth;
    pLaser->m_fRot       = fRot;
    pLaser->m_nDamage    = nDamage;
    pLaser->m_bPenetrate = bPenetrate;
	//オブジェクトタイプ設定
    pLaser->SetObjType(OBJTYPE_LASER);
	//使用するポリゴンのメモリ確保
    pLaser->m_pPolygon    = CPolygon::Create(D3DXVECTOR3((float)(pLaser->m_pos.x + fDefaultLaserLength/2), pLaser->m_pos.y, 0.0f), D3DXVECTOR3(fDefaultLaserLength, (float)pLaser->m_nWidth, 0), pLaser->m_fRot, OBJTYPE_LASER);
    pLaser->m_pLaserLayer = CLaserLayer::Create(D3DXVECTOR3((float)(pLaser->m_pos.x + fDefaultLaserLength/2), pLaser->m_pos.y, 0.0f), pLaser->m_col, pLaser->m_nWidth, (int)fDefaultLaserLength, pLaser->m_fRot);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//当たり判定処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
bool CLaser::CheckCollision(D3DXVECTOR3* pObjVtx)
{
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        m_vtxPos[nCount] = m_pPolygon->GetVtxPos(nCount);
    }

    D3DXVECTOR3 nullvec;
    D3DXVECTOR3 vec1 = m_vtxPos[1] - m_vtxPos[0];
    D3DXVECTOR3 vec2 = m_vtxPos[3] - m_vtxPos[1];
    D3DXVECTOR3 vec3 = m_vtxPos[2] - m_vtxPos[3];
    D3DXVECTOR3 vec4 = m_vtxPos[0] - m_vtxPos[2];

    for(int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
    {
        if((*D3DXVec3Cross(&nullvec, &vec1, &(pObjVtx[nCountVtx] - m_vtxPos[0]))).z > 0 && (*D3DXVec3Cross(&nullvec, &vec3, &(pObjVtx[nCountVtx] - m_vtxPos[3]))).z < 0)
        {
            if(nCountVtx == 3)
            {
                return false;
            }
        }
        else
        {
            break;
        }
    }

    for(int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
    {
        if((*D3DXVec3Cross(&nullvec, &vec2, &(pObjVtx[nCountVtx] - m_vtxPos[1]))).z < 0 && (*D3DXVec3Cross(&nullvec, &vec4, &(pObjVtx[nCountVtx] - m_vtxPos[2]))).z > 0)
        {
            if(nCountVtx == 3)
            {
                return false;
            }
        }
        else
        {
            break;
        }
    }

    for(int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
    {
        if((*D3DXVec3Cross(&nullvec, &vec3, &(pObjVtx[nCountVtx] - m_vtxPos[3]))).z > 0 && (*D3DXVec3Cross(&nullvec, &vec1, &(pObjVtx[nCountVtx] - m_vtxPos[0]))).z < 0)
        {
            if(nCountVtx == 3)
            {
                return false;
            }
        }
        else
        {
            break;
        }
    }

    for(int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
    {
        if((*D3DXVec3Cross(&nullvec, &vec4, &(pObjVtx[nCountVtx] - m_vtxPos[2]))).z < 0 && (*D3DXVec3Cross(&nullvec, &vec2, &(pObjVtx[nCountVtx] - m_vtxPos[1]))).z > 0)
        {
            if(nCountVtx == 3)
            {
                return false;
            }
        }
        else
        {
            break;
        }
    }

    return true;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//レーザーがあたったオブジェクトを取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaser::GetHittedObject(CScene** pScene, CEnemy** apHitEnemy, int* pHitEnemyCount, CEnemy** pClosestEnemy, CScene2d** pClosestTile)
{
    int nHitEnemyCount = 0;
    //レーザーが当たったオブジェクトを取得
    for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
    {
        if((*(pScene + nCount)) != NULL)
        {
			//敵の当たり判定
            if((*(pScene + nCount))->GetObjType() == OBJTYPE_ENEMY)
            {
                D3DXVECTOR3 EnemyPos = ((CEnemy*)(*(pScene + nCount)))->GetPos();
                D3DXVECTOR3 EnemyVtx[4];
                EnemyVtx[0] = EnemyPos + D3DXVECTOR3((float)-ENEMY_SIZE / 2, (float)-ENEMY_SIZE / 2, 0.0f);
                EnemyVtx[1] = EnemyPos + D3DXVECTOR3((float)ENEMY_SIZE / 2, (float)-ENEMY_SIZE / 2, 0.0f);
                EnemyVtx[2] = EnemyPos + D3DXVECTOR3((float)-ENEMY_SIZE / 2, (float)ENEMY_SIZE / 2, 0.0f);
                EnemyVtx[3] = EnemyPos + D3DXVECTOR3((float)ENEMY_SIZE / 2, (float)ENEMY_SIZE / 2, 0.0f);
                if(EnemyPos.x - ENEMY_SIZE / 2 < SCREEN_WIDTH && EnemyPos.x + ENEMY_SIZE / 2 > 0)
                {
                    if(CheckCollision(EnemyVtx))
                    {
						//レーザーが貫通するかどうか
                        if(m_bPenetrate)
                        {
                            apHitEnemy[nHitEnemyCount] = (CEnemy*)pScene[nCount];
                            *pClosestEnemy             = (CEnemy*)pScene[nCount];
                            nHitEnemyCount++;
                        }
                        else
                        {
							//貫通しないなら一番近い敵を探索
                            if(*pClosestEnemy == NULL)
                            {
                                *pClosestEnemy = (CEnemy*)pScene[nCount];
                            }
                            else
                            {
                                D3DXVECTOR3 ClosestEnemyPos = (*pClosestEnemy)->GetPos();
                                if(D3DXVec3Length(&(EnemyPos - m_pos)) < D3DXVec3Length(&(ClosestEnemyPos - m_pos)))
                                {
                                    *pClosestEnemy = (CEnemy*)pScene[nCount];
                                }
                            }
                        }
                    }
                }
            }
            else if((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE || (*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
            {
				//タイルの当たり判定
                D3DXVECTOR3 TilePos = ((CScene2d*)(*(pScene + nCount)))->GetPos();
                D3DXVECTOR3 TileVtx[4];
                TileVtx[0] = TilePos + D3DXVECTOR3((float)-MAP_TILE_SIZE / 2, (float)-MAP_TILE_SIZE / 2, 0.0f);
                TileVtx[1] = TilePos + D3DXVECTOR3((float)MAP_TILE_SIZE / 2, (float)-MAP_TILE_SIZE / 2, 0.0f);
                TileVtx[2] = TilePos + D3DXVECTOR3((float)-MAP_TILE_SIZE / 2, (float)MAP_TILE_SIZE / 2, 0.0f);
                TileVtx[3] = TilePos + D3DXVECTOR3((float)MAP_TILE_SIZE / 2, (float)MAP_TILE_SIZE / 2, 0.0f);
                if(TilePos.x - MAP_TILE_SIZE / 2 < SCREEN_WIDTH && TilePos.x + MAP_TILE_SIZE / 2 > 0)
                {
					//あたった中で一番近いタイルを探索
                    if(CheckCollision(TileVtx))
                    {
                        if(*pClosestTile == NULL)
                        {
                            *pClosestTile = (CScene2d*)pScene[nCount];
                        }
                        else
                        {
                            D3DXVECTOR3 ClosestTilePos = (*pClosestTile)->GetPos();
                            if(D3DXVec3Length(&(TilePos - m_pos)) < D3DXVec3Length(&(ClosestTilePos - m_pos)))
                            {
                                *pClosestTile = (CScene2d*)pScene[nCount];
                            }
                        }
                    }
                }
            }
        }
    }
    *pHitEnemyCount = nHitEnemyCount;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//タイルにあたったときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaser::HitTile(CScene2d* pTile, CScore* pScore)
{
	if (pTile != NULL)
	{
		//一番近いタイルが破壊可能なら
		if (pTile->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
		{
			//一番近いタイルの色の赤以外の成分を減らす
			pTile->SetCol(pTile->GetCol() - D3DCOLOR_RGBA(0, 255 / FRAME_BLOCK_BRAKE, 255 / FRAME_BLOCK_BRAKE, 0));
			if (pTile->GetCol() <= RED)
			{
				pTile->Uninit();
			}
		}
		else
		{
			if (pTile->GetCol() != m_col)
			{
				if (pTile->GetCol() == WHITE)
				{
					pScore->AddScore(10);
				}
				pTile->SetCol(m_col);
			}
		}
		SetLaserSize(D3DXVECTOR3(D3DXVec3Length(&(pTile->GetPos() - m_pos)), (float)m_nWidth, 0.0f));
	}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//レーザーのサイズ設定
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaser::SetLaserSize(D3DXVECTOR3 size)
{
    m_pPolygon->SetSize(size);
    m_pLaserLayer->SetSize(size);
}
