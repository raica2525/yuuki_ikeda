//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	scene2d.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "object2d.h"

#include "input.h"
#include "inputkeyboard.h"
#include "manager.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
    //�e��ϐ�������
    m_pTexture = NULL;
    m_pVtxBuff = NULL;
    m_pos      = ZEROVECTOR3;
    m_move     = ZEROVECTOR3;
    m_fRot     = 0.0f;
    m_col      = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CObject2D::~CObject2D()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CObject2D::Init(void)
{
    VERTEX_2D* pVtx;
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //���_�o�b�t�@�̐���
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //���_����ݒ�
    pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

    //�e�N�X�`�����W�̐ݒ�
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

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
void CObject2D::Uninit(void)
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
void CObject2D::Update(void)
{
    D3DXMATRIX mtxTrans;
    D3DXMATRIX mtxRot;
    VERTEX_2D* pVtx;

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //���_���W�X�V
    pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

    //���_�J���[�X�V
    pVtx[0].col = m_col;
    pVtx[1].col = m_col;
    pVtx[2].col = m_col;
    pVtx[3].col = m_col;

    m_pVtxBuff->Unlock();

    //��]�s�񐶐�
    D3DXMatrixRotationZ(&mtxRot, D3DXToRadian(m_fRot));
    //���s�ړ��s�񐶐�
    D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        //��]�s��ŕϊ�
        D3DXVec3TransformCoord(&(pVtx[nCount].pos), &(pVtx[nCount].pos), &mtxRot);
        //�ړ�
        D3DXVec3TransformCoord(&(pVtx[nCount].pos), &(pVtx[nCount].pos), &mtxTrans);
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CObject2D::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    //�e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, m_pTexture);

    //�|���S���̕`��
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CObject2D::SetPos(const D3DXVECTOR3 pos)
{
    m_pos = pos;
}

void CObject2D::SetMove(const D3DXVECTOR3 move)
{
    m_move = move;
}

void CObject2D::SetSize(const D3DXVECTOR3 size)
{
    m_size = size;
}

void CObject2D::SetRot(const float rot)
{
    m_fRot = rot;
}

void CObject2D::SetTexPos(D3DXVECTOR2* const pTexPos)
{
    VERTEX_2D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].tex = *(pTexPos + nCount);
    }
    m_pVtxBuff->Unlock();
}

void CObject2D::SetCol(const D3DCOLOR col)
{
    m_col = col;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
D3DXVECTOR3 CObject2D::GetMove(void)
{
    return m_move;
}

D3DXVECTOR3 CObject2D::GetPos(void)
{
    return m_pos;
}

D3DXVECTOR3 CObject2D::GetSize(void)
{
    return m_size;
}
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//��������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority)
{
    CObject2D* pScene2d = new CObject2D(nPriority);
    pScene2d->m_pos     = pos;
    pScene2d->m_size    = size;
    pScene2d->Init();

    return pScene2d;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`���̊���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
    m_pTexture = pTexture;
}
