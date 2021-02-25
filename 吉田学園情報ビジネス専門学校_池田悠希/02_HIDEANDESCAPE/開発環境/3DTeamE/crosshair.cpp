//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	crosshair.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

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
    m_fspread    = 0;
    m_fminspread = 0;
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
    //2Dポリゴンの生成
    for(int nCount = 0; nCount < 4; nCount++)
    {
        if(m_apObject2d[nCount] != NULL)
        {
            m_apObject2d[nCount] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), CROSSHAIR_PART_SIZE, 2);
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
    for(int nCount = 0; nCount < 4; nCount++)
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
    D3DXVECTOR3 pos;
    if(m_fspread > 0)
    {
        m_fspread -= 2;
        if(m_fspread < 0)
        {
            m_fspread = 0;
        }
    }
    if(m_fspread > MAX_SPREAD)
    {
        m_fspread = MAX_SPREAD;
    }
    for(int nCount = 0; nCount < 4; nCount++)
    {
        //画面の中心から広がり分外側にポリゴンの位置を移動
        if(m_apObject2d[nCount] != NULL)
        {
            switch(nCount)
            {
                case 0:
                    pos = D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - (m_fminspread + m_fspread), 0);
                    break;
                case 1:
                    pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (m_fminspread + m_fspread), SCREEN_HEIGHT / 2, 0);
                    break;
                case 2:
                    pos = D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + (m_fminspread + m_fspread), 0);
                    break;
                case 3:
                    pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (m_fminspread + m_fspread), (SCREEN_HEIGHT / 2), 0);
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
CCrosshair* CCrosshair::Create(float minSpread)
{
    CCrosshair* pCrosshair   = NULL;
    pCrosshair               = new CCrosshair;
    pCrosshair->m_fminspread = minSpread;
    pCrosshair->Init();
    return pCrosshair;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//広がりの変更
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCrosshair::AddSpread(float value)
{

    m_fspread += value;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//広がりの最低値の変更
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCrosshair::SetMinSpread(float minspread)
{
    m_fminspread = minspread;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//広がりを取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
float CCrosshair::GetSpread(void)
{
    return m_fspread + m_fminspread;
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
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}