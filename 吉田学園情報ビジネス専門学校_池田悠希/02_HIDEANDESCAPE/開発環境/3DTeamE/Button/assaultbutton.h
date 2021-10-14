//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	assultbutton.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _ASSAULTBUTTON_H_
#define _ASSAULTBUTTON_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "button.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CAssaultButton : public CButton
{
public:
    CAssaultButton();
    ~CAssaultButton();

	HRESULT Init(void);	//初期化処理

	static CAssaultButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成処理

    static HRESULT Load(void);	//テクスチャ読み込み
    static void Unload(void);	//テクスチャ破棄

    void Push(void);	//押したときの処理
    void Select(void);//選ばれたときの処理
    void Unselect(void);	//選択されていないときの処理

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
};
#endif
