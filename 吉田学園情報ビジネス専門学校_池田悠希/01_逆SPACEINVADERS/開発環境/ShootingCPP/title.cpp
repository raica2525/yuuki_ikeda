//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	title.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;
CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}

HRESULT CTitle::Init(void)
{
    CPolygon::Init();
    BindTexture(m_pTexture);

    return S_OK;
}

void CTitle::Uninit(void)
{
    CPolygon::Uninit();
}

void CTitle::Update(void)
{
    CPolygon::Update();
}

void CTitle::Draw(void)
{
    CPolygon::Draw();
}

CTitle* CTitle::Create(void)
{
    CTitle* pTitle = new CTitle;  
    pTitle->Init();
    pTitle->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
    pTitle->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
    pTitle->SetRot(0);
    pTitle->SetCol(D3DXCOLOR(1, 1, 1, 1));
    return pTitle;
}

HRESULT CTitle::Load(void)
{
    D3DXCreateTextureFromFile(
      CManager::GetRenderer()->GetDevice(), "Resources\\title.png", &m_pTexture);

    return S_OK;
}

void CTitle::Unload(void)
{
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
