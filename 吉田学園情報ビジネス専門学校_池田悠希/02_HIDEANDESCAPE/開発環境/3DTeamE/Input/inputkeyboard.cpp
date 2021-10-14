//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	inputkeyboard.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "inputkeyboard.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CInputKeyboard::CInputKeyboard()
{
    memset(m_aState, 0, sizeof(m_aState));
    memset(m_aStateTrigger, 0, sizeof(m_aStateTrigger));
    memset(m_aStateRelease, 0, sizeof(m_aStateRelease));
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CInputKeyboard::~CInputKeyboard()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
    CInput::Init(hInstance, hWnd);

    //���̓f�o�C�X�̍쐬
    if(FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDeviceInput, NULL)))
    {
        return E_FAIL;
    }
    //�f�[�^�E�t�H�[�}�b�g�ݒ�
    if(FAILED(m_pDeviceInput->SetDataFormat(&c_dfDIKeyboard)))
    {
        return E_FAIL;
    }
    //�������[�h�ݒ�
    if(FAILED(m_pDeviceInput->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
    {
        return E_FAIL;
    }
    //�L�[�{�[�h�ւ̃A�N�Z�X���l��
    m_pDeviceInput->Acquire();

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CInputKeyboard::Update(void)
{
    BYTE akeyState[NUM_KEY_MAX];    //�L�[�̍ő吔
    int nCntkey;

    //�f�o�C�X����f�[�^�擾
    if(SUCCEEDED(m_pDeviceInput->GetDeviceState(sizeof(akeyState), akeyState)))
    {
        for(nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
        {
            m_aStateTrigger[nCntkey] = (m_aState[nCntkey] ^ akeyState[nCntkey]) & akeyState[nCntkey];
            m_aStateRelease[nCntkey] = (m_aState[nCntkey] ^ akeyState[nCntkey]) & ~akeyState[nCntkey];
            m_aState[nCntkey]        = akeyState[nCntkey];
        }
    }
    else
    {
        //�L�[�{�[�h�̃A�N�Z�X���擾
        m_pDeviceInput->Acquire();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CInputKeyboard::Uninit(void)
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
//�L�[�̏�Ԏ擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CInputKeyboard::GetKeyPress(const int nkey)
{
    return (m_aState[nkey] & 0x80) ? true : false;
}
bool CInputKeyboard::GetKeyTrigger(const int nkey)
{
    return (m_aStateTrigger[nkey] & 0x80) ? true : false;
}
bool CInputKeyboard::GetKeyRelease(const int nkey)
{
    return (m_aStateRelease[nkey] & 0x80) ? true : false;
}
