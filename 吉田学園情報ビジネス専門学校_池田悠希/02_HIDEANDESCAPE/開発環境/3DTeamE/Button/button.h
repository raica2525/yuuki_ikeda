//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	button.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _BUTTON_H_
#define _BUTTON_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "object2d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CButton : public CObject2D
{
public:
    CButton(int nPriority = 0);	
    virtual ~CButton();

    HRESULT Init(void);	//初期化処理
    void Uninit(void);	//終了処理
    void Update(void);	//更新処理
    void Draw(void);	//描画処理

    virtual void Push(void)     = 0;	//押されたときの処理
    virtual void Select(void)   = 0;	//選択されたときの処理
    virtual void Unselect(void) = 0;	//選択されていないときの処理

private:
	bool m_bSelect;	//選択されているかどうか
};
#endif
