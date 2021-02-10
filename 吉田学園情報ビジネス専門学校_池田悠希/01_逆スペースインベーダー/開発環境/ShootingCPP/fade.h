//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	input.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"
#include "polygon.h"

// フェードの状態
class CFade : public CPolygon
{
public:
    CFade();
    ~CFade();
    typedef enum
    {
        FADE_NONE = 0,    // 何もない状態
        FADE_IN,          // フェードイン処理
        FADE_OUT,         // フェードアウト処理
        FADE_MAX
    } FADE;

    // プロトタイプ宣言
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CFade* Create(CManager::GAMEMODE modeNext);
    FADE GetFadePhase(void);
    static bool GetUse(void);

private:
    FADE m_fadePhase;                 // フェード状態
    CManager::GAMEMODE m_modeNext;    // 次の画面（モード）
    D3DXCOLOR m_colorFade;            // フェード色
    static bool m_bUse;
};
#endif
