//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	laserlayer.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "laserlayer.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CLaserLayer::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CLaserLayer::CLaserLayer()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CLaserLayer::~CLaserLayer()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CLaserLayer::Init(void)
{
    CPolygon::Init();
    BindTexture(m_pTexture);

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaserLayer::Uninit(void)
{
    CPolygon::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaserLayer::Update(void)
{
    CPolygon::Update();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaserLayer::Draw(void)
{
    CPolygon::Draw();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CLaserLayer* CLaserLayer::Create(D3DXVECTOR3 pos, D3DCOLOR col, int nWidth, int Length, float fRot)
{
    CLaserLayer* pLaserLayer = new CLaserLayer;   
	//各種変数初期化
    pLaserLayer->SetPos(pos);
    pLaserLayer->SetCol(col);
    pLaserLayer->SetRot(fRot);
    pLaserLayer->SetSize(D3DXVECTOR3((float)Length, (float)nWidth, 0));
    pLaserLayer->SetObjType(CScene::OBJTYPE_LASER);
	//初期化関数
    pLaserLayer->Init();
    return pLaserLayer;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル読み込み処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CLaserLayer::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\Laser.png", &m_pTexture);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//読み込みデータ破棄処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CLaserLayer::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
