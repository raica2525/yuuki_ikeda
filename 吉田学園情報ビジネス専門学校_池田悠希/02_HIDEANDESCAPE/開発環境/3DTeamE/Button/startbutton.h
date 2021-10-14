//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	startbutton.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _STARTBUTTON_H_
#define _STARTBUTTON_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "button.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CStartButton :public CButton
{
public:
	CStartButton();
	~CStartButton();

	HRESULT Init(void);	//����������

	static CStartButton* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//��������

	static HRESULT Load(void);	//�e�N�X�`���Ǎ�����
	static void Unload(void);	//�e�N�X�`���j������

	void Push(void);	//�����ꂽ�Ƃ��̏���
	void Select(void);	//�I�΂ꂽ�Ƃ��̏���
	void Unselect(void);//�I�΂�Ă��Ȃ��Ƃ��̏���

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_DefaultSize;					//�f�t�H���g�̑傫��
};
#endif