//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	countdown.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "object2d.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define TIME_SIZE_X (200.0f)
#define TIME_SIZE_Y (100.0f)
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CNumber;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

class CCountDown :public CObject
{
public:
	CCountDown();
	~CCountDown();
	static HRESULT Load(void);
	static void Unload(void);
	static CCountDown * Create(int nLimitTime,D3DXVECTOR3 pos,D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	int m_nTimeLimit;
	int m_nElapsedTime;
	int m_nSoundCount;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DCOLOR m_col;
	CNumber* m_apNumber[5];
	CObject2D* m_pObject2d;

};
#endif