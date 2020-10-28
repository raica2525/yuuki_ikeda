//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	cursol.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "cursol.h"

LPDIRECT3DTEXTURE9 CCursol::m_pTexture = NULL;
CCursol::CCursol() : CScene(4)
{
	m_pPolygon = NULL;
}

CCursol::~CCursol()
{

}

HRESULT CCursol::Init(void)
{
	m_pPolygon = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH / 2, UI_BAR_HEIGHT / 2, 0), D3DXVECTOR3(CURSOL_SIZE, CURSOL_SIZE, 0), 0, OBJTYPE_UI);
	m_pPolygon->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
	m_pPolygon->BindTexture(m_pTexture);

	return S_OK;
}

void CCursol::Uninit(void)
{
	ShowCursor(true);
	m_pPolygon->Uninit();
	m_pPolygon = NULL;
	Release();
}

void CCursol::Update(void)
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
	m_pPolygon->SetPos(D3DXVECTOR3(point.x,point.y, 0));
	m_pPolygon->Update();

}

void CCursol::Draw(void)
{
	m_pPolygon->Draw();
}

CCursol* CCursol::Create(void)
{
	CCursol* pCursol = NULL;
	pCursol = new CCursol;
	ShowCursor(false);

	pCursol->SetObjType(OBJTYPE_UI);
	pCursol->Init();
	return pCursol;
}

HRESULT CCursol::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\cursol.png", &m_pTexture);
	return S_OK;
}

void CCursol::Unload(void)
{
	if (m_pTexture != NULL) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}