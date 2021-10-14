//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	crosshair.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define MAX_SPREAD (200.0f)
#define CROSSHAIR_PART_SIZE D3DXVECTOR3(6.0f, 20.0f, 0.0f)
#define CROSSHAIR_SPREAD_REDUCE_RATE (2.0f)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "crosshair.h"

#include "camera.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CCrosshair::m_pTexture = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCrosshair::CCrosshair()
{
    m_fSpread    = 0.0f;
    m_fMinSpread = 0.0f;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCrosshair::~CCrosshair()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CCrosshair::Init(void)
{
    // 2D�|���S���̐���
    for(int nCount = 0; nCount < CROSSHAIR_PARTS_COUNT; nCount++)
    {
        if(m_apObject2d[nCount] != NULL)
        {
            m_apObject2d[nCount] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0), CROSSHAIR_PART_SIZE, 2);
            m_apObject2d[nCount]->SetRot(nCount * 90.0f);
            m_apObject2d[nCount]->SetCol(D3DCOLOR_RGBA(0, 255, 0, 255));
            m_apObject2d[nCount]->BindTexture(m_pTexture);
        }
    }
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::Uninit(void)
{
    //�|���S���̏I��
    for(int nCount = 0; nCount < CROSSHAIR_PARTS_COUNT; nCount++)
    {
        if(m_apObject2d[nCount] != NULL)
        {
            m_apObject2d[nCount]->Uninit();
        }
    }
    Release();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::Update(void)
{
    //�g�U���ւ炷
    if(m_fSpread > 0)
    {
        m_fSpread -= CROSSHAIR_SPREAD_REDUCE_RATE;
        if(m_fSpread < 0.0f)
        {
            m_fSpread = 0.0f;
        }
    }

    //�g�U���ő�ȏ�Ȃ�ő�ɖ߂�
    if(m_fSpread > MAX_SPREAD)
    {
        m_fSpread = MAX_SPREAD;
    }

    //�g�U�ʂɉ����ă|���S�����ړ�
    for(int nCount = 0; nCount < CROSSHAIR_PARTS_COUNT; nCount++)
    {
        D3DXVECTOR3 pos;
        if(m_apObject2d[nCount] != NULL)
        {
            switch(nCount)
            {
                case 0:
                    pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) - (m_fMinSpread + m_fSpread), 0);
                    break;
                case 1:
                    pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (m_fMinSpread + m_fSpread), SCREEN_HEIGHT / 2.0f, 0);
                    break;
                case 2:
                    pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) + (m_fMinSpread + m_fSpread), 0);
                    break;
                case 3:
                    pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (m_fMinSpread + m_fSpread), (SCREEN_HEIGHT / 2.0f), 0);
                    break;
            }
            m_apObject2d[nCount]->SetPos(pos);
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::Draw(void)
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CCrosshair* CCrosshair::Create(const float fMinSpread)
{
    CCrosshair* pCrosshair   = new CCrosshair;
    pCrosshair->m_fMinSpread = fMinSpread;
    pCrosshair->Init();
    return pCrosshair;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�L����̕ύX
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::AddSpread(const float fValue)
{
    m_fSpread += fValue;
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�L����̍Œ�l�̕ύX
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::SetMinSpread(const float fMinSpread)
{
    m_fMinSpread = fMinSpread;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�L������擾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
float CCrosshair::GetSpread(void)
{
    return m_fSpread + m_fMinSpread;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`�����[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Data/Texture/crosshair.png", &m_pTexture);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`���A�����[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CCrosshair::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
