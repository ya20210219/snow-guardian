/*==============================================================================

   �e�N�X�`���Ǘ����W���[�� [texture.h]
                                                         Author : Youhei Sato
                                                         Date   : 2018/06/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include <d3d9.h>


/*------------------------------------------------------------------------------
   �e�N�X�`���񋓌^
------------------------------------------------------------------------------*/
// �e�N�X�`���Ǘ��ԍ�
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
   �֐��̃v���g�^�C�v�錾
------------------------------------------------------------------------------*/

// �e�N�X�`���̓ǂݍ���
//
// �߂�l:�ǂݍ��߂Ȃ�������
//
int Texture_Load(void);

// �e�N�X�`���̉��
void Texture_Release(void);

// �e�N�X�`���C���^�[�t�F�[�X�̎擾
//
// ���� ... index �e�N�X�`���Ǘ��ԍ�
//
// �߂�l:�e�N�X�`���C���^�[�t�F�[�X
//        ���������݂��Ȃ�index���w�肵���ꍇ�ANULL
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);

// �e�N�X�`���𑜓x���̎擾
//
// ���� ... index �e�N�X�`���Ǘ��ԍ�
//
int Texture_GetWidth(TextureIndex index);

// �e�N�X�`���𑜓x�����̎擾
//
// ���� ... index �e�N�X�`���Ǘ��ԍ�
//
int Texture_GetHeight(TextureIndex index);
