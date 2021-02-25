//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	item.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "item.h"

#include "inputkeyboard.h"
#include "inputmouse.h"
#include "main.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CModel::MODELDATA CItem::m_modelData = {};

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CItem::CItem()
{
    m_fFrameCounter = 0;
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
    CPlayer* pPlayer      = NULL;
    pPlayer               = CManager::GetPlayer();
    D3DXVECTOR3 playerPos = pPlayer->GetPos();
    //いい感じにふわふわさせる処理
    m_fFrameCounter += 0.05f;
    SetRotation(GetRotation() + D3DXVECTOR3(0, D3DXToRadian(1), 0));
    SetPosition(GetPosition() + D3DXVECTOR3(0, sinf(m_fFrameCounter) / 5, 0));
    CModel::Update();
    //一定距離まで近づいたらアイテムを入手する処理
    if(sqrt(pow(GetPosition().x - playerPos.x, 2.0f) + pow(GetPosition().z - playerPos.z, 2.0f)) < ITEM_OBTAIN_RANGE)
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
    CItem* pItem;
    pItem = new CItem;
    //各種情報の設定
    pItem->SetPosition(pos);
    pItem->SetRotation(rot);
	pItem->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
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
}
