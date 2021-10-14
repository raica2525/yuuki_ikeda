//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	button.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "button.h"

#include "fade.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CButton::CButton(int nPriority) : CObject2D(nPriority)
{
    m_bSelect = false;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CButton::~CButton()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�������֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CButton::Init(void)
{
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
    CObject2D::Init();
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CButton::Uninit(void)
{
    CObject2D::Uninit();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CButton::Update(void)
{
    D3DXVECTOR3 pos  = GetPos();
    D3DXVECTOR3 size = GetSize();
    POINT point;
    //�}�E�X�J�[�\���ʒu�擾
    GetCursorPos(&point);
    //�}�E�X�J�[�\���ʒu���N���C�A���g�̑��Έʒu�ɕϊ�
    ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
    //�}�E�X�J�[�\�����{�^���ɐG��Ă����
    if(point.x > pos.x - size.x / 2.0f && point.x < pos.x + size.x / 2.0f && point.y > pos.y - size.y / 2.0f && point.y < pos.y + size.y / 2.0f)
    {
        CSound* pSound = CManager::GetSound();
        //�I�������Ƃ��̏���
        Select();
        //�O�t���[���őI������Ă��Ȃ����
        if(!m_bSelect)
        {
            //�T�E���h�Đ�
            pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONSELECT);
            m_bSelect = true;
        }
        //���̏�ԂŃN���b�N���ꂽ�ꍇ�̏���
        if(((CInputMouse*)CManager::GetInputMou())->GetKeyTrigger(CInputMouse::MOUSE_BUTTON_LEFT))
        {
            pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTONPUSH);
            Push();
        }
    }
    else
    {
        //�O�t���[���őI������Ă����
        if(m_bSelect)
        {
            //�I������Ă��Ȃ��Ƃ��̏���
            m_bSelect = false;
            Unselect();
        }
    }
	CObject2D::Update();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CButton::Draw(void)
{
    CObject2D::Draw();
}
