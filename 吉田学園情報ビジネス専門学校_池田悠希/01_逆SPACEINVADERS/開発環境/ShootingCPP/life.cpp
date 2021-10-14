//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	life.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "player.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CLife::CLife() : CScene(4)
{
    memset(m_apPolygon, NULL, sizeof(m_apPolygon));
    m_nLife = START_LIFE;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CLife::~CLife()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CLife::Init(void)
{
	//���C�t�Q�[�W��UI
    m_apPolygon[0] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH / 2, UI_BAR_HEIGHT / 2, 0), D3DXVECTOR3(UI_BAR_LENGTH, UI_BAR_HEIGHT, 0), 0, OBJTYPE_LIFE);
    m_apPolygon[0]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
    m_apPolygon[0]->BindTexture(m_pTexture);

	//���C�t�Q�[�W�̔w�i�i���j
    m_apPolygon[1] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH / 2, UI_BAR_HEIGHT * (2.0f / 3.0f), 0), D3DXVECTOR3(UI_BAR_LENGTH - 20, UI_BAR_HEIGHT * 0.4f, 0), 0, OBJTYPE_LIFE);
    m_apPolygon[1]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));

	//���C�t�Q�[�W�{��
    m_apPolygon[2] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH / 2, UI_BAR_HEIGHT * (2.0f / 3.0f), 0), D3DXVECTOR3(UI_BAR_LENGTH - 20, UI_BAR_HEIGHT * 0.4f, 0), 0, OBJTYPE_LIFE);
    m_apPolygon[2]->SetCol(D3DCOLOR_RGBA(0, 255, 0, 255));
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLife::Uninit(void)
{
    for(int nCount = 0; nCount < NUM_GAUGE_LAYER; nCount++)
    {
        m_apPolygon[nCount]->Uninit();
		delete m_apPolygon[nCount];
        m_apPolygon[nCount] = NULL;
    }
    Release();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLife::Update(void)
{
	//�Q�[�W�{�̂̒����𒲐�
    m_apPolygon[2]->SetSize(D3DXVECTOR3(((UI_BAR_LENGTH - 20) / START_LIFE) * m_nLife, UI_BAR_HEIGHT * 0.4f, 0));
    m_apPolygon[2]->SetPos(D3DXVECTOR3((((UI_BAR_LENGTH - 20) / START_LIFE) * m_nLife) / 2 + 10, UI_BAR_HEIGHT * (2.0f / 3.0f), 0));
    m_apPolygon[2]->Update();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLife::Draw(void)
{
    for(int nCount = 0; nCount < NUM_GAUGE_LAYER; nCount++)
    {
        m_apPolygon[nCount]->Draw();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CLife* CLife::Create(void)
{
    CLife* pLife = new CLife;
    pLife->SetObjType(OBJTYPE_LIFE);
    pLife->Init();
    return pLife;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���C�t��������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLife::AddLife(int nLife)
{
    m_nLife += nLife;

	//�ő�̗͂�葽���Ȃ�Ȃ��悤����
    if(m_nLife >= START_LIFE)
    {
        m_nLife = START_LIFE;
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���C�t�擾����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
int CLife::GetLife(void)
{
    return m_nLife;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���ǂݍ��ݏ���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CLife::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\LIFE BAR.png", &m_pTexture);
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ǂݍ��݃f�[�^�j������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CLife::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
