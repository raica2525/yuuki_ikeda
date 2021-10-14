//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	continuebutton.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _CONTINUEBUTTON_H_
#define _CONTINUEBUTTON_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "button.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CContinueButton : public CButton
{
public:
    CContinueButton();
    ~CContinueButton();

	HRESULT Init(void);//����������

	static CContinueButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);//�����֐�

    static HRESULT Load(void);//�e�N�X�`���ǂݍ���
    static void Unload(void);//�e�N�X�`���j��
    
    void Push(void);	//�����ꂽ�Ƃ��̏���
    void Select(void);	//�I�΂ꂽ�Ƃ��̏���
    void Unselect(void);//�I�΂�Ă��Ȃ��Ƃ��̏���

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // �e�N�X�`���ւ̃|�C���^
};
#endif
