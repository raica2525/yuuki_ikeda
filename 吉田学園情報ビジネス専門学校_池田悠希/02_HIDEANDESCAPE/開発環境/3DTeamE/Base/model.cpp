//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	model.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "model.h"

#include "inputkeyboard.h"
#include "inputmouse.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CModel::CModel()
{
    //各種変数初期化
    ZeroMemory(&m_ModelData, sizeof(m_ModelData));
    m_rotAnime      = ZEROVECTOR3;
    m_posAnime      = ZEROVECTOR3;
    m_pParentModel  = NULL;
    m_pParentObject = NULL;

    SetObjType(OBJTYPE_MODEL);    //オブジェクトタイプ更新
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CModel::~CModel()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CModel::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans, mtxScale;
    D3DXMATRIX mtxParent;
    D3DMATERIAL9 matDef;
    D3DXMATERIAL* pMat;
    //ワールド変換行列の初期化
    D3DXMatrixIdentity(&m_ModelData.mtxWorld);

	D3DXVECTOR3 size = GetSize();

    //拡大縮小行列の生成と計算
    D3DXMatrixScaling(&mtxScale, size.x, size.y, size.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

	D3DXVECTOR3 rot = GetRot();

    //回転行列の生成と計算
    D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotAnime.y, m_rotAnime.x, m_rotAnime.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

	D3DXVECTOR3 pos = GetPos();

    //平行移動行列の生成と計算
    D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);
    D3DXMatrixTranslation(&mtxTrans, m_posAnime.x, m_posAnime.y, m_posAnime.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);

    //親モデルがあれば親モデルの変換行列を掛ける
    if(m_pParentModel != NULL)
    {
        mtxParent = m_pParentModel->m_ModelData.mtxWorld;
        D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxParent);
    }

    //計算結果を適用
    pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);

    //マテリアル情報の取得
    pDevice->GetMaterial(&matDef);
    if(m_ModelData.pBuffMat != NULL)
    {
        pMat = (D3DXMATERIAL*)m_ModelData.pBuffMat->GetBufferPointer();
    }

    //マテリアル情報の設定とマテリアルごとに描画
    for(int nCntMat = 0; nCntMat < (int)m_ModelData.nNumMat; nCntMat++)
    {
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
        pDevice->SetTexture(0, m_ModelData.pTexture[nCntMat]);
        m_ModelData.pMesh->DrawSubset(nCntMat);
    }
    //マテリアル情報のリセット
    pDevice->SetMaterial(&matDef);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//生成関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CModel* CModel::Create(CModel* const pParentModel, CObject* const pParentObject, const MODELDATA modeldata, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
    // メモリの確保
    CModel* pModel = new CModel;
    //各種情報の設定
    pModel->SetPos(pos);
    pModel->SetRot(rot);
    pModel->SetSize(size);
    pModel->m_pParentModel  = pParentModel;
    pModel->m_ModelData     = modeldata;
    pModel->m_pParentObject = pParentObject;
    // 初期化処理
    pModel->Init();

    return pModel;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CModel::MODELDATA CModel::GetModelData(void)
{
    return m_ModelData;
}

CObject* CModel::GetParentObject(void)
{
    return m_pParentObject;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CModel::SetAnimationRot(const D3DXVECTOR3 rot)
{
    m_rotAnime = rot;
}

void CModel::BindModel(const MODELDATA modeldata)
{
    m_ModelData = modeldata;
}

void CModel::SetAnimationPos(const D3DXVECTOR3 pos)
{
    m_posAnime = pos;
}

void CModel::SetAnimationSize(const D3DXVECTOR3 size)
{
    m_sizeAnime = size;
}
