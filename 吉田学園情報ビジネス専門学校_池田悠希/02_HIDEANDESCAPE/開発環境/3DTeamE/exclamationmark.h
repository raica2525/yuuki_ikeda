//=============================================================================
//
// !マーク [exclamationmark.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _EXCLAMATIONMARK_H_
#define _EXCLAMATIONMARK_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
#include "billboard.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EXCLAMATIONMARK_TEXTURE 	"Data/Texture/bikkuri.png"	//爆発テクスチャの保存先
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CExclamationMark :public CBillboard
{
public:
	CExclamationMark();
	~CExclamationMark();
	static HRESULT Load(void);
	static void Unload(void);
	static CExclamationMark * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;
};
#endif