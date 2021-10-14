//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	bullet.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "player.h"
#include "score.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CBullet::CBullet() : CScene2d(1)
{
	//変数初期化
    m_bHit = false;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CBullet::~CBullet()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CBullet::Init(void)
{
	//初期化
    CScene2d::Init();
	//テクスチャ割当
    BindTexture(m_pTexture);

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CBullet::Uninit(void)
{
    CScene2d::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CBullet::Update(void)
{
	//ワールド座標取得
    D3DXVECTOR3 worldPos = GetWorldPos();
	//スクリーン上の座標取得
    D3DXVECTOR3 screenPos = GetPos();;
    CScene** pScene = GetScene();
	bool bElase = false;
	//弾を移動
    SetWorldPos(worldPos + m_move);
    CScene2d::Update();

	//スコアポインタ取得
    CScore* pScore = NULL;
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

	//当たり判定
    for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
    {
        if((*(pScene + nCount)) != NULL)
        {
            if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)	//プレイヤーとの当たり判定
            {
                D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();
				
                if(screenPos.x + (BULLET_SIZE_X / 2) > PlayerPos.x - (PLAYER_SIZE_X / 2) && screenPos.x - (BULLET_SIZE_X / 2) < PlayerPos.x + (PLAYER_SIZE_X / 2) 
					&& screenPos.y + (BULLET_SIZE_Y / 2) > PlayerPos.y - (PLAYER_SIZE_Y / 2) && screenPos.y - (BULLET_SIZE_Y / 2) < PlayerPos.y + (PLAYER_SIZE_Y / 2))
                {
					//当たったときの処理
                    ((CPlayer*)(*(pScene + nCount)))->HitBullet();
                    m_bHit = true;
                }
            }
            else if((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE || (*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE_BRAKABLE)	//マップタイルとの当たり判定
            {
                D3DXVECTOR3 TilePos = ((CScene2d*)(*(pScene + nCount)))->GetPos();

                if(screenPos.x + (BULLET_SIZE_X / 2) > TilePos.x - (MAP_TILE_SIZE / 2) && screenPos.x - (BULLET_SIZE_X / 2) < TilePos.x + (MAP_TILE_SIZE / 2) 
					&& screenPos.y + (BULLET_SIZE_Y / 2) > TilePos.y - (MAP_TILE_SIZE / 2) && screenPos.y - (BULLET_SIZE_Y / 2) < TilePos.y + (MAP_TILE_SIZE / 2))
                {
					//当たったときの処理
                    m_bHit = true;
                    if((*(pScene + nCount))->GetObjType() == OBJTYPE_MAP_TILE)
                    {
						//当たったタイルの色が白でなければ白くする
                        if(((CScene2d*)(*(pScene + nCount)))->GetCol() != D3DCOLOR_RGBA(255,255,255,255))
                        {
                            pScore->AddScore(-10);
                            ((CScene2d*)(*(pScene + nCount)))->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
                        }
                    }
                }
            }
        }
    }
	if (screenPos.x<0 || screenPos.x>SCREEN_WIDTH || screenPos.y < 0 || screenPos.y > SCREEN_HEIGHT)
	{
		bElase = true;
	}
	//弾が当たった場合
    if(m_bHit)
    {
		//爆発生成
		CExplosion::Create(screenPos, D3DCOLOR_RGBA(255, 255, 255, 255));
		bElase = true;
    }
	if (bElase)
	{
		Uninit();
	}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CBullet::Draw(void)
{
    CScene2d::Draw();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
    CBullet* pBullet = new CBullet;
	//ワールド座標の設定
    pBullet->SetWorldPos(pos);
	//発射音再生
    CManager::GetSound()->Play(CSound::SE_SHOT);
	//移動量設定
    pBullet->m_move = move;
	//大きさ初期化
    pBullet->SetSize(D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0));
	//オブジェクトタイプ設定
    pBullet->SetObjType(OBJTYPE_BULLET);
	//初期化関数実行
    pBullet->Init();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル読み込み関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CBullet::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\Explosion.png", &m_pTexture);
	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//読み込みデータ破棄処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CBullet::Unload(void)
{
	//テクスチャ破棄
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
