//=============================================================================
//
// ライン処理 [line.cpp]
// Author : 吉田悠人
//
//=============================================================================


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "line.h"
//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CLine::CLine()
{
	m_pVtxBuff = NULL;
	m_Startpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Endpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//=============================================================================
// デストラクタ
//=============================================================================
CLine::~CLine()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CLine::Init(void)
{
	VERTEX_POINT *pVtx = NULL;
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	//頂点バッファの生成

	pDevice->CreateVertexBuffer(sizeof(VERTEX_POINT) * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_POINT, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	
	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3((m_Startpos.x) , m_Startpos.y, m_Startpos.z);
	pVtx[1].pos = D3DXVECTOR3((m_Endpos.x) , m_Endpos.y, m_Endpos.z);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	//アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CLine::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CLine::Update(void)
{
	VERTEX_POINT *pVtx = NULL;

	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3((m_Startpos.x), m_Startpos.y, m_Startpos.z);
	pVtx[1].pos = D3DXVECTOR3((m_Endpos.x), m_Endpos.y, m_Endpos.z);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	//アンロック
	m_pVtxBuff->Unlock();
	
}

//=============================================================================
// 描画関数
//=============================================================================
void CLine::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	D3DMATERIAL9 matDef;
	pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //行列計算用のマトリクス
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);    //αデスティ

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_StartWorld);

	//回転行列の生成と計算
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&m_StartWorld, &m_StartWorld, &mtxRot);

	//位置を反映	
	D3DXMatrixTranslation(&mtxTrans, (m_Startpos.x+ m_Endpos.x)/2, (m_Startpos.y+ m_Endpos.y)/2,(m_Startpos.z+ m_Endpos.z)/2);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	D3DXMatrixMultiply(&m_StartWorld, &m_StartWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_POINT));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_POINT);

	//ライン描画
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 2);
	pDevice->SetTexture(0, NULL);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);    //αデスティ
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);

}

void CLine::SetStartPosition(D3DXVECTOR3 pos)
{
	m_Startpos = pos;
}
void CLine::SetEndPosition(D3DXVECTOR3 pos)
{
	m_Endpos = pos;
}


void CLine::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}


void CLine::SetCol(D3DCOLOR col)
{
	m_col = col;
}


