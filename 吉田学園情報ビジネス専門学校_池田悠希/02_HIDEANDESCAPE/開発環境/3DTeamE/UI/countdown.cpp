//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	countdown.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "countdown.h"
#include "gameoveroverlay.h"
#include "number.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"
#include "sound.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CCountDown::m_pTexture = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCountDown::CCountDown() : CObject(2)
{
    ZeroMemory(m_apNumber, sizeof(m_apNumber));
    m_nTimeLimit   = 0;
    m_nElapsedTime = 0;
    m_nSoundCount  = 0;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCountDown::~CCountDown()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//��������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCountDown* CCountDown::Create(const int nLimitTime, const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
    CCountDown* pCountDown = new CCountDown;

    pCountDown->m_nTimeLimit = nLimitTime * 60;
    pCountDown->m_pos        = pos;
    pCountDown->m_size       = size;

    pCountDown->Init();
    return pCountDown;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�������֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CCountDown::Init(void)
{
    for(int nCount = 0; nCount < DIGIT_NUM; nCount++)
    {
        if(nCount < DIGIT_NUM - DIGIT_NUM_INT)
        {
            m_apNumber[nCount] = CNumber::Create(0, D3DXVECTOR3(m_pos.x + m_size.x / 2.0f - m_size.x / 5.0f * nCount - m_size.x / 10.0f, m_pos.y + m_size.y * 0.1f, 0.0f), D3DXVECTOR3(m_size.x / 5.0f * 1.5f, (m_size.y - 25.0f) / 3.0f * 2.0f, 0.0f));
        }
        else
        {
            m_apNumber[nCount] = CNumber::Create(0, D3DXVECTOR3(m_pos.x + m_size.x / 2.0f - m_size.x / 5.0f * nCount - m_size.x / 10.0f, m_pos.y, 0.0f), D3DXVECTOR3(m_size.x / 5.0f * 1.5f, m_size.y - 25.0f, 0.0f));
        }
    }
    m_pObject2d = CObject2D::Create(m_pos, m_size, 1);
    m_pObject2d->BindTexture(m_pTexture);
    m_nSoundCount = 0;
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCountDown::Uninit(void)
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCountDown::Update(void)
{
    float fDisplayTime = 0;    //�\���p�̎���
    m_nElapsedTime++;          //�o�ߎ��Ԃ𑝂₷
    //�c�莞�Ԃ����炷
    fDisplayTime = (float)((m_nTimeLimit - m_nElapsedTime) * 1000.0f / 60.0f);
    //�c�莞�Ԃ�0�ȉ��ɂȂ�����0�ɖ߂�
    if(fDisplayTime < 0)
    {
        fDisplayTime = 0.0f;
    }
    //�����Ƃɕ����ĕ\�����鐔����ύX����
    for(int nCount = 0; nCount < DIGIT_NUM; nCount++)
    {
        m_apNumber[nCount]->SetValue(((int)fDisplayTime % (int)powf(10.0f, nCount + 1)) / (int)powf(10.0f, nCount));
    }

    //���Ԑ؂�̏���
    if(m_nElapsedTime >= m_nTimeLimit)
    {
        if(m_nSoundCount == 0)
        {
            CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_MAPEXPLOSION);
            m_nSoundCount++;
        }
        //�v���C���[�̗̑͂��ő�̗͕����炷(��ΎE��)
        CManager::GetPlayer()->AddLife(-START_LIFE);
    }
    //�����̍X�V����
    for(int nCount = 0; nCount < DIGIT_NUM; nCount++)
    {
        m_apNumber[nCount]->Update();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCountDown::Draw(void)
{
    for(int nCount = 0; nCount < DIGIT_NUM; nCount++)
    {
        m_apNumber[nCount]->Draw();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`�����[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CCountDown::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Data/Texture/Num_Haikei.png", &m_pTexture);
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`���A�����[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCountDown::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
