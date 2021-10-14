//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	player.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _PLAYER_H_
#define _PLAYER_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene2d.h"
#include "laser.h"
class CLife;
class CEnergy;
class CNumber;
class CCursol;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CPlayer : public CScene2d
{
public:
    CPlayer();     //�R���X�g���N�^
    ~CPlayer();    //�f�X�g���N�^

    HRESULT Init(void);    //����������
    void Uninit(void);     //�I������
    void Update(void);     //�X�V����
    void Draw(void);       //�`�揈��
    static HRESULT Load(void);
    static void Unload(void);
    void HitBullet(void);
    static void Create(D3DXVECTOR3 pos);    //�|���S����������
    void SetOverHeat(bool bOverHeat);
    CLife* GetLife(void);

private:
	int InputToAngle(void);
	D3DXVECTOR3 Move(void);
	bool OutOfScreen(void);
	void CollisionTile(D3DXVECTOR3* pWorldPos);
	void ShotLaser(void);
	int CheckSide(D3DXVECTOR3* pObjVtx);
	void ChangeLaserType(void);

    CPolygon* m_pPolygon;
    CNumber* m_CountNumber;
    int m_nMoveVector;
    CLife* m_pLife;
    CEnergy* m_pEnergy;
    static LPDIRECT3DTEXTURE9 m_pTexture;    // �e�N�X�`���ւ̃|�C���^
    static LPDIRECT3DTEXTURE9 m_pTextureUI;
    int m_nStateCount;
    bool m_bOverHeat;
    D3DXVECTOR3 m_posOld;
    CLaser::LASERTYPE m_LaserType;
    int m_nCountFrame;
    CCursol* m_pCursol;
};

#endif
