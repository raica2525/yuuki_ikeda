//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	polygon.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _POLYGON_H_
#define _POLYGON_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "scene.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CPolygon
{
public:
    CPolygon();             //コンストラクタ
    virtual ~CPolygon();    //デストラクタ

    virtual HRESULT Init(void);    //初期化処理
    virtual void Uninit(void);     //終了処理
    virtual void Update(void);     //更新処理
    virtual void Draw(void);       //描画処理

    void SetPos(D3DXVECTOR3 pos);    //位置設定処理
    D3DXVECTOR3 GetPos(void);

    void SetCol(D3DXCOLOR col);

    void SetSize(D3DXVECTOR3 size);
    void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
    void SetTexPos(D3DXVECTOR2* pTexPos);
    D3DXVECTOR3 GetVtxPos(int nIndex);
    void SetRot(float fRot);
    void SetObjType(CScene::OBJTYPE objtype);
    static CPolygon* Create(D3DXVECTOR3 pos,
                            D3DXVECTOR3 size,
                            float fRot,
                            CScene::OBJTYPE objtype);    //ポリゴン生成処理

private:
    LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
    D3DXVECTOR3 m_pos;                // ポリゴンの位置
    D3DXVECTOR3 m_size;
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;    // 頂点バッファへのポインタ
    D3DXCOLOR m_col;
    float m_fRot;
    CScene::OBJTYPE m_objtype;
    D3DXVECTOR3 m_vtxPos[NUM_VERTEX];
};

#endif
