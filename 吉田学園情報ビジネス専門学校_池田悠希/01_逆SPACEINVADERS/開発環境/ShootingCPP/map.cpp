//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	map.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "map.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include <stdio.h>
#include "enemy.h"
#include "score.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
LPDIRECT3DTEXTURE9 CMap::m_apTexture[TILE_TYPE_MAX] = {};
D3DXVECTOR2 CMap::m_mapSize                         = D3DXVECTOR2(0, 0);
bool CMap::m_bGoal                                  = false;

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CMap::CMap()
{
    memset(m_apScene2d, NULL, sizeof(m_apScene2d));
    memset(m_mapData, NULL, sizeof(m_mapData));
    m_bGoal = false;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CMap::~CMap()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CMap::Init(void)
{
    FILE* pFile;
    pFile         = fopen("Resources\\map.csv", "r");
    int TileCount = 0;
    if(pFile != NULL)
    {
        for(int nCountY = 0; nCountY < MAX_MAP_HEIGHT; nCountY++)
        {
            char cTile = NULL;
            for(int nCountX = 0; nCountX < MAX_MAP_WIDTH;)
            {
                cTile = fgetc(pFile);
                if(cTile == 0x0a || cTile == EOF)	//�}�b�v�̒����擾
                {
                    if(m_mapSize.x < nCountX)
                    {
                        m_mapSize.x = (float)nCountX;
                    }
                    break;
                }
                else if(cTile != ',')	//�J���}��e��
                {
					int nTile = atoi(&cTile);	//�ǂݍ��񂾕�����𐔎��ɕϊ�
                    m_mapData[nCountY][nCountX] = (TILE_TYPE)nTile;	//�}�b�v�f�[�^�ɑ��
                    switch(nTile)	//�t�@�C������ǂݍ��񂾐����ɂ���ăI�u�W�F�N�g��z�u����
                    {
                        case TILE_TYPE_BLOCK:
                            m_apScene2d[TileCount] = CScene2d::Create(3);
                            m_apScene2d[TileCount]->SetWorldPos(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0));
                            m_apScene2d[TileCount]->SetObjType(OBJTYPE_MAP_TILE);
                            m_apScene2d[TileCount]->SetSize(D3DXVECTOR3(MAP_TILE_SIZE, MAP_TILE_SIZE, 0));
                            m_apScene2d[TileCount]->BindTexture(m_apTexture[0]);
                            break;
                        case TILE_TYPE_BRAKABLE_BLOCK:
                            m_apScene2d[TileCount] = CScene2d::Create(3);
                            m_apScene2d[TileCount]->SetWorldPos(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0));
                            m_apScene2d[TileCount]->SetObjType(OBJTYPE_MAP_TILE_BRAKABLE);
                            m_apScene2d[TileCount]->SetSize(D3DXVECTOR3(MAP_TILE_SIZE, MAP_TILE_SIZE, 0));
                            m_apScene2d[TileCount]->BindTexture(m_apTexture[1]);
                            break;
                        case TILE_TYPE_ENEMY:
                            CEnemy::Create(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0), CEnemy::TYPE_NORMAL);
                            break;
                        case TILE_TYPE_ENEMY_SPLINKLER:
                            CEnemy::Create(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0), CEnemy::TYPE_SPRINKLER);
                            break;
                        case TILE_TYPE_ENEMY_CANON_UP:
                            CEnemy::Create(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0), CEnemy::TYPE_CANON_UP);
                            break;
                        case TILE_TYPE_ENEMY_CANON_DOWN:
                            CEnemy::Create(D3DXVECTOR3((nCountX + 0.5f) * MAP_TILE_SIZE, (nCountY + 0.5f) * MAP_TILE_SIZE, 0), CEnemy::TYPE_CANON_DOWN);
                            break;
                    }
                    nCountX++;
                    TileCount++;
                }
            }
            if(cTile == EOF)
            {
                m_mapSize.y = (float)nCountY;	//�}�b�v�̍������擾
                break;
            }
        }
		fclose(pFile);
    }
    else
    {
		//�G���[����
        MessageBox(FindWindow(CLASS_NAME, NULL), "�}�b�v�f�[�^���ǂݍ��߂܂���", "�ǂݍ��݃G���[", MB_ICONSTOP);
        exit(1);
    }

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CMap::Uninit(void)
{
    for(int nCount = 0; nCount < NUM_BG_LAYER; nCount++)
    {
        m_apScene2d[nCount] = NULL;
    }
    Release();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CMap::Update(void)
{
    CScene** pScene = CScene::GetScene();
    if(m_bGoal && CManager::GetAlive())	//�S�[����ɐ����Ă�����X�R�A�����Z
    {
        for(int nCount = 0; nCount < MAX_SCENE * PRIORITY_MAX; nCount++)
        {
            if((*(pScene + nCount)) != NULL)
            {
                if((*(pScene + nCount))->GetObjType() == OBJTYPE_SCORE)
                {
                    ((CScore*)(*(pScene + nCount)))->AddScore(1);
                }
            }
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CMap::Draw(void)
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CMap* CMap::Create(void)
{
    CMap* pMap = new CMap;
    pMap->Init();
    return pMap;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���ǂݍ��ݏ���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CMap::Load(void)
{
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\Wall.png", &m_apTexture[0]);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\wall_Damaged.png", &m_apTexture[1]);
    D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "Resources\\bg102.png", &m_apTexture[2]);

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ǂݍ��݃f�[�^�j������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CMap::Unload(void)
{
    for(int nCount = 0; nCount < NUM_BG_LAYER; nCount++)
    {
        if(m_apTexture[nCount] != NULL)
        {
            m_apTexture[nCount]->Release();
            m_apTexture[nCount] = NULL;
        }
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�b�v���擾����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
int CMap::GetLength(void)
{
    return (int)m_mapSize.x;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�S�[���������ݒ肷�鏈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CMap::SetGoal(bool bGoal)
{
    m_bGoal = bGoal;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�S�[���������擾���鏈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
bool CMap::GetGoal(void)
{
    return m_bGoal;
}
