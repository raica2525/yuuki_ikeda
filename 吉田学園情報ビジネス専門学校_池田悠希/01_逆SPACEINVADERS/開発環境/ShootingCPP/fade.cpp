//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	fade.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "fade.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CFade::m_bUse = false;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CFade::CFade()
{
    m_fadePhase = FADE_NONE;                            // �t�F�[�h���
    m_modeNext  = CManager::GAMEMODE_TITLE;             // ���̉�ʁi���[�h�j
    m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);    // �t�F�[�h�F
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CFade::~CFade()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CFade::Init(void)
{
    CPolygon::Init();
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CFade::Uninit(void)
{
    m_bUse = false;
    CPolygon::Uninit();
    CManager::KillFade();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CFade::Update(void)
{

    if(m_fadePhase == FADE_IN)    // �t�F�[�h�C������
    {
        m_colorFade.a -= FADE_RATE;    // ���l�����Z���Č��̉�ʂ𕂂��オ�点��
        if(m_colorFade.a <= 0.0f)
        {
            // �t�F�[�h�����I��
            m_colorFade.a = 0.0f;
            m_fadePhase   = FADE_NONE;
        }
    }
    else if(m_fadePhase == FADE_OUT)    // �t�F�[�h�A�E�g����
    {
        m_colorFade.a += FADE_RATE;    // ���l�����Z���Č��̉�ʂ������Ă���

        if(m_colorFade.a >= 1.0f)
        {
            // �t�F�[�h�C�������ɐ؂�ւ�
            m_colorFade.a = 1.0f;
            m_fadePhase   = FADE_IN;

            // ���[�h��ݒ�
            CManager::SetGamemode(m_modeNext);
        }
    }
    //�|���S���̐F�����X�V
    CPolygon::SetCol(m_colorFade);
    CPolygon::Update();
    //�t�F�[�h���I�����������
    if(m_fadePhase == FADE_NONE)
    {
        Uninit();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CFade::Draw(void)
{
    CPolygon::Draw();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CFade* CFade::Create(CManager::GAMEMODE modeNext)
{
    CFade* pFade = NULL;
	//�t�F�[�h���łȂ����
    if(!m_bUse)
    {
		//�������m��
        pFade              = new CFade;
		//�e����ݒ�
        pFade->m_fadePhase = FADE_OUT;
        pFade->m_modeNext  = modeNext;
        pFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
        pFade->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
        pFade->SetRot(0);
        pFade->m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);    // ������ʁi�����j
        m_bUse             = true;
		//�������֐�
        pFade->Init();
    }
    return pFade;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�F�[�h�̒i�K�擾����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CFade::FADE CFade::GetFadePhase(void)
{
    return m_fadePhase;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�F�[�h���擾����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CFade::GetUse(void)
{
    return m_bUse;
}
