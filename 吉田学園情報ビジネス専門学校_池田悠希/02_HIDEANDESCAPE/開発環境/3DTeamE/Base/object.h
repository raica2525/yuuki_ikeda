//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	object.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _SCENE_H_
#define _SCENE_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CObject
{
public:
    typedef enum
    {
        OBJTYPE_NONE = 0,
        OBJTYPE_PLAYER,
        OBJTYPE_ENEMY,
        OBJTYPE_MODEL,
        OBJTYPE_OBSTACLE,
        OBJTYPE_STAGE
    } OBJTYPE;

    CObject(int nPriority = 0);
    virtual ~CObject();

    virtual HRESULT Init(void) = 0;    //�������z�֐��Q
    virtual void Uninit(void)  = 0;
    virtual void Update(void)  = 0;
    virtual void Draw(void)    = 0;

    static void UpdateAll(void);    //�S�V�[�������Q
    static void DrawAll(void);
    static void ReleaseAll(void);

    //�Z�b�^�[
    void SetObjType(OBJTYPE type);
    void SetCollisionBullet(bool bHit);

    //�Q�b�^�[
    static CObject** GetTop(void);
    CObject* GetNext(void);
    CObject* GetPrev(void);
    OBJTYPE GetObjType(void);
    bool GetCollisionBullet(void);

protected:
    void Release(void);    //�V�[���̊J��

private:
    void Death(void);    //�V�[���폜

    static CObject* m_pTop[PRIORITY_MAX];    //�e�`��D��x�̍ŏ��̗v�f
    static CObject* m_pCur[PRIORITY_MAX];    //�e�`��D��x�̍Ō�̗v�f
    CObject* m_pPrev;                        //�O�̃I�u�W�F�N�g
    CObject* m_pNext;                        //���̃I�u�W�F�N�g
    int m_nPriority;                         //�D��x
    bool m_bDestroy;                         //���S�t���O
    OBJTYPE m_objType;                       //�I�u�W�F�N�g�^�C�v
    bool bCollisionBullet;                   //�e�ۂɓ����邩
};

#endif
