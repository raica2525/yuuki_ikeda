//=============================================================================
//
// ��@�@ [uav.h]
// Author : ��K������
//
//=============================================================================
#ifndef _UAV_H_
#define _UAV_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "enemy.h"
#include "model.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CUav :public CEnemy
{
public:
	typedef enum
	{
		STATE_NONE = -1,
		STATE_MOVE,
		STATE_MAX
	}STATE;
	CUav();
	 ~CUav();
	static HRESULT Load(void);
	static void Unload(void);
	static CUav* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool EnemyCall(void);
private:
	static CModel::MODELDATA m_modeldata;
	static D3DXMATERIAL *m_pMat;
	CModel* m_pModel;
	int m_nLife;		//���C�t
	float m_fSpeed;		//�X�s�[�h
	bool m_bSearch;		//�{���Ă邩�ǂ���
	int nWaryCoutn;		//�x���J�E���g
	bool m_bWary;		//?
	bool m_bDiscovery;	//!
	int m_nFly;			//��ԃJ�E���g

	bool bCall;			//���������Ƃ��G���Ăяo������
};
#endif