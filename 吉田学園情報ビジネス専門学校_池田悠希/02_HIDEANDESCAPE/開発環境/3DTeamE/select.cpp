//=============================================================================
//
// セレクト処理 [tutorial.cpp]
// Author : 吉田　悠人
//
//=============================================================================
#include "manager.h"
#include "select.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CSelect::CSelect()
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CSelect::~CSelect()
{

}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// 生成処理関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CSelect * CSelect::Create(void)
{
	CSelect *pSelect;
	//インスタンス生成
	pSelect = new CSelect;
	//初期化処理
	if (pSelect != NULL)
	{
		pSelect->Init();
	}
	return pSelect;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CSelect::Init(void)
{
	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CSelect::Uninit(void)
{
	Release();
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CSelect::Update(void)
{

}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CSelect::Draw(void)
{
}