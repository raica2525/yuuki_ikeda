//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	cursol.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "cursol.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CCursol::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CCursol::CCursol() : CScene(4)
{
    m_pPolygon = NULL;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CCursol::~CCursol()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CCursol::Init(void)
{
	//ポリゴン生成
    m_pPolygon = CPolygon::Create(D3DXVECTOR3(UI_BAR_LENGTH / 2, UI_BAR_HEIGHT / 2, 0), D3DXVECTOR3(CURSOL_SIZE, CURSOL_SIZE, 0), 0, OBJTYPE_UI);
	//色設定
    m_pPolygon->SetCol(D3DCOLOR_RGBA(255, 255, 255, 255));
	//テクスチャ割当
    m_pPolygon->BindTexture(m_pTexture);

    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCursol::Uninit(void)
{
	//カーソル表示
	while (ShowCursor(true)<0);
	//ポリゴンの終了
    m_pPolygon->Uninit();
	delete m_pPolygon;
    m_pPolygon = NULL;
    Release();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCursol::Update(void)
{
	//マウスポインタ座標取得
    POINT point;
    GetCursorPos(&point);
	//マウスポインタ座標変換
    ScreenToClient(FindWindow(CLASS_NAME, NULL), &point);
	//マウスポインタの位置にポリゴンをあわせる
    m_pPolygon->SetPos(D3DXVECTOR3((float)point.x, (float)point.y, 0));
    m_pPolygon->Update();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCursol::Draw(void)
{
    m_pPolygon->Draw();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クリエイト関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CCursol* CCursol::Create(void)
{
    CCursol* pCursol = new CCursol;  
	//マウスカーソル非表示
    while(ShowCursor(false) >= 0);
	//オブジェクトタイプ設定
    pCursol->SetObjType(OBJTYPE_UI);
	//初期化関数
    pCursol->Init();
    return pCursol;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイル読み込み処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CCursol::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\cursol.png", &m_pTexture);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//読み込みデータ破棄処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CCursol::Unload(void)
{
	//テクスチャ破棄
    if(m_pTexture != NULL)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }
}
