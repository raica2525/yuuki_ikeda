
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	map.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "map.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include <stdio.h>
#include "enemy.h"
#include "score.h"
LPDIRECT3DTEXTURE9 CMap::m_apTexture[TILE_TYPE_MAX] = {};
D3DXVECTOR2 CMap::m_mapSize = D3DXVECTOR2(0,0);
bool CMap::m_bGoal = false;
CMap::CMap()
{
	memset(m_apScene2d, NULL, sizeof(m_apScene2d));
	memset(m_mapData, NULL, sizeof(m_mapData));
	m_bGoal = false;
}

CMap::~CMap()
{

}

HRESULT CMap::Init(void)
{
	FILE* pFile;
	pFile = fopen("Resources\\map.csv", "r");
	int TileCount = 0;
	if (pFile != NULL)
	{
		for (int nCountY = 0; nCountY < MAX_MAP_HEIGHT; nCountY++)
		{
			char nTile = NULL;
			for (int nCountX = 0; nCountX < MAX_MAP_WIDTH;)
			{
				nTile = fgetc(pFile);
				if (nTile == 0x0a || nTile == EOF)
				{
					if (m_mapSize.x < nCountX)
					{
						m_mapSize.x = nCountX;
					}
					break;
				}
				else if(nTile != ',')
				{
					nTile = atoi((char*)&nTile);
					m_mapData[nCountY][nCountX] = (TILE_TYPE)nTile;
					switch (nTile)
					{
					case TILE_TYPE_BLOCK:
						m_apScene2d[TileCount] = CScene2d::Create(3);
						m_apScene2d[TileCount]->SetWorldPos(D3DXVECTOR3((nCountX + 0.5)*MAP_TILE_SIZE, (nCountY + 0.5)*MAP_TILE_SIZE, 0));
						m_apScene2d[TileCount]->SetObjType(OBJTYPE_MAP_TILE);
						m_apScene2d[TileCount]->SetSize(D3DXVECTOR3(MAP_TILE_SIZE, MAP_TILE_SIZE, 0));
						m_apScene2d[TileCount]->BindTexture(m_apTexture[0]);
						break;
					case TILE_TYPE_BRAKABLE_BLOCK:
						m_apScene2d[TileCount] = CScene2d::Create(3);
						m_apScene2d[TileCount]->SetWorldPos(D3DXVECTOR3((nCountX + 0.5)*MAP_TILE_SIZE, (nCountY + 0.5)*MAP_TILE_SIZE, 0));
						m_apScene2d[TileCount]->SetObjType(OBJTYPE_MAP_TILE_BRAKABLE);
						m_apScene2d[TileCount]->SetSize(D3DXVECTOR3(MAP_TILE_SIZE, MAP_TILE_SIZE, 0));
						m_apScene2d[TileCount]->BindTexture(m_apTexture[1]);
						break;
					case TILE_TYPE_ENEMY:
						CEnemy::Create(D3DXVECTOR3((nCountX + 0.5)*MAP_TILE_SIZE, (nCountY + 0.5)*MAP_TILE_SIZE, 0),CEnemy::TYPE_NORMAL);
						break;
					case TILE_TYPE_ENEMY_SPLINKLER:
						CEnemy::Create(D3DXVECTOR3((nCountX + 0.5)*MAP_TILE_SIZE, (nCountY + 0.5)*MAP_TILE_SIZE, 0), CEnemy::TYPE_SPRINKLER);
						break;
					case TILE_TYPE_ENEMY_CANON_UP:
						CEnemy::Create(D3DXVECTOR3((nCountX + 0.5)*MAP_TILE_SIZE, (nCountY + 0.5)*MAP_TILE_SIZE, 0), CEnemy::TYPE_CANON_UP);
						break;
					case TILE_TYPE_ENEMY_CANON_DOWN:
						CEnemy::Create(D3DXVECTOR3((nCountX + 0.5)*MAP_TILE_SIZE, (nCountY + 0.5)*MAP_TILE_SIZE, 0), CEnemy::TYPE_CANON_DOWN);
						break;
					}
					nCountX++;
					TileCount++;
				}
			}
			if (nTile == EOF)
			{
				m_mapSize.y = nCountY;

				break;
			}
		}
	}
	else
	{
		MessageBox(FindWindow(CLASS_NAME,NULL), "マップデータが読み込めません", "読み込みエラー", MB_ICONSTOP);
		exit(1);
	}

	return S_OK;
}

void CMap::Uninit(void)
{
	for (int nCount = 0; nCount < NUM_BG_LAYER; nCount++)
	{
		m_apScene2d[nCount] = NULL;
	}
	Release();
}

void CMap::Update(void)
{
	CScene** pScene = CScene::GetScene();
	if (m_bGoal&&CManager::GetAlive())
	{	
		for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
		{
			if ((*(pScene + nCount)) != NULL)
			{
				if ((*(pScene + nCount))->GetObjType() == OBJTYPE_SCORE)
				{
					((CScore*)(*(pScene + nCount)))->AddScore(1);
				}
			}
		}
	}
}

void CMap::Draw(void)
{

}

CMap* CMap::Create(void)
{
	CMap* pMap = NULL;
	pMap = new CMap;
	pMap->Init();
	return pMap;
}

HRESULT CMap::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\Wall.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\wall_Damaged.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\bg102.png", &m_apTexture[2]);

	return S_OK;
}

void CMap::Unload(void)
{
	for (int nCount = 0; nCount < NUM_BG_LAYER; nCount++)
	{
		if (m_apTexture[nCount] != NULL) {
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

int CMap::GetLength(void)
{
	return m_mapSize.x;
}
void CMap::SetGoal(bool bGoal)
{
	m_bGoal = bGoal;
}
bool CMap::GetGoal(void)
{
	return m_bGoal;
}