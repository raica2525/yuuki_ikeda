//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	camera.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CCamera
{
public:
    CCamera();
    ~CCamera();

    HRESULT Init(void);      //����������
    void Uninit(void);       //�I������
    void Update(void);       //�X�V����
    void SetCamera(void);    //�J�����ݒ�

    D3DXVECTOR3 GetRot(void);     //��]�擾
    D3DXVECTOR3 GetPosR(void);    //�����_�擾

    void SetRot(D3DXVECTOR3 rot);    //��]�ݒ�

private:
    D3DXVECTOR3 m_posV;                 //�J�����̍��W
    D3DXVECTOR3 m_posR;                 //�����_�̍��W
    D3DXVECTOR3 m_vecU;                 //�J�����̏����
    D3DXMATRIX m_mtxProjection;         //�v���W�F�N�V�����}�g���b�N�X
    D3DXMATRIX m_mtxView;               //�r���[�}�g���b�N�X
    float m_fDistance;                  //���_-���ӓ_�̋���
    float m_fDistanceFromPlayer;        //�v���C���[����̋���
    float m_fDistanceFromPlayerDest;    //�v���C���[����̋����̖ڕW�l
    D3DXVECTOR3 m_rot;                  //��]�p
};

#endif
