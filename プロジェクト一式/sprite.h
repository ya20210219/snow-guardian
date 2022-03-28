/*==============================================================================

   スプライト描画モジュール [sprite.h]
                                                         Author : Youhei Sato
                                                         Date   : 2018/06/17
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include <d3d9.h>    // D3DCOLOR
#include "texture.h" // TextureIndex


/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/

// スプライトポリゴンの頂点カラー設定
// ※4頂点すべてに同じカラーを設定する
//
// 引数 ... color 設定する色
void Sprite_SetColor(D3DCOLOR color);

// スプライト描画
// ※テクスチャ解像度と同じ大きさのスプライトを指定座標に描画する
//
// 引数:texture_index ... テクスチャ管理番号
//      dx            ... 描画座標x
//      dy            ... 描画座標y
//		colortype	　･･･ 色のパターン(1:赤 2:黄色 3:緑)
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int colortype);

// スプライト描画
// ※テクスチャ切り取り幅、高さと同じ大きさのスプライトを指定座標に描画する
//
// 引数:texture_index ... テクスチャ管理番号
//      dx            ... 描画座標x
//      dy            ... 描画座標y
//      tx            ... テクスチャ切り取り座標x
//      ty            ... テクスチャ切り取り座標y
//      tw            ... テクスチャ切り取り幅
//      th            ... テクスチャ切り取り高さ
//		colortype	　･･･ 色のパターン(1:赤 2:黄色 3:緑)
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, int colortype);

// スプライト描画
// ※テクスチャ切り取り幅、高さと同じ大きさのスプライトを指定座標に配置してスプライトの指定座標を中心に拡大、回転描画する
//
// 引数:texture_index ... テクスチャ管理番号
//      dx            ... 描画座標x
//      dy            ... 描画座標y
//      tx            ... テクスチャ切り取り座標x
//      ty            ... テクスチャ切り取り座標y
//      tw            ... テクスチャ切り取り幅
//      th            ... テクスチャ切り取り高さ
//      cx            ... 中心座標x
//      cy            ... 中心座標y
//      sx            ... 拡大率x方向
//      sy            ... 拡大率y方向
//      rotation      ... 回転角度（ラジアン）
//		colortype	　･･･ 色のパターン(1:赤 2:黄色 3:緑)
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation, int colortype);
