#include "main.h"
#include "texture.h"
#include "sprite.h"
#include <math.h>
#include "BackGround.h"

void BackGround_Initialize(void)
{

}

void BackGround_Update(void)
{

}

void BackGround_Draw(void)
{
	int tw = Texture_GetWidth(TEXTURE_INDEX_BACKGROUND);
	int th = Texture_GetHeight(TEXTURE_INDEX_BACKGROUND);
	Sprite_Draw(TEXTURE_INDEX_BACKGROUND,					//�e�N�X�`���Ǘ��ԍ�
		SCREEN_WIDTH * 0.5f,								//�`����Wx
		SCREEN_HEIGHT * 0.5f,								//�`����Wy
		0, 0,												//�e�N�X�`���؂�����Wx,y
		tw, th,												//�e�N�X�`���؂��蕝x,y
		tw * 0.5f,											//���S���Wx
		th * 0.5f,											//���S���Wy
		1.0f,												//�g�嗦x����
		1.0f,												//�g�嗦y����
		0.0f,												//��]�p�x(���W�A��)
		0);
}
