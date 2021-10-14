//=============================================================================
//
// 爆発 [explosion.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
#include "billboard.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EXPLOSION_TEXTURE 	"Data/Texture/explosion.png"	//爆発テクスチャの保存先
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CExplosion :public CBillboard
{
public:
	CExplosion();
	~CExplosion();
	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
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
	int m_nCounterAnim;				//アニメカウンタ
	int m_nPatternAnim;				//アニメパターン
};
#endif