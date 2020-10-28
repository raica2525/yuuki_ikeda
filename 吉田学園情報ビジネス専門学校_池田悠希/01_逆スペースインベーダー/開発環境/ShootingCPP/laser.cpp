//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	laser.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "laser.h"
#include "laserlayer.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include <stdio.h>
#include "score.h"
CLaser::CLaser() : CScene(1)
{
	m_nDamage = 0;
	m_fRot = 0;
	m_nWidth = 0;
	m_bHit = false;
	m_bPenetrate = false;
	memset(m_vtxPos, 0, sizeof(m_vtxPos));
}

CLaser::~CLaser()
{

}

HRESULT CLaser::Init(void)
{
	return S_OK;
}

void CLaser::Uninit(void)
{
	m_pPolygon->Uninit();
	m_pLaserLayer->Uninit();
	CScene::Release();
}

void CLaser::Update(void)
{
	CEnemy* pClosestEnemy = NULL;
	CEnemy* apHitEnemy[MAX_SCENE] = {};
	int nHitEnemyCount = 0;
	ZeroMemory(apHitEnemy, sizeof(apHitEnemy));
	CScene2d* pClosestTile = NULL;
	CScene** pScene = GetScene();
	CScore *pScore = NULL;
	for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
	{
		if ((*(pScene + nCount)) != NULL)
		{
			if ((*(pScene + nCount))->GetObjType() == OBJTYPE_SCORE)
			{
				pScore = (CScore*)(*(pScene + nCount));
			}
		}
	}
	
	int HittedSide = 0;
	for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
	{
		if ((*(pScene + nCount)) != NULL)
		{
			if ((*(pScene + nCount))->GetObjType() == OBJTYPE_ENEMY)
			{
				D3DXVECTOR3 EnemyPos = ((CEnemy*)(*(pScene + nCount)))->GetPos();
				D3DXVECTOR3 EnemyVtx[4];
				EnemyVtx[0] = EnemyPos + D3DXVECTOR3((float)-ENEMY_SIZE / 2, (float)-ENEMY_SIZE / 2, 0.0f);
				EnemyVtx[1] = EnemyPos + D3DXVECTOR3((float)ENEMY_SIZE / 2, (float)-ENEMY_SIZE / 2, 0.0f);
				EnemyVtx[2] = EnemyPos + D3DXVECTOR3((float)-ENEMY_SIZE / 2, (float)ENEMY_SIZE / 2, 0.0f);
				EnemyVtx[3] = EnemyPos + D3DXVECTOR3((float)ENEMY_SIZE / 2, (float)ENEMY_SIZE / 2, 0.0f);
				if (EnemyPos.x - ENEMY_SIZE / 2 < SCREEN_WIDTH&&EnemyPos.x + ENEMY_SIZE / 2 > 0)
				{
					if (CheckCollision(EnemyVtx))
					{
						if (m_bPenetrate)
						{
							apHitEnemy[nHitEnemyCount] = ((CEnemy*)(*(pScene + nCount)));
							nHitEnemyCount++;
						}
						else
						{
							if (pClosestEnemy == NULL)
							{
								pClosestEnemy = ((CEnemy*)(*(pScene + nCount)));
							}
							else
							{
								D3DXVECTOR3 ClosestEnemyPos = pClosestEnemy->GetPos();
								if (sqrt(pow(EnemyPos.x - m_pos.x, 2) + pow(EnemyPos.y - m_pos.y, 2)) < sqrt(pow(ClosestEnemyPos.x - m_pos.x, 2) + pow(ClosestEnemyPos.y - m_pos.y, 2)))
								{
									pClosestEnemy = ((CEnemy*)(*(pScene + nCount)));
								}
							}
						}
					}
				}
			}
			else if ((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE|| (*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
			{
				
				D3DXVECTOR3 TilePos = ((CScene2d*)(*(pScene + nCount)))->GetPos();
				D3DXVECTOR3 TileVtx[4];
				TileVtx[0] = TilePos + D3DXVECTOR3((float)-MAP_TILE_SIZE / 2, (float)-MAP_TILE_SIZE / 2, 0.0f);
				TileVtx[1] = TilePos + D3DXVECTOR3((float)MAP_TILE_SIZE / 2, (float)-MAP_TILE_SIZE / 2, 0.0f);
				TileVtx[2] = TilePos + D3DXVECTOR3((float)-MAP_TILE_SIZE / 2, (float)MAP_TILE_SIZE / 2, 0.0f);
				TileVtx[3] = TilePos + D3DXVECTOR3((float)MAP_TILE_SIZE / 2, (float)MAP_TILE_SIZE / 2, 0.0f);
				if (TilePos.x - ENEMY_SIZE / 2 < SCREEN_WIDTH&&TilePos.x + MAP_TILE_SIZE / 2 > 0)
				{
					if (CheckCollision(TileVtx))
					{
						if (pClosestTile == NULL)
						{
							pClosestTile = ((CScene2d*)(*(pScene + nCount)));
						}
						else
						{
							D3DXVECTOR3 ClosestTilePos = pClosestTile->GetPos();
							if (sqrt(pow(TilePos.x - m_pos.x, 2) + pow(TilePos.y - m_pos.y, 2)) < sqrt(pow(ClosestTilePos.x - m_pos.x, 2) + pow(ClosestTilePos.y - m_pos.y, 2)))
							{
								pClosestTile = ((CScene2d*)(*(pScene + nCount)));
							}
						}
					}
				}
			}
			
		}


	}
	if (pClosestEnemy != NULL && pClosestTile != NULL || apHitEnemy[0] != NULL&& pClosestTile != NULL)
	{
		D3DXVECTOR3 TilePos = pClosestTile->GetPos();
		D3DXVECTOR3 size;
		D3DXVECTOR3 pos;
		
		if (m_bPenetrate)
		{
			for (int nCount = 0; nCount < nHitEnemyCount; nCount++)
			{
				
				D3DXVECTOR3 EnemyPos = apHitEnemy[nCount]->GetPos();
				if ((sqrt(pow(EnemyPos.x - m_pos.x, 2) + pow(EnemyPos.y - m_pos.y, 2))) < (sqrt(pow(TilePos.x - m_pos.x, 2) + pow(TilePos.y - m_pos.y, 2))))
				{
					apHitEnemy[nCount]->HitBullet(m_nDamage);
				}
				size = D3DXVECTOR3(sqrt(pow(TilePos.x - m_pos.x, 2) + pow(TilePos.y - m_pos.y, 2)), m_nWidth, 0);
				//pos = D3DXVECTOR3((m_pos.x + ((TilePos.x - m_pos.x) / 2)), m_pos.y, 0.0f);
				m_pPolygon->SetSize(size);
				m_pLaserLayer->SetSize(size);
				m_pPolygon->SetPos(m_pos);
				m_pLaserLayer->SetPos(m_pos);
				if (pClosestTile->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
				{
					pClosestTile->SetCol(pClosestTile->GetCol() - D3DCOLOR_RGBA(0, 5, 5, 0));
					if (pClosestTile->GetCol() <= D3DCOLOR_RGBA(255, 0, 0, 255))
					{
						pClosestTile->Uninit();
					}
				}
				else
				{
					if (pClosestTile->GetCol() != m_col)
					{
						if (pClosestTile->GetCol() == 0xffffffff)
						{
							pScore->AddScore(10);
						}
						pClosestTile->SetCol(m_col);
					}
				}
				
			}
		}
		else
		{
			D3DXVECTOR3 EnemyPos = pClosestEnemy->GetPos();
			if ((sqrt(pow(EnemyPos.x - m_pos.x, 2) + pow(EnemyPos.y - m_pos.y, 2))) < (sqrt(pow(TilePos.x - m_pos.x, 2) + pow(TilePos.y - m_pos.y, 2))))
			{
				pClosestEnemy->HitBullet(m_nDamage);
				size = D3DXVECTOR3(sqrt(pow(EnemyPos.x - m_pos.x, 2) + pow(EnemyPos.y - m_pos.y, 2)), m_nWidth, 0);
				pos = D3DXVECTOR3((m_pos.x + ((EnemyPos.x - m_pos.x) / 2)), m_pos.y, 0.0f);
			}
			else
			{

				size = D3DXVECTOR3(sqrt(pow(TilePos.x - m_pos.x, 2) + pow(TilePos.y - m_pos.y, 2)), m_nWidth, 0);
				pos = D3DXVECTOR3((m_pos.x + ((TilePos.x - m_pos.x) / 2)), m_pos.y, 0.0f);
				if (pClosestTile->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
				{
					pClosestTile->SetCol(pClosestTile->GetCol() - D3DCOLOR_RGBA(0,5,5,0));
					if (pClosestTile->GetCol() <= D3DCOLOR_RGBA(255, 0, 0, 255))
					{
						pClosestTile->Uninit();
					}
				}
				else
				{
					if (pClosestTile->GetCol() != m_col)
					{
						if (pClosestTile->GetCol() == 0xffffffff)
						{
							pScore->AddScore(10);
						}
						pClosestTile->SetCol(m_col);

					}
				}
			}
			m_pPolygon->SetSize(size);
			m_pLaserLayer->SetSize(size);
			m_pPolygon->SetPos(m_pos);
			m_pLaserLayer->SetPos(m_pos);
			
		}

	}
	else if (pClosestEnemy != NULL|| apHitEnemy[0] != NULL)
	{
		D3DXVECTOR3 size;
		D3DXVECTOR3 pos;
		if (m_bPenetrate)
		{
			for (int nCount = 0; nCount < nHitEnemyCount; nCount++)
			{
				D3DXVECTOR3 EnemyPos = apHitEnemy[nCount]->GetPos();
				apHitEnemy[nCount]->HitBullet(m_nDamage);
			}
		}
		else
		{
			D3DXVECTOR3 EnemyPos = pClosestEnemy->GetPos();

			pClosestEnemy->HitBullet(m_nDamage);
			size = D3DXVECTOR3(sqrt(pow(EnemyPos.x - m_pos.x, 2) + pow(EnemyPos.y - m_pos.y, 2)), m_nWidth, 0);
			pos = D3DXVECTOR3((m_pos.x + ((EnemyPos.x - m_pos.x) / 2)), m_pos.y, 0.0f);
	
			m_pPolygon->SetSize(size);
			m_pLaserLayer->SetSize(size);
		}
		m_pPolygon->SetPos(m_pos);
		m_pLaserLayer->SetPos(m_pos);
	}
	else if (pClosestTile != NULL)
	{
		D3DXVECTOR3 TilePos = pClosestTile->GetPos();
		D3DXVECTOR3 size = D3DXVECTOR3(sqrt(pow(TilePos.x - m_pos.x, 2) + pow(TilePos.y - m_pos.y, 2)), m_nWidth, 0);
		D3DXVECTOR3 pos = D3DXVECTOR3((m_pos.x + ((TilePos.x - m_pos.x) / 2)), m_pos.y, 0.0f);
		m_pPolygon->SetSize(size);
		m_pLaserLayer->SetSize(size);
		m_pPolygon->SetPos(m_pos);
		m_pLaserLayer->SetPos(m_pos);
		if (pClosestTile->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)
		{
			pClosestTile->SetCol(pClosestTile->GetCol() - D3DCOLOR_RGBA(0, 5, 5, 0));
			if (pClosestTile->GetCol() <= D3DCOLOR_RGBA(255, 0, 0, 255))
			{
				pScore->AddScore(50);
				CManager::GetSound()->Play(CSound::SE_EXPLOSION);
				pClosestTile->Uninit();
			}
		}
		else
		{
			if (pClosestTile->GetCol() != m_col)
			{
				if (pClosestTile->GetCol() == 0xffffffff)
				{
					pScore->AddScore(10);
				}
				pClosestTile->SetCol(m_col);

			}
		}

	}
	else
	{
		m_pPolygon->SetPos(m_pos);
		m_pLaserLayer->SetPos(m_pos);
	}
	m_pPolygon->Update();
	m_pLaserLayer->Update();
}

void CLaser::Draw(void)
{
	m_pPolygon->Draw();
	m_pLaserLayer->Draw();
	Uninit();
	
}

void CLaser::Create(D3DXVECTOR3 pos, D3DCOLOR col, int nWidth, float fRot, int nDamage,bool bPenetrate)
{
	CLaser* pLaser = new CLaser();
	pLaser->m_pos = pos;
	pLaser->m_col = col;
	pLaser->m_nWidth = nWidth;
	pLaser->m_fRot = fRot;
	pLaser->m_nDamage = nDamage;
	pLaser->SetObjType(OBJTYPE_LASER);
	pLaser->m_bPenetrate = bPenetrate;
	pLaser->m_pPolygon = CPolygon::Create(D3DXVECTOR3((float)(pLaser->m_pos.x + ((SCREEN_WIDTH * 1.5) / 2)), pLaser->m_pos.y, 0.0f), D3DXVECTOR3(SCREEN_WIDTH*1.5, pLaser->m_nWidth, 0), pLaser->m_fRot, OBJTYPE_LASER);
	pLaser->m_pLaserLayer = CLaserLayer::Create(D3DXVECTOR3((float)(pLaser->m_pos.x + ((SCREEN_WIDTH * 1.5) / 2)), pLaser->m_pos.y, 0.0f), pLaser->m_col, pLaser->m_nWidth, SCREEN_WIDTH*1.5, pLaser->m_fRot);
}

bool CLaser::CheckCollision(D3DXVECTOR3* pObjVtx)
{
	bool bHit = true;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vtxPos[nCount] = m_pPolygon->GetVtxPos(nCount);
	}
	
	for (int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
	{
		if (((m_vtxPos[1].x - m_vtxPos[0].x)*(pObjVtx[nCountVtx].y - m_vtxPos[0].y)) - ((pObjVtx[nCountVtx].x - m_vtxPos[0].x)*(m_vtxPos[1].y - m_vtxPos[0].y)) < 0
			&& ((m_vtxPos[2].x - m_vtxPos[3].x)*(pObjVtx[nCountVtx].y - m_vtxPos[3].y)) - ((pObjVtx[nCountVtx].x - m_vtxPos[3].x)*(m_vtxPos[2].y - m_vtxPos[3].y)) >= 0)
		{
			if (nCountVtx == 3)
			{
				bHit = false;
			}
		}
		else
		{
			break;
		}
	}
	for (int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
	{
		if (((m_vtxPos[1].x - m_vtxPos[0].x)*(pObjVtx[nCountVtx].y - m_vtxPos[0].y)) - ((pObjVtx[nCountVtx].x - m_vtxPos[0].x)*(m_vtxPos[1].y - m_vtxPos[0].y)) >= 0
			&& ((m_vtxPos[2].x - m_vtxPos[3].x)*(pObjVtx[nCountVtx].y - m_vtxPos[3].y)) - ((pObjVtx[nCountVtx].x - m_vtxPos[3].x)*(m_vtxPos[2].y - m_vtxPos[3].y)) < 0)
		{
			if (nCountVtx == 3)
			{
				bHit = false;
			}
		}
		else
		{
			break;
		}
	}
	for (int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
	{
		if (((m_vtxPos[2].x - m_vtxPos[0].x)*(pObjVtx[nCountVtx].y - m_vtxPos[0].y)) - ((pObjVtx[nCountVtx].x - m_vtxPos[0].x)*(m_vtxPos[2].y - m_vtxPos[0].y)) < 0
			&& ((m_vtxPos[1].x - m_vtxPos[3].x)*(pObjVtx[nCountVtx].y - m_vtxPos[3].y)) - ((pObjVtx[nCountVtx].x - m_vtxPos[3].x)*(m_vtxPos[1].y - m_vtxPos[3].y)) >= 0)
		{
			if (nCountVtx == 3)
			{
				bHit = false;
			}
		}
		else
		{
			break;
		}
	}
	for (int nCountVtx = 0; nCountVtx < NUM_VERTEX; nCountVtx++)
	{
		if (((m_vtxPos[2].x - m_vtxPos[0].x)*(pObjVtx[nCountVtx].y - m_vtxPos[0].y)) - ((pObjVtx[nCountVtx].x - m_vtxPos[0].x)*(m_vtxPos[2].y - m_vtxPos[0].y)) >= 0
			&& ((m_vtxPos[1].x - m_vtxPos[3].x)*(pObjVtx[nCountVtx].y - m_vtxPos[3].y)) - ((pObjVtx[nCountVtx].x - m_vtxPos[3].x)*(m_vtxPos[1].y - m_vtxPos[3].y)) < 0)
		{
			if (nCountVtx == 3)
			{
				bHit = false;
			}
		}
		else
		{
			break;
		}
	}
	return bHit;
}

int CLaser::CheckSide(D3DXVECTOR3* pObjVtx)
{
	bool bHit = true;
	D3DXVECTOR3 LaserCenter = (m_vtxPos[1]+ m_vtxPos[3])/2;
	float vx1 = pObjVtx[3].x - pObjVtx[0].x;
	float vy1 = pObjVtx[3].y - pObjVtx[0].y;
	float vx2 = LaserCenter.x - pObjVtx[0].x;
	float vy2 = LaserCenter.y - pObjVtx[0].y;
	float vx3 = pObjVtx[1].x - pObjVtx[2].x;
	float vy3 = pObjVtx[1].y - pObjVtx[2].y;
	float vx4 = LaserCenter.x - pObjVtx[2].x;
	float vy4 = LaserCenter.y - pObjVtx[2].y;
	if (vx1 * vy2 - vy1 * vx2 < 0)
	{
		if (vx3 * vy4 - vy3 * vx4 < 0)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		if (vx3 * vy4 - vy3 * vx4 < 0)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
}