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
    //モデルデータの初期化
    ZeroMemory(&m_ModelData, sizeof(m_ModelData));
    m_rotAnime      = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_posAnime      = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_pParentModel  = NULL;
    m_pParentObject = NULL;
    SetObjType(OBJTYPE_MODEL);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CModel::~CModel()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CModel::Init(void)
{
    CObject3D::Init();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CModel::Uninit(void)
{
    CObject3D::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CModel::Update(void)
{
    CObject3D::Update();
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

    //拡大縮小行列の生成と計算
    D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

    //回転行列の生成と計算
    D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRotation().y, GetRotation().x, GetRotation().z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotAnime.y, m_rotAnime.x, m_rotAnime.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

    //平行移動行列の生成と計算
    D3DXMatrixTranslation(&mtxTrans, GetPosition().x, GetPosition().y, GetPosition().z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);
    D3DXMatrixTranslation(&mtxTrans, m_posAnime.x, m_posAnime.y, m_posAnime.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);

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

//=============================================================================
// 3Dオブジェクトの生成
//=============================================================================
CModel* CModel::Create(CModel* pParentModel, CObject* pParentObject, MODELDATA modeldata, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
    // メモリの確保
    CModel* pModel;
    pModel = new CModel;
    //各種情報の設定
    pModel->SetPosition(pos);
    pModel->SetRotation(rot);
    pModel->SetScale(size);
    pModel->m_pParentModel  = pParentModel;
    pModel->m_ModelData     = modeldata;
    pModel->m_pParentObject = pParentObject;
    // 初期化処理
    pModel->Init();

    return pModel;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//モデルの割当
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CModel::BindModel(MODELDATA modeldata)
{
    m_ModelData = modeldata;
}

CModel::MODELDATA CModel::GetModelData(void)
{
    return m_ModelData;
}

CObject* CModel::GetParentObject(void)
{
    return m_pParentObject;
}
