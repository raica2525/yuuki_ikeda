//=============================================================================
//
// ダメージUi処理 [damage_ui.h]
// Author : 若山　言稀
//
//=============================================================================
#ifndef _DAMAGE_UI_H_
#define _DAMAGE_UI_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
#include "object2d.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DAMAGE_UI_TEXTURE 	"Data/Texture/Blood.png"	//読み込む用のダメージテクスチャ
#define TEXTURE_MAX 1
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CDamage_ui :public CObject2D
{
public:
	CDamage_ui();
	~CDamage_ui();
	static HRESULT Load(void);
	static void Unload(void);
	static CDamage_ui * Create(void);//(D3DXVECTOR3 pos, float frot, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetDamageUi(int nlife);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	static char *m_cFileName;			//ファイルの名前

	D3DXVECTOR3 m_pos;
	float m_frot;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;


};
#endif