
#include "MyDirect3D.h"
#include "main.h"


static LPDIRECT3D9			g_pD3D = NULL;		//D3D�C���^�[�t�F�[�X
static LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;//D3D�f�o�C�X�̃C���^�[�t�F�[�X


bool MyD3D_Initialize(HWND hWnd)
{
	//D3D�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	//�擾�Ɏ��s���Ă����ꍇ�͏I��������
	if (g_pD3D == NULL)
	{
		MessageBox(hWnd, "Direct3D�C���^�[�t�F�[�X�̎擾�Ɏ��s",
			"�G���[", MB_OK);

		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp = {};

	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//�o�b�N�o�b�t�@�̉���
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//�o�b�N�o�b�t�@�̍���
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//�o�b�N�o�b�t�@�̃t�H�[�}�b�g
	d3dpp.BackBufferCount = 1;					//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�X���b�v���@
	d3dpp.Windowed = TRUE;						//�E�B���h�E���[�h�ݒ�
	d3dpp.EnableAutoDepthStencil = TRUE;		//�[�x�o�b�t�@�E�X�e���V���o�b�t�@�̎g�p
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//�[�x�o�b�t�@�E�X�e���V���o�b�t�@�̃t�H�[�}�b�g
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//�t���X�N���[�����̃��t���b�V�����[�g�ݒ�
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//���t���b�V�����[�g��Present�̊֌W

	// Direct3D�f�o�C�X�̎擾
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		// �f�o�C�X�̍쐬�Ɏ��s
		MessageBox(
			hWnd,
			"Direct3D�f�o�C�X�̍쐬�Ɏ��s���܂���",
			"�G���[",
			MB_OK);
		return false;
	}



	// �A�h���b�V���O���[�h�̐ݒ�
	// �J��Ԃ��\���i���f�t�H���g�ݒ�j
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	// �~���[�����O�i���]���ČJ��Ԃ��j
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	// �N�����v�i�Ō�̐F���J��Ԃ����j
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	// �{�[�_�[�i�w��F�œh��Ԃ��j
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 255));

	// �t�B���^�����O�̐ݒ�
	// �|�C���g�t�B���^
	// �k�������̃t�B���^���@���w��
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MINFILTER, D3DTEXF_POINT);
	// �g������̃t�B���^���@���w��
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	// �o�C���j�A�t�B���^
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
//	g_pD3DDevice->SetSamplerState(0,
//		D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	// �ٕ����t�B���^
//	g_pD3DDevice->SetSamplerState(0,
//		D3DSAMP_MINFILTER,
//		D3DTEXF_ANISOTROPIC);

	// �A���t�@�u�����h�ݒ�
	g_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE); // �A���t�@�u�����h��L���ɂ���
	g_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return true;
}

void MyD3D_Finalize(void)
{
	//�f�o�C�X�̉������
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//D3D�̉������
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

// D3D�f�o�C�X�̃Q�b�^�[
LPDIRECT3DDEVICE9 MyD3D_GetDevice(void) 
{
	return g_pD3DDevice;
}
