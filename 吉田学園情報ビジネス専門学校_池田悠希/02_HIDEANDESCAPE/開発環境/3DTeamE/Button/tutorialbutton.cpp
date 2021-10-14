//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	tutorialbutton.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "tutorialbutton.h"
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
LPDIRECT3DTEXTURE9 CTutorialButton::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CTutorialButton::CTutorialButton() : CButton(3)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CTutorialButton::~CTutorialButton()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ読み込み関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CTutorialButton::Load(void)
{
    // テクスチャの生成
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Data/Texture/tutorial.png", &m_pTexture);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ破棄関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTutorialButton::Unload(void)
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
CTutorialButton* CTutorialButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CTutorialButton* pTutorialButton = new CTutorialButton;
    pTutorialButton->SetPos(pos);
    pTutorialButton->m_DefaultSize = size;
    pTutorialButton->SetSize(size);
    pTutorialButton->Init();

    return pTutorialButton;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CTutorialButton::Init(void)
{
    BindTexture(m_pTexture);    //テクスチャの割り当て
    CButton::Init();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//押されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTutorialButton::Push(void)
{
    //チュートリアルモードに移行
    CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTutorialButton::Select(void)
{
    //大きくする
    SetSize(m_DefaultSize * SELECT_SIZE_MULTIPLE_RATE);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されていないときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTutorialButton::Unselect(void)
{
    //元に戻す
    SetSize(m_DefaultSize);
}
