//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	Assaultbutton.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "assaultbutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CAssaultButton::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CAssaultButton::CAssaultButton() : CButton(3)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CAssaultButton::~CAssaultButton()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ読み込み関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CAssaultButton::Load(void)
{
    // テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Data/Texture/AR.png", &m_pTexture);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ破棄関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CAssaultButton::Unload(void)
{
    // テクスチャの破棄
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//生成関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CAssaultButton* CAssaultButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
    CAssaultButton* pAssaultButton = new CAssaultButton;
    pAssaultButton->SetPos(pos);
    pAssaultButton->SetSize(size);
    pAssaultButton->Init();

    return pAssaultButton;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CAssaultButton::Init(void)
{

    BindTexture(m_pTexture);    //テクスチャの割り当て
    CButton::Init();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//押されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CAssaultButton::Push(void)
{
    //武器設定
    CManager::SetWeaponsMode(CManager::WEAPONS_MODE_AR);
    //最初のステージに移行
    CManager::GetFade()->SetFade(CManager::MODE_MAP01);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CAssaultButton::Select(void)
{
    //不透明にする
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されていない場合の処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CAssaultButton::Unselect(void)
{
    //半透明にする
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 128));
}
