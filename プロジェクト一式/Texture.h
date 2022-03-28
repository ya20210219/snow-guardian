/*==============================================================================

   テクスチャ管理モジュール [texture.h]
                                                         Author : Youhei Sato
                                                         Date   : 2018/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include <d3d9.h>


/*------------------------------------------------------------------------------
   テクスチャ列挙型
------------------------------------------------------------------------------*/
// テクスチャ管理番号
typedef enum
{
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_TUTORIAL,
	TEXTURE_INDEX_RESULT,

	TEXTURE_INDEX_PLAYER,
	TEXTURE_INDEX_BACKGROUND,
	TEXTURE_INDEX_FIRE_ENEMY,
	TEXTURE_INDEX_SNOW_JEWEL,
	TEXTURE_INDEX_BULLET,
	TEXTURE_INDEX_PRESSENTER,
	TEXTURE_INDEX_NOWTUTORIAL,
	TEXTURE_INDEX_BOMB,
	TEXTURE_INDEX_FRIEND,
	TEXTURE_INDEX_BOSS,
	TEXTURE_INDEX_NUMBER,
	TEXTURE_INDEX_HPBAR,
	TEXTURE_INDEX_FRIEND_SKILL,
	TEXTURE_INDEX_BOMB_SKILL,
	TEXTURE_INDEX_TIMER,
	TEXTURE_INDEX_EXPLOSION,
	TEXTURE_INDEX_SHOP,
	TEXTURE_INDEX_SHOP_BG,
	TEXTURE_INDEX_WITCH,
	TEXTURE_INDEX_SHOP_ARROW,
	TEXTURE_INDEX_SHOP_TXT_WELCOME,
	TEXTURE_INDEX_SHOP_TXT_LIST1,
	TEXTURE_INDEX_SHOP_TXT_LIST2,
	TEXTURE_INDEX_SHOP_TXT_LIST3,
	TEXTURE_INDEX_SHOP_TXT_LIST4,
	TEXTURE_INDEX_SHOP_TXT_THX,
	TEXTURE_INDEX_SHOP_TXT_DEFAULT,
	TEXTURE_INDEX_SHOP_SOLDOUT,
	TEXTURE_INDEX_SHOP_NOT_ENOUGH,

    TEXTURE_INDEX_MAX
}TextureIndex;


/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/

// テクスチャの読み込み
//
// 戻り値:読み込めなかった数
//
int Texture_Load(void);

// テクスチャの解放
void Texture_Release(void);

// テクスチャインターフェースの取得
//
// 引数 ... index テクスチャ管理番号
//
// 戻り値:テクスチャインターフェース
//        ただし存在しないindexを指定した場合、NULL
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);

// テクスチャ解像度幅の取得
//
// 引数 ... index テクスチャ管理番号
//
int Texture_GetWidth(TextureIndex index);

// テクスチャ解像度高さの取得
//
// 引数 ... index テクスチャ管理番号
//
int Texture_GetHeight(TextureIndex index);
