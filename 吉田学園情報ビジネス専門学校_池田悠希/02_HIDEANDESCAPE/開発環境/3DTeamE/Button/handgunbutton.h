//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	hundgunbutton.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _HANDGUNBUTTON_H_
#define _HANDGUNBUTTON_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "button.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CHandgunButton :public CButton
{
public:
	CHandgunButton();
	~CHandgunButton();

	HRESULT Init(void);	//初期化処理

	static CHandgunButton * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成処理

	static HRESULT Load(void);	//テクスチャ読込処理
	static void Unload(void);	//テクスチャ破棄処理
	
	void Push(void);	//押されたときの処理
	void Select(void);	//選ばれたときの処理
	void Unselect(void);//選ばれていないときの処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
};
#endif