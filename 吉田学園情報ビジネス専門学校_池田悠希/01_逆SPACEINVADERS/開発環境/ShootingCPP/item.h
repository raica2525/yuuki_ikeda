//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	item.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _ITEM_H_
#define _ITEM_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene2d.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CItem : public CScene2d
{
public:
    CItem();     //�R���X�g���N�^
    ~CItem();    //�f�X�g���N�^
    typedef enum
    {
        TYPE_LIFE = 0,
        TYPE_MAX
    } TYPE;

    HRESULT Init(void);    //����������
    void Uninit(void);     //�I������
    void Update(void);     //�X�V����
    void Draw(void);       //�`�揈��

    static HRESULT Load(void);
    static void Unload(void);

    static void Create(D3DXVECTOR3 pos, TYPE type);    //�|���S������
private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];    // �e�N�X�`���ւ̃|�C���^
    TYPE m_type;
};

#endif
