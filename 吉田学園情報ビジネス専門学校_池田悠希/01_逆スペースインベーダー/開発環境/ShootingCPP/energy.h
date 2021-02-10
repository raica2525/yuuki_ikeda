//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	energy.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _ENERGY_H_
#define _ENERGY_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene.h"

class CPolygon;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CEnergy : public CScene
{
public:
    CEnergy();     //コンストラクタ
    ~CEnergy();    //デストラクタ

    typedef enum
    {
        MODE_NORMAL = 0,
        MODE_OVERHEAT,
        MODE_MAX
    } MODE;
    static CEnergy* Create();    //ポリゴン生成処理

    HRESULT Init();       //初期化処理
    void Uninit(void);    //終了処理
    void Update(void);    //更新処理
    void Draw(void);      //描画処理
    int GetEnergy(void);
    void ReduceEnergy(int nValue);
    static HRESULT Load(void);
    static void Unload(void);

private:
    CPolygon* m_apPolygon[NUM_GAUGE_LAYER];
    int m_nEnergy;
    MODE m_mode;
    static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif
