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
    virtual HRESULT Init(void);
    virtual void Uninit(void);
    virtual void Update(void);
    virtual void Draw(void);
    static CModel* Create(CModel* pParentModel, CObject* pParentObject, MODELDATA modeldata, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
    void SetAnimationRot(D3DXVECTOR3 rot)
    {
        m_rotAnime = rot;
    }
    void SetAnimationPos(D3DXVECTOR3 pos)
    {
        m_posAnime = pos;
    }
    void SetAnimationSize(D3DXVECTOR3 size)
    {
        m_sizeAnime = size;
    }
    MODELDATA GetModelData(void);
    void BindModel(MODELDATA modeldata);
    CObject* GetParentObject(void);

private:
    CModel* m_pParentModel;
    MODELDATA m_ModelData;
    D3DXVECTOR3 m_posAnime;
    D3DXVECTOR3 m_rotAnime;
    D3DXVECTOR3 m_sizeAnime;
    CObject* m_pParentObject;
};
#endif
