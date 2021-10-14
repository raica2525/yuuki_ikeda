//=============================================================================
//
// アイテムUI処理 [item_ui.h]
// Author : 若山　言稀
//
//=============================================================================
#ifndef _ITEM_UI_H_
#define _ITEM_UI_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "model.h"
#include "object2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ITEM_UI_TEXTURE 	"Data/Texture/HealItem.png"	//読み込む用のアイテムテクスチャ
#define TEXTURE_MAX 1
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CItem_ui :public CObject2D
{
public:
	CItem_ui();
	~CItem_ui();
	static HRESULT Load(void);
	static void Unload(void);
	static CItem_ui * Create(D3DXVECTOR3 pos);//(D3DXVECTOR3 pos, float frot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	static char *m_cFileName;			//ファイルの名前

	D3DXVECTOR3 m_pos;
	float m_frot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;

};
#endif