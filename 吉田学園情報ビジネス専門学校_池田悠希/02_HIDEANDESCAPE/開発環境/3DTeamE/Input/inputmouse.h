//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	inputmouse.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "input.h"
#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CInputMouse : public CInput
{
public:
    typedef enum
    {
        MOUSE_BUTTON_LEFT = 0,
        MOUSE_BUTTON_RIGHT,
        MOUSE_BUTTON_CENTER,
        MOUSE_BUTTON_MAX
    } MOUSE_BUTTON;

    CInputMouse();
    ~CInputMouse();

    HRESULT Init(HINSTANCE hInstance, HWND hWnd);    //����������
    void Uninit(void);                               //�I������
    void Update(void);                               //�X�V����

    //��Ԏ擾�p�֐�
    bool GetKeyPress(int nkey);
    bool GetKeyTrigger(int nkey);

private:
    DIMOUSESTATE2 m_State;    //�}�E�X�X�e�[�g
};

#endif
