//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	button.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _BUTTON_H_
#define _BUTTON_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "object2d.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CButton : public CObject2D
{
public:
    CButton(int nPriority = 0);	
    virtual ~CButton();

    HRESULT Init(void);	//����������
    void Uninit(void);	//�I������
    void Update(void);	//�X�V����
    void Draw(void);	//�`�揈��

    virtual void Push(void)     = 0;	//�����ꂽ�Ƃ��̏���
    virtual void Select(void)   = 0;	//�I�����ꂽ�Ƃ��̏���
    virtual void Unselect(void) = 0;	//�I������Ă��Ȃ��Ƃ��̏���

private:
	bool m_bSelect;	//�I������Ă��邩�ǂ���
};
#endif
