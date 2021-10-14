//=============================================================================
//
// ���C������ [main.h]
// Author :
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION (0x0800)
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************

#include <windows.h>
#include <dinput.h>
#include "d3dx9.h"
#include <time.h>
#include <crtdbg.h>

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")    //�V�X�e�������擾
#pragma comment(lib, "dinput8.lib")
//*****************************************************************************
// �}�N����`
//*****************************************************************************

// ���������[�N
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define CLASS_NAME "AppClass"    // �E�C���h�E�̃N���X��
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SCREEN_WIDTH (1600)                //��ʂ̉𑜓x�iX����)
#define SCREEN_HEIGHT (900)                //��ʂ̉𑜓x�iY�����j
#define NUM_POLYGON (2)                    // 1�̃v���~�e�B�u�Ɋ܂܂��|���S���̐�
#define NUM_VERTEX (4)                     // 1�̃v���~�e�B�u�Ɋ܂܂�钸�_�̐�
#define MAX_SCENE (1024)                   //�I�u�W�F�N�g�̍ő吔
#define PLAYER_SIZE_X (75.0f)              //�v���C���[�̑傫��(X�����j
#define PLAYER_SIZE_Y (75.0f)              //�v���C���[�̑傫��(Y����)
#define BULLET_SIZE_X (20.0f)              //�G�̒e�̑傫���iX�����j
#define BULLET_SIZE_Y (20.0f)              //�G�̒e�̑傫���iY�����j
#define PLAYER_MOVE_RATE (5.0f)            //�v���C���[�̈ړ����x�i�ʏ펞�j
#define PLAYER_MOVE_RATE_SPRINT (10.0f)    //�v���C���[�̈ړ����x�i�����ړ����j
#define EXPLOSION_LIFE (1)                 //�����̎�������
#define NUM_BG_LAYER (4)                   //�w�i�̃��C���[��
#define ENEMY_SIZE (100.0f)                //�G�̑傫��
#define ENEMY_LIFE (150)                   //�G�̃��C�t
#define DIGIT_SCORE (8)                    //�X�R�A�\������
#define SCORE_SIZE_X (50.0f)               //�X�R�A�̐����̑傫���iX�����j
#define SCORE_SIZE_Y (100.0f)              //�X�R�A�̐����̑傫���iY�����j
#define NUM_GAUGE_LAYER (3)                //�Q�[�W��UI�̃��C���[��
#define EXPLOSION_SIZE (50.0f)             //�����̑傫��
#define LASER_WIDTH (30)                   //���[�U�[�̑���
#define PRIORITY_MAX (5)                   //�`��D��x�̂��ő吔
#define START_LIFE (100)                   //�v���C���[�̏������C�t
#define MAX_ENERGY (400)                   //�G�l���M�[�̍ő�l
#define BULLET_SPEED (10.0f)               //�e�ۂ̑��x
#define SHOT_CYCLE (180)                   //�G���e�����Ԋu
#define FADE_RATE (0.02f)                  //�t�F�[�h�̃��[�g
#define UI_BAR_LENGTH (500.0f)             // UI�̃Q�[�W�̒���
#define UI_BAR_HEIGHT (150.f)              // UI�̃Q�[�W�̍���
#define MAP_TILE_SIZE (90.0f)              //�}�b�v�^�C��1���̑傫��
#define MAX_MAP_WIDTH (1024)               //�}�b�v�̉����̍ő�l
#define MAX_MAP_HEIGHT (128)               //�}�b�v�̏c���̍ő�l
#define LOST_FLAME (240)                   //��ʊO�ɏo�����̃Q�[���I�[�o�[�ɂȂ�܂ł̎���
#define MAX_RANKING (10)                   //�����L���O�̐�
#define ITEM_SIZE (50)                     //�A�C�e���̑傫��
#define CURSOL_SIZE (75)                   //���R�W�����[�h�̃J�[�\���̑傫��
#define ENEMY_SPAWN_CYCLE (60)             //�N���A��̖����N���̊Ԋu
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

typedef struct
{
    D3DXVECTOR3 pos;    //���_��
    float rhw;          //���W�ϊ��p�W��(1.0f�Œ�)
    D3DCOLOR col;       //���_�J���[
    D3DXVECTOR2 tex;    //�e�N�X�`�����W
} VERTEX_2D;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CManager;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�v���g�^�C�v�錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifdef _DEBUG
int GetFPS(void);
#endif

#endif
