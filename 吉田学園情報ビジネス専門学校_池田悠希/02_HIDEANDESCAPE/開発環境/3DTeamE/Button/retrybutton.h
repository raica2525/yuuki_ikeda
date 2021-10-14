//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	retrybutton.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _RETRYBUTTON_H_
#define _RETRYBUTTON_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "button.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CRetryButton : public CButton
{
public:
    CRetryButton();
    ~CRetryButton();

	HRESULT Init(void);	//����������

	static CRetryButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//��������

	static HRESULT Load(void);	//�e�N�X�`���Ǎ�����
	static void Unload(void);	//�e�N�X�`���j������

	void Push(void);	//�����ꂽ�Ƃ��̏���
	void Select(void);	//�I�΂ꂽ�Ƃ��̏���
	void Unselect(void);//�I�΂�Ă��Ȃ��Ƃ��̏���

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
};
#endif
