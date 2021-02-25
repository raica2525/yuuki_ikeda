//=============================================================================
//
// ビルボード処理 [billboard.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "billboard.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"	
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CBillboard::CBillboard()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	m_mtxWorld;		//行列計算用
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fTexX = 0.0f;
	m_fTexY = 0.0f;
	m_fTexX2 = 0.0f;
	m_fTexY2 = 0.0f;
}

//=============================================================================
//	デストラクタ
//=============================================================================
CBillboard::~CBillboard()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_3D *pVtx = NULL;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の初期化 ※位置は行列で計算するため原点中心の4頂点を定義
	pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2, m_size.y / 2, +m_size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(m_size.x / 2, m_size.y / 2, +m_size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2, -m_size.y / 2, +m_size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(m_size.x / 2, -m_size.y / 2, +m_size.z / 2);

	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	//アンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CBillboard::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CBillboard::Update(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2, m_size.y / 2, +m_size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(m_size.x / 2, m_size.y / 2, +m_size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2, -m_size.y / 2, +m_size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(m_size.x / 2, -m_size.y / 2, +m_size.z / 2);

	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画関数
//=============================================================================
void CBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //行列計算用のマトリクス
	D3DMATERIAL9 matDef;

	pDevice->SetTexture(0, m_pTexture);
	//アルファテスト有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	//アルファテストの比較方法の設定（GREATERは基準値より大きい場合）
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転の逆行列
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x,
		m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld,
		&mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//マテリアル情報
	ZeroMemory(&matDef, sizeof(matDef));
	matDef.Ambient.r = m_col.r;
	matDef.Ambient.g = m_col.g;
	matDef.Ambient.b = m_col.b;
	matDef.Ambient.a = m_col.a;

	pDevice->SetMaterial(&matDef);
	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);   //数値
	pDevice->SetTexture(0, NULL);

	//アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

}

//=============================================================================
// 位置の設定関数
//=============================================================================
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//=============================================================================
// 拡大率の設定関数
//=============================================================================
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// テクスチャの割り当て関数
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// テクスチャの位置の設定関数
//=============================================================================
void CBillboard::SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2)
{
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexX2 = fTexX2;
	m_fTexY2 = fTexY2;
}

//=============================================================================
// 色の設定関数
//=============================================================================
void CBillboard::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
