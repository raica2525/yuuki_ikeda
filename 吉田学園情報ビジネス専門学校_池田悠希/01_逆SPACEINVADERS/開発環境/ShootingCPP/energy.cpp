//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	energy.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "energy.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "player.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CEnergy::m_pTexture = NULL;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CEnergy::CEnergy() : CScene(4)
{
    memset(m_apPolygon, NULL, sizeof(m_apPolygon));
    m_nEnergy = MAX_ENERGY;
    m_mode    = MODE_NORMAL;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CEnergy::~CEnergy()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CEnergy::Init(void)
{
    m_apPolygon[0] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH * 1.5 + 50, UI_BAR_HEIGHT / 2, 0), D3DXVECTOR3(UI_BAR_LENGTH, UI_BAR_HEIGHT, 0), 0, OBJTYPE_ENERGY);
    m_apPolygon[0]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
    m_apPolygon[0]->BindTexture(m_pTexture);

    m_apPolygon[1] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH * 1.5 + 50, UI_BAR_HEIGHT * (2.0f / 3.0f), 0), D3DXVECTOR3(UI_BAR_LENGTH - 20, UI_BAR_HEIGHT * 0.4f, 0), 0, OBJTYPE_ENERGY);
    m_apPolygon[1]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));

    m_apPolygon[2] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH * 1.5 + 50, UI_BAR_HEIGHT * (2.0f / 3.0f), 0), D3DXVECTOR3(UI_BAR_LENGTH - 20, UI_BAR_HEIGHT * 0.4f, 0), 0, OBJTYPE_ENERGY);
    m_apPolygon[2]->SetCol(D3DCOLOR_RGBA(0, 200, 200, 255));

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CEnergy::Uninit(void)
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
void CEnergy::Update(void)
{
    D3DXVECTOR3 polygonVtxPos[NUM_VERTEX];

	//���t���[��2���G�l���M�[����
    m_nEnergy += 2;
    if(m_nEnergy >= MAX_ENERGY)
    {
        m_nEnergy = MAX_ENERGY;
    }
	//��ԏ�̃��C���[�̃T�C�Y���G�l���M�[�ʂɂ���ĕω�������
    m_apPolygon[2]->SetSize(D3DXVECTOR3(((UI_BAR_LENGTH - 20) / MAX_ENERGY) * m_nEnergy, UI_BAR_HEIGHT * 0.4f, 0));
    m_apPolygon[2]->SetPos(D3DXVECTOR3((((UI_BAR_LENGTH - 20) / MAX_ENERGY) * m_nEnergy) / 2 + 60 + UI_BAR_LENGTH, UI_BAR_HEIGHT * (2.0f / 3.0f), 0));

	//�I�[�o�[�q�[�g��Ԃ̐؂�ւ�
	CScene** pScene = GetScene();
	for (int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
	{
		if ((*(pScene + nCount)) != NULL)
		{
			if ((*(pScene + nCount))->GetObjType() == OBJTYPE_PLAYER)
			{
				if (m_nEnergy <= 0)
				{
					((CPlayer*)(*(pScene + nCount)))->SetOverHeat(true);
					m_mode = MODE_OVERHEAT;
				}
				else if (m_nEnergy >= MAX_ENERGY && MODE_OVERHEAT)
				{
					((CPlayer*)(*(pScene + nCount)))->SetOverHeat(false);
					m_mode = MODE_NORMAL;
				}
			}
		}
	}

	//�I�[�o�[�q�[�g��ԂȂ�F��ς���
    if(m_mode == MODE_NORMAL)
    {
        m_apPolygon[2]->SetCol(D3DCOLOR_RGBA(0, 200, 200, 255));
    }
    else if(m_mode == MODE_OVERHEAT)
    {
        m_apPolygon[2]->SetCol(D3DCOLOR_RGBA((int)(m_nEnergy * (255.0f / MAX_ENERGY)), 0, 0, 255));
    }
    m_apPolygon[2]->Update();


}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CEnergy::Draw(void)
{
    for(int nCount = 0; nCount < NUM_GAUGE_LAYER; nCount++)
    {
        m_apPolygon[nCount]->Draw();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CEnergy* CEnergy::Create(void)
{
    CEnergy* pEnergy = new CEnergy;        
    pEnergy->Init();
    return pEnergy;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�c�G�l���M�[�擾����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
int CEnergy::GetEnergy(void)
{
    return m_nEnergy;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�G�l���M�[��������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CEnergy::ReduceEnergy(int nValue)
{
    m_nEnergy -= (nValue + 1);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���ǂݍ��݊֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CEnergy::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\ENERGY BAR.png", &m_pTexture);
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ǂݍ��݃f�[�^�j������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CEnergy::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
