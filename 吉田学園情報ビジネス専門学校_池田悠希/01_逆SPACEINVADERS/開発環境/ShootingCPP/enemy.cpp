//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	enemy.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "bullet.h"
#include "player.h"
#include "item.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[TYPE_MAX] = {};

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CEnemy::CEnemy() : CScene2d(2)
{
    m_nLife      = ENEMY_LIFE;
    m_state      = STATE_NORMAL;
    m_nShotCount = 60;
    m_nBulletRot = 0;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CEnemy::~CEnemy()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CEnemy::Init(void)
{
    CScene2d::Init();

    if(m_type == TYPE_CANON_DOWN)	//上向きのテクスチャを割当
    {
        BindTexture(m_apTexture[TYPE_CANON_UP]);
    }
    else	//その他の場合はそれぞれのテクスチャを割当
    {
        BindTexture(m_apTexture[m_type]);
    }
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CEnemy::Uninit(void)
{
    CScene2d::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CEnemy::Update(void)
{
    D3DXVECTOR3 move      = D3DXVECTOR3(0, 0, 0);
    D3DXVECTOR3 screenPos = GetPos();
    if(screenPos.x < SCREEN_WIDTH && m_type != TYPE_CANON_DOWN && m_type != TYPE_CANON_UP)//砲台以外の敵を左に動かす
    {
        move.x -= 1;
    }
	//座標設定
    SetWorldPos(GetWorldPos() + move);
    CScene** pScene = GetScene();
	//ダメージを受けている敵は色を変える
    if(m_state == STATE_DAMAGE)
    {
        SetCol(D3DCOLOR_RGBA(255, 0, 0, 255));
    }
    else if(m_state == STATE_NORMAL)
    {
        SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
    }
	//敵の種別によって処理を変える
    switch(m_type)
    {
		//砲台
        case TYPE_CANON_UP:
        case TYPE_CANON_DOWN:
            for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
            {
                if((*(pScene + nCount)) != NULL)
                {
                    if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
                    {
						//プレイヤー座標取得
                        D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();

                        D3DXVECTOR2 texPos[4];
						//プレイヤーの方向に向ける
                        if(m_type == TYPE_CANON_UP)
                        {
                            if(GetPos().x < PlayerPos.x)
                            {
                                texPos[0] = D3DXVECTOR2(1, 0);
                                texPos[1] = D3DXVECTOR2(0, 0);
                                texPos[2] = D3DXVECTOR2(1, 1);
                                texPos[3] = D3DXVECTOR2(0, 1);
                            }
                            else
                            {
                                texPos[0] = D3DXVECTOR2(0, 0);
                                texPos[1] = D3DXVECTOR2(1, 0);
                                texPos[2] = D3DXVECTOR2(0, 1);
                                texPos[3] = D3DXVECTOR2(1, 1);
                            }
                        }
                        else
                        {
                            if(GetPos().x < PlayerPos.x)
                            {
                                texPos[0] = D3DXVECTOR2(1, 1);
                                texPos[1] = D3DXVECTOR2(0, 1);
                                texPos[2] = D3DXVECTOR2(1, 0);
                                texPos[3] = D3DXVECTOR2(0, 0);
                            }
                            else
                            {
                                texPos[0] = D3DXVECTOR2(0, 1);
                                texPos[1] = D3DXVECTOR2(1, 1);
                                texPos[2] = D3DXVECTOR2(0, 0);
                                texPos[3] = D3DXVECTOR2(1, 0);
                            }
                        }
                        SetTexPos(texPos);
						
						//画面内ならプレイヤーに向かって弾を飛ばす
                        if(GetPos().x > 0 && GetPos().x < SCREEN_WIDTH)
                        {
                            if(m_nShotCount-- <= 0)
                            {

                                D3DXVECTOR3 BulletMove;
                                for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
                                {
                                    if((*(pScene + nCount)) != NULL)
                                    {
                                        if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
                                        {
                                            D3DXVec3Normalize(&BulletMove, &((((CPlayer*)(*(pScene + nCount)))->GetPos()) - GetPos()));
                                            BulletMove *= BULLET_SPEED;
                                            break;
                                        }
                                    }
                                }
                                CBullet::Create(GetPos(), BulletMove);
                                m_nShotCount = SHOT_CYCLE;
                            }
                        }
                    }
                }
            }
            break;

			//通常の敵
        case TYPE_NORMAL:

			//一定時間ごとにプレイヤーに向かって弾を発射する
            if(m_nShotCount-- <= 0)
            {
                for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
                {
                    if((*(pScene + nCount)) != NULL)
                    {
                        if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
                        {
                            D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();
                            if(GetPos().x > PlayerPos.x && GetPos().x < SCREEN_WIDTH)
                            {
                                D3DXVECTOR3 BulletMove;
                                for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
                                {
                                    if((*(pScene + nCount)) != NULL)
                                    {
                                        if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
                                        {
                                            D3DXVec3Normalize(&BulletMove, &((((CPlayer*)(*(pScene + nCount)))->GetPos()) - GetPos()));
                                            BulletMove *= BULLET_SPEED;
                                            break;
                                        }
                                    }
                                }
                                CBullet::Create(GetPos(), BulletMove);
                                m_nShotCount = SHOT_CYCLE;
                            }
                        }
                    }
                }
            }
            break;

			//スプリンクラー風敵
        case TYPE_SPRINKLER:
			//画面内なら一定時間ごとに弾をばらまく
            if(m_nShotCount-- < 0)
            {
                if(GetPos().x > 0 && GetPos().x < SCREEN_WIDTH)
                {
                    m_nBulletRot += 13;
                    D3DXVECTOR3 BulletVec = D3DXVECTOR3(cosf(D3DXToRadian(m_nBulletRot)), sinf(D3DXToRadian(m_nBulletRot)), 0);
                    CBullet::Create(GetPos(), BulletVec * BULLET_SPEED);
                    BulletVec = D3DXVECTOR3(cosf(D3DXToRadian(m_nBulletRot - 180)), sinf(D3DXToRadian(m_nBulletRot - 180)), 0);
                    CBullet::Create(GetPos(), BulletVec * BULLET_SPEED);
                    m_nShotCount = 3;
                }
            }
    }
    m_state = STATE_NORMAL;
    CScene2d::Update();

	//画面の左端より左にいれば消す
    if(GetPos().x + ENEMY_SIZE / 2 < 0)
    {
        Uninit();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CEnemy::Draw(void)
{
    CScene2d::Draw();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CEnemy::Create(D3DXVECTOR3 pos, TYPE type)
{
    CEnemy* pEnemy = new CEnemy;
    pEnemy->SetWorldPos(pos);
    pEnemy->SetSize(D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0));
    pEnemy->SetObjType(OBJTYPE_ENEMY);
    pEnemy->m_type = type;
    pEnemy->Init();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル読み込み関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CEnemy::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\enemy01.png", &m_apTexture[TYPE_NORMAL]);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\enemy02.png", &m_apTexture[TYPE_SPRINKLER]);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\enemy03.png", &m_apTexture[TYPE_CANON_UP]);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//読み込みデータ破棄処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CEnemy::Unload(void)
{
	//テクスチャ破棄
    for(int nCount = 0; nCount < TYPE_MAX; nCount++)
    {
        if(m_apTexture[nCount] != NULL)
        {
            m_apTexture[nCount]->Release();
            m_apTexture[nCount] = NULL;
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//弾丸が当たった時の処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CEnemy::HitLaser(int nDamage)
{
    m_state = STATE_DAMAGE;
    m_nLife -= nDamage;
    if(m_nLife <= 0)
    {
		//スプリンクラーの敵を倒した時は回復アイテムを出す
        if(m_type == TYPE_SPRINKLER)
        {
            CItem::Create(GetPos(), CItem::TYPE_LIFE);
        }

		//死亡時の音を出す
        CManager::GetSound()->Play(CSound::SE_EXPLOSION);
        CScene** pScene = GetScene();

		//倒した敵の種類によってスコアを加算
        for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
        {
            if((*(pScene + nCount)) != NULL)
            {
                if((*(pScene + nCount))->GetObjType() == OBJTYPE_SCORE)
                {
                    switch(m_type)
                    {
                        case TYPE_NORMAL:
                            ((CScore*)(*(pScene + nCount)))->AddScore(100);
                            break;
                        case TYPE_SPRINKLER:
                            ((CScore*)(*(pScene + nCount)))->AddScore(500);
                            break;
                        case TYPE_CANON_DOWN:
                        case TYPE_CANON_UP:
                            ((CScore*)(*(pScene + nCount)))->AddScore(150);
                    }
                }
            }
        }
        Uninit();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//状態取得処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CEnemy::STATE CEnemy::GetState(void)
{
    return m_state;
}
