//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	polygon3d.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "polygon3d.h"

#include "manager.h"
#include "renderer.h"

CPolygon3D::CPolygon3D()
{
    m_pTexture = NULL;
    m_pVtxBuff = NULL;
}
CPolygon3D::~CPolygon3D()
{
}

HRESULT CPolygon3D::Init(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
    VERTEX_3D* pVtx  = NULL;
    D3DXVECTOR3 size = GetScale();
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].pos = D3DXVECTOR3(-size.x, 0, -size.y);
    pVtx[1].pos = D3DXVECTOR3(size.x, 0, -size.y);
    pVtx[2].pos = D3DXVECTOR3(-size.x, 0, size.y);
    pVtx[3].pos = D3DXVECTOR3(size.x, 0, size.y);

    pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
    pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
    pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
    pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

    pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
    m_pVtxBuff->Unlock();
	CObject3D::Init();
    return S_OK;
}
void CPolygon3D::Uninit(void)
{
    if(m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
	CObject3D::Uninit();
}
void CPolygon3D::Update(void)
{
    VERTEX_3D* pVtx  = NULL;
    D3DXVECTOR3 size = GetScale();
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].pos = D3DXVECTOR3(-size.x, 0, -size.y);
    pVtx[1].pos = D3DXVECTOR3(size.x, 0, -size.y);
    pVtx[2].pos = D3DXVECTOR3(-size.x, 0, size.y);
    pVtx[3].pos = D3DXVECTOR3(size.x, 0, size.y);

    pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
    pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
    pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
    pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
    m_pVtxBuff->Unlock();
}
void CPolygon3D::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans, mtxWorld;
	D3DMATERIAL9 matDef;
    D3DXVECTOR3 rot = GetRotation();
	//アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	//アルファテストの比較方法の設定（GREATERは基準値より大きい場合）
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
    D3DXMatrixIdentity(&mtxWorld);
    D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(rot.y), D3DXToRadian(rot.x), D3DXToRadian(rot.z));
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
    D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	ZeroMemory(&matDef, sizeof(matDef));
	matDef.Ambient = D3DXCOLOR(1,1,1,0.5);
	pDevice->SetMaterial(&matDef);
    pDevice->SetTexture(0, m_pTexture);
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
    pDevice->SetFVF(FVF_VERTEX_3D);
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    pDevice->SetTexture(0, NULL);
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
}

CPolygon3D* CPolygon3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
    CPolygon3D* pPolygon3D = NULL;
    pPolygon3D             = new CPolygon3D;
    pPolygon3D->SetPosition(pos);
    pPolygon3D->SetRotation(rot);
    pPolygon3D->SetScale(size);
    pPolygon3D->Init();
    return pPolygon3D;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャの割当
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPolygon3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
