//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	debug.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define _CRT_SECURE_NO_WARNINGS
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "debug.h"

#include <stdio.h>

#include "manager.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPD3DXFONT CDebug::m_pFont = NULL;
char CDebug::m_str[512]    = {};

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CDebug::CDebug()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CDebug::~CDebug()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CDebug::Init()
{
    //フォント生成
    D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//表示設定処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CDebug::Print(char* fmt, ...)
{

    //ZeroMemory(m_str, sizeof(m_str));
    va_list list;
    va_start(list, fmt);
    for(char* pointer = fmt; *pointer != '\0'; pointer++)
    {
        char str[256] = {};
        ZeroMemory(str, sizeof(str));
        switch(*pointer)
        {
            pointer++;
            case 'd':
                wsprintf(str, "%d", va_arg(list, int));
                break;
            case 'f':
                wsprintf(str, "%f", va_arg(list, double));
                break;
            case 'c':
                wsprintf(str, "%c", va_arg(list, char));
                break;
            case 's':
                wsprintf(str, "%s", va_arg(list, const char*));
                break;
            case '%':
                break;
            default:
                memcpy(str, pointer, 1);
                break;
        }
        strcat(m_str, str);
    }
    va_end(list);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CDebug::Draw()
{
    RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    // テキスト描画
    m_pFont->DrawText(NULL, m_str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
    ZeroMemory(m_str, sizeof(m_str));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CDebug::Uninit()
{
    //フォントの開放
    if(m_pFont != NULL)
    {
        m_pFont->Release();
        m_pFont = NULL;
    }
}
