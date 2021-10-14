//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	model.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _MODEL_H_
#define _MODEL_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "object3d.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define MAX_MATERIAL (30)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CModel : public CObject3D
{
public:
    typedef struct
    {
        LPD3DXBUFFER pBuffMat;                        // �}�e���A�����ւ̃|�C���^
        DWORD nNumMat;                                // �}�e���A�����̐�
        LPD3DXMESH pMesh;                             // ���b�V�����ւ̃|�C���^
        LPDIRECT3DTEXTURE9 pTexture[MAX_MATERIAL];    // �e�N�X�`���ւ̃|�C���^
        D3DXMATRIX mtxWorld;                          // �A�j���[�V�������
    } MODELDATA;

    CModel();
    virtual ~CModel();

    virtual void Draw(void);    //�`��֐�

    static CModel* Create(CModel* pParentModel, CObject* pParentObject, MODELDATA modeldata, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);    //�����֐�

    void SetAnimationRot(D3DXVECTOR3 rot);      //�A�j���[�V������]�ݒ�
    void SetAnimationPos(D3DXVECTOR3 pos);      //�A�j���[�V�����ړ��ݒ�
    void SetAnimationSize(D3DXVECTOR3 size);    //�A�j���[�V�����傫���ݒ�
    MODELDATA GetModelData(void);               //���f���f�[�^�擾
    void BindModel(MODELDATA modeldata);        //���f���f�[�^�ݒ�
    CObject* GetParentObject(void);             //�e�I�u�W�F�N�g�擾

private:
    CModel* m_pParentModel;      //�e���f��
    MODELDATA m_ModelData;       //���f���f�[�^
    D3DXVECTOR3 m_posAnime;      //�A�j���[�V�����ړ�
    D3DXVECTOR3 m_rotAnime;      //�A�j���[�V������]
    D3DXVECTOR3 m_sizeAnime;     //�A�j���[�V�����傫��
    CObject* m_pParentObject;    //�e�I�u�W�F�N�g
};
#endif
