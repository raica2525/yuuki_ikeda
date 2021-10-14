//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	gameoveroverlay.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "object.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CObject2D;
class CReturnTitleButton;
class CRetryButton;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

class CGameoverOverlay : public CObject
{
public:
    CGameoverOverlay();
    ~CGameoverOverlay();

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理

    static CGameoverOverlay* Create(void);    //生成処理

private:
    int m_nBackgroundAlpha;    //背景のアルファ値
    CObject2D* m_pObject2d;    //背景のポインタ

    //ボタンのポインタ
    CReturnTitleButton* m_pReturnTitleButton;
    CRetryButton* m_pRetryButton;
};
