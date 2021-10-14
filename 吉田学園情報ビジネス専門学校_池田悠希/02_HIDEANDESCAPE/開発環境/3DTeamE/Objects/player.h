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
#include "animation.h"
#include "main.h"
#include "manager.h"
#include "model.h"
#include "object.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define START_LIFE (100)
#define ASSAULT_RIFLE_RATE (5)
#define HANDGUN_RATE (5)
#define PLAYER_MODEL_COUNT (16)
#define PLAYER_MOVE_SPEED (1.0f)
#define PLAYER_MOVE_SPEED_SPRINT (1.5f)
#define PLAYER_MOVE_SPEED_AIM (0.75f)
#define PLAYER_MOVE_SPEED_CROUCH (0.5f)
#define COLLISION_RAY_COUNT (16)
#define PLAYER_COLLISION_HEIGHT (5.0f)
#define PLAYER_COLLISION_RADIUS (7.5f)
#define SENSI_RATE (0.01f)
#define START_SENSI (15.0f)
#define GAMEOVER_COUNT (180)
#define MAGAZINE_SIZE_AR (30)
#define MAGAZINE_SIZE_HG (16)
#define MAX_ITEM (5)
#define PLAYER_HEAD_HEIGHT (37.0f)
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�O���錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CAnimation;
class CCrosshair;
class CInputKeyboard;
class CInputMouse;
class CDamage_ui;
class CBullet_ui;
class CItem_ui;
class CWeapons_ui;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CPlayer : public CObject
{
public:
    typedef enum    //�p�[�c
    {
        PARTS_CHEST,             //��
        PARTS_BELLY,             //��
        PARTS_WAIST,             //��
        PARTS_HEAD,              //��
        PARTS_RIGHT_SHOULDER,    //�E��
        PARTS_RIGHT,             //�E�r
        PARTS_RIGHT_HAND,        //�E��
        PARTS_LEFT_SHOULDER,     //����
        PARTS_LEFT,              //���r
        PARTS_LEFT_HAND,         //����
        PARTS_RIGHT_THIGHS,      //�E������
        PARTS_RIGHT_CALF,        //�E�ӂ���͂�
        PARTS_RIGHT_FOOT,        //�E��
        PARTS_LEFT_THIGHS,       //��������
        PARTS_LEFT_CALF,         //���ӂ���͂�
        PARTS_LEFT_FOOT,         //����
        PARTS_MAX
    } PLAYER_PARTS;

    typedef enum
    {
        STATE_STAND = 0,
        STATE_WALK,
        STATE_SPRINT,
        STATE_CROUCH,
        STATE_CROUCH_WALK,
        STATE_AIM,
        STATE_RELOAD,
        STATE_RELOAD_WALK,
        STATE_DEATH,
        STATE_MAX
    } STATE;

    CPlayer();
    ~CPlayer();

    HRESULT Init(void);    //����������
    void Uninit(void);     //�I������
    void Update(void);     //�X�V����
    void Draw(void);       //�`�揈��

    static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);    //��������

    static void Load(void);      //�t�@�C���f�[�^�ǂݍ���
    static void Unload(void);    //�t�@�C���f�[�^�j��

    //�Q�b�^�[�֐�
    D3DXVECTOR3 GetPos(void);
    D3DXVECTOR3 GetPartsPos(int nParts);
    D3DXVECTOR3 GetCenter(void);
    D3DXVECTOR3 GetRot(void);
    STATE GetState(void);
    int GetLife(void);

    void AddLife(int Value);    //���C�t����
    void AddItem(void);         //�A�C�e���ǉ�
