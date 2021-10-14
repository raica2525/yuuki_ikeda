//=============================================================================
//
// トラップ処理 [trap.cpp]
// Author : 吉田悠人
//
//=============================================================================


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "trap.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "sound.h"

//*****************************************************************************
//　静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTrap::CTrap()
{
	m_Startpos = ZEROVECTOR3;
	m_Endpos = ZEROVECTOR3;
	m_pTexture = NULL;
	SetObjType(OBJTYPE_NONE);
}

//=============================================================================
// デストラクタ
//=============================================================================
CTrap::~CTrap()
{
}

CTrap * CTrap::Create(D3DXVECTOR3 Startpos, D3DXVECTOR3 Endpos)
{
	CTrap* pTrap = NULL;
	pTrap = new CTrap;
	pTrap->m_Startpos = Startpos;
	pTrap->m_Endpos = Endpos;
	pTrap->SetPos((Startpos + Endpos) / 2);
	pTrap->SetRot(D3DXVECTOR3(90.0f, D3DXToDegree(atan2f((Startpos.x - Endpos.x), (Startpos.z - Endpos.z))), 0.0f));
	pTrap->SetSize(D3DXVECTOR3(1.0f, sqrtf(((Startpos.x - Endpos.x)*(Startpos.x - Endpos.x)) + ((Startpos.z - Endpos.z)*(Startpos.z - Endpos.z))), 1.0f));
	for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
	{
		pTrap->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f - (nMesh*0.1f)), nMesh);
	}
	pTrap->Init();
	return pTrap;
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CTrap::Init(void)
{
	CMeshCylinder::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CTrap::Uninit(void)
{
	CMeshCylinder::Uninit();
	Release();
}

//=============================================================================
// 更新関数
//=============================================================================
void CTrap::Update(void)
{
	CObject* pTop[PRIORITY_MAX] = {};
	CObject* pNext = NULL;
	CSound* pSound = CManager::GetSound();              //サウンドの取得
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//リストトップ取得
		pTop[nCount] = *(CObject::GetTop() + nCount);
	}

	//距離
	float fDistanve;
	//NULLチェック
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		//NULLチェック
		if (pTop[nCount] != NULL)
		{
			pNext = pTop[nCount];
			while (pNext != NULL)
			{
				//オブジェクトタイプチェック
				if (pNext->GetObjType() == OBJTYPE_MODEL)
				{
					//NULLチェック
					if (((CModel *)pNext)->GetParentObject() != NULL)
					{
						if (((CModel*)pNext)->GetParentObject()->GetObjType() == OBJTYPE_PLAYER)
						{
							if (Search(((CModel*)pNext)->GetModelData(), fDistanve) == TRUE)
							{
								if (GetSize().y>fDistanve)
								{
									//爆破
									CExplosion::Create(D3DXVECTOR3(CManager::GetPlayer()->GetPos().x, CManager::GetPlayer()->GetPos().y + 30, CManager::GetPlayer()->GetPos().z), ZEROVECTOR3, D3DXVECTOR3(100, 100, 100));

									//プレイヤーダメージ
									CManager::GetPlayer()->AddLife(-45);

									//終了処理
									Uninit();
								}
							}
						}
					}
				}
				//次の対象を読み込む
				pNext = pNext->GetNext();
			}
		}
	}
	CMeshCylinder::Update();

}

//=============================================================================
// 描画関数
//=============================================================================
void CTrap::Draw(void)
{
	CMeshCylinder::Draw();
}

//=============================================================================
// 感知関数
//=============================================================================
BOOL CTrap::Search(CModel::MODELDATA modeldata, float &fDistanve)
{
	BOOL bSearch = FALSE;					//反応しているか
	D3DXMATRIX mtxWorld;
	D3DXMATRIX InversedWorldMatrix;	//逆列用マトリックス
	D3DXVECTOR3 TransformedPos, NormalizedVec, TranceformedVec;

	//単位ベクトルに変換
	D3DXVec3Normalize(&NormalizedVec, &(m_Endpos - m_Startpos));
	//逆行列生成
	D3DXMatrixInverse(&InversedWorldMatrix, NULL, &modeldata.mtxWorld);
	//逆行列で変換
	D3DXVec3TransformCoord(&TransformedPos, &m_Startpos, &InversedWorldMatrix);
	D3DXVec3TransformNormal(&TranceformedVec, &NormalizedVec, &InversedWorldMatrix);
	//当たり判定を確認
	D3DXIntersect(modeldata.pMesh, &TransformedPos, &TranceformedVec, &bSearch, NULL, NULL, NULL, &fDistanve, NULL, NULL);
	return bSearch;

}


