/*==============================================================================

   [main.cpp]
                                                         Author : ��
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#include <Windows.h>
#include <stdio.h>
#include "main.h"
#include "system_timer.h"
#include "MyDirect3d.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "debug_font.h"
#include "Game.h"
#include "scene.h"
#include "fade.h"
#include "sound.h"

#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/
#define CLASS_NAME     "GameWindow"       // �E�C���h�E�N���X�̖��O
#define WINDOW_CAPTION "�Q�[���E�B���h�E" // �E�B���h�E�̖��O
#define FPS_MEASUREMENT_TIME (1.0f)       // FPS�v������


/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/
// �E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �Q�[���̏������֐�
// �߂�l:�������Ɏ��s�����Ƃ�false
static bool Initialize(HINSTANCE hInst, HWND hWnd);
// �Q�[���̍X�V�֐�
static void Update(void);
// �Q�[���̕`��֐�
static void Draw(void);
// �Q�[���̏I������
static void Finalize(void);


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
static int g_FrameCounter = 0;      // �t���[���J�E���^�[
static double g_FPSBaseTime = 0.0;  // FPS�v���̊�{�ƂȂ鎞��
static double g_FrameBaseTime = 0.0;
static char g_FPSText[256] = {};

/*------------------------------------------------------------------------------
   �֐���`
------------------------------------------------------------------------------*/

// ���C���֐�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // �g�p���Ȃ��ꎞ�ϐ��𖾎�
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // �E�B���h�E�N���X�\���̂̐ݒ�
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;                          // �E�B���h�E�v���V�[�W���̎w��
    wc.lpszClassName = CLASS_NAME;                     // �N���X���̐ݒ�
    wc.hInstance = hInstance;                          // �C���X�^���X�n���h���̎w��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // �}�E�X�J�[�\�����w��
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1); // �E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�

    // �N���X�o�^
    RegisterClass(&wc);


    // �E�B���h�E�X�^�C��
    DWORD window_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);

    // ��{��`���W
    RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    // �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɐV���ȋ�`���W���v�Z
    AdjustWindowRect(&window_rect, window_style, FALSE);

    // �V����Window�̋�`���W���畝�ƍ������Z�o
    int window_width = window_rect.right - window_rect.left;
    int window_height = window_rect.bottom - window_rect.top;

    // �v���C�}�����j�^�[�̉�ʉ𑜓x�擾
    int desktop_width = GetSystemMetrics(SM_CXSCREEN);
    int desktop_height = GetSystemMetrics(SM_CYSCREEN);

    // �f�X�N�g�b�v�̐^�񒆂ɃE�B���h�E�����������悤�ɍ��W���v�Z
    // ��������������A�f�X�N�g�b�v���E�B���h�E���傫���ꍇ�͍���ɕ\��
    int window_x = max((desktop_width - window_width) / 2, 0);
    int window_y = max((desktop_height - window_height) / 2, 0);

	HWND hWnd;

	// �E�B���h�E�̐���
    hWnd = CreateWindow(
        CLASS_NAME,     // �E�B���h�E�N���X
        WINDOW_CAPTION, // �E�B���h�E�e�L�X�g
        window_style,   // �E�B���h�E�X�^�C��
        window_x,       // �E�B���h�E���Wx
        window_y,       // �E�B���h�E���Wy
        window_width,   // �E�B���h�E�̕�
        window_height,  // �E�B���h�E�̍���
        NULL,           // �e�E�B���h�E�n���h��
        NULL,           // ���j���[�n���h��
        hInstance,      // �C���X�^���X�n���h��
        NULL            // �ǉ��̃A�v���P�[�V�����f�[�^
    );

    if( hWnd == NULL ) {
        // �E�B���h�E�n���h�������炩�̗��R�Ő����o���Ȃ�����
        return -1;
    }

    // �w��̃E�B���h�E�n���h���̃E�B���h�E���w��̕��@�ŕ\��
    ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// �Q�[���̏�����(Direct3D�̏�����)
	if( !Initialize(hInstance, hWnd) ) {
        // �Q�[���̏������Ɏ��s����
		return -1;
	}

    // Windows�Q�[���p���C�����[�v
    MSG msg = {}; // msg.message == WM_NULL
    while( WM_QUIT != msg.message ) {

        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
            // ���b�Z�[�W������ꍇ�̓��b�Z�[�W������D��
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else {
			// ���݂̃V�X�e�����Ԃ��擾
			double time = SystemTimer_GetTime();

			if( time - g_FrameBaseTime >= 1.0 / 60.0 ) {
				// �t���[���Œ�p�̌v�����Ԃ��X�V����
				g_FrameBaseTime = time;

			    // �Q�[���̍X�V
				Update();
				// �Q�[���̕`��
				Draw();
				// �V�[���̃`�F�b�N
				Scene_Check();
			}
			else {
				// 1 / 60 �b�o���Ă��Ȃ����������
				Sleep(0);
			}
        }
    }

	// �Q�[���̏I������(Direct3D�̏I������)
	Finalize();

    return (int)msg.wParam;
}


