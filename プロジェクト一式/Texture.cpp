/*==============================================================================

   テクスチャ管理モジュール [texture.cpp]
                                                         Author : Youhei Sato
                                                         Date   : 2018/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#include <d3dx9.h>
#include "debugPrintf.h"
#include "MyDirect3d.h"
#include "texture.h"


/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/
#define TEXTURE_FILENAME_MAX (64) // テクスチャファイル名最大文字数（パス、NULL文字含む）

// テクスチャファイル管理構造体
typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX]; // テクスチャファイル名
	int width;  // テクスチャ解像度横幅
	int height; // テクスチャ解像度縦幅
} TextureFile;


/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/
// 読み込みテクスチャ情報
static const TextureFile g_TextureFiles[] = {
	{ "texture/title3.png",			1024,  576 },
	{ "texture/tutorial4.png",		1024,  576 },
	{ "texture/result3.png",		1024,  576 },

	{ "texture/player2.png",		  80,   60 },
	{ "texture/BackGround.png",		1024,  576 },
	{ "texture/fire-enemy01.png",	  48,   48 },
	{ "texture/Snow-Jewel01.png",	 120,  120 },
	{ "texture/snow2.png",			  32,   32 },
	{ "texture/PressEnter.png",		 250,   50 },
	{ "texture/NowTutorial.png",	 400,   80 },
	{ "texture/bomb.png",			 200,  200 },
	{ "texture/friend.png",			  40,   60 },
	{ "texture/Boss01.png",			 120,  120 },
	{ "texture/Number.png",			 256,  100 },
	{ "texture/HPbar.png",			  10,   10 },
	{ "texture/friend-skill.png",	  40,   80 },
	{ "texture/bomb-skill.png",		  64,   80 },
	{ "texture/timer.png",			  20,   23 },
	{ "texture/explosion.png",		 240,  240 },
	{ "texture/Shop2.png",			 100,   80 },
	{ "texture/shop-bg6.png",		1024,  576 },
	{ "texture/witch.png",			 350,  300 },
	{ "texture/shop-arrow.png",		  80,   80 },
	{ "texture/Shop-txt-welcome.png",625,  200 },
	{ "texture/Shop-txt-list1.png",  625,  200 },
	{ "texture/Shop-txt-list2.png",  625,  200 },
	{ "texture/Shop-txt-list3.png",  625,  200 },
	{ "texture/Shop-txt-list4.png",  625,  200 },
	{ "texture/Shop-txt-thx.png"  ,  625,  200 },
	{ "texture/Shop-txt-default.png",625,  200 },
	{ "texture/shop-soldout.png",	 350,   95 },
	{ "texture/shop-not-enough.png", 625,  200 },
};

// 読み込みテクスチャ数
static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);
// static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_TextureFiles); // required Windows.h

// 読み込みテクスチャ数とテクスチャ管理番号列挙数に差があった場合コンパイルエラーとする
static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");


/*------------------------------------------------------------------------------
   グローバル変数宣言
------------------------------------------------------------------------------*/
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {}; // テクスチャインターフェース管理配列


/*------------------------------------------------------------------------------
   関数定義
------------------------------------------------------------------------------*/

// テクスチャの読み込み
int Texture_Load(void)
{   
    LPDIRECT3DDEVICE9 pDevice = MyD3D_GetDevice();
	if( !pDevice ) {
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( FAILED(D3DXCreateTextureFromFile(pDevice, g_TextureFiles[i].filename, &g_pTextures[i])) ) {
            // DebugPrintf("テクスチャの読み込みに失敗 ... %s\n", g_TextureFiles[i].filename);
			failed_count++;
		}
	}

	return failed_count;
}

// テクスチャの解放
void Texture_Release(void)
{
	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( g_pTextures[i] ) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

// テクスチャインターフェースの取得
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_pTextures[index];
}

// テクスチャ解像度幅の取得
int Texture_GetWidth(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].width;
}

// テクスチャ解像度高さの取得
int Texture_GetHeight(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].height;
}
