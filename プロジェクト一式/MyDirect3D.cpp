
#include "MyDirect3D.h"
#include "main.h"


static LPDIRECT3D9			g_pD3D = NULL;		//D3Dインターフェース
static LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;//D3Dデバイスのインターフェース


bool MyD3D_Initialize(HWND hWnd)
{
	//D3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	//取得に失敗していた場合は終了させる
	if (g_pD3D == NULL)
	{
		MessageBox(hWnd, "Direct3Dインターフェースの取得に失敗",
			"エラー", MB_OK);

		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp = {};

	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//バックバッファの横幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//バックバッファの高さ
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//バックバッファのフォーマット
	d3dpp.BackBufferCount = 1;					//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//スワップ方法
	d3dpp.Windowed = TRUE;						//ウィンドウモード設定
	d3dpp.EnableAutoDepthStencil = TRUE;		//深度バッファ・ステンシルバッファの使用
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//深度バッファ・ステンシルバッファのフォーマット
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//フルスクリーン時のリフレッシュレート設定
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//リフレッシュレートとPresentの関係

	// Direct3Dデバイスの取得
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		// デバイスの作成に失敗
		MessageBox(
			hWnd,
			"Direct3Dデバイスの作成に失敗しました",
			"エラー",
			MB_OK);
		return false;
	}



	// アドレッシングモードの設定
	// 繰り返し表示（※デフォルト設定）
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	// ミラーリング（反転して繰り返し）
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	// クランプ（最後の色が繰り返される）
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	// ボーダー（指定色で塗りつぶす）
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
//	g_pD3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 255));

	// フィルタリングの設定
	// ポイントフィルタ
	// 縮小方向のフィルタ方法を指定
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MINFILTER, D3DTEXF_POINT);
	// 拡大方向のフィルタ方法を指定
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	// バイリニアフィルタ
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,
		D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
//	g_pD3DDevice->SetSamplerState(0,
//		D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	// 異方性フィルタ
//	g_pD3DDevice->SetSamplerState(0,
//		D3DSAMP_MINFILTER,
//		D3DTEXF_ANISOTROPIC);

	// アルファブレンド設定
	g_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE); // アルファブレンドを有効にする
	g_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return true;
}

void MyD3D_Finalize(void)
{
	//デバイスの解放処理
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//D3Dの解放処理
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

// D3Dデバイスのゲッター
LPDIRECT3DDEVICE9 MyD3D_GetDevice(void) 
{
	return g_pD3DDevice;
}