// �E�B���h�E�v���V�[�W��(�R�[���o�b�N�֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch( uMsg ) {
        case WM_KEYDOWN:
            if( wParam == VK_ESCAPE ) {
                SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSE���b�Z�[�W�̑��M
            }
            break;

        case WM_CLOSE:
            if( MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK ) {
                DestroyWindow(hWnd); // �w��̃E�B���h�E��WM_DESTROY���b�Z�[�W�𑗂�
            }
            return 0; // DefWindowProc�֐��Ƀ��b�Z�[�W�𗬂����I�����邱�Ƃɂ���ĉ����Ȃ��������Ƃɂ���

        case WM_DESTROY: // �E�B���h�E�̔j�����b�Z�[�W
            PostQuitMessage(0); // WM_QUIT���b�Z�[�W�̑��M
            return 0;
    };

    // �ʏ탁�b�Z�[�W�����͂��̊֐��ɔC����
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


// �Q�[���̏������֐�
bool Initialize(HINSTANCE hInst, HWND hWnd)
{
    // Direct3D���b�p�[���W���[���̏�����
    if( !MyD3D_Initialize(hWnd) ) {
        return false;
    }

	if (!InitSound(hWnd)) {
		return false;
	}

	// �L�[�{�[�h�̏�����
	Keyboard_Initialize(hInst, hWnd);

    // �e�N�X�`���̓ǂݍ���
    if( Texture_Load() > 0 ) {
        MessageBox(hWnd, "�������ǂݍ��߂Ȃ������e�N�X�`���t�@�C��������܂�", "�G���[", MB_OK);
    }

	//�f�o�b�O�t�H���g�̏�����
	DebugFont_Initialize();

	// �V�X�e���^�C�}�[�̏�����
	SystemTimer_Initialize();

	// �V�X�e���^�C�}�[�̋N��
	SystemTimer_Start();

	// �t���[���Œ�p�v�����Ԃ̏�����
	g_FrameCounter = 0;
	g_FPSBaseTime = SystemTimer_GetTime();
	sprintf_s(g_FPSText, "--- fps");

	//�t�F�[�h�̏���������
	Fade_Initialize();

	//�V�[�������������i�^�C�g���ցj
	Scene_Initialize(SCENE_INDEX_TITLE);

	return true;
}

// �Q�[���̍X�V�֐�
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	Keyboard_Update();
	
	//�V�[���X�V����
	Scene_Update();

	//�t�F�[�h�X�V����
	Fade_Update();
}

// �Q�[���̕`��֐�
void Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = MyD3D_GetDevice();
    if( !pDevice ) return;
     
    // ��ʂ̃N���A
    pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 80, 200, 255), 1.0f, 0);

    // �`��o�b�`���߂̊J�n
    pDevice->BeginScene();

	// �Q�[���`�揈��
	Scene_Draw();

	// �t�F�[�h�`�揈��
	Fade_Draw();

#ifdef _DEBUG
	g_FrameCounter++;

	double time = SystemTimer_GetTime();

	// FPS���v��
	if (time - g_FPSBaseTime > 0.5f) {
		sprintf_s(g_FPSText, "%4.2f fps", g_FrameCounter / (time - g_FPSBaseTime));

		g_FPSBaseTime = time;
		g_FrameCounter = 0;
	}
	// ��ʂɏo��
	//DebugFont_Draw(0, 0, g_FPSText);
#endif

    // �`��o�b�`���߂̏I��
    pDevice->EndScene();

    // �o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ��j
    pDevice->Present(NULL, NULL, NULL, NULL);
}

// �Q�[���̏I������
void Finalize(void)
{
	//�f�o�b�O�t�H���g�̏I������
	DebugFont_Finalize();

	//�t�F�[�h�̏I������
	Fade_Finalize();

    //�e�N�X�`���̉��
    Texture_Release();

	//�L�[�{�[�h�̏I������
	Keyboard_Finalize();

	//XAudio�̏I������
	UninitSound();

    // Direct3D���b�p�[���W���[���̏I������
    MyD3D_Finalize();
}
