//=============================================================================
//
// メッシュフィールド_円柱 [meshfield_cylinder.h]
// Author : 吉田悠人
//
//=============================================================================


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "meshfield_cylinder.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"


//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshCylinder::CMeshCylinder() : CObject(1)
{
	m_pos = ZEROVECTOR3;
	m_rot = D3DXVECTOR3(90.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	m_col[MESH_Y_BLOCK] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_pTexture = NULL;
	SetObjType(OBJTYPE_NONE);
	for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
	{
		m_bColAnima[nMesh] = false;

	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshCylinder::~CMeshCylinder()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CMeshCylinder::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_3D *pVtx = NULL;
	D3DXVECTOR3 nor;
	//インデックス
	int index = 0;
	//テクスチャ座標
	int texpos = 0;
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_VERTEX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	for (int vIndex = 0; vIndex < MESH_Y_BLOCK + 1; vIndex++)
	{
		texpos = 0;
		for (int hlndex = 0; hlndex < MESH_X_BLOCK + 1; hlndex++)
		{
			//座標
			float angle = (float)hlndex * 360.0f / (float)MESH_X_BLOCK;
			pVtx[index].pos = D3DXVECTOR3(sinf(D3DXToRadian(-angle))*(m_size.x / 2),
				(-vIndex*(m_size.y / MESH_Y_BLOCK)) + (m_size.y / 2),
				cosf(D3DXToRadian(angle))*(m_size.z / 2));
			//各頂点の法線の設定（ベクトルの大きさは１にする必要がある）
			D3DXVec3Normalize(&nor, &m_rot);

			pVtx[index].nor = -m_rot;

			//頂点カラーの設定
			pVtx[index].col = m_col[vIndex];
			//テクスチャ
			pVtx[index].tex = D3DXVECTOR2((float)texpos*0.125f,(float)vIndex);
			index += 1;
			texpos += 1;
		}
	}
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, NULL, &m_pTexture);
	//インデックスバッファ（ポリゴンバッファ）の生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_INDEX_NUM, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL);
	WORD*pldx;
	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pldx, 0);
	//インデックス数値の初期化
	index = 0;
	for (int nyBlockCount = 0; nyBlockCount < MESH_Y_BLOCK; nyBlockCount++)
	{
		for (int nxBlockCount = 0; nxBlockCount < MESH_X_BLOCK + 1; nxBlockCount++)
		{
			//インデックス設定
			pldx[index] = 9 + (index / 2) - nyBlockCount;
			pldx[index + 1] = (index / 2) - nyBlockCount;
			index += 2;
		}

		//縮退ポリゴン用インデックス設定
		if (index < MESH_INDEX_NUM)
		{
			pldx[index] = (index / 2) - (nyBlockCount + 1);
			pldx[index + 1] = (9 + (index / 2)) - nyBlockCount;
			index += 2;
		}
	}
	m_pIdxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CMeshCylinder::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CMeshCylinder::Update(void)
{
	VERTEX_3D *pVtx = NULL;
	int index = 0;
	for (int vIndex = 0; vIndex < MESH_Y_BLOCK + 1; vIndex++)
	{
		for (int hlndex = 0; hlndex < MESH_X_BLOCK + 1; hlndex++)
		{
			//頂点バッファのロック
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			//頂点カラーの設定
			pVtx[index].col = m_col[vIndex];
			//頂点バッファのアンロック
			m_pVtxBuff->Unlock();

			index += 1;
		}
	}

}

//=============================================================================
// 描画関数
//=============================================================================
void CMeshCylinder::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//行列計算用のマトリクス
	D3DMATERIAL9 matDef;
	//ワールドマトリクスの初期化処理
	D3DXMatrixIdentity(&m_mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(m_rot.y), D3DXToRadian(m_rot.x), D3DXToRadian(m_rot.z));
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	ZeroMemory(&matDef, sizeof(matDef));
	matDef.Ambient = m_col[0];
	pDevice->SetMaterial(&matDef);
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの描画
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴン描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESH_VERTEX_NUM, 0, MESH_PRIMITIVE_NUM);
	//テクスチャの初期化
	pDevice->SetTexture(0, NULL);
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// セットpos関数
//=============================================================================
void CMeshCylinder::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// セットrot関数
//=============================================================================
void CMeshCylinder::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// セットサイズ関数
//=============================================================================
void CMeshCylinder::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// セットテクスチャ関数
//=============================================================================
void CMeshCylinder::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// セットカラー関数
//=============================================================================
void CMeshCylinder::SetColor(D3DXCOLOR col, int fMeshY)
{
	m_col[fMeshY] = col;
}
//=============================================================================
// ゲットカラー関数
//=============================================================================
D3DXCOLOR CMeshCylinder::GetColor(int fMeshY)
{
	return m_col[fMeshY];
}
//=============================================================================
// 位置取得関数
//=============================================================================
D3DXVECTOR3 CMeshCylinder::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 向き取得関数
//=============================================================================
D3DXVECTOR3 CMeshCylinder::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// ゲットサイズ関数
//=============================================================================
D3DXVECTOR3 CMeshCylinder::GetSize(void)
{
	return m_size;
}

//=============================================================================
// ゲットサイズ関数
//=============================================================================
void CMeshCylinder::ColorAnimation(void)
{
	//メッシュのカラー変更
	for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
	{
		if (m_bColAnima[nMesh] == true)
		{
			m_col[nMesh] = (D3DXCOLOR(m_col[nMesh].r, m_col[nMesh].g, m_col[nMesh].b, m_col[nMesh].a + 0.01f));
		}
		else
		{
			m_col[nMesh] = (D3DXCOLOR(m_col[nMesh].r, m_col[nMesh].g, m_col[nMesh].b, m_col[nMesh].a - 0.01f));
		}
		if (m_col[nMesh].a <= 0.0f)
		{
			m_bColAnima[nMesh] = true;
		}
		else if (m_col[nMesh].a>=1.0f)
		{
			m_bColAnima[nMesh] = false;
		}
	}
}

