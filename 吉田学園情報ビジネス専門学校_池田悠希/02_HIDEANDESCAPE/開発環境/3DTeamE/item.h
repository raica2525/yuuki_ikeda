//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	item.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "model.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define ITEM_OBTAIN_RANGE (20.0f)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CItem : public CModel
{
public:
    CItem();
    ~CItem();

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
    static void Load(void);
    static void Unload(void);

private:
    static MODELDATA m_modelData;
    float m_fFrameCounter;
};
