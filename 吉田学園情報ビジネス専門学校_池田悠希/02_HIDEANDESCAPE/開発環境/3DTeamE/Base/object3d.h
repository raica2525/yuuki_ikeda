//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	object3d.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "object.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CObject3D : public CObject
{
public:
    CObject3D();
    virtual ~CObject3D();

    virtual HRESULT Init(void);    //初期化処理
    virtual void Uninit(void);     //終了処理
    virtual void Update(void);     //更新処理
    virtual void Draw(void);       //描画処理

    //セッター関数
    void SetPos(D3DXVECTOR3 pos);
    void SetRot(D3DXVECTOR3 rot);
    void SetSize(D3DXVECTOR3 size);

    //ゲッター関数
    D3DXVECTOR3 GetPos(void);
    D3DXVECTOR3 GetRot(void);
    D3DXVECTOR3 GetSize(void);

private:
    D3DXVECTOR3 m_pos;     // 位置
    D3DXVECTOR3 m_rot;     // 回転情報
    D3DXVECTOR3 m_size;    // サイズ
};

#endif
