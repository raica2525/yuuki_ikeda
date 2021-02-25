//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	crosshair.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _CROSSHAIR_H_
#define _CROSSHAIR_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "main.h"
#include "object.h"
#include "object2d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define MAX_SPREAD (200)
#define CROSSHAIR_PART_SIZE D3DXVECTOR3(6, 20, 0)

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CCrosshair : public CObject
{
public:
    CCrosshair();
    ~CCrosshair();
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    void AddSpread(float value);
    void SetMinSpread(float minspread);
    float GetSpread(void);
    static void Load(void);
	static void Unload(void);
    static CCrosshair* Create(float minSpread);

private:
    static LPDIRECT3DTEXTURE9 m_pTexture;    // テクスチャへのポインタ
    CObject2D* m_apObject2d[4];
    float m_fspread;
    float m_fminspread;
};

#endif
