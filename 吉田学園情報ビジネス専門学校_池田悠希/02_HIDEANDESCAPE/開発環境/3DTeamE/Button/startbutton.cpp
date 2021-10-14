//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	startbutton.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "startbutton.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputmouse.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define SELECT_SIZE_MULTIPLE_RATE (1.1f)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CStartButton::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CStartButton::CStartButton() : CButton(3)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CStartButton::~CStartButton()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ読み込み関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CStartButton::Load(void)
{
    // テクスチャの生成
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Data/Texture/gamestart.png", &m_pTexture);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ破棄関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CStartButton::Unload(void)
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
CStartButton* CStartButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
    CStartButton* pStartButton = new CStartButton;
    pStartButton->SetPos(pos);
    pStartButton->m_DefaultSize = size;
    pStartButton->SetSize(size);
    pStartButton->Init();

    return pStartButton;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CStartButton::Init(void)
{
    BindTexture(m_pTexture);    //テクスチャの割り当て
    CButton::Init();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//押されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CStartButton::Push(void)
{
    CManager::GetFade()->SetFade(CManager::MODE_WEAPONSELECT);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CStartButton::Select(void)
{
    SetSize(m_DefaultSize * SELECT_SIZE_MULTIPLE_RATE);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されていないときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CStartButton::Unselect(void)
{
    SetSize(m_DefaultSize);
}
