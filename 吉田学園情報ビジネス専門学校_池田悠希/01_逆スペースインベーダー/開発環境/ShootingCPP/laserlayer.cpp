//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	laser.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "laserlayer.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
LPDIRECT3DTEXTURE9 CLaserLayer::m_pTexture = NULL;
CLaserLayer::CLaserLayer()
{

}

CLaserLayer::~CLaserLayer()
{

}

HRESULT CLaserLayer::Init(void)
{
	CPolygon::Init();
	BindTexture(m_pTexture);

	return S_OK;
}

void CLaserLayer::Uninit(void)
{
	CPolygon::Uninit();
}

void CLaserLayer::Update(void)
{
	CPolygon::Update();
}

void CLaserLayer::Draw(void)
{
	CPolygon::Draw();
}

CLaserLayer* CLaserLayer::Create(D3DXVECTOR3 pos, D3DCOLOR col,int nWidth,int Length,float fRot)
{
	CLaserLayer* pLaserLayer = NULL;
	pLaserLayer = new CLaserLayer;
	pLaserLayer->SetPos(pos);
	pLaserLayer->SetCol(col);
	pLaserLayer->SetRot(fRot);
	pLaserLayer->SetSize(D3DXVECTOR3(Length, nWidth,0));
	pLaserLayer->SetObjType(CScene::OBJTYPE_LASER);
	pLaserLayer->Init();
	return pLaserLayer;
}

HRESULT CLaserLayer::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\Laser.png", &m_pTexture);

	return S_OK;
}

void CLaserLayer::Unload(void)
{
	if (m_pTexture != NULL) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}