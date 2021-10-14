//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	polygon.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "polygon.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "scene.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPolygon::CPolygon()
{
    m_pTexture = NULL;                    // �e�N�X�`���ւ̃|�C���^
    m_pVtxBuff = NULL;                    // ���_�o�b�t�@�ւ̃|�C���^
    m_pos      = D3DXVECTOR3(0, 0, 0);    // �|���S���̈ʒu
    m_col      = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPolygon::~CPolygon()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CPolygon::Init(void)
{

    VERTEX_2D* pVtx;
    LPDIRECT3DDEVICE9 pDevice = NULL;
    pDevice                   = CManager::GetRenderer()->GetDevice();

    // ���_�o�b�t�@�̐���
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,    //�o�b�t�@�T�C�Y
                                D3DUSAGE_WRITEONLY,                //�Œ�
                                FVF_VERTEX_2D,                     //���_�t�H�[�}�b�g
                                D3DPOOL_MANAGED,                   //�Œ�
                                &m_pVtxBuff,                       //�ϐ����ɂ���ĕω�
                                NULL);

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���W�ݒ�
    pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, -m_size.y / 2, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2, -m_size.y / 2, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, m_size.y / 2, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2, m_size.y / 2, 0.0f);

    D3DXMATRIX posMatrix;       // ���_�s��
    D3DXMATRIX rotateMatrix;    // ��]�s��
    D3DXVECTOR3 rotationCenter;	//��]�̒��S

    if(m_objtype == CScene::OBJTYPE_LASER)	//���[�U�[�̏ꍇ
    {
        CScene** pScene = CScene::GetScene();
        for(int nCount = 0; nCount <= PRIORITY_MAX * MAX_SCENE; nCount++)
        {
            if(pScene[nCount] != NULL)
            {
                if(pScene[nCount]->GetObjType() == CScene::OBJTYPE_PLAYER)
                {
                    rotationCenter = ((CPlayer*)(pScene[nCount]))->GetPos();	//��]�̒��S���v���C���[�̍��W�ɐݒ�
                    break;
                }
            }
        }
    }
    else
    {
		rotationCenter = m_pos;	//��]�̒��S���|���S���̒��S�ɐݒ�
    }

	//��]�̂��߈�U���_�Ƀ|���S�����ړ�����
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].pos -= rotationCenter;
    }
    // �s��̏������i�P�ʍs�񐶐��j
    D3DXMatrixIdentity(&posMatrix);
    D3DXMatrixIdentity(&rotateMatrix);

    D3DXMatrixRotationZ(&rotateMatrix, m_fRot);

	//���_���W����]������
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        // ���݂̒��_���W���s��Ɋi�[
        D3DXMatrixTranslation(&posMatrix, pVtx[nCount].pos.x, pVtx[nCount].pos.y, pVtx[nCount].pos.z);
        // ���Z
        posMatrix *= rotateMatrix;
        // ���Z���ʂ�߂�
        pVtx[nCount].pos.x = posMatrix._41;    // ���Z���ʂ��|���S���̂w���W�Ɋi�[
        pVtx[nCount].pos.y = posMatrix._42;    // ���Z���ʂ��|���S���̂x���W�Ɋi�[
        pVtx[nCount].pos.z = posMatrix._43;    // ���Z���ʂ��|���S���̂y���W�Ɋi�[
        pVtx[nCount].pos += rotationCenter;
        m_vtxPos[nCount] = pVtx[nCount].pos;
    }
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

    //���_�J���[�̐ݒ�(0�`255)
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
void CPolygon::Uninit(void)
{
    // ���_�o�b�t�@�̔j��
    if(m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPolygon::Update(void)
{
    VERTEX_2D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
    if(m_objtype == CScene::OBJTYPE_LASER)
    {
        pVtx[0].pos = m_pos + D3DXVECTOR3(0, -m_size.y / 2, 0.0f);
        pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x, -m_size.y / 2, 0.0f);
        pVtx[2].pos = m_pos + D3DXVECTOR3(0, m_size.y / 2, 0.0f);
        pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x, m_size.y / 2, 0.0f);
    }
    else
    {
        pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, -m_size.y / 2, 0.0f);
        pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2, -m_size.y / 2, 0.0f);
        pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2, m_size.y / 2, 0.0f);
        pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2, m_size.y / 2, 0.0f);
    }
    D3DXMATRIX posMatrix;       // ���_�s��
    D3DXMATRIX rotateMatrix;    // ��]�s��
    D3DXVECTOR3 rotationCenter;
    rotationCenter = m_pos;
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].pos -= rotationCenter;
    }
    // �s��̏������i�P�ʍs�񐶐��j
    D3DXMatrixIdentity(&posMatrix);
    D3DXMatrixIdentity(&rotateMatrix);

    D3DXMatrixRotationZ(&rotateMatrix, m_fRot);

    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        // ���݂̒��_���W���i�[
        D3DXMatrixTranslation(
          &posMatrix, pVtx[nCount].pos.x, pVtx[nCount].pos.y, pVtx[nCount].pos.z);
        // ���Z
        posMatrix *= rotateMatrix;
        // ���Z���ʂ�߂�
        pVtx[nCount].pos.x = posMatrix._41;    // ���Z���ʂ��|���S���̂w���W�Ɋi�[
        pVtx[nCount].pos.y = posMatrix._42;    // ���Z���ʂ��|���S���̂x���W�Ɋi�[
        pVtx[nCount].pos.z = posMatrix._43;    // ���Z���ʂ��|���S���̂y���W�Ɋi�[
        pVtx[nCount].pos += rotationCenter;
        m_vtxPos[nCount] = pVtx[nCount].pos;
    }

	//�|���S���J���[�ݒ�
    pVtx[0].col = m_col;
    pVtx[1].col = m_col;
    pVtx[2].col = m_col;
    pVtx[3].col = m_col;

    m_pVtxBuff->Unlock();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPolygon::Draw(void)
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
CPolygon* CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRot, CScene::OBJTYPE objtype)
{
	CPolygon* pPolygon = new CPolygon();
	//�e��ϐ�������
	pPolygon->m_pos = pos;
	pPolygon->m_size = size;
	pPolygon->m_fRot = fRot;
	pPolygon->m_objtype = objtype;
	//�������֐�
	pPolygon->Init();

	return pPolygon;
}


//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Z�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPolygon::SetPos(D3DXVECTOR3 pos)
{
    m_pos = pos;
}

void CPolygon::SetCol(D3DXCOLOR col)
{
    m_col = col;
}

void CPolygon::SetRot(float fRot)
{
	m_fRot = fRot;
}

void CPolygon::SetObjType(CScene::OBJTYPE objtype)
{
	m_objtype = objtype;
}

void CPolygon::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

void CPolygon::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

void CPolygon::SetTexPos(D3DXVECTOR2* pTexPos)
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
D3DXVECTOR3 CPolygon::GetPos(void)
{
	return m_pos;
}

D3DXVECTOR3 CPolygon::GetVtxPos(int nIndex)
{
    return m_vtxPos[nIndex];
}