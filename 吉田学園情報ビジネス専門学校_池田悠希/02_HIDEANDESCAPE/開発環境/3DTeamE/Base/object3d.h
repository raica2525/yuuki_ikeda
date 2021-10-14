//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	object3d.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "object.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CObject3D : public CObject
{
public:
    CObject3D();
    virtual ~CObject3D();

    virtual HRESULT Init(void);    //����������
    virtual void Uninit(void);     //�I������
    virtual void Update(void);     //�X�V����
    virtual void Draw(void);       //�`�揈��

    //�Z�b�^�[�֐�
    void SetPos(D3DXVECTOR3 pos);
    void SetRot(D3DXVECTOR3 rot);
    void SetSize(D3DXVECTOR3 size);

    //�Q�b�^�[�֐�
    D3DXVECTOR3 GetPos(void);
    D3DXVECTOR3 GetRot(void);
    D3DXVECTOR3 GetSize(void);

private:
    D3DXVECTOR3 m_pos;     // �ʒu
    D3DXVECTOR3 m_rot;     // ��]���
    D3DXVECTOR3 m_size;    // �T�C�Y
};

#endif
