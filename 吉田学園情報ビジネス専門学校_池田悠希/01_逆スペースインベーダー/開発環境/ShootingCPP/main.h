//=============================================================================
//
// メイン処理 [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define DIRECTINPUT_VERSION (0x0800)
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************

#include <windows.h>
#include <dinput.h>
#include "d3dx9.h"
#include <time.h>

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")//システム時刻取得
#pragma comment(lib, "dinput8.lib")
//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define CLASS_NAME		"AppClass"			// ウインドウのクラス名
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define SCREEN_WIDTH (1600.0f) //画面の解像度（X方向)
#define SCREEN_HEIGHT (900.0f)	//画面の解像度（Y方向）
#define NUM_POLYGON		(2)
#define NUM_VERTEX		(4)
#define MAX_SCENE		(1024)
#define PLAYER_SIZE_X	(75.0f)
#define PLAYER_SIZE_Y	(75.0f)
#define BULLET_SIZE_X		(10.0f)
#define BULLET_SIZE_Y		(10.0f)
#define PLAYER_MOVE_RATE (5.0f)
#define PLAYER_MOVE_RATE_SPRINT	(10.0f)
#define EXPLOSION_LIFE	(1)
#define NUM_BG_LAYER	(4)
#define ENEMY_SIZE		(100.0f)
#define ENEMY_LIFE		(150)
#define DIGIT_SCORE		(8)
#define SCORE_SIZE_X	(50.0f)
#define SCORE_SIZE_Y	(100.0f)
#define NUM_GAUGE_LAYER	(3)
#define EXPLOSION_SIZE	(50.0f)
#define LASER_WIDTH		(30.0f)
#define PRIORITY_MAX	(5)
#define START_LIFE		(100)
#define MAX_ENERGY		(400.0f)
#define BULLET_SPEED	(10.0f)
#define SHOT_CYCLE		(180)
#define FADE_RATE		(0.02f)
#define UI_BAR_LENGTH	(500.0f)
#define UI_BAR_HEIGHT	(150.f)
#define MAP_TILE_SIZE	(90.0f)
#define MAX_MAP_WIDTH	(1024)
#define MAX_MAP_HEIGHT	(128)
#define TIME_SCREENOVER (240)
#define MAX_RANKING		(10)
#define ITEM_SIZE		(50)
#define CURSOL_SIZE		(75)
#define ENEMY_SPAWN_CYCLE (60)
//*****************************************************************************
// 構造体定義
//*****************************************************************************

typedef struct 
{
	D3DXVECTOR3 pos;//頂点数
	float rhw;//座標変換用係数(1.0f固定)
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
} VERTEX_2D;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CManager;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//プロトタイプ宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifdef _DEBUG
int GetFPS(void);
#endif

#endif