private:
    typedef struct
    {
        char* FileName;          //�t�@�C���̖��O
        int nParent;             //�e�p�[�c
        D3DXVECTOR3 Partspos;    //�p�[�c���W
    } PARTS_DATA;

    void PartsUpdate(void);                                                                                //�p�[�c�A�b�v�f�[�g�֐�
    void AnimaControl(void);                                                                               //�A�j���[�V�����R���g���[���֐�
    BOOL CheckHitBullet(CModel::MODELDATA modeldata, BOOL* pHit, float* pDistance, D3DXVECTOR3 spread);    //�e��(���C)�����f���ɓ������ꂢ�邩�ǂ���
    CObject* GetHitObject(void);                                                                           //�e��(���C)���������Ă���I�u�W�F�N�g�擾
    BOOL Collision(CModel::MODELDATA modeldata, D3DXVECTOR3* pHittedPolyNormal, int* pCountHit);           //�ǂƂ̓����蔻��
    void FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvecVertices);               //���b�V�����_���W�擾
    D3DXVECTOR3 CalcWallScratchVector(D3DXVECTOR3 move, D3DXVECTOR3 nomal);                                //�ǐ���x�N�g���v�Z
    float InputToAngle(CInputKeyboard* pInputKey);                                                         //�L�[�{�[�h���͂��p�x�ɕϊ�
    float ChangeMoveSpeed(void);                                                                           //�ړ����x��ύX
    void Move(CInputKeyboard* pInputKey);                                                                  //�ړ�
    void UseItem(CSound* pSound);                                                                          //�A�C�e���g�p
    void BeginReload(CSound* pSound, bool bMove);                                                          //�����[�h�J�n
    void EndReload(CSound* pSound);                                                                        //�����[�h�I��
    void ChangeState(CInputKeyboard* pInputKey, CInputMouse* pInputMou, CSound* pSound, bool bMove);       //�X�e�[�g�ύX
    void Shot(int nBulletDamage, float fSpread, CSound* pSound);                                           //�ˌ�

    D3DXVECTOR3 m_pos;     //�ʒu
    D3DXVECTOR3 m_rot;     //����
    D3DXVECTOR3 m_size;    //�傫��

    int m_nLife;             //���C�t
    int m_nRemainingAmmo;    //�c�e��
    int m_nMagazineSize;     //�ő�e��
    int m_nHaveItem;         //�A�C�e��������

    float m_fMoveVector;           //�ړ�����
    static int m_nFrameCounter;    //�t���[���J�E���^�[
    STATE m_state;                 //���
    static int m_nSensi;           //�}�E�X���x

    static PARTS_DATA m_PartsData[PARTS_MAX];                                  //�p�[�c���
    static char* m_PartsWeapon[CManager::WEAPONS_MODE_MAX];                    //����p�[�c�̏��
    D3DXVECTOR3 m_Partsrot[PARTS_MAX];                                         //�p�[�crot���
    D3DXVECTOR3 m_Partspos[PARTS_MAX];                                         //�p�[�cpos���
    D3DXVECTOR3 m_PartsSize[PARTS_MAX];                                        //�p�[�csize���
    static CAnimation* m_pAnimaSave;                                           //�A�j���[�V�����ۑ��|�C���^
    CAnimation* m_pAnime;                                                      //�A�j���[�V�����|�C���^
    CAnimation::MOTION_PLAYER m_AnimaMotion;                                   //�A�j���[�V�����p�^�[��
    CModel* m_apModelWorld;                                                    //���[���h���W�擾�p���f��
    CModel* m_apModel[PARTS_MAX];                                              //���f���|�C���^
    static CModel::MODELDATA m_modeldata[PARTS_MAX];                           //���f�����
    static CModel::MODELDATA m_modelWeaponData[CManager::WEAPONS_MODE_MAX];    //���f���E�F�|�����
    static D3DXMATERIAL* m_pMat;                                               //�}�e���A�����

    CCrosshair* m_pCrosshair;                     //�N���X�w�A�̃|�C���^
    CDamage_ui* m_pDamageUi;                      //�_���[�WUI�̃|�C���^
    CBullet_ui* m_pBulletUi[MAGAZINE_SIZE_AR];    //�c�e��UI�̃|�C���^
    CItem_ui* m_apItemUI[MAX_ITEM];               //�A�C�e��UI�̃|�C���^
    CWeapons_ui* m_Weapons_UI;                    //����UI�̃|�C���^
};
#endif
