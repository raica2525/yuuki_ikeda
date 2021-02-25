//=============================================================================
//
// ライン生成 [line.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _LINE_H_
#define _LINE_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLine :public CObject
{
public:
	CLine();
	~CLine();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetStartPosition(D3DXVECTOR3 pos);
	void SetEndPosition(D3DXVECTOR3 pos);

	void SetRotation(D3DXVECTOR3 rot);
	void SetCol(D3DCOLOR col);
	D3DXMATRIX GetWorld(void) { return m_StartWorld; };
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	static CModel::MODELDATA m_modeldata;
	static D3DXMATERIAL *m_pMat;
	D3DXMATRIX m_mtxWorld; //行列計算用
	D3DXMATRIX m_StartWorld; //行列計算用

	D3DXVECTOR3 m_Startpos;
	D3DXVECTOR3 m_Endpos;

	D3DXVECTOR3 m_rot;
	D3DCOLOR m_col;

};
#endif