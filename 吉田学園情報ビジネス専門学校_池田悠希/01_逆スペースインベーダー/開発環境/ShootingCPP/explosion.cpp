//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	explosion.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;
CExplosion::CExplosion() :CScene2d(3)
{
	m_nLife = EXPLOSION_LIFE;
}

CExplosion::~CExplosion()
{

}

HRESULT CExplosion::Init(void)
{
	CScene2d::Init();
	BindTexture(m_pTexture);

	return S_OK;
}

void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

void CExplosion::Update(void)
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	//位置取得
	pos = GetPos();
	CScene2d::Update();
	if (m_nLife-- <= 0)
	{
		Uninit();
	}
}

void CExplosion::Draw(void)
{
	CScene2d::Draw();
}

CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DCOLOR col)
{
	CExplosion* pExplosion = NULL;
	pExplosion = new CExplosion;
	CManager::GetSound()->Play(CSound::SE_EXPLOSION);
	pExplosion->SetPos(pos);
	pExplosion->SetCol(col);
	pExplosion->SetSize(D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE,0));
	pExplosion->SetObjType(OBJTYPE_EXPLOSION);
	pExplosion->Init();
	return pExplosion;

}

HRESULT CExplosion::Load(void)
{
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\explosion.png", &m_pTexture);

	return S_OK;
}

void CExplosion::Unload(void)
{
	if (m_pTexture != NULL) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}