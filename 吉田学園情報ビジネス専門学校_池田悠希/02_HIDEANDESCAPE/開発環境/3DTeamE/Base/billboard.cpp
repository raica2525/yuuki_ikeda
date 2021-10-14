//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "billboard.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"	
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillboard::CBillboard()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_mtxWorld;		//�s��v�Z�p
	m_pos = ZEROVECTOR3;
	m_size = ZEROVECTOR3;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fTexX = 0.0f;
	m_fTexY = 0.0f;
	m_fTexX2 = 0.0f;
	m_fTexY2 = 0.0f;
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CBillboard::~CBillboard()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CBillboard::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̏����� ���ʒu�͍s��Ōv�Z���邽�ߌ��_���S��4���_���`
	pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2, m_size.y / 2, +m_size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(m_size.x / 2, m_size.y / 2, +m_size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2, -m_size.y / 2, +m_size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(m_size.x / 2, -m_size.y / 2, +m_size.z / 2);

	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	//�A�����b�N
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CBillboard::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CBillboard::Update(void)
{
	// ���_����ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2, m_size.y / 2, +m_size.z / 2);
	pVtx[1].pos = D3DXVECTOR3(m_size.x / 2, m_size.y / 2, +m_size.z / 2);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2, -m_size.y / 2, +m_size.z / 2);
	pVtx[3].pos = D3DXVECTOR3(m_size.x / 2, -m_size.y / 2, +m_size.z / 2);

	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`��֐�
//=============================================================================
void CBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans; //�s��v�Z�p�̃}�g���N�X
	D3DMATERIAL9 matDef;

	pDevice->SetTexture(0, m_pTexture);
	//�A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	//�A���t�@�e�X�g�̔�r���@�̐ݒ�iGREATER�͊�l���傫���ꍇ�j
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�̋t�s��
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x,
		m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld,
		&mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//�}�e���A�����
	ZeroMemory(&matDef, sizeof(matDef));
	matDef.Ambient.r = m_col.r;
	matDef.Ambient.g = m_col.g;
	matDef.Ambient.b = m_col.b;
	matDef.Ambient.a = m_col.a;

	pDevice->SetMaterial(&matDef);
	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);   //���l
	pDevice->SetTexture(0, NULL);

	//�A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

}

//=============================================================================
// �ʒu�̐ݒ�֐�
//=============================================================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//=============================================================================
// �g�嗦�̐ݒ�֐�
//=============================================================================
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �e�N�X�`���̊��蓖�Ċ֐�
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// �e�N�X�`���̈ʒu�̐ݒ�֐�
//=============================================================================
void CBillboard::SetTex(float fTexX, float fTexY, float fTexX2, float fTexY2)
{
	m_fTexX = fTexX;
	m_fTexY = fTexY;
	m_fTexX2 = fTexX2;
	m_fTexY2 = fTexY2;
}

//=============================================================================
// �F�̐ݒ�֐�
//=============================================================================
void CBillboard::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
