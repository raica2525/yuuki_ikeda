//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	polygon3d.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "polygon3d.h"

#include "manager.h"
#include "renderer.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPolygon3D::CPolygon3D()
{
    m_pTexture = NULL;
    m_pVtxBuff = NULL;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPolygon3D::~CPolygon3D()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�������֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CPolygon3D::Init(void)
{
    //���_�o�b�t�@����
    CManager::GetRenderer()->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
    VERTEX_3D* pVtx  = NULL;
    D3DXVECTOR3 size = GetSize();
    //�e���񏉊���
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    pVtx[0].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(size.x, -size.y, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(-size.x, size.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(size.x, size.y, 0.0f);

    pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
    m_pVtxBuff->Unlock();
    CObject3D::Init();
    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPolygon3D::Uninit(void)
{
    if(m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
    CObject3D::Uninit();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPolygon3D::Update(void)
{
    VERTEX_3D* pVtx  = NULL;
    D3DXVECTOR3 size = GetSize();
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size.x, -size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x, size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size.x, size.y, 0.0f);

    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
    m_pVtxBuff->Unlock();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPolygon3D::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
   
   
    
    //�A���t�@�e�X�g�L��
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    //�A���t�@�e�X�g��l�̐ݒ�
    pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
    //�A���t�@�e�X�g�̔�r���@�̐ݒ�
    pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;
    D3DXMatrixIdentity(&mtxWorld);

	D3DXVECTOR3 rot = GetRot();
    D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(rot.y), D3DXToRadian(rot.x), D3DXToRadian(rot.z));
    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	D3DXVECTOR3 pos = GetPos();
    D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

    D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
    pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	D3DMATERIAL9 matDef;
    ZeroMemory(&matDef, sizeof(matDef));
    matDef.Ambient = D3DXCOLOR(1, 1, 1, 0.5);
    pDevice->SetMaterial(&matDef);
    pDevice->SetTexture(0, m_pTexture);
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
    pDevice->SetFVF(FVF_VERTEX_3D);
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    pDevice->SetTexture(0, NULL);
    ZeroMemory(&matDef, sizeof(matDef));
    pDevice->SetMaterial(&matDef);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�����֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CPolygon3D* CPolygon3D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
    CPolygon3D* pPolygon3D = new CPolygon3D;
    pPolygon3D->SetPos(pos);
    pPolygon3D->SetRot(rot);
    pPolygon3D->SetSize(size);
    pPolygon3D->Init();
    return pPolygon3D;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�e�N�X�`���̊���
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CPolygon3D::BindTexture(const LPDIRECT3DTEXTURE9 pTexture)
{
    m_pTexture = pTexture;
}
