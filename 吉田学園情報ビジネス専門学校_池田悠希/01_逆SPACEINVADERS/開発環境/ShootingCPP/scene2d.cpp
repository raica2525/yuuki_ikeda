//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	scene2d.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "inputkeyboard.h"
#include "map.h"
#include "score.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
    m_pTexture = NULL;    // テクスチャへのポインタ
    m_pVtxBuff = NULL;    // 頂点バッファへのポインタ
    m_fScroll  = 0;
    m_pos      = D3DXVECTOR3(0, 0, 0);    // ポリゴンの位置
    m_col      = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScene2d::~CScene2d()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CScene2d::Init(void)
{
    VERTEX_2D* pVtx;
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // 頂点バッファの生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,    //バッファサイズ
                                D3DUSAGE_WRITEONLY,                //固定
                                FVF_VERTEX_2D,                     //頂点フォーマット
                                D3DPOOL_MANAGED,                   //固定
                                &m_pVtxBuff,                       //変数名によって変化
                                NULL);

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
    // 頂点情報を設定

    //テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2(0, 0);
    pVtx[1].tex = D3DXVECTOR2(1, 0);
    pVtx[2].tex = D3DXVECTOR2(0, 1);
    pVtx[3].tex = D3DXVECTOR2(1, 1);

    // rhwの設定
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //頂点カラーの設定
    pVtx[0].col = m_col;  
    pVtx[1].col = m_col;  
    pVtx[2].col = m_col;  
    pVtx[3].col = m_col;  
    m_pVtxBuff->Unlock();

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScene2d::Uninit(void)
{
    // 頂点バッファの破棄
    if(m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }

    Release();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScene2d::Update(void)
{
    VERTEX_2D* pVtx;
    //スクロール
    if(SCREEN_WIDTH + m_fScroll < CMap::GetLength() * MAP_TILE_SIZE)
    {
        if(CScene::GetObjType() == OBJTYPE_BG || CScene::GetObjType() == OBJTYPE_PLAYER)
        {
            m_worldPos.x += 2;
        }
        m_fScroll += 2;
        m_pos.x = m_worldPos.x - m_fScroll;
    }
    else if(CManager::GetAlive())
    {
        CMap::SetGoal(true);
    }

    m_pos.y = m_worldPos.y;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, -m_size.y / 2, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2, -m_size.y / 2, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, m_size.y / 2, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2, m_size.y / 2, 0.0f);

    pVtx[0].col = m_col;
    pVtx[1].col = m_col;
    pVtx[2].col = m_col;
    pVtx[3].col = m_col;

    m_pVtxBuff->Unlock();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScene2d::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = NULL;
    pDevice                   = CManager::GetRenderer()->GetDevice();
    // 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

    // 頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_2D);

    // テクスチャの設定
    pDevice->SetTexture(0, m_pTexture);

    // ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CScene2d* CScene2d::Create(int nPriority)
{
	CScene2d* pScene2d = new CScene2d(nPriority);
	pScene2d->Init();
	return pScene2d;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CScene2d::SetPos(D3DXVECTOR3 pos)
{
    m_pos      = pos;    // m_posを設定
    m_worldPos = pos + D3DXVECTOR3(m_fScroll, 0, 0);
}

void CScene2d::SetWorldPos(D3DXVECTOR3 pos)
{
    m_worldPos = pos;
    m_pos      = pos - D3DXVECTOR3(m_fScroll, 0, 0);
}

void CScene2d::SetCol(D3DCOLOR col)
{
	m_col = col;
}

void CScene2d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

void CScene2d::SetTexPos(D3DXVECTOR2* pTexPos)
{
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		pVtx[nCount].tex = *(pTexPos + nCount);
	}

	m_pVtxBuff->Unlock();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
D3DXVECTOR3 CScene2d::GetPos(void)
{
    return m_worldPos - D3DXVECTOR3(m_fScroll, 0, 0);
}

D3DXVECTOR3 CScene2d::GetWorldPos(void)
{
    return m_worldPos;
}

D3DCOLOR CScene2d::GetCol(void)
{
    return m_col;
}