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

    static CGameoverOverlay* Create(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:
    int m_nBackgroundAlpha;
    CObject2D* m_pObject2d;
    CReturnTitleButton* m_pReturnTitleButton;
    CRetryButton* m_pRetryButton;
};
