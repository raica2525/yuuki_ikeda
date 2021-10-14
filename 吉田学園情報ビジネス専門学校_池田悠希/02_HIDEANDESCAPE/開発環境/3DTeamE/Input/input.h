//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	input.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _INPUT_H_
#define _INPUT_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CInput
{
public:
    CInput();
    virtual ~CInput();

    virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);    //�������֐�
    virtual void Uninit(void);                               //�I���֐�
    virtual void Update(void) = 0;                           //�X�V����

protected:
    static LPDIRECTINPUT8 m_pInput;         // DirectInput�I�u�W�F�N�g
    LPDIRECTINPUTDEVICE8 m_pDeviceInput;    //�C���v�b�g�f�o�C�X�ւ̃|�C���^
};

#endif
