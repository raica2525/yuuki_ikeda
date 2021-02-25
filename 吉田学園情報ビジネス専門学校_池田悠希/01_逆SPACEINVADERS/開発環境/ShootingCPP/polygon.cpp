#include "polygon.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "scene.h"

CPolygon::CPolygon()
{
    m_pTexture = NULL;                    // テクスチャへのポインタ
    m_pVtxBuff = NULL;                    // 頂点バッファへのポインタ
    m_pos      = D3DXVECTOR3(0, 0, 0);    // ポリゴンの位置
    m_col      = D3DCOLOR_RGBA(255, 255, 255, 255);
}
CPolygon::~CPolygon()
{
}

HRESULT CPolygon::Init(void)
{

    VERTEX_2D* pVtx;
    LPDIRECT3DDEVICE9 pDevice = NULL;
    pDevice                   = CManager::GetRenderer()->GetDevice();
    // ポリゴンの位置を設定

    // テクスチャの生成

    // 頂点バッファの生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,    //バッファサイズ
                                D3DUSAGE_WRITEONLY,                //固定
                                FVF_VERTEX_2D,                     //頂点フォーマット
                                D3DPOOL_MANAGED,                   //固定
                                &m_pVtxBuff,                       //変数名によって変化
                                NULL);

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, -m_size.y / 2, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2, -m_size.y / 2, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, m_size.y / 2, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2, m_size.y / 2, 0.0f);
    D3DXMATRIX posMatrix;       // 頂点行列
    D3DXMATRIX rotateMatrix;    // 回転行列
    D3DXVECTOR3 rotationCenter;

    if(m_objtype == CScene::OBJTYPE_LASER)
    {
        CScene** pScene = CScene::GetScene();
        for(int nCount = 0; nCount <= PRIORITY_MAX * MAX_SCENE; nCount++)
        {
            if(pScene[nCount] != NULL)
            {
                if(pScene[nCount]->GetObjType() == CScene::OBJTYPE_PLAYER)
                {
                    rotationCenter = ((CPlayer*)(pScene[nCount]))->GetPos();
                    break;
                }
            }
        }
    }
    else
    {
        rotationCenter = m_pos;
    }
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].pos -= rotationCenter;
    }
    // 行列の初期化（単位行列生成）
    D3DXMatrixIdentity(&posMatrix);
    D3DXMatrixIdentity(&rotateMatrix);

    D3DXMatrixRotationZ(&rotateMatrix, m_fRot);

    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        // 現在の頂点座標を格納
        D3DXMatrixTranslation(
          &posMatrix, pVtx[nCount].pos.x, pVtx[nCount].pos.y, pVtx[nCount].pos.z);
        // 演算
        posMatrix *= rotateMatrix;
        // 演算結果を戻す
        pVtx[nCount].pos.x = posMatrix._41;    // 演算結果をポリゴンのＸ座標に格納
        pVtx[nCount].pos.y = posMatrix._42;    // 演算結果をポリゴンのＹ座標に格納
        pVtx[nCount].pos.z = posMatrix._43;    // 演算結果をポリゴンのＺ座標に格納
        pVtx[nCount].pos += rotationCenter;
        m_vtxPos[nCount] = pVtx[nCount].pos;
    }
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

    //頂点カラーの設定(0～255)
    pVtx[0].col = m_col;    // aは透明度
    pVtx[1].col = m_col;    // aは透明度
    pVtx[2].col = m_col;    // aは透明度
    pVtx[3].col = m_col;    // aは透明度
    m_pVtxBuff->Unlock();

    return S_OK;
}
void CPolygon::Uninit(void)
{
    // 頂点バッファの破棄
    if(m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
    delete this;
}
void CPolygon::Update(void)
{
    VERTEX_2D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    if(m_objtype == CScene::OBJTYPE_LASER)
    {
        pVtx[0].pos = m_pos + D3DXVECTOR3(0, -m_size.y / 2, 0.0f);
        pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x, -m_size.y / 2, 0.0f);
        pVtx[2].pos = m_pos + D3DXVECTOR3(0, m_size.y / 2, 0.0f);
        pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x, m_size.y / 2, 0.0f);
    }
    else
    {
        pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, -m_size.y / 2, 0.0f);
        pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2, -m_size.y / 2, 0.0f);
        pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, m_size.y / 2, 0.0f);
        pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2, m_size.y / 2, 0.0f);
    }
    D3DXMATRIX posMatrix;       // 頂点行列
    D3DXMATRIX rotateMatrix;    // 回転行列
    D3DXVECTOR3 rotationCenter;
    rotationCenter = m_pos;
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].pos -= rotationCenter;
    }
    // 行列の初期化（単位行列生成）
    D3DXMatrixIdentity(&posMatrix);
    D3DXMatrixIdentity(&rotateMatrix);

    D3DXMatrixRotationZ(&rotateMatrix, m_fRot);

    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        // 現在の頂点座標を格納
        D3DXMatrixTranslation(
          &posMatrix, pVtx[nCount].pos.x, pVtx[nCount].pos.y, pVtx[nCount].pos.z);
        // 演算
        posMatrix *= rotateMatrix;
        // 演算結果を戻す
        pVtx[nCount].pos.x = posMatrix._41;    // 演算結果をポリゴンのＸ座標に格納
        pVtx[nCount].pos.y = posMatrix._42;    // 演算結果をポリゴンのＹ座標に格納
        pVtx[nCount].pos.z = posMatrix._43;    // 演算結果をポリゴンのＺ座標に格納
        pVtx[nCount].pos += rotationCenter;
        m_vtxPos[nCount] = pVtx[nCount].pos;
    }

    pVtx[0].col = m_col;    // aは透明度
    pVtx[1].col = m_col;    // aは透明度
    pVtx[2].col = m_col;    // aは透明度
    pVtx[3].col = m_col;    // aは透明度

    m_pVtxBuff->Unlock();
}
void CPolygon::Draw(void)
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
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリティブの種類
                           0,
                           NUM_POLYGON    //プリティブの数
    );
}

void CPolygon::SetPos(D3DXVECTOR3 pos)
{
    m_pos = pos;    // m_posを設定
}

D3DXVECTOR3 CPolygon::GetPos(void)
{
    return m_pos;
}

void CPolygon::SetCol(D3DXCOLOR col)
{
    m_col = col;    // m_posを設定
}

D3DXVECTOR3 CPolygon::GetVtxPos(int nIndex)
{
    return m_vtxPos[nIndex];
}

void CPolygon::SetRot(float fRot)
{
    m_fRot = fRot;
}

void CPolygon::SetObjType(CScene::OBJTYPE objtype)
{
    m_objtype = objtype;
}

CPolygon* CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRot, CScene::OBJTYPE objtype)
{
    CPolygon* pPolygon  = new CPolygon();
    pPolygon->m_pos     = pos;
    pPolygon->m_size    = size;
    pPolygon->m_fRot    = fRot;
    pPolygon->m_objtype = objtype;
    pPolygon->Init();

    return pPolygon;
}

void CPolygon::SetSize(D3DXVECTOR3 size)
{
    m_size = size;
}

void CPolygon::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
    m_pTexture = pTexture;
}

void CPolygon::SetTexPos(D3DXVECTOR2* pTexPos)
{
    VERTEX_2D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].tex = *(pTexPos + nCount);
    }

    m_pVtxBuff->Unlock();
}
