//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	polygon3d
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "object3d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CPolygon3D : public CObject3D
{
public:
    CPolygon3D();
    ~CPolygon3D();

    HRESULT Init(void);    //初期化処理
    void Uninit(void);     //終了処理
    void Update(void);     //更新処理
    void Draw(void);       //描画処理

    static CPolygon3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);    //生成処理

    void BindTexture(LPDIRECT3DTEXTURE9 pTexture);    //テクスチャ割当

private:
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;    // 頂点バッファへのポインタ
    LPDIRECT3DTEXTURE9 m_pTexture;         //テクスチャへのポインタ
};
#endif
