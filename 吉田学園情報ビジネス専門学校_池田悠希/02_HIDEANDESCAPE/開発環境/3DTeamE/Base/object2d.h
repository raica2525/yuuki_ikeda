//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	object2d.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "object.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CObject2D : public CObject
{
public:
    CObject2D(int nPriority = 0);    //コンストラクタ
    virtual ~CObject2D();            //デストラクタ

    virtual HRESULT Init(void);    //初期化処理
    virtual void Uninit(void);     //終了処理
    virtual void Update(void);     //更新処理
    virtual void Draw(void);       //描画処理

    static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority);    //生成処理

    //セッター関数
    void SetPos(D3DXVECTOR3 pos);
    void SetMove(D3DXVECTOR3 move);
    void SetRot(float rot);
    void SetSize(D3DXVECTOR3 size);
    void SetTexPos(D3DXVECTOR2* pTexPos);
    void SetCol(D3DCOLOR col);
    void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

    //ゲッター関数
    D3DXVECTOR3 GetPos(void);
    D3DXVECTOR3 GetMove(void);
    D3DXVECTOR3 GetSize(void);

private:
    LPDIRECT3DTEXTURE9 m_pTexture;         // テクスチャへのポインタ
    D3DXVECTOR3 m_pos;                     // ポリゴンの位置
    D3DXVECTOR3 m_move;                    //ポリゴンの移動量
    D3DXVECTOR3 m_size;                    //ポリゴンサイズ
    D3DCOLOR m_col;                        //ポリゴンカラー
    float m_fRot;                          //ポリゴンの向き
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;    // 頂点バッファへのポインタ
};

#endif
