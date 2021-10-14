//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	model.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "model.h"

#include "inputkeyboard.h"
#include "inputmouse.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CModel::CModel()
{
    //�e��ϐ�������
    ZeroMemory(&m_ModelData, sizeof(m_ModelData));
    m_rotAnime      = ZEROVECTOR3;
    m_posAnime      = ZEROVECTOR3;
    m_pParentModel  = NULL;
    m_pParentObject = NULL;

    SetObjType(OBJTYPE_MODEL);    //�I�u�W�F�N�g�^�C�v�X�V
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CModel::~CModel()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CModel::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans, mtxScale;
    D3DXMATRIX mtxParent;
    D3DMATERIAL9 matDef;
    D3DXMATERIAL* pMat;
    //���[���h�ϊ��s��̏�����
    D3DXMatrixIdentity(&m_ModelData.mtxWorld);

	D3DXVECTOR3 size = GetSize();

    //�g��k���s��̐����ƌv�Z
    D3DXMatrixScaling(&mtxScale, size.x, size.y, size.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxScale);

	D3DXVECTOR3 rot = GetRot();

    //��]�s��̐����ƌv�Z
    D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotAnime.y, m_rotAnime.x, m_rotAnime.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxRot);

	D3DXVECTOR3 pos = GetPos();

    //���s�ړ��s��̐����ƌv�Z
    D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);
    D3DXMatrixTranslation(&mtxTrans, m_posAnime.x, m_posAnime.y, m_posAnime.z);
    D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxTrans);

    //�e���f��������ΐe���f���̕ϊ��s����|����
    if(m_pParentModel != NULL)
    {
        mtxParent = m_pParentModel->m_ModelData.mtxWorld;
        D3DXMatrixMultiply(&m_ModelData.mtxWorld, &m_ModelData.mtxWorld, &mtxParent);
    }

    //�v�Z���ʂ�K�p
    pDevice->SetTransform(D3DTS_WORLD, &m_ModelData.mtxWorld);

    //�}�e���A�����̎擾
    pDevice->GetMaterial(&matDef);
    if(m_ModelData.pBuffMat != NULL)
    {
        pMat = (D3DXMATERIAL*)m_ModelData.pBuffMat->GetBufferPointer();
    }

    //�}�e���A�����̐ݒ�ƃ}�e���A�����Ƃɕ`��
    for(int nCntMat = 0; nCntMat < (int)m_ModelData.nNumMat; nCntMat++)
    {
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
        pDevice->SetTexture(0, m_ModelData.pTexture[nCntMat]);
        m_ModelData.pMesh->DrawSubset(nCntMat);
    }
    //�}�e���A�����̃��Z�b�g
    pDevice->SetMaterial(&matDef);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�����֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CModel* CModel::Create(CModel* const pParentModel, CObject* const pParentObject, const MODELDATA modeldata, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
    // �������̊m��
    CModel* pModel = new CModel;
    //�e����̐ݒ�
    pModel->SetPos(pos);
    pModel->SetRot(rot);
    pModel->SetSize(size);
    pModel->m_pParentModel  = pParentModel;
    pModel->m_ModelData     = modeldata;
    pModel->m_pParentObject = pParentObject;
    // ����������
    pModel->Init();

    return pModel;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CModel::MODELDATA CModel::GetModelData(void)
{
    return m_ModelData;
}

CObject* CModel::GetParentObject(void)
{
    return m_pParentObject;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
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
