//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	scene2d.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "object2d.h"

#include "input.h"
#include "inputkeyboard.h"
#include "manager.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
    //各種変数初期化
    m_pTexture = NULL;
    m_pVtxBuff = NULL;
    m_pos      = ZEROVECTOR3;
    m_move     = ZEROVECTOR3;
    m_fRot     = 0.0f;
    m_col      = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject2D::~CObject2D()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CObject2D::Init(void)
{
    VERTEX_2D* pVtx;
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //頂点バッファの生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //頂点情報を設定
    pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

    //テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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
void CObject2D::Uninit(void)
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
void CObject2D::Update(void)
{
    D3DXMATRIX mtxTrans;
    D3DXMATRIX mtxRot;
    VERTEX_2D* pVtx;

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //頂点座標更新
    pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

    //頂点カラー更新
    pVtx[0].col = m_col;
    pVtx[1].col = m_col;
    pVtx[2].col = m_col;
    pVtx[3].col = m_col;

    m_pVtxBuff->Unlock();

    //回転行列生成
    D3DXMatrixRotationZ(&mtxRot, D3DXToRadian(m_fRot));
    //平行移動行列生成
    D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        //回転行列で変換
        D3DXVec3TransformCoord(&(pVtx[nCount].pos), &(pVtx[nCount].pos), &mtxRot);
        //移動
        D3DXVec3TransformCoord(&(pVtx[nCount].pos), &(pVtx[nCount].pos), &mtxTrans);
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject2D::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    //頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

    //頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_2D);

    //テクスチャの設定
    pDevice->SetTexture(0, m_pTexture);

    //ポリゴンの描画
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject2D::SetPos(const D3DXVECTOR3 pos)
{
    m_pos = pos;
}

void CObject2D::SetMove(const D3DXVECTOR3 move)
{
    m_move = move;
}

void CObject2D::SetSize(const D3DXVECTOR3 size)
{
    m_size = size;
}

void CObject2D::SetRot(const float rot)
{
    m_fRot = rot;
}

void CObject2D::SetTexPos(D3DXVECTOR2* const pTexPos)
{
    VERTEX_2D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].tex = *(pTexPos + nCount);
    }
    m_pVtxBuff->Unlock();
}

void CObject2D::SetCol(const D3DCOLOR col)
{
    m_col = col;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
D3DXVECTOR3 CObject2D::GetMove(void)
{
    return m_move;
}

D3DXVECTOR3 CObject2D::GetPos(void)
{
    return m_pos;
}

D3DXVECTOR3 CObject2D::GetSize(void)
{
    return m_size;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//生成処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority)
{
    CObject2D* pScene2d = new CObject2D(nPriority);
    pScene2d->m_pos     = pos;
    pScene2d->m_size    = size;
    pScene2d->Init();

    return pScene2d;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャの割当
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
    m_pTexture = pTexture;
}
