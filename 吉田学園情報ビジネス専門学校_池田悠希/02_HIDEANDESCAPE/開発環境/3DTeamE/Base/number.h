//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
// number.h
// Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _NUMBER_H_
#define _NUMBER_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CNumber
{
public:
    CNumber();
    ~CNumber();

    HRESULT Init(void);    //�������֐�
    void Update(void);     //�X�V�֐�
    void Draw(void);       //�`��֐�
    void Uninit(void);     //�I���֐�

    static HRESULT Load(void);    //�e�N�X�`���ǂݍ���
    static void Unload(void);     //�e�N�X�`���j��

    static CNumber* Create(int nValue, D3DXVECTOR3 pos, D3DXVECTOR3 size);    //�����֐�

    //�Z�b�^�[�֐�
    void SetValue(int nValue);
    void SetPos(D3DXVECTOR3 pos);
    void SetSize(D3DXVECTOR3 size);

private:
    int m_nValue;                            //�\�����鐔��
    static LPDIRECT3DTEXTURE9 m_pTexture;    //�e�N�X�`���̃|�C���^
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;      // ���_�o�b�t�@�ւ̃|�C���^
    D3DXVECTOR3 m_pos;                       //���W
    D3DXVECTOR3 m_size;                      //�傫��
};

#endif
