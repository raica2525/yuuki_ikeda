//=============================================================================
//
// �d�����@ [heavy_enemy.h]
// Author : �g�c�I�l ��K������
//
//=============================================================================
#ifndef _HEAVY_ENEMY_H_
#define _HEAVY_ENEMY_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "enemy.h"
#include "model.h"
#include "animation.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//*****************************************************************************
//�O���錾
//*****************************************************************************
class CAnimation;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CHeavyEnemy :public CEnemy
{
public:
	//�p�[�c
	typedef enum
	{
		PARTS_NONE = -1,
		PARTS_BODY,
		PARTS_RIGHT_THIGHS,
		PARTS_RIGHT_FOOT,
		PARTS_RIGHT_RIGHT,
		PARTS_LEFT_THIGHS,
		PARTS_LEFT_FOOT,
		PARTS_LEFT_RIGHT,
		PARTS_MAX
	}PARTS;

	//�X�e�[�^�X
	typedef enum
	{
		STATE_NONE = -1,
		STATE_MOVE,
		STATE_MAX
	}STATE;

	CHeavyEnemy();
	~CHeavyEnemy();
	static HRESULT Load(void);
	static void Unload(void);
	static CHeavyEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void PartsUpdate(void);

	typedef struct
	{
		char *FileName;			//�t�@�C���̖��O
		int nParent;			//�e�p�[�c
		D3DXVECTOR3 Partspos;	//�p�[�c���W
	}PARTS_DATA;

	static PARTS_DATA m_PartsData[PARTS_MAX];	//�p�[�c���
	D3DXVECTOR3 m_Partsrot[PARTS_MAX];			//�p�[�crot���
	D3DXVECTOR3 m_Partspos[PARTS_MAX];			//�p�[�cpos���
	static CAnimation *m_pAnimaSave;			//�A�j���[�V�����ۑ��|�C���^
	CAnimation *m_pAnime;						//�A�j���[�V�����|�C���^
	CAnimation::MOTION_HEAVY_ENEMY m_AnimaMotion;	//���[�V�����Z�b�g

	static CModel::MODELDATA m_modeldata[PARTS_MAX];	//���f���f�[�^
	CModel* m_apModel[PARTS_MAX];

	int m_nLife;		//���C�t
	float m_fSpeed;		//�X�s�[�h
	bool m_bSearch;		//�{���Ă邩�ǂ���
	int nWaryCoutn;		//�x���J�E���g
	bool m_bWary;		//?
	bool m_bDiscovery;	//!
};
#endif