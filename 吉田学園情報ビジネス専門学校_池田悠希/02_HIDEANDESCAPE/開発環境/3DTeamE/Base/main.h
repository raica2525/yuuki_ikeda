//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	main.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _MAIN_H_
#define _MAIN_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
// DirectInputのバージョン設定
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define DIRECTINPUT_VERSION (0x0800)

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include <dinput.h>
#include <time.h>
#include <windows.h>
#include <assert.h>
#include "d3dx9.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ライブラリのリンク
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

#define SCREEN_WIDTH (1920)                               //画面の解像度（X方向)
#define SCREEN_HEIGHT (1080)                              //画面の解像度（Y方向）
#define FVF_VERTEX_POINT (D3DFVF_XYZ | D3DFVF_DIFFUSE)    //ライン用
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define NUM_POLYGON (2)
#define NUM_VERTEX (4)
#define CLASS_NAME "AppClass"    // ウインドウのクラス名
#define PRIORITY_MAX (4)         //描画優先度の最大値
#define SAFE_DELETE(p) {if(p != NULL){delete p; p = nullptr;}}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//構造体定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//ライン用
typedef struct
{
    D3DXVECTOR3 pos;    //座標
    D3DCOLOR col;       //頂点カラー

} VERTEX_POINT;

typedef struct
{
    D3DXVECTOR3 pos;    //座標
    float rhw;          //座標変換用係数(1.0f固定)
    D3DCOLOR col;       //頂点カラー
    D3DXVECTOR2 tex;    //テクスチャ座標
} VERTEX_2D;

typedef struct
{
    D3DXVECTOR3 pos;    //座標
    D3DXVECTOR3 nor;    //法線
    D3DCOLOR col;       //頂点カラー
    D3DXVECTOR2 tex;    //テクスチャ座標
} VERTEX_3D;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//プロトタイプ宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

int GetFPS(void);

#endif
