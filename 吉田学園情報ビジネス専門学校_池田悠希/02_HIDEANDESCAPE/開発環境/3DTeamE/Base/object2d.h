//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	object2d.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "object.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CObject2D : public CObject
{
public:
    CObject2D(int nPriority = 0);    //�R���X�g���N�^
    virtual ~CObject2D();            //�f�X�g���N�^

    virtual HRESULT Init(void);    //����������
    virtual void Uninit(void);     //�I������
    virtual void Update(void);     //�X�V����
    virtual void Draw(void);       //�`�揈��

    static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority);    //��������

    //�Z�b�^�[�֐�
    void SetPos(D3DXVECTOR3 pos);
    void SetMove(D3DXVECTOR3 move);
    void SetRot(float rot);
    void SetSize(D3DXVECTOR3 size);
    void SetTexPos(D3DXVECTOR2* pTexPos);
    void SetCol(D3DCOLOR col);
    void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

    //�Q�b�^�[�֐�
    D3DXVECTOR3 GetPos(void);
    D3DXVECTOR3 GetMove(void);
    D3DXVECTOR3 GetSize(void);

private:
    LPDIRECT3DTEXTURE9 m_pTexture;         // �e�N�X�`���ւ̃|�C���^
    D3DXVECTOR3 m_pos;                     // �|���S���̈ʒu
    D3DXVECTOR3 m_move;                    //�|���S���̈ړ���
    D3DXVECTOR3 m_size;                    //�|���S���T�C�Y
    D3DCOLOR m_col;                        //�|���S���J���[
    float m_fRot;                          //�|���S���̌���
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;    // ���_�o�b�t�@�ւ̃|�C���^
};

#endif
