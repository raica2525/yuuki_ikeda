//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	inputkeyboard.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "input.h"
#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define NUM_KEY_MAX (256)    //�L�[�{�[�h�̍ő吔

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CInputKeyboard : public CInput
{
public:
    CInputKeyboard();
    ~CInputKeyboard();

    HRESULT Init(HINSTANCE hInstance, HWND hWnd);    //����������
    void Uninit(void);                               //�I������
    void Update(void);                               //�X�V����

    //�L�[��Ԏ擾�֐�
    bool GetKeyPress(int nkey);
    bool GetKeyTrigger(int nkey);
    bool GetKeyRelease(int nkey);

private:
    //�L�[��ԕۑ��p
    BYTE m_aState[NUM_KEY_MAX];
    BYTE m_aStateTrigger[NUM_KEY_MAX];
    BYTE m_aStateRelease[NUM_KEY_MAX];
};

#endif
