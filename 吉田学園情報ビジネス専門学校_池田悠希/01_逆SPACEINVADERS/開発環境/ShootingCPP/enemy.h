//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	enemy.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _ENEMY_H_
#define _ENEMY_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene2d.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CEnemy : public CScene2d
{
public:
    CEnemy();     //�R���X�g���N�^
    ~CEnemy();    //�f�X�g���N�^
    typedef enum
    {
        TYPE_NORMAL = 0,
        TYPE_SPRINKLER,
        TYPE_CANON_UP,
        TYPE_CANON_DOWN,
        TYPE_MAX
    } TYPE;
    typedef enum
    {
        STATE_NORMAL = 0,
        STATE_DAMAGE,
        STATE_MAX
    } STATE;

    HRESULT Init(void);    //����������
    void Uninit(void);     //�I������
    void Update(void);     //�X�V����
    void Draw(void);       //�`�揈��

    static HRESULT Load(void);
    static void Unload(void);

    static void Create(D3DXVECTOR3 pos, TYPE type);    //�|���S����������
    void HitLaser(int nDamage);
    STATE GetState(void);

private:
    static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];    // �e�N�X�`���ւ̃|�C���^
    int m_nLife;
    STATE m_state;
    int m_nShotCount;
    TYPE m_type;
    int m_nBulletRot;
};

#endif
