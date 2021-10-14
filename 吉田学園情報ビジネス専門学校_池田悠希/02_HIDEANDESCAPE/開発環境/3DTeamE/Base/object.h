//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	object.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _SCENE_H_
#define _SCENE_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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

    virtual HRESULT Init(void) = 0;    //純粋仮想関数群
    virtual void Uninit(void)  = 0;
    virtual void Update(void)  = 0;
    virtual void Draw(void)    = 0;

    static void UpdateAll(void);    //全シーン処理群
    static void DrawAll(void);
    static void ReleaseAll(void);

    //セッター
    void SetObjType(OBJTYPE type);
    void SetCollisionBullet(bool bHit);

    //ゲッター
    static CObject** GetTop(void);
    CObject* GetNext(void);
    CObject* GetPrev(void);
    OBJTYPE GetObjType(void);
    bool GetCollisionBullet(void);

protected:
    void Release(void);    //シーンの開放

private:
    void Death(void);    //シーン削除

    static CObject* m_pTop[PRIORITY_MAX];    //各描画優先度の最初の要素
    static CObject* m_pCur[PRIORITY_MAX];    //各描画優先度の最後の要素
    CObject* m_pPrev;                        //前のオブジェクト
    CObject* m_pNext;                        //次のオブジェクト
    int m_nPriority;                         //優先度
    bool m_bDestroy;                         //死亡フラグ
    OBJTYPE m_objType;                       //オブジェクトタイプ
    bool bCollisionBullet;                   //弾丸に当たるか
};

#endif
