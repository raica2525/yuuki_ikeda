//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	model.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _MODEL_H_
#define _MODEL_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "object3d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define MAX_MATERIAL (30)

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CModel : public CObject3D
{
public:
    typedef struct
    {
        LPD3DXBUFFER pBuffMat;                        // マテリアル情報へのポインタ
        DWORD nNumMat;                                // マテリアル情報の数
        LPD3DXMESH pMesh;                             // メッシュ情報へのポインタ
        LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // テクスチャへのポインタ
        D3DXMATRIX mtxWorld;                          // アニメーション情報
    } MODELDATA;

    CModel();
    virtual ~CModel();

    virtual void Draw(void);    //描画関数

    static CModel* Create(CModel* pParentModel, CObject* pParentObject, MODELDATA modeldata, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);    //生成関数

    void SetAnimationRot(D3DXVECTOR3 rot);      //アニメーション回転設定
    void SetAnimationPos(D3DXVECTOR3 pos);      //アニメーション移動設定
    void SetAnimationSize(D3DXVECTOR3 size);    //アニメーション大きさ設定
    MODELDATA GetModelData(void);               //モデルデータ取得
    void BindModel(MODELDATA modeldata);        //モデルデータ設定
    CObject* GetParentObject(void);             //親オブジェクト取得

private:
    CModel* m_pParentModel;      //親モデル
    MODELDATA m_ModelData;       //モデルデータ
    D3DXVECTOR3 m_posAnime;      //アニメーション移動
    D3DXVECTOR3 m_rotAnime;      //アニメーション回転
    D3DXVECTOR3 m_sizeAnime;     //アニメーション大きさ
    CObject* m_pParentObject;    //親オブジェクト
};
#endif
