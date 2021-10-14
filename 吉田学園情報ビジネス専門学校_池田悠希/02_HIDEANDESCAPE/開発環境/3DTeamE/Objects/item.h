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
//クラス宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CItem : public CModel
{
public:
    CItem();
    ~CItem();

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理

    static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);    //生成処理

    static void Load(void);      //ファイルデータ読み込み
    static void Unload(void);    //ファイルデータ破棄

private:
    static MODELDATA m_modelData;    //モデルデータ
    float m_fFrameCounter;           //フレームカウント
};
