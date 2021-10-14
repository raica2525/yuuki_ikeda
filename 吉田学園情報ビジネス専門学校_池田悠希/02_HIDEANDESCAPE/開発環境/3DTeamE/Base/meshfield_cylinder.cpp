//=============================================================================
//
// ���b�V���t�B�[���h_�~�� [meshfield_cylinder.h]
// Author : �g�c�I�l
//
//=============================================================================


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "meshfield_cylinder.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"


//*****************************************************************************
//�@�ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshCylinder::CMeshCylinder() : CObject(1)
{
	m_pos = ZEROVECTOR3;
	m_rot = D3DXVECTOR3(90.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	m_col[MESH_Y_BLOCK] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_pTexture = NULL;
	SetObjType(OBJTYPE_NONE);
	for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
	{
		m_bColAnima[nMesh] = false;

	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshCylinder::~CMeshCylinder()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CMeshCylinder::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_3D *pVtx = NULL;
	D3DXVECTOR3 nor;
	//�C���f�b�N�X
	int index = 0;
	//�e�N�X�`�����W
	int texpos = 0;
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_VERTEX_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	for (int vIndex = 0; vIndex < MESH_Y_BLOCK + 1; vIndex++)
	{
		texpos = 0;
		for (int hlndex = 0; hlndex < MESH_X_BLOCK + 1; hlndex++)
		{
			//���W
			float angle = (float)hlndex * 360.0f / (float)MESH_X_BLOCK;
			pVtx[index].pos = D3DXVECTOR3(sinf(D3DXToRadian(-angle))*(m_size.x / 2),
				(-vIndex*(m_size.y / MESH_Y_BLOCK)) + (m_size.y / 2),
				cosf(D3DXToRadian(angle))*(m_size.z / 2));
			//�e���_�̖@���̐ݒ�i�x�N�g���̑傫���͂P�ɂ���K�v������j
			D3DXVec3Normalize(&nor, &m_rot);

			pVtx[index].nor = -m_rot;

			//���_�J���[�̐ݒ�
			pVtx[index].col = m_col[vIndex];
			//�e�N�X�`��
			pVtx[index].tex = D3DXVECTOR2((float)texpos*0.125f,(float)vIndex);
			index += 1;
			texpos += 1;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, NULL, &m_pTexture);
	//�C���f�b�N�X�o�b�t�@�i�|���S���o�b�t�@�j�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_INDEX_NUM, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL);
	WORD*pldx;
	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pldx, 0);
	//�C���f�b�N�X���l�̏�����
	index = 0;
	for (int nyBlockCount = 0; nyBlockCount < MESH_Y_BLOCK; nyBlockCount++)
	{
		for (int nxBlockCount = 0; nxBlockCount < MESH_X_BLOCK + 1; nxBlockCount++)
		{
			//�C���f�b�N�X�ݒ�
			pldx[index] = 9 + (index / 2) - nyBlockCount;
			pldx[index + 1] = (index / 2) - nyBlockCount;
			index += 2;
		}

		//�k�ރ|���S���p�C���f�b�N�X�ݒ�
		if (index < MESH_INDEX_NUM)
		{
			pldx[index] = (index / 2) - (nyBlockCount + 1);
			pldx[index + 1] = (9 + (index / 2)) - nyBlockCount;
			index += 2;
		}
	}
	m_pIdxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CMeshCylinder::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CMeshCylinder::Update(void)
{
	VERTEX_3D *pVtx = NULL;
	int index = 0;
	for (int vIndex = 0; vIndex < MESH_Y_BLOCK + 1; vIndex++)
	{
		for (int hlndex = 0; hlndex < MESH_X_BLOCK + 1; hlndex++)
		{
			//���_�o�b�t�@�̃��b�N
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			//���_�J���[�̐ݒ�
			pVtx[index].col = m_col[vIndex];
			//���_�o�b�t�@�̃A�����b�N
			m_pVtxBuff->Unlock();

			index += 1;
		}
	}

}

//=============================================================================
// �`��֐�
//=============================================================================
void CMeshCylinder::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�s��v�Z�p�̃}�g���N�X
	D3DMATERIAL9 matDef;
	//���[���h�}�g���N�X�̏���������
	D3DXMatrixIdentity(&m_mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(m_rot.y), D3DXToRadian(m_rot.x), D3DXToRadian(m_rot.z));
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	ZeroMemory(&matDef, sizeof(matDef));
	matDef.Ambient = m_col[0];
	pDevice->SetMaterial(&matDef);
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̕`��
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESH_VERTEX_NUM, 0, MESH_PRIMITIVE_NUM);
	//�e�N�X�`���̏�����
	pDevice->SetTexture(0, NULL);
	ZeroMemory(&matDef, sizeof(matDef));
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �Z�b�gpos�֐�
//=============================================================================
void CMeshCylinder::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �Z�b�grot�֐�
//=============================================================================
void CMeshCylinder::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �Z�b�g�T�C�Y�֐�
//=============================================================================
void CMeshCylinder::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �Z�b�g�e�N�X�`���֐�
//=============================================================================
void CMeshCylinder::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// �Z�b�g�J���[�֐�
//=============================================================================
void CMeshCylinder::SetColor(D3DXCOLOR col, int fMeshY)
{
	m_col[fMeshY] = col;
}
//=============================================================================
// �Q�b�g�J���[�֐�
//=============================================================================
D3DXCOLOR CMeshCylinder::GetColor(int fMeshY)
{
	return m_col[fMeshY];
}
//=============================================================================
// �ʒu�擾�֐�
//=============================================================================
D3DXVECTOR3 CMeshCylinder::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �����擾�֐�
//=============================================================================
D3DXVECTOR3 CMeshCylinder::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �Q�b�g�T�C�Y�֐�
//=============================================================================
D3DXVECTOR3 CMeshCylinder::GetSize(void)
{
	return m_size;
}

//=============================================================================
// �Q�b�g�T�C�Y�֐�
//=============================================================================
void CMeshCylinder::ColorAnimation(void)
{
	//���b�V���̃J���[�ύX
	for (int nMesh = 0; nMesh < MESH_Y_BLOCK + 1; nMesh++)
	{
		if (m_bColAnima[nMesh] == true)
		{
			m_col[nMesh] = (D3DXCOLOR(m_col[nMesh].r, m_col[nMesh].g, m_col[nMesh].b, m_col[nMesh].a + 0.01f));
		}
		else
		{
			m_col[nMesh] = (D3DXCOLOR(m_col[nMesh].r, m_col[nMesh].g, m_col[nMesh].b, m_col[nMesh].a - 0.01f));
		}
		if (m_col[nMesh].a <= 0.0f)
		{
			m_bColAnima[nMesh] = true;
		}
		else if (m_col[nMesh].a>=1.0f)
		{
			m_bColAnima[nMesh] = false;
		}
	}
}

