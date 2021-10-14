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
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CInputMouse::m_bPrevState[4];
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
	//���̓f�o�C�X�̐���
    if(FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDeviceInput, NULL)))
    {
        return E_FAIL;
    }
	//�f�[�^�E�t�H�[�}�b�g����
	if (FAILED(m_pDeviceInput->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}
	//�������x���ݒ�
	if (FAILED(m_pDeviceInput->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}
	//�����[�h�ݒ�
    DIPROPDWORD diprop;
    diprop.diph.dwSize       = sizeof(diprop);
    diprop.diph.dwHeaderSize = sizeof(diprop.diph);
    diprop.diph.dwObj        = 0;
    diprop.diph.dwHow        = DIPH_DEVICE;
    diprop.dwData = DIPROPAXISMODE_REL;
    m_pDeviceInput->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	//�A�N�Z�X���擾
    m_pDeviceInput->Acquire();
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
    if(m_pDeviceInput != NULL)
    {
		//�A�N�Z�X���J��
        m_pDeviceInput->Unacquire();
		m_pDeviceInput->Release();
        m_pDeviceInput = NULL;
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CInputMouse::Update(void)
{
	//��ԏ�����
    for(int nCount = 0; nCount < sizeof(m_State.rgbButtons) / sizeof(m_State.rgbButtons[0]); nCount++)
    {
        m_State.rgbButtons[nCount] = 0;
    }
	//��Ԏ擾
    m_pDeviceInput->GetDeviceState(sizeof(DIMOUSESTATE2), &m_State);
	//�A�N�Z�X���擾
	m_pDeviceInput->Acquire();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//��Ԏ擾����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CInputMouse::GetKeyPress(int nkey)
{
    return (m_State.rgbButtons[nkey] & 0x80) ? true : false;
}

bool CInputMouse::GetKeyTrigger(int nkey)
{
	//���݂̏��ۑ�
    bool current = GetKeyPress(nkey);
	//�O�t���[���ƌ��݂̃}�E�X�̏�Ԃ��������Ⴄ��
    bool ret = current && !m_bPrevState[nkey];
	//���݂̃t���[���̏���ۑ�
	m_bPrevState[nkey] = current;
    return ret;
}
