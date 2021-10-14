//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	map.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "map.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include <stdio.h>
#include "enemy.h"
#include "score.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CMap::m_apTexture[TILE_TYPE_MAX] = {};
D3DXVECTOR2 CMap::m_mapSize                         = D3DXVECTOR2(0, 0);
bool CMap::m_bGoal                                  = false;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CMap::CMap()
{
    memset(m_apScene2d, NULL, sizeof(m_apScene2d));
    memset(m_mapData, NULL, sizeof(m_mapData));
    m_bGoal = false;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CMap::~CMap()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CMap::Init(void)
{
    FILE* pFile;
    pFile         = fopen("Resources\\map.csv", "r");
    int TileCount = 0;
    if(pFile != NULL)
    {
        for(int nCountY = 0; nCountY < MAX_MAP_HEIGHT; nCountY++)
        {
            char cTile = NULL;
            for(int nCountX = 0; nCountX < MAX_MAP_WIDTH;)
            {
                cTile = fgetc(pFile);
                if(cTile == 0x0a || cTile == EOF)	//マップの長さ取得
                {
                    if(m_mapSize.x < nCountX)
                    {
                        m_mapSize.x = (float)nCountX;
                    }
                    break;
                }
                else if(cTile != ',')	//カンマを弾く
                {
					int nTile = atoi(&cTile);	//読み込んだ文字列を数字に変換
                    m_mapData[nCountY][nCountX] = (TILE_TYPE)nTile;	//マップデータに代入
                    switch(nTile)	//ファイルから読み込んだ数字によってオブジェクトを配置する
                    {
                        case TILE_TYPE_BLOCK:
                            m_apScene2d[TileCount] = CScene2d::Create(3);
                            m_apScene2d[TileCount]->SetWorldPos(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0));
                            m_apScene2d[TileCount]->SetObjType(OBJTYPE_MAP_TILE);
                            m_apScene2d[TileCount]->SetSize(D3DXVECTOR3(MAP_TILE_SIZE, MAP_TILE_SIZE, 0));
                            m_apScene2d[TileCount]->BindTexture(m_apTexture[0]);
                            break;
                        case TILE_TYPE_BRAKABLE_BLOCK:
                            m_apScene2d[TileCount] = CScene2d::Create(3);
                            m_apScene2d[TileCount]->SetWorldPos(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0));
                            m_apScene2d[TileCount]->SetObjType(OBJTYPE_MAP_TILE_BRAKABLE);
                            m_apScene2d[TileCount]->SetSize(D3DXVECTOR3(MAP_TILE_SIZE, MAP_TILE_SIZE, 0));
                            m_apScene2d[TileCount]->BindTexture(m_apTexture[1]);
                            break;
                        case TILE_TYPE_ENEMY:
                            CEnemy::Create(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0), CEnemy::TYPE_NORMAL);
                            break;
                        case TILE_TYPE_ENEMY_SPLINKLER:
                            CEnemy::Create(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0), CEnemy::TYPE_SPRINKLER);
                            break;
                        case TILE_TYPE_ENEMY_CANON_UP:
                            CEnemy::Create(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0), CEnemy::TYPE_CANON_UP);
                            break;
                        case TILE_TYPE_ENEMY_CANON_DOWN:
                            CEnemy::Create(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0), CEnemy::TYPE_CANON_DOWN);
                            break;
                    }
                    nCountX++;
                    TileCount++;
                }
            }
            if(cTile == EOF)
            {
                m_mapSize.y = (float)nCountY;	//マップの高さを取得
                break;
            }
        }
		fclose(pFile);
    }
    else
    {
		//エラー処理
        MessageBox(FindWindow(CLASS_NAME, NULL), "マップデータが読み込めません", "読み込みエラー", MB_ICONSTOP);
        exit(1);
    }

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CMap::Uninit(void)
{
    for(int nCount = 0; nCount < NUM_BG_LAYER; nCount++)
    {
        m_apScene2d[nCount] = NULL;
    }
    Release();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CMap::Update(void)
{
    CScene** pScene = CScene::GetScene();
    if(m_bGoal && CManager::GetAlive())	//ゴール後に生きていたらスコアを加算
    {
        for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
        {
            if((*(pScene + nCount)) != NULL)
            {
                if((*(pScene + nCount))->GetObjType() == OBJTYPE_SCORE)
                {
                    ((CScore*)(*(pScene + nCount)))->AddScore(1);
                }
            }
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CMap::Draw(void)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CMap* CMap::Create(void)
{
    CMap* pMap = new CMap;
    pMap->Init();
    return pMap;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル読み込み処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CMap::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\Wall.png", &m_apTexture[0]);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\wall_Damaged.png", &m_apTexture[1]);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\bg102.png", &m_apTexture[2]);

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//読み込みデータ破棄処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CMap::Unload(void)
{
    for(int nCount = 0; nCount < NUM_BG_LAYER; nCount++)
    {
        if(m_apTexture[nCount] != NULL)
        {
            m_apTexture[nCount]->Release();
            m_apTexture[nCount] = NULL;
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マップ長取得処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
int CMap::GetLength(void)
{
    return (int)m_mapSize.x;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゴールしたか設定する処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CMap::SetGoal(bool bGoal)
{
    m_bGoal = bGoal;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゴールしたか取得する処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
bool CMap::GetGoal(void)
{
    return m_bGoal;
}
