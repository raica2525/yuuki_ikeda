//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	pause.h
//	Author:池田悠希
//
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

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CPause* Create(void);

private:
    CObject2D* m_pObject2d;
    CReturnTitleButton* m_pReturnTitleButton;
    CRetryButton* m_pRetryButton;
    CContinueButton* m_pContinueButton;
};
