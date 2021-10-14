//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	laser.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _LASER_H_
#define _LASER_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene.h"
#include "polygon.h"
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

class CLaserLayer;
class CScene2d;
class CEnemy;
class CScore;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CLaser : public CScene
{
public:
    CLaser();     //�R���X�g���N�^
    ~CLaser();    //�f�X�g���N�^

    typedef enum
    {
        LASERTYPE_STRONG_STRAIGHT = 0,
        LASERTYPE_WEEK_DIAGONAL,
        LASERTYPE_MAX
    } LASERTYPE;

    HRESULT Init(void);    //����������
    void Uninit(void);     //�I������
    void Update(void);     //�X�V����
    void Draw(void);       //�`�揈��

    static void Create(D3DXVECTOR3 pos, D3DCOLOR col, int nWidth, float fRot, int nDamage, bool bPenetrate);    //�|���S����������
	

private:
    bool CheckCollision(D3DXVECTOR3* pObjVtx);	//�����蔻��
	void GetHittedObject(CScene** pScene, CEnemy** apHitEnemy, int* pHitEnemyCount, CEnemy** pClosestEnemy, CScene2d** pClosestTile);	//���[�U�[�����������I�u�W�F�N�g���擾
	void HitTile(CScene2d* pTile, CScore* pScore);	//�^�C���ɂ��������Ƃ��̏���
	void SetLaserSize(D3DXVECTOR3 size);			//�傫���ݒ�
    CPolygon* m_pPolygon;							//���[�U�[�̖{��
    CLaserLayer* m_pLaserLayer;						//���[�U�[�̐F�ύX�p�|���S��
    int m_nDamage;									//���[�U�[�̃_���[�W
    D3DXVECTOR3 m_pos;								//���W
    D3DCOLOR m_col;									//�F
    int m_nWidth;									//����
    float m_fRot;									//�p�x
    bool m_bHit;									//�������Ă��邩
    D3DXVECTOR3 m_vtxPos[NUM_VERTEX];				//���_���W
    bool m_bPenetrate;								//�ђʑ���
};

#endif
