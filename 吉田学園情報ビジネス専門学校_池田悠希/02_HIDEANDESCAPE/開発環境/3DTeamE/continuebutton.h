//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	continuebutton.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _CONTINUEBUTTON_H_
#define _CONTINUEBUTTON_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "button.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CContinueButton : public CButton
{
public:
    CContinueButton();
    ~CContinueButton();
    static HRESULT Load(void);
    static void Unload(void);
    static CContinueButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    void Push(void);
    void Select(void);
    void Unselect(void);

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
};
#endif
