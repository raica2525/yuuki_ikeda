//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	wave.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "wave.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "library.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define TEX_DIV_RATE (1.2f)
#define SIZE_SCALE_RATE (1.1f)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//Author:�r�c�I��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CWave::CWave() :CScene(OBJTYPE_WAVE)
{
    m_pos = DEFAULT_VECTOR;
    m_size = DEFAULT_VECTOR;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//Author:�r�c�I��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CWave::~CWave()
{

}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//����������
//Author:�r�c�I��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CWave::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // �����o�ϐ��Ɍ��т���
    m_pos = pos;
    m_size = size;
    m_pTexture = CManager::GetTexture()->GetInfo(7)->pTexture;    // �g�̃h�[�i�b�c

    VERTEX_2D*pVtx = NULL;
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // ���_�o�b�t�@�̐���
    for (int nCount = 0; nCount < POLYTYPE_MAX ; nCount++)
    {
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_apVtxBuff[nCount], NULL);
    }

    //�~�`�̃X�e���V�������p�|���S��
    m_apVtxBuff[POLYTYPE_STENCIL]->Lock(0, 0, (void**)&pVtx, 0);

    // ���_����ݒ�
    pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

    //�e�N�X�`�����W�̐ݒ�
    pVtx[0].tex[0] = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex[0] = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex[0] = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex[0] = D3DXVECTOR2(1.0f, 1.0f);

    //rhw�̐ݒ�
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //���_�J���[�̐ݒ�(0�`255)
    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    m_apVtxBuff[0]->Unlock();

    pVtx = NULL;

    //�e�N�X�`��
    m_apVtxBuff[POLYTYPE_REAL]->Lock(0, 0, (void**)&pVtx, 0);

    // ���_����ݒ�
    pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

    //�e�N�X�`�����W�̐ݒ�
    for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].tex[0] = D3DXVECTOR2(pVtx[nCount].pos.x / (float)SCREEN_WIDTH, pVtx[nCount].pos.y / (float)SCREEN_HEIGHT);
    }

    //rhw�̐ݒ�
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //���_�J���[�̐ݒ�
    pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

    m_apVtxBuff[POLYTYPE_REAL]->Unlock();

    return S_OK;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I������
//Author:�r�c�I��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CWave::Uninit(void)
{
    // ���_�o�b�t�@�̔j��
    for (int nCount = 0; nCount < POLYTYPE_MAX; nCount++)
    {
        if (m_apVtxBuff[nCount] != NULL)
        {
            m_apVtxBuff[nCount]->Release();
            m_apVtxBuff[nCount] = NULL;
        }
    }
    Release();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V����
//Author:�r�c�I��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CWave::Update(void)
{
    VERTEX_2D*pVtx = NULL;

	//�|���S�����g�傷��
    m_size.x *= SIZE_SCALE_RATE;
    m_size.y *= SIZE_SCALE_RATE;

    for (int nCount = 0; nCount < POLYTYPE_MAX; nCount++)
    {
        pVtx = NULL;
        m_apVtxBuff[nCount]->Lock(0, 0, (void**)&pVtx, 0);
        if (nCount == POLYTYPE_REAL)
        {
			//��U�|���S������������������
            m_size.x /= TEX_DIV_RATE;
            m_size.y /= TEX_DIV_RATE;

            pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f,-m_size.y / 2.0f, 0.0f);
            pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
            pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
            pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

			//������������ԂŃe�N�X�`�������蓖�Ă邱�ƂŃe�N�X�`�����������炷
            for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
            {
                pVtx[nCount].tex[0] = D3DXVECTOR2(pVtx[nCount].pos.x / SCREEN_WIDTH, pVtx[nCount].pos.y / SCREEN_HEIGHT);
            }

			//�傫�������ɖ߂�
			m_size.x *= TEX_DIV_RATE;
			m_size.y *= TEX_DIV_RATE;
        }

		//���_���W�̍X�V
        pVtx[0].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f,-m_size.y / 2.0f, 0.0f);
        pVtx[1].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, 0.0f);
        pVtx[2].pos = m_pos + D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);
        pVtx[3].pos = m_pos + D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, 0.0f);

        m_apVtxBuff[nCount]->Unlock();
    }

    // ���T�C�Y�ɒB������j��
    if (m_size.x > SCREEN_WIDTH * 2)
    {
        Uninit();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`�揈��
//Author:�r�c�I��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CWave::Draw(void)
{
	//�X�e���V���ɕ`��
    CreateStencil();
	
	//���������X�e���V�����g���ĕ`��

    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Z�e�X�g�̐ݒ�
    pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
    pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

    pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
    pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

    pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

    pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
    pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
    pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

    // ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_apVtxBuff[POLYTYPE_REAL], 0, sizeof(VERTEX_2D));

    // ���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    // �e�N�X�`���̐ݒ�i�X�N���[���S�̂̃e�N�X�`���j
    pDevice->SetTexture(0, CManager::GetRenderer()->GetScreenTexture());

    // �|���S���̕`��
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
    pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
    pDevice->SetTexture(0, NULL);
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���G�C�g�֐�
//Author:�r�c�I��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CWave* CWave::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CWave* pWave = new CWave;
    pWave->Init(ConvertScreenPos(pos), size);
    return pWave;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�e���V������
//Author:�r�c�I��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CWave::CreateStencil(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    // �A���t�@�e�X�g�̗L����
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

    // �s�����ɂ���l�̐ݒ�
    pDevice->SetRenderState(D3DRS_ALPHAREF, 128);

	//Z�e�X�g���������Ȃ��悤�ɐݒ�
    pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);

	//�X�e���V���̐ݒ�
    pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
    pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
    pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

    pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
    pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
    pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

    // ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_apVtxBuff[POLYTYPE_STENCIL], 0, sizeof(VERTEX_2D));

    // ���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    // �e�N�X�`���̐ݒ�i����ʂ��e�N�X�`���j
    pDevice->SetTexture(0, m_pTexture);

    // �|���S���̕`��
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

    pDevice->SetTexture(0, NULL);
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
