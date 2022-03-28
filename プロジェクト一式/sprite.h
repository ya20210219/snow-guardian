/*==============================================================================

   �X�v���C�g�`�惂�W���[�� [sprite.h]
                                                         Author : Youhei Sato
                                                         Date   : 2018/06/17
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include <d3d9.h>    // D3DCOLOR
#include "texture.h" // TextureIndex


/*------------------------------------------------------------------------------
   �֐��̃v���g�^�C�v�錾
------------------------------------------------------------------------------*/

// �X�v���C�g�|���S���̒��_�J���[�ݒ�
// ��4���_���ׂĂɓ����J���[��ݒ肷��
//
// ���� ... color �ݒ肷��F
void Sprite_SetColor(D3DCOLOR color);

// �X�v���C�g�`��
// ���e�N�X�`���𑜓x�Ɠ����傫���̃X�v���C�g���w����W�ɕ`�悷��
//
// ����:texture_index ... �e�N�X�`���Ǘ��ԍ�
//      dx            ... �`����Wx
//      dy            ... �`����Wy
//		colortype	�@��� �F�̃p�^�[��(1:�� 2:���F 3:��)
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int colortype);

// �X�v���C�g�`��
// ���e�N�X�`���؂��蕝�A�����Ɠ����傫���̃X�v���C�g���w����W�ɕ`�悷��
//
// ����:texture_index ... �e�N�X�`���Ǘ��ԍ�
//      dx            ... �`����Wx
//      dy            ... �`����Wy
//      tx            ... �e�N�X�`���؂�����Wx
//      ty            ... �e�N�X�`���؂�����Wy
//      tw            ... �e�N�X�`���؂��蕝
//      th            ... �e�N�X�`���؂��荂��
//		colortype	�@��� �F�̃p�^�[��(1:�� 2:���F 3:��)
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, int colortype);

// �X�v���C�g�`��
// ���e�N�X�`���؂��蕝�A�����Ɠ����傫���̃X�v���C�g���w����W�ɔz�u���ăX�v���C�g�̎w����W�𒆐S�Ɋg��A��]�`�悷��
//
// ����:texture_index ... �e�N�X�`���Ǘ��ԍ�
//      dx            ... �`����Wx
//      dy            ... �`����Wy
//      tx            ... �e�N�X�`���؂�����Wx
//      ty            ... �e�N�X�`���؂�����Wy
//      tw            ... �e�N�X�`���؂��蕝
//      th            ... �e�N�X�`���؂��荂��
//      cx            ... ���S���Wx
//      cy            ... ���S���Wy
//      sx            ... �g�嗦x����
//      sy            ... �g�嗦y����
//      rotation      ... ��]�p�x�i���W�A���j
//		colortype	�@��� �F�̃p�^�[��(1:�� 2:���F 3:��)
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation, int colortype);
