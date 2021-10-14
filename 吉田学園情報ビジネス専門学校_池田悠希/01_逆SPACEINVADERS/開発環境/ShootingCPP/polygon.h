//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	polygon.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _POLYGON_H_
#define _POLYGON_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CPolygon
{
public:
    CPolygon();             //�R���X�g���N�^
    virtual ~CPolygon();    //�f�X�g���N�^

    virtual HRESULT Init(void);    //����������
    virtual void Uninit(void);     //�I������
    virtual void Update(void);     //�X�V����
    virtual void Draw(void);       //�`�揈��

    void SetPos(D3DXVECTOR3 pos);    //�ʒu�ݒ菈��
    D3DXVECTOR3 GetPos(void);

    void SetCol(D3DXCOLOR col);

    void SetSize(D3DXVECTOR3 size);
    void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
    void SetTexPos(D3DXVECTOR2* pTexPos);
    D3DXVECTOR3 GetVtxPos(int nIndex);
    void SetRot(float fRot);
    void SetObjType(CScene::OBJTYPE objtype);
    static CPolygon* Create(D3DXVECTOR3 pos,
                            D3DXVECTOR3 size,
                            float fRot,
                            CScene::OBJTYPE objtype);    //�|���S����������

private:
    LPDIRECT3DTEXTURE9 m_pTexture;    // �e�N�X�`���ւ̃|�C���^
    D3DXVECTOR3 m_pos;                // �|���S���̈ʒu
    D3DXVECTOR3 m_size;
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;    // ���_�o�b�t�@�ւ̃|�C���^
    D3DXCOLOR m_col;
    float m_fRot;
    CScene::OBJTYPE m_objtype;
    D3DXVECTOR3 m_vtxPos[NUM_VERTEX];
};

#endif
