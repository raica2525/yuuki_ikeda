//=============================================================================
//
// メイン処理 [main.h]
// Author :
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION (0x0800)
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************

#include <windows.h>
#include <dinput.h>
#include "d3dx9.h"
#include <time.h>
#include <crtdbg.h>

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")    //システム時刻取得
#pragma comment(lib, "dinput8.lib")
//*****************************************************************************
// マクロ定義
//*****************************************************************************

// メモリリーク
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define CLASS_NAME "AppClass"    // ウインドウのクラス名
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SCREEN_WIDTH (1600)                //画面の解像度（X方向)
#define SCREEN_HEIGHT (900)                //画面の解像度（Y方向）
#define NUM_POLYGON (2)                    // 1つのプリミティブに含まれるポリゴンの数
#define NUM_VERTEX (4)                     // 1つのプリミティブに含まれる頂点の数
#define MAX_SCENE (1024)                   //オブジェクトの最大数
#define PLAYER_SIZE_X (75.0f)              //プレイヤーの大きさ(X方向）
#define PLAYER_SIZE_Y (75.0f)              //プレイヤーの大きさ(Y方向)
#define BULLET_SIZE_X (20.0f)              //敵の弾の大きさ（X方向）
#define BULLET_SIZE_Y (20.0f)              //敵の弾の大きさ（Y方向）
#define PLAYER_MOVE_RATE (5.0f)            //プレイヤーの移動速度（通常時）
#define PLAYER_MOVE_RATE_SPRINT (10.0f)    //プレイヤーの移動速度（高速移動時）
#define EXPLOSION_LIFE (1)                 //爆発の持続時間
#define NUM_BG_LAYER (4)                   //背景のレイヤー数
#define ENEMY_SIZE (100.0f)                //敵の大きさ
#define ENEMY_LIFE (150)                   //敵のライフ
#define DIGIT_SCORE (8)                    //スコア表示桁数
#define SCORE_SIZE_X (50.0f)               //スコアの数字の大きさ（X方向）
#define SCORE_SIZE_Y (100.0f)              //スコアの数字の大きさ（Y方向）
#define NUM_GAUGE_LAYER (3)                //ゲージのUIのレイヤー数
#define EXPLOSION_SIZE (50.0f)             //爆発の大きさ
#define LASER_WIDTH (30)                   //レーザーの太さ
#define PRIORITY_MAX (5)                   //描画優先度のい最大数
#define START_LIFE (100)                   //プレイヤーの初期ライフ
#define MAX_ENERGY (400)                   //エネルギーの最大値
#define BULLET_SPEED (10.0f)               //弾丸の速度
#define SHOT_CYCLE (180)                   //敵が弾を撃つ間隔
#define FADE_RATE (0.02f)                  //フェードのレート
#define UI_BAR_LENGTH (500.0f)             // UIのゲージの長さ
#define UI_BAR_HEIGHT (150.f)              // UIのゲージの高さ
#define MAP_TILE_SIZE (90.0f)              //マップタイル1つ分の大きさ
#define MAX_MAP_WIDTH (1024)               //マップの横幅の最大値
#define MAX_MAP_HEIGHT (128)               //マップの縦幅の最大値
#define LOST_FLAME (240)                   //画面外に出た時のゲームオーバーになるまでの時間
#define MAX_RANKING (10)                   //ランキングの数
#define ITEM_SIZE (50)                     //アイテムの大きさ
#define CURSOL_SIZE (75)                   //自由標準モードのカーソルの大きさ
#define ENEMY_SPAWN_CYCLE (60)             //クリア後の無限湧きの間隔
//*****************************************************************************
// 構造体定義
//*****************************************************************************

typedef struct
{
    D3DXVECTOR3 pos;    //頂点数
    float rhw;          //座標変換用係数(1.0f固定)
    D3DCOLOR col;       //頂点カラー
    D3DXVECTOR2 tex;    //テクスチャ座標
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
