//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	crosshair.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define MAX_SPREAD (200.0f)
#define CROSSHAIR_PART_SIZE D3DXVECTOR3(6.0f, 20.0f, 0.0f)
#define CROSSHAIR_SPREAD_REDUCE_RATE (2.0f)

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "crosshair.h"

#include "camera.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CCrosshair::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CCrosshair::CCrosshair()
{
    m_fSpread    = 0.0f;
    m_fMinSpread = 0.0f;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CCrosshair::~CCrosshair()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CCrosshair::Init(void)
{
    // 2Dポリゴンの生成
    for(int nCount = 0; nCount < CROSSHAIR_PARTS_COUNT; nCount++)
    {
        if(m_apObject2d[nCount] != NULL)
        {
            m_apObject2d[nCount] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0), CROSSHAIR_PART_SIZE, 2);
            m_apObject2d[nCount]->SetRot(nCount * 90.0f);
            m_apObject2d[nCount]->SetCol(D3DCOLOR_RGBA(0, 255, 0, 255));
            m_apObject2d[nCount]->BindTexture(m_pTexture);
        }
    }
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCrosshair::Uninit(void)
{
    //ポリゴンの終了
    for(int nCount = 0; nCount < CROSSHAIR_PARTS_COUNT; nCount++)
    {
        if(m_apObject2d[nCount] != NULL)
        {
            m_apObject2d[nCount]->Uninit();
        }
    }
    Release();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCrosshair::Update(void)
{
    //拡散をへらす
    if(m_fSpread > 0)
    {
        m_fSpread -= CROSSHAIR_SPREAD_REDUCE_RATE;
        if(m_fSpread < 0.0f)
        {
            m_fSpread = 0.0f;
        }
    }

    //拡散が最大以上なら最大に戻す
    if(m_fSpread > MAX_SPREAD)
    {
        m_fSpread = MAX_SPREAD;
    }

    //拡散量に応じてポリゴンを移動
    for(int nCount = 0; nCount < CROSSHAIR_PARTS_COUNT; nCount++)
    {
        D3DXVECTOR3 pos;
        if(m_apObject2d[nCount] != NULL)
        {
            switch(nCount)
            {
                case 0:
                    pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) - (m_fMinSpread + m_fSpread), 0);
                    break;
                case 1:
                    pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (m_fMinSpread + m_fSpread), SCREEN_HEIGHT / 2.0f, 0);
                    break;
                case 2:
                    pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) + (m_fMinSpread + m_fSpread), 0);
                    break;
                case 3:
                    pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (m_fMinSpread + m_fSpread), (SCREEN_HEIGHT / 2.0f), 0);
                    break;
            }
            m_apObject2d[nCount]->SetPos(pos);
        }
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCrosshair::Draw(void)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CCrosshair* CCrosshair::Create(const float fMinSpread)
{
    CCrosshair* pCrosshair   = new CCrosshair;
    pCrosshair->m_fMinSpread = fMinSpread;
    pCrosshair->Init();
    return pCrosshair;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//広がりの変更
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCrosshair::AddSpread(const float fValue)
{
    m_fSpread += fValue;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//広がりの最低値の変更
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCrosshair::SetMinSpread(const float fMinSpread)
{
    m_fMinSpread = fMinSpread;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//広がりを取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
float CCrosshair::GetSpread(void)
{
    return m_fSpread + m_fMinSpread;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCrosshair::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Data/Texture/crosshair.png", &m_pTexture);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャアンロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCrosshair::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
