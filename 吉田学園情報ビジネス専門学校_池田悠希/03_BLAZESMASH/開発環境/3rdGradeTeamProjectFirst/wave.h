//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	wave.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _WAVE_H_
#define _WAVE_H_
#include "main.h"
#include "scene.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CWave : public CScene
{
public:

	enum POLYTYPE
	{
		POLYTYPE_STENCIL = 0,
		POLYTYPE_REAL,
		POLYTYPE_MAX
	};

    CWave();
    ~CWave();

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    static CWave* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
    void CreateStencil(void);

    D3DXVECTOR3 m_pos;
    D3DXVECTOR3 m_size;
    LPDIRECT3DTEXTURE9		m_pTexture;
    LPDIRECT3DVERTEXBUFFER9 m_apVtxBuff[2];
};
#endif