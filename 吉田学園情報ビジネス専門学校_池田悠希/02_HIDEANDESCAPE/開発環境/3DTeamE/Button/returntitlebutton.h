//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	returntitlebutton.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _RETURNTITLEBUTTON_H_
#define _RETURNTITLEBUTTON_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "button.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CReturnTitleButton : public CButton
{
public:
    CReturnTitleButton();
    ~CReturnTitleButton();

	HRESULT Init(void);	//初期化処理

	static CReturnTitleButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成処理

	static HRESULT Load(void);	//テクスチャ読込処理
	static void Unload(void);	//テクスチャ破棄処理

	void Push(void);	//押されたときの処理
	void Select(void);	//選ばれたときの処理
	void Unselect(void);//選ばれていないときの処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
};
#endif
