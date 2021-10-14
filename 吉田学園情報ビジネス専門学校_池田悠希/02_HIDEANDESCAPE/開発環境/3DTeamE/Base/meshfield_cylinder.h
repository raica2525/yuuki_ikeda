//=============================================================================
//
// メッシュフィールド_円柱 [meshfield_cylinder.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _MESHFIELD_CYLINDER_H_
#define _MESHFIELD_CYLINDER_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESH_X_BLOCK 8				//X方向のブロック数
#define MESH_Y_BLOCK 10				//Y方向のブロック数
#define MESH_VERTEX_NUM ((MESH_X_BLOCK+1)*(MESH_Y_BLOCK+1))								//頂点								
#define MESH_INDEX_NUM (((MESH_X_BLOCK+1)*2)*MESH_Y_BLOCK+(MESH_Y_BLOCK-1)*2)	//インデックス
#define MESH_PRIMITIVE_NUM (MESH_X_BLOCK*MESH_Y_BLOCK*2)+((MESH_Y_BLOCK-1)*4)			//ポリゴン


//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMeshCylinder :public CObject
{
public:
	CMeshCylinder();
	~CMeshCylinder();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col,int fMeshY);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	D3DXCOLOR GetColor(int fMeshY);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetSize(void);

	void ColorAnimation(void);
private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;//インデックスバッファへのポイント
	D3DXMATRIX m_mtxWorld; //行列計算用
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DXCOLOR m_col[MESH_Y_BLOCK+1];
	bool m_bColAnima[MESH_Y_BLOCK+1];
};
#endif