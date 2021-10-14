//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	scene.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//�I�u�W�F�N�g�N���X

class CScene
{
public:
    CScene(int nPriority = 2);
    virtual ~CScene();
    typedef enum
    {
        OBJTYPE_NONE = 0,
        OBJTYPE_PLAYER,
        OBJTYPE_BULLET,
        OBJTYPE_EXPLOSION,
        OBJTYPE_ENEMY,
        OBJTYPE_BG,
        OBJTYPE_SCORE,
        OBJTYPE_LASER,
        OBJTYPE_LIFE,
        OBJTYPE_ENERGY,
        OBJTYPE_MAP_TILE,
        OBJTYPE_MAP_TILE_BRAKABLE,
        OBJTYPE_UI,
        OBJTYPE_ITEM,
        OBJTYPE_MAX
    } OBJTYPE;
    virtual HRESULT Init(void) = 0;    //�������z�֐��Q
    virtual void Uninit(void)  = 0;
    virtual void Update(void)  = 0;
    virtual void Draw(void)    = 0;

    static void UpdateAll(void);    //�S�V�[�������Q
    static void DrawAll(void);
    static void ReleaseAll(void);

    static int GetNumAll(void)
    {
        return m_nNumAll;
    }    //�V�[�����̎擾
    OBJTYPE GetObjType(void);
    void SetObjType(OBJTYPE type);
    static CScene** GetScene(void);

protected:
    void Release(void);    //�V�[���̊J��

private:
    int m_nNumScene;                                      //�V�[���̃C���f�b�N�X�i���o
    static CScene* m_apScene[PRIORITY_MAX][MAX_SCENE];    //�V�[���i�[�p�|�C���^�z��
    static int m_nNumAll;                                 //�V�[���S�̐�
    OBJTYPE m_objType;
    int m_nPriority;
};

#endif
