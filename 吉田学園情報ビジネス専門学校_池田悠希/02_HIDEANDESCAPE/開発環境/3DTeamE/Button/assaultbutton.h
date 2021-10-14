//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	assultbutton.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _ASSAULTBUTTON_H_
#define _ASSAULTBUTTON_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "button.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CAssaultButton : public CButton
{
public:
    CAssaultButton();
    ~CAssaultButton();

	HRESULT Init(void);	//����������

	static CAssaultButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//��������

    static HRESULT Load(void);	//�e�N�X�`���ǂݍ���
    static void Unload(void);	//�e�N�X�`���j��

    void Push(void);	//�������Ƃ��̏���
    void Select(void);//�I�΂ꂽ�Ƃ��̏���
    void Unselect(void);	//�I������Ă��Ȃ��Ƃ��̏���

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // �e�N�X�`���ւ̃|�C���^
};
#endif
