//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	life.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "player.h"

LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;
CLife::CLife():CScene(4)
{
	memset(m_apPolygon, NULL, sizeof(m_apPolygon));
	m_nLife = START_LIFE;
}

CLife::~CLife()
{

}

HRESULT CLife::Init(void)
{
		m_apPolygon[0] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH / 2, UI_BAR_HEIGHT/2, 0),D3DXVECTOR3(UI_BAR_LENGTH, UI_BAR_HEIGHT,0),0,OBJTYPE_LIFE);
		m_apPolygon[0]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
		m_apPolygon[0]->BindTexture(m_pTexture);

		m_apPolygon[1] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH / 2, UI_BAR_HEIGHT * (2.0f/3.0f), 0), D3DXVECTOR3(UI_BAR_LENGTH-20, UI_BAR_HEIGHT*0.4f, 0), 0, OBJTYPE_LIFE);
		m_apPolygon[1]->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));

		m_apPolygon[2] = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH / 2, UI_BAR_HEIGHT * (2.0f / 3.0f), 0), D3DXVECTOR3(UI_BAR_LENGTH - 20, UI_BAR_HEIGHT*0.4f, 0), 0, OBJTYPE_LIFE);
		m_apPolygon[2]->SetCol(D3DCOLOR_RGBA(0, 255, 0, 255));
	return S_OK;
}

void CLife::Uninit(void)
{
	for (int nCount = 0; nCount < NUM_GAUGE_LAYER; nCount++)
	{
		m_apPolygon[nCount]->Uninit();
		m_apPolygon[nCount] = NULL;
	}
	Release();
}

void CLife::Update(void)
{

		m_apPolygon[2]->SetSize(D3DXVECTOR3(((UI_BAR_LENGTH - 20) / START_LIFE)*m_nLife, UI_BAR_HEIGHT*0.4f, 0));
		m_apPolygon[2]->SetPos(D3DXVECTOR3((((UI_BAR_LENGTH - 20) / START_LIFE)*m_nLife) / 2+10, UI_BAR_HEIGHT * (2.0f / 3.0f), 0));
		m_apPolygon[2]->Update();

}

void CLife::Draw(void)
{
	for (int nCount = 0; nCount < NUM_GAUGE_LAYER; nCount++)
	{
		m_apPolygon[nCount]->Draw();
	}
}

CLife* CLife::Create(void)
{
	CLife* pLife = NULL;
	pLife = new CLife;
	pLife->SetObjType(OBJTYPE_LIFE);
	pLife->Init();
	return pLife;
}
void CLife::AddLife(int nLife)
{
	m_nLife += nLife;
	if (m_nLife >= START_LIFE)
	{
		m_nLife = START_LIFE;
	}
}

int CLife::GetLife(void)
{
	return m_nLife;
}

HRESULT CLife::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\LIFE BAR.png", &m_pTexture);

	return S_OK;
}

void CLife::Unload(void)
{
	if (m_pTexture != NULL) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}