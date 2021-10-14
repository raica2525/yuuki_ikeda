//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	main.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _MAIN_H_
#define _MAIN_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
// DirectInput�̃o�[�W�����ݒ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define DIRECTINPUT_VERSION (0x0800)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include <dinput.h>
#include <time.h>
#include <windows.h>
#include <assert.h>
#include "d3dx9.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���C�u�����̃����N
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#define SCREEN_WIDTH (1920)                               //��ʂ̉𑜓x�iX����)
#define SCREEN_HEIGHT (1080)                              //��ʂ̉𑜓x�iY�����j
#define FVF_VERTEX_POINT (D3DFVF_XYZ | D3DFVF_DIFFUSE)    //���C���p
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define NUM_POLYGON (2)
#define NUM_VERTEX (4)
#define CLASS_NAME "AppClass"    // �E�C���h�E�̃N���X��
#define PRIORITY_MAX (4)         //�`��D��x�̍ő�l
#define SAFE_DELETE(p) {if(p != NULL){delete p; p = nullptr;}}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�\���̒�`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//���C���p
typedef struct
{
    D3DXVECTOR3 pos;    //���W
    D3DCOLOR col;       //���_�J���[

} VERTEX_POINT;

typedef struct
{
    D3DXVECTOR3 pos;    //���W
    float rhw;          //���W�ϊ��p�W��(1.0f�Œ�)
    D3DCOLOR col;       //���_�J���[
    D3DXVECTOR2 tex;    //�e�N�X�`�����W
} VERTEX_2D;

typedef struct
{
    D3DXVECTOR3 pos;    //���W
    D3DXVECTOR3 nor;    //�@��
    D3DCOLOR col;       //���_�J���[
    D3DXVECTOR2 tex;    //�e�N�X�`�����W
} VERTEX_3D;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�v���g�^�C�v�錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

int GetFPS(void);

#endif
