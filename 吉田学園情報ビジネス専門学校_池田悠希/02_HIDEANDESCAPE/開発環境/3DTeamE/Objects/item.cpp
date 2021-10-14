//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	item.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "item.h"

#include "inputkeyboard.h"
#include "inputmouse.h"
#include "main.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define ITEM_MODEL_SIZE (0.05f)
#define ITEM_OBTAIN_RANGE (20.0f)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CModel::MODELDATA CItem::m_modelData = {};

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CItem::CItem()
{
    m_fFrameCounter = 0.0f;
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
    CModel::Init();
    //モデルの割当
    BindModel(m_modelData);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CItem::Uninit(void)
{
    //モデルの破棄
    CModel::Uninit();
    Release();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CItem::Update(void)
{
    CPlayer* pPlayer      = CManager::GetPlayer();
    D3DXVECTOR3 playerPos = pPlayer->GetPos();
    D3DXVECTOR3 pos       = GetPos();
    //いい感じにふわふわさせる処理
    m_fFrameCounter += 0.05f;
    SetRot(GetRot() + D3DXVECTOR3(0.0f, D3DXToRadian(1.0f), 0.0f));
    SetPos(pos + D3DXVECTOR3(0.0f, sinf(m_fFrameCounter) / 5.0f, 0.0f));
    CModel::Update();

    // y座標を無視する
    playerPos.y = pos.y = 0.0f;
    //一定距離まで近づいたらアイテムを入手する処理
    if(D3DXVec3Length(&(playerPos - pos)) < ITEM_OBTAIN_RANGE)
    {
        //入手したときの処理
        pPlayer->AddItem();
        Uninit();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CItem::Draw(void)
{
    CModel::Draw();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // メモリの確保
    CItem* pItem = new CItem;
    //各種情報の設定
    pItem->SetPos(pos);
    pItem->SetRot(rot);
    pItem->SetSize(D3DXVECTOR3(ITEM_MODEL_SIZE, ITEM_MODEL_SIZE, ITEM_MODEL_SIZE));
    // 初期化処理
    pItem->Init();

    return pItem;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//モデル読み込み
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CItem::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXLoadMeshFromX("Data\\Model\\Kaihuku.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_modelData.pBuffMat, NULL, &m_modelData.nNumMat, &m_modelData.pMesh);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//モデル破棄
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CItem::Unload(void)
{
    //メッシュの破棄
    if(m_modelData.pMesh != NULL)
    {
        m_modelData.pMesh->Release();
    }
    //マテリアルの破棄
    if(m_modelData.pBuffMat != NULL)
    {
        m_modelData.pBuffMat->Release();
    }
	ZeroMemory(&m_modelData, sizeof(m_modelData));
}
