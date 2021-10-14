//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
// number.h
// Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _NUMBER_H_
#define _NUMBER_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CNumber
{
public:
    CNumber();
    ~CNumber();

    HRESULT Init(void);    //初期化関数
    void Update(void);     //更新関数
    void Draw(void);       //描画関数
    void Uninit(void);     //終了関数

    static HRESULT Load(void);    //テクスチャ読み込み
    static void Unload(void);     //テクスチャ破棄

    static CNumber* Create(int nValue, D3DXVECTOR3 pos, D3DXVECTOR3 size);    //生成関数

    //セッター関数
    void SetValue(int nValue);
    void SetPos(D3DXVECTOR3 pos);
    void SetSize(D3DXVECTOR3 size);

private:
    int m_nValue;                            //表示する数字
    static LPDIRECT3DTEXTURE9 m_pTexture;    //テクスチャのポインタ
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;      // 頂点バッファへのポインタ
    D3DXVECTOR3 m_pos;                       //座標
    D3DXVECTOR3 m_size;                      //大きさ
};

#endif
