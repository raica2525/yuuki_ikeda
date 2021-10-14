//=============================================================================
//
// �A�j���[�V���� [animation.h]
// Author : ��K���E�g�c
//
//=============================================================================
#ifndef _ANIMATION_H_
#define _ANIMATION_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOTION_KEYSET_MAX		5	//�L�[�Z�b�g�ő吔
#define MODEL_LABEL_MAX			17	//���f���p�[�c�̍ő吔
#define MAX_ANIME				10	//�A�j���V�����̍ő吔
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CAnimation
{
public:
	typedef enum
	{
		ANIMATION_NONE = -1,
		ANIMATION_PLAYER_AR,
		ANIMATION_PLAYER_HG,
		ANIMATION_LIGHT_ENEMY,
		ANIMATION_HEAVY_ENEMY,
		ANIMATION_MAX
	}ANIMATION_TYPE;

	typedef enum
	{
		MOTION_PLAYER_NONE = -1,
		MOTION_PLAYER_NEUTRAL,
		MOTION_PLAYER_MOVE,
		MOTION_PLAYER_CROUCHING,
		MOTION_PLAYER_SPRINT,
		MOTION_PLAYER_AIM,
		MOTION_PLAYER_CROUCHING_MOVE,
		MOTION_PLAYER_RELOAD,
		MOTION_PLAYER_RELOAD_MOVE,
		MOTION_PLAYER_DEATH,
		MOTION_PLAYER_MAX
	}MOTION_PLAYER;

	typedef enum
	{
		MOTION_LIGHT_ENEMY_NONE = -1,
		MOTION_LIGHT_ENEMY_NEUTRAL,
		MOTION_LIGHT_ENEMY_MOVE,
		MOTION_LIGHT_ENEMY_ATTACK,
		MOTION_LIGHT_ENEMY_DEATH,
		MOTION_LIGHT_ENEMY_MAX
	}MOTION_LIGHT_ENEMY;

	typedef enum
	{
		MOTION_HEAVY_ENEMY_NONE = -1,
		MOTION_HEAVY_ENEMY_NEUTRAL,
		MOTION_HEAVY_ENEMY_MOVE,
		MOTION_HEAVY_ENEMY_ATTACK,
		MOTION_HEAVY_ENEMY_DEATH,
		MOTION_HEAVY_ENEMY_MAX
	}MOTION_HEAVY_ENEMY;


	CAnimation(int nPriority = 0);
	~CAnimation();
	static HRESULT Load(void);
	static CAnimation * Create(ANIMATION_TYPE AnimationType);
	HRESULT Init(ANIMATION_TYPE AnimationType);
	void Uninit(void);
	void Update(void);
	static void DataLoad(ANIMATION_TYPE AnimationType);
	void SetAnimation(int PlayerAnima);
	bool GetAnimeEnd(void) { return m_AnimatEnd; }
	int GetAnimation(void) { return m_nCountAnime; };
	D3DXVECTOR3 GetAnimePos(int nParts) { return m_modelData[nParts].pos; }
	D3DXVECTOR3 GetAnimeRot(int nParts) { return m_modelData[nParts].rot; }
	void SetAnimePos(int nParts,D3DXVECTOR3 pos) { m_modelData[nParts].pos = pos; }
	void SetAnimeRot(int nParts,D3DXVECTOR3 rot) { m_modelData[nParts].rot = rot; }
private:

	/*�A�j���[�V�����L�[���*/
	typedef struct
	{
		D3DXVECTOR3		pos;						//�ʒu
		D3DXVECTOR3		rot;						//��]
		D3DXMATRIX		mtxWorldAnime;				//�s��v�Z
	}AnimationKey;
	/*�A�j���[�V�����L�[�Z�b�g���*/
	typedef struct
	{
		int				frame;						//�L�[�t���[����
		AnimationKey	key[MODEL_LABEL_MAX];		//�L�[�Z�b�g�Ɋ܂ރL�[���
	}AnimationKeySet;
	/*�A�j���[�V�������*/
	typedef struct
	{
		bool			isLoop;						//���[�V�������[�v�ݒ�
		int				keyNum;						//�L�[��
		AnimationKeySet keySet[MOTION_KEYSET_MAX];	//�A�j���[�V�����Ɋ܂ރL�[�Z�b�g���
	}Animation;
	typedef struct
	{
		D3DXVECTOR3		pos;						//�ʒu
		D3DXVECTOR3		rot;						//��]
		D3DXVECTOR3		posMove;					//�ʒu
		D3DXVECTOR3		rotMove;					//��]
		D3DXMATRIX		mtxWorldAnime;				//�s��v�Z
	}ModelData;

	ModelData	m_modelData[MODEL_LABEL_MAX];		//�A�j���[�V����������p�[�c�̏��
	static Animation	m_animation[ANIMATION_MAX][MAX_ANIME];				//�A�j���[�V�������
	
	static FILE * m_pFile[ANIMATION_MAX];
	static char * m_pFileName[ANIMATION_MAX];
	int				m_nCountAnime;					//�Đ����̃A�j���[�V����
	int				m_nCountFrame;					//�Đ����̃t���[��
	int				m_nCountKeySet;					//�Đ����̃L�[�Z�b�g
	ANIMATION_TYPE	m_AnimationType;				//�A�j���[�V�����^�C�v
	bool			m_AnimatEnd;					//�A�j�����I�����Ă��邩
};
#endif