//===============================================
//
// クリッピングマスクの処理 (cliping_musk.cpp)
// Author : 池田悠希
//
//===============================================

//========================
// インクルードファイル
//========================
#include "cliping_musk.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=======================
// 静的メンバ変数宣言
//=======================
bool CClipingMusk::m_abUsingReferenceValue[MAX_REFERENCE_VALUE] = {};

//============================================================
// シーン上の2Dポリゴンのデフォルトコンストラクタ
// Author : 池田悠希
//============================================================
CClipingMusk::CClipingMusk()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = DEFAULT_VECTOR;
	m_size = DEFAULT_VECTOR;

	m_nAlphaTestBorder = DEFAULT_ALPHATEST_BORDER_2D;

	//参照値設定
	for (int nCount = 0; nCount < MAX_REFERENCE_VALUE; nCount++)
	{
		if (m_abUsingReferenceValue[nCount] == false)
		{
			m_dwReferenceValue = nCount;
			m_abUsingReferenceValue[nCount] = true;
			break;
		}
	}

}

//============================================================
// シーン上の2Dポリゴンのデストラクタ
// Author : 池田悠希
//============================================================
CClipingMusk::~CClipingMusk()
{

}

//============================================================
// シーン上の2Dポリゴンの初期化処理
// Author : 池田悠希
//============================================================
HRESULT CClipingMusk::Init(void)
{
	// レンダラーからデバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	VERTEX_2D *pVtx = NULL;	// 頂点情報へのポインタ

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	

	// 頂点座標の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, -(m_size.y / 2.0f), 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -(m_size.y / 2.0f), 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, +(m_size.y / 2.0f), 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, +(m_size.y / 2.0f), 0.0f);

	// rhwの設定（値は1.0で設定する）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーを設定（0.0f～1.0fの値で設定する）
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex[0] = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex[0] = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex[0] = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================================
// シーン上の2Dポリゴンの終了処理
// Author : 池田悠希
//============================================================
void CClipingMusk::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	m_abUsingReferenceValue[m_dwReferenceValue] = false;
}

//============================================================
// シーン上の2Dポリゴンの更新処理
// Author : 池田悠希
//============================================================
void CClipingMusk::Update(void)
{

}

//=============================================================
// シーン上の2Dポリゴンの描画処理
// Author : 池田悠希
//=============================================================
void CClipingMusk::Draw(void)
{
	// レンダラーからデバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlphaTestBorder);

	//アルファテストの比較方法の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Zテストを常に失敗するように
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);

	//ステンシルの設定
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILREF, m_dwReferenceValue + 1);
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	//テクスチャを指定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ステンシルの無効化
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	//Zテストの比較方法をもとに戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// テクスチャの設定の解除　
	pDevice->SetTexture(0, NULL);

}

//=============================================================
// シーン上の2Dポリゴンのテクスチャを割り当て
// Author : 池田悠希
//=============================================================
void CClipingMusk::BindTexture(const int nNumTexture)
{
	m_pTexture = CManager::GetTexture()->GetInfo(nNumTexture)->pTexture;
}

//=============================================================
// シーン上の2Dポリゴンの頂点座標を設定
// Author : 池田悠希
//=============================================================
void CClipingMusk::SetVertex(void)
{
	VERTEX_2D *pVtx = NULL;	// 頂点情報へのポインタ

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================
// シーン上の2Dポリゴンの回転する頂点座標を設定
// Author : 池田悠希
//=============================================================
void CClipingMusk::SetRotVertex(float fAngle)
{
	// 頂点情報へのポインタ
	VERTEX_2D *pVtx = NULL;

	D3DXMATRIX mtxRot;
	D3DXMatrixRotationZ(&mtxRot, fAngle);

	D3DXVECTOR3 vtxPos[NUM_VERTEX];
	vtxPos[0] = D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
	vtxPos[1] = D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
	vtxPos[2] = D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
	vtxPos[3] = D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		D3DXVec3TransformNormal(&vtxPos[nCount], &vtxPos[nCount], &mtxRot);
		pVtx[nCount].pos = m_pos + vtxPos[nCount];
	}

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================
// クリエイト関数
// Author : 池田悠希
//=============================================================
CClipingMusk* CClipingMusk::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumTexture)
{
	CClipingMusk* pClipingMusk = new CClipingMusk;
	pClipingMusk->m_pos = pos;
	pClipingMusk->m_size = size;
	pClipingMusk->BindTexture(nNumTexture);
	pClipingMusk->Init();

	return pClipingMusk;
}

//=============================================================
// テクスチャを使わない場合のクリエイト関数
// Author : 池田悠希
//=============================================================
CClipingMusk* CClipingMusk::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CClipingMusk* pClipingMusk = new CClipingMusk;
	pClipingMusk->m_pos = pos;
	pClipingMusk->m_size = size;
	pClipingMusk->Init();

	return pClipingMusk;
}