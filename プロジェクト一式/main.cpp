/*==============================================================================

   [main.cpp]
                                                         Author : 俺
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

#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/
#define CLASS_NAME     "GameWindow"       // ウインドウクラスの名前
#define WINDOW_CAPTION "ゲームウィンドウ" // ウィンドウの名前
#define FPS_MEASUREMENT_TIME (1.0f)       // FPS計測時間


/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/
// ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ゲームの初期化関数
// 戻り値:初期化に失敗したときfalse
static bool Initialize(HINSTANCE hInst, HWND hWnd);
// ゲームの更新関数
static void Update(void);
// ゲームの描画関数
static void Draw(void);
// ゲームの終了処理
static void Finalize(void);


/*------------------------------------------------------------------------------
   グローバル変数宣言
------------------------------------------------------------------------------*/
static int g_FrameCounter = 0;      // フレームカウンター
static double g_FPSBaseTime = 0.0;  // FPS計測の基本となる時間
static double g_FrameBaseTime = 0.0;
static char g_FPSText[256] = {};

/*------------------------------------------------------------------------------
   関数定義
------------------------------------------------------------------------------*/

// メイン関数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 使用しない一時変数を明示
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ウィンドウクラス構造体の設定
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;                          // ウィンドウプロシージャの指定
    wc.lpszClassName = CLASS_NAME;                     // クラス名の設定
    wc.hInstance = hInstance;                          // インスタンスハンドルの指定
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);          // マウスカーソルを指定
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1); // ウインドウのクライアント領域の背景色を設定

    // クラス登録
    RegisterClass(&wc);


    // ウィンドウスタイル
    DWORD window_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);

    // 基本矩形座標
    RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    // 指定したクライアント領域を確保するために新たな矩形座標を計算
    AdjustWindowRect(&window_rect, window_style, FALSE);

    // 新たなWindowの矩形座標から幅と高さを算出
    int window_width = window_rect.right - window_rect.left;
    int window_height = window_rect.bottom - window_rect.top;

    // プライマリモニターの画面解像度取得
    int desktop_width = GetSystemMetrics(SM_CXSCREEN);
    int desktop_height = GetSystemMetrics(SM_CYSCREEN);

    // デスクトップの真ん中にウィンドウが生成されるように座標を計算
    // ※ただし万が一、デスクトップよりウィンドウが大きい場合は左上に表示
    int window_x = max((desktop_width - window_width) / 2, 0);
    int window_y = max((desktop_height - window_height) / 2, 0);

	HWND hWnd;

	// ウィンドウの生成
    hWnd = CreateWindow(
        CLASS_NAME,     // ウィンドウクラス
        WINDOW_CAPTION, // ウィンドウテキスト
        window_style,   // ウィンドウスタイル
        window_x,       // ウィンドウ座標x
        window_y,       // ウィンドウ座標y
        window_width,   // ウィンドウの幅
        window_height,  // ウィンドウの高さ
        NULL,           // 親ウィンドウハンドル
        NULL,           // メニューハンドル
        hInstance,      // インスタンスハンドル
        NULL            // 追加のアプリケーションデータ
    );

    if( hWnd == NULL ) {
        // ウィンドウハンドルが何らかの理由で生成出来なかった
        return -1;
    }

    // 指定のウィンドウハンドルのウィンドウを指定の方法で表示
    ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ゲームの初期化(Direct3Dの初期化)
	if( !Initialize(hInstance, hWnd) ) {
        // ゲームの初期化に失敗した
		return -1;
	}

    // Windowsゲーム用メインループ
    MSG msg = {}; // msg.message == WM_NULL
    while( WM_QUIT != msg.message ) {

        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
            // メッセージがある場合はメッセージ処理を優先
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else {
			// 現在のシステム時間を取得
			double time = SystemTimer_GetTime();

			if( time - g_FrameBaseTime >= 1.0 / 60.0 ) {
				// フレーム固定用の計測時間を更新する
				g_FrameBaseTime = time;

			    // ゲームの更新
				Update();
				// ゲームの描画
				Draw();
				// シーンのチェック
				Scene_Check();
			}
			else {
				// 1 / 60 秒経っていなかったら空回り
				Sleep(0);
			}
        }
    }

	// ゲームの終了処理(Direct3Dの終了処理)
	Finalize();

    return (int)msg.wParam;
}


// ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch( uMsg ) {
        case WM_KEYDOWN:
            if( wParam == VK_ESCAPE ) {
                SendMessage(hWnd, WM_CLOSE, 0, 0); // WM_CLOSEメッセージの送信
            }
            break;

        case WM_CLOSE:
            if( MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK ) {
                DestroyWindow(hWnd); // 指定のウィンドウにWM_DESTROYメッセージを送る
            }
            return 0; // DefWindowProc関数にメッセージを流さず終了することによって何もなかったことにする

        case WM_DESTROY: // ウィンドウの破棄メッセージ
            PostQuitMessage(0); // WM_QUITメッセージの送信
            return 0;
    };

    // 通常メッセージ処理はこの関数に任せる
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


// ゲームの初期化関数
bool Initialize(HINSTANCE hInst, HWND hWnd)
{
    // Direct3Dラッパーモジュールの初期化
    if( !MyD3D_Initialize(hWnd) ) {
        return false;
    }

	if (!InitSound(hWnd)) {
		return false;
	}

	// キーボードの初期化
	Keyboard_Initialize(hInst, hWnd);

    // テクスチャの読み込み
    if( Texture_Load() > 0 ) {
        MessageBox(hWnd, "いくつか読み込めなかったテクスチャファイルがあります", "エラー", MB_OK);
    }

	//デバッグフォントの初期化
	DebugFont_Initialize();

	// システムタイマーの初期化
	SystemTimer_Initialize();

	// システムタイマーの起動
	SystemTimer_Start();

	// フレーム固定用計測時間の初期化
	g_FrameCounter = 0;
	g_FPSBaseTime = SystemTimer_GetTime();
	sprintf_s(g_FPSText, "--- fps");

	//フェードの初期化処理
	Fade_Initialize();

	//シーン初期化処理（タイトルへ）
	Scene_Initialize(SCENE_INDEX_TITLE);

	return true;
}

// ゲームの更新関数
void Update(void)
{
	//キーボードの更新処理
	Keyboard_Update();
	
	//シーン更新処理
	Scene_Update();

	//フェード更新処理
	Fade_Update();
}

// ゲームの描画関数
void Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = MyD3D_GetDevice();
    if( !pDevice ) return;
     
    // 画面のクリア
    pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 80, 200, 255), 1.0f, 0);

    // 描画バッチ命令の開始
    pDevice->BeginScene();

	// ゲーム描画処理
	Scene_Draw();

	// フェード描画処理
	Fade_Draw();

#ifdef _DEBUG
	g_FrameCounter++;

	double time = SystemTimer_GetTime();

	// FPSを計測
	if (time - g_FPSBaseTime > 0.5f) {
		sprintf_s(g_FPSText, "%4.2f fps", g_FrameCounter / (time - g_FPSBaseTime));

		g_FPSBaseTime = time;
		g_FrameCounter = 0;
	}
	// 画面に出力
	//DebugFont_Draw(0, 0, g_FPSText);
#endif

    // 描画バッチ命令の終了
    pDevice->EndScene();

    // バックバッファをフリップ（タイミングはD3DPRESENT_PARAMETERSの設定による）
    pDevice->Present(NULL, NULL, NULL, NULL);
}

// ゲームの終了処理
void Finalize(void)
{
	//デバッグフォントの終了処理
	DebugFont_Finalize();

	//フェードの終了処理
	Fade_Finalize();

    //テクスチャの解放
    Texture_Release();

	//キーボードの終了処理
	Keyboard_Finalize();

	//XAudioの終了処理
	UninitSound();

    // Direct3Dラッパーモジュールの終了処理
    MyD3D_Finalize();
}
