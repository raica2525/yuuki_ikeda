//=============================================================================
//
// ゴール処理 [trap.cpp]
// Author : 吉田悠人
//
//=============================================================================


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "goal.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGoal::CGoal()
{
	m_GameMode = {};
	m_pTexture = NULL;
	SetObjType(OBJTYPE_NONE);
}

//=============================================================================
// デストラクタ
//=============================================================================
CGoal::~CGoal()
{
}

//=============================================================================
// 生成関数
//=============================================================================
CGoal * CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, CManager::GAMEMODE Mode)
{
	CGoal* pGoal = NULL;
	pGoal = new CGoal;
	pGoal->SetPos(pos);
	pGoal->SetRot(rot);
	pGoal->SetSize(size);
	pGoal->m_GameMode = Mode;
	for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
	{
		pGoal->SetColor(D3DXCOLOR(col.r, col.g, col.b, nMesh*0.1f), nMesh);
	}

	pGoal->Init();
	return pGoal;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CGoal::Init(void)
{
	CMeshCylinder::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CGoal::Uninit(void)
{
	CMeshCylinder::Uninit();
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CGoal::Update(void)
{
	//メッシュのカラー変更
	CMeshCylinder::ColorAnimation();
	//ゴール判定
	HitGoal();
	//メッシュのアップデート
	CMeshCylinder::Update();
}

//=============================================================================
// 描画関数
//=============================================================================
void CGoal::Draw(void)
{
	CMeshCylinder::Draw();
}

void CGoal::HitGoal(void)
{
	D3DXVECTOR3 Playerpos = CManager::GetPlayer()->GetPos();
	if (GetPos().x+(GetSize().x/2)>Playerpos.x
		&&GetPos().x - (GetSize().x / 2)<Playerpos.x
		&&GetPos().z + (GetSize().z / 2)> Playerpos.z
		&&GetPos().z - (GetSize().z / 2)< Playerpos.z)
	{
		//サウンドの取得
		CSound * pSound = CManager::GetSound();
		pSound->StopSound();
		CManager::GetFade()->SetFade(m_GameMode);
		Uninit();
	}
}

