//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	item.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "bullet.h"
#include "player.h"
#include "life.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CItem::m_apTexture[TYPE_MAX] = {};

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CItem::CItem() : CScene2d(2)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CItem::~CItem()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CItem::Init(void)
{
    CScene2d::Init();
	//テクスチャ割当
    BindTexture(m_apTexture[m_type]);

    return S_OK;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CItem::Uninit(void)
{
    CScene2d::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CItem::Update(void)
{
	//シーン取得
    CScene** pScene       = GetScene();
	//取得されたか
    bool bGet             = false;
	//画面上の座標を取得
    D3DXVECTOR3 screenPos = GetPos();

	//プレイヤーのポインタを探索
    for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
    {
        if((*(pScene + nCount)) != NULL)
        {
            if((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
            {
				//プレイヤーの座標取得
                D3DXVECTOR3 PlayerPos = ((CPlayer*)(*(pScene + nCount)))->GetPos();
				//プレイヤーと重なっていれば
                if(screenPos.x + (ITEM_SIZE / 2) > PlayerPos.x - (PLAYER_SIZE_X / 2) && screenPos.x - (ITEM_SIZE / 2) < PlayerPos.x + (PLAYER_SIZE_X / 2) 
					&& screenPos.y + (ITEM_SIZE / 2) > PlayerPos.y - (PLAYER_SIZE_Y / 2)&& screenPos.y - (ITEM_SIZE / 2) < PlayerPos.y + (PLAYER_SIZE_Y / 2))
                {
					//プレイヤーのライフを増やす
                    ((CPlayer*)(*(pScene + nCount)))->GetLife()->AddLife(30);
                    bGet = true;
                }
            }
        }
    }
    CScene2d::Update();
	//取得されていれば消す
    if(bGet)
    {
        Uninit();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CItem::Draw(void)
{
    CScene2d::Draw();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CItem::Create(D3DXVECTOR3 pos, TYPE type)
{
	//メモリ確保
    CItem* pItem = new CItem; 
	//各種情報設定
    pItem->SetWorldPos(pos);
    pItem->SetSize(D3DXVECTOR3(ITEM_SIZE, ITEM_SIZE, 0));
    pItem->SetObjType(OBJTYPE_ITEM);
    pItem->m_type = type;
	//初期関数
    pItem->Init();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル読み込み処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CItem::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\item01.png", &m_apTexture[TYPE_LIFE]);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//読み込みデータ破棄処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CItem::Unload(void)
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
