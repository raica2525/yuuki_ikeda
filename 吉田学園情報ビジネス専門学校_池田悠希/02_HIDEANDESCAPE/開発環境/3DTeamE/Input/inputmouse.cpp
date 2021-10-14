//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	inputmouse.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "inputmouse.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CInputMouse::CInputMouse()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CInputMouse::~CInputMouse()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
    CInput::Init(hInstance, hWnd);
    if(FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDeviceInput, NULL)))
    {
        return E_FAIL;
    }

    m_pDeviceInput->SetDataFormat(&c_dfDIMouse2);    //�f�[�^�t�H�[�}�b�g�ݒ�
    m_pDeviceInput->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

    DIPROPDWORD diprop;
    diprop.diph.dwSize       = sizeof(diprop);
    diprop.diph.dwHeaderSize = sizeof(diprop.diph);
    diprop.diph.dwObj        = 0;
    diprop.diph.dwHow        = DIPH_DEVICE;
    diprop.dwData            = DIPROPAXISMODE_REL;    // ���Βl���[�h�Őݒ�
    m_pDeviceInput->SetProperty(DIPROP_AXISMODE, &diprop.diph);

    m_pDeviceInput->Acquire();
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CInputMouse::Uninit(void)
{
    //���̓f�o�C�X�J��
    if(m_pDeviceInput != NULL)
    {
        //�L�[�{�[�h�̃A�N�Z�X���J��
        m_pDeviceInput->Unacquire();
        m_pDeviceInput = NULL;
    }
    CInput::Uninit();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CInputMouse::Update(void)
{
    for(int nCount = 0; nCount < MOUSE_BUTTON_MAX; nCount++)
    {
        m_State.rgbButtons[nCount] = 0;
    }
    m_pDeviceInput->GetDeviceState(sizeof(DIMOUSESTATE2), &m_State);

    m_pDeviceInput->Acquire();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�E�X�{�^���̏�Ԏ擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CInputMouse::GetKeyPress(const int Mouse)
{
    return (m_State.rgbButtons[Mouse] & 0x80) ? true : false;
}

bool CInputMouse::GetKeyTrigger(const int nkey)
{
    //�O�̃t���[���ƍ��̃t���[�����Ⴄ�Ȃ�true;
    static bool prevState[sizeof(m_State.rgbButtons) / sizeof(m_State.rgbButtons[0])];
    bool current    = GetKeyPress(nkey);
    bool ret        = current && !prevState[nkey];
    prevState[nkey] = current;
    return ret;
}
