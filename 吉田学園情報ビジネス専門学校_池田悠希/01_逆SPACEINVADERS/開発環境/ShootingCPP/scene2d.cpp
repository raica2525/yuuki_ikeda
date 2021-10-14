//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	scene2d.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "inputkeyboard.h"
#include "map.h"
#include "score.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
    m_pTexture = NULL;    // �e�N�X�`���ւ̃|�C���^
    m_pVtxBuff = NULL;    // ���_�o�b�t�@�ւ̃|�C���^
    m_fScroll  = 0;
    m_pos      = D3DXVECTOR3(0, 0, 0);    // �|���S���̈ʒu
    m_col      = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CScene2d::~CScene2d()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CScene2d::Init(void)
{
    VERTEX_2D* pVtx;
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // ���_�o�b�t�@�̐���
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,    //�o�b�t�@�T�C�Y
                                D3DUSAGE_WRITEONLY,                //�Œ�
                                FVF_VERTEX_2D,                     //���_�t�H�[�}�b�g
                                D3DPOOL_MANAGED,                   //�Œ�
                                &m_pVtxBuff,                       //�ϐ����ɂ���ĕω�
                                NULL);

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
    // ���_����ݒ�

    //�e�N�X�`�����W�̐ݒ�
    pVtx[0].tex = D3DXVECTOR2(0, 0);
    pVtx[1].tex = D3DXVECTOR2(1, 0);
    pVtx[2].tex = D3DXVECTOR2(0, 1);
    pVtx[3].tex = D3DXVECTOR2(1, 1);

    // rhw�̐ݒ�
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //���_�J���[�̐ݒ�
    pVtx[0].col = m_col;  
    pVtx[1].col = m_col;  
    pVtx[2].col = m_col;  
    pVtx[3].col = m_col;  
    m_pVtxBuff->Unlock();

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CScene2d::Uninit(void)
{
    // ���_�o�b�t�@�̔j��
    if(m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }

    Release();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CScene2d::Update(void)
{
    VERTEX_2D* pVtx;
    //�X�N���[��
    if(SCREEN_WIDTH + m_fScroll < CMap::GetLength() * MAP_TILE_SIZE)
    {
        if(CScene::GetObjType() == OBJTYPE_BG || CScene::GetObjType() == OBJTYPE_PLAYER)
        {
            m_worldPos.x += 2;
        }
        m_fScroll += 2;
        m_pos.x = m_worldPos.x - m_fScroll;
    }
    else if(CManager::GetAlive())
    {
        CMap::SetGoal(true);
    }

    m_pos.y = m_worldPos.y;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, -m_size.y / 2, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2, -m_size.y / 2, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, m_size.y / 2, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2, m_size.y / 2, 0.0f);

    pVtx[0].col = m_col;
    pVtx[1].col = m_col;
    pVtx[2].col = m_col;
    pVtx[3].col = m_col;

    m_pVtxBuff->Unlock();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CScene2d::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = NULL;
    pDevice                   = CManager::GetRenderer()->GetDevice();
    // ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

    // ���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    // �e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, m_pTexture);

    // �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CScene2d* CScene2d::Create(int nPriority)
{
	CScene2d* pScene2d = new CScene2d(nPriority);
	pScene2d->Init();
	return pScene2d;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CScene2d::SetPos(D3DXVECTOR3 pos)
{
    m_pos      = pos;    // m_pos��ݒ�
    m_worldPos = pos + D3DXVECTOR3(m_fScroll, 0, 0);
}

void CScene2d::SetWorldPos(D3DXVECTOR3 pos)
{
    m_worldPos = pos;
    m_pos      = pos - D3DXVECTOR3(m_fScroll, 0, 0);
}

void CScene2d::SetCol(D3DCOLOR col)
{
	m_col = col;
}

void CScene2d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

void CScene2d::SetTexPos(D3DXVECTOR2* pTexPos)
{
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		pVtx[nCount].tex = *(pTexPos + nCount);
	}

	m_pVtxBuff->Unlock();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
D3DXVECTOR3 CScene2d::GetPos(void)
{
    return m_worldPos - D3DXVECTOR3(m_fScroll, 0, 0);
}

D3DXVECTOR3 CScene2d::GetWorldPos(void)
{
    return m_worldPos;
}

D3DCOLOR CScene2d::GetCol(void)
{
    return m_col;
}