//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	map.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

#ifndef _MAP_H_
#define _MAP_H_
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "main.h"
#include "scene.h"

class CScene2d;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CMap : public CScene
{
public:
    CMap();     //�R���X�g���N�^
    ~CMap();    //�f�X�g���N�^

    typedef enum
    {
        TILE_TYPE_NONE = 0,
        TILE_TYPE_BLOCK,
        TILE_TYPE_BRAKABLE_BLOCK,
        TILE_TYPE_ENEMY_CANON_UP,
        TILE_TYPE_ENEMY_CANON_DOWN,
        TILE_TYPE_ENEMY_SPLINKLER,
        TILE_TYPE_ENEMY,
        TILE_TYPE_MAX
    } TILE_TYPE;

    static HRESULT Load(void);
    static void Unload(void);
    static CMap* Create();    //�|���S����������

    HRESULT Init();       //����������
    void Uninit(void);    //�I������
    void Update(void);    //�X�V����
    void Draw(void);      //�`�揈��
    static int GetLength(void);
    static void SetGoal(bool bGoal);
    static bool GetGoal(void);

private:
    CScene2d* m_apScene2d[MAX_MAP_HEIGHT * MAX_MAP_WIDTH];
    static LPDIRECT3DTEXTURE9 m_apTexture[TILE_TYPE_MAX];    // �e�N�X�`���ւ̃|�C���^
    TILE_TYPE m_mapData[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
    static D3DXVECTOR2 m_mapSize;
    static bool m_bGoal;
};

#endif
