//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	energy.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "energy.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "player.h"

LPDIRECT3DTEXTURE9 CEnergy::m_pTexture = NULL;

CEnergy::CEnergy() :CScene(4)
{
	memset(m_apPolygon, NULL, sizeof(m_apPolygon));
	m_nEnergy = MAX_ENERGY;
	m_mode = MODE_NORMAL;
}

CEnergy::~CEnergy()
{

}

HRESULT CEnergy::Init(void)
{
	m_apPolygon[0] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH *1.5 + 50, UI_BAR_HEIGHT / 2, 0), D3DXVECTOR3(UI_BAR_LENGTH, UI_BAR_HEIGHT, 0), 0, OBJTYPE_ENERGY);
	m_apPolygon[0]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
	m_apPolygon[0]->BindTexture(m_pTexture);

	m_apPolygon[1] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH *1.5 + 50, UI_BAR_HEIGHT * (2.0f / 3.0f), 0), D3DXVECTOR3(UI_BAR_LENGTH - 20, UI_BAR_HEIGHT*0.4f, 0), 0, OBJTYPE_ENERGY);
	m_apPolygon[1]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));

	m_apPolygon[2] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH *1.5 + 50, UI_BAR_HEIGHT * (2.0f / 3.0f), 0), D3DXVECTOR3(UI_BAR_LENGTH - 20, UI_BAR_HEIGHT*0.4f, 0), 0, OBJTYPE_ENERGY);
	m_apPolygon[2]->SetCol(D3DCOLOR_RGBA(0, 200, 200, 255));

	return S_OK;
}

void CEnergy::Uninit(void)
{
	for (int nCount = 0; nCount < NUM_GAUGE_LAYER; nCount++)
	{
		m_apPolygon[nCount]->Uninit();
		m_apPolygon[nCount] = NULL;
	}
	Release();
}

void CEnergy::Update(void)
{
	D3DXVECTOR3 polygonVtxPos[NUM_VERTEX];
	
		m_nEnergy+=2;
		if (m_nEnergy >= MAX_ENERGY)
		{
			m_nEnergy = MAX_ENERGY;
		}

 		m_apPolygon[2]->SetSize(D3DXVECTOR3(((UI_BAR_LENGTH - 20) /MAX_ENERGY)*m_nEnergy, UI_BAR_HEIGHT*0.4f, 0));
		m_apPolygon[2]->SetPos (D3DXVECTOR3((((UI_BAR_LENGTH - 20) / MAX_ENERGY)*m_nEnergy)/2 + 60 + UI_BAR_LENGTH, UI_BAR_HEIGHT * (2.0f / 3.0f),0));
		if (m_mode == MODE_NORMAL)
		{
			m_apPolygon[2]->SetCol(D3DCOLOR_RGBA(0, 200, 200, 255));
		}
		else if (m_mode == MODE_OVERHEAT)
		{
   			m_apPolygon[2]->SetCol(D3DCOLOR_RGBA((int)(m_nEnergy*(255.0f/MAX_ENERGY)), 0, 0, 255));
		}
		m_apPolygon[2]->Update();
	
	CScene** pScene = GetScene();
	for (int nCount = 0; nCount < MAX_SCENE*PRIORITY_MAX; nCount++)
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
	
}

void CEnergy::Draw(void)
{
	for (int nCount = 0; nCount < NUM_GAUGE_LAYER; nCount++)
	{
		m_apPolygon[nCount]->Draw();
	}
}

CEnergy* CEnergy::Create(void)
{
	CEnergy* pEnergy = NULL;
	pEnergy = new CEnergy;
	pEnergy->Init();
	return pEnergy;
}

int CEnergy::GetEnergy(void)
{
	return m_nEnergy;
}
void CEnergy::ReduceEnergy(int nValue)
{
   	m_nEnergy -= (nValue+1);
}

HRESULT CEnergy::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\ENERGY BAR.png", &m_pTexture);

	return S_OK;
}

void CEnergy::Unload(void)
{
	if (m_pTexture != NULL) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}