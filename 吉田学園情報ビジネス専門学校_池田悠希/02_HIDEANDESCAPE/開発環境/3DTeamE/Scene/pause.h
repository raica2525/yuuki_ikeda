//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	pause.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CObject2D;
class CReturnTitleButton;
class CRetryButton;
class CContinueButton;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CPause
{
public:
    CPause();
    ~CPause();

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理

    static CPause* Create(void);    //生成関数

private:
    CObject2D* m_pObject2d;    //背景ポインタ

    //ボタンポインタ
    CReturnTitleButton* m_pReturnTitleButton;
    CRetryButton* m_pRetryButton;
    CContinueButton* m_pContinueButton;
};
