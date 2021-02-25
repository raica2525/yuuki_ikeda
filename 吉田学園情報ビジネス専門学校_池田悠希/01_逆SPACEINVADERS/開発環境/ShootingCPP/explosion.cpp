//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	explosion.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CExplosion::CExplosion() : CScene2d(3)
{
    m_nLife = EXPLOSION_LIFE;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CExplosion::~CExplosion()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CExplosion::Init(void)
{
    CScene2d::Init();
    BindTexture(m_pTexture);

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CExplosion::Uninit(void)
{
    CScene2d::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CExplosion::Update(void)
{
    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 move;
	CScene2d::Update();
	
	//持続時間が切れたら消す
    if(m_nLife-- <= 0)
    {
        Uninit();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CExplosion::Draw(void)
{
    CScene2d::Draw();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DCOLOR col)
{
	//メモリ確保
    CExplosion* pExplosion = new CExplosion;   
	//音声再生
    CManager::GetSound()->Play(CSound::SE_EXPLOSION);
	//各種情報初期化
    pExplosion->SetPos(pos);
    pExplosion->SetCol(col);
    pExplosion->SetSize(D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0));
    pExplosion->SetObjType(OBJTYPE_EXPLOSION);
	//初期関数
    pExplosion->Init();
	//確保したメモリのアドレスを返す
    return pExplosion;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル読み込み関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CExplosion::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\explosion.png", &m_pTexture);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//読み込みデータ破棄処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CExplosion::Unload(void)
{
	//テクスチャ破棄
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
