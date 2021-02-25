//=============================================================================
//
// マズルフラッシュ [muzzleflash.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _MUZZLEFLASH_H_
#define _MUZZLEFLASH_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
#include "billboard.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MUZZLEFLASH_TEXTURE 	"Data/Texture/explosion.png"	//爆発テクスチャの保存先
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMuzzleflash :public CBillboard
{
public:
	CMuzzleflash();
	~CMuzzleflash();
	static HRESULT Load(void);
	static void Unload(void);
	static CMuzzleflash * Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size,D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;
};
#endif