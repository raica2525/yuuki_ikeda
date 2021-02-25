//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	scene.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//オブジェクトクラス

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
    virtual HRESULT Init(void) = 0;    //純粋仮想関数群
    virtual void Uninit(void)  = 0;
    virtual void Update(void)  = 0;
    virtual void Draw(void)    = 0;

    static void UpdateAll(void);    //全シーン処理群
    static void DrawAll(void);
    static void ReleaseAll(void);

    static int GetNumAll(void)
    {
        return m_nNumAll;
    }    //シーン数の取得
    OBJTYPE GetObjType(void);
    void SetObjType(OBJTYPE type);
    static CScene** GetScene(void);

protected:
    void Release(void);    //シーンの開放

private:
    int m_nNumScene;                                      //シーンのインデックスナンバ
    static CScene* m_apScene[PRIORITY_MAX][MAX_SCENE];    //シーン格納用ポインタ配列
    static int m_nNumAll;                                 //シーン全体数
    OBJTYPE m_objType;
    int m_nPriority;
};

#endif
