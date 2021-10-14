//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	continuebutton.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _CONTINUEBUTTON_H_
#define _CONTINUEBUTTON_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "button.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CContinueButton : public CButton
{
public:
    CContinueButton();
    ~CContinueButton();

	HRESULT Init(void);//初期化処理

	static CContinueButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//生成関数

    static HRESULT Load(void);//テクスチャ読み込み
    static void Unload(void);//テクスチャ破棄
    
    void Push(void);	//押されたときの処理
    void Select(void);	//選ばれたときの処理
    void Unselect(void);//選ばれていないときの処理

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
};
#endif
