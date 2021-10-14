//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	continuebutton.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "continuebutton.h"

#include "fade.h"
#include "inputmouse.h"
#include "manager.h"
#include "renderer.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CContinueButton::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CContinueButton::CContinueButton() : CButton(3)
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CContinueButton::~CContinueButton()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ読み込み関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CContinueButton::Load(void)
{
    // テクスチャの生成
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Data/Texture/continue.png", &m_pTexture);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ破棄関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CContinueButton::Unload(void)
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
CContinueButton* CContinueButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
    CContinueButton* pRetryButton = new CContinueButton;
    pRetryButton->SetPos(pos);
    pRetryButton->SetSize(size);
    pRetryButton->Init();
    return pRetryButton;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CContinueButton::Init(void)
{
    BindTexture(m_pTexture);    //テクスチャの割り当て
    CButton::Init();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//押されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CContinueButton::Push(void)
{
    //カーソルのリセット
    SetCursorPos(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
    while(ShowCursor(false) >= 0);

    //ポーズ終了
    CManager::EndPause();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CContinueButton::Select(void)
{
    //明るくする
    SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されていないときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CContinueButton::Unselect(void)
{
    //暗くする
    SetCol(D3DCOLOR_RGBA(128, 128, 128, 255));
}
