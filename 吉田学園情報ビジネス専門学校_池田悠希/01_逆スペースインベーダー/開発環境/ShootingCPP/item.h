//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	item.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _ITEM_H_
#define _ITEM_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene2d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CItem : public CScene2d
{
public:
    CItem();     //コンストラクタ
    ~CItem();    //デストラクタ
    typedef enum
    {
        TYPE_LIFE = 0,
        TYPE_MAX
    } TYPE;

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理

    static HRESULT Load(void);
    static void Unload(void);

    static void Create(D3DXVECTOR3 pos, TYPE type);    //ポリゴン生成
private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];    // テクスチャへのポインタ
    TYPE m_type;
};

#endif
