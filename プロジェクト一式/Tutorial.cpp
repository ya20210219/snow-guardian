#include "input.h"
#include "main.h"
#include "player.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include "sound.h"
#include "fade.h"
#include "scene.h"

#include "enemy.h"
#include "bullet.h"
#include "collision.h"
#include "BackGround.h"
#include "SnowJewel.h"


#include "sound.h"


static bool g_bEnd = false;

void Tutorial_Initialize(void)
{
	g_bEnd = false;
	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));

	Player_Initialize();
	Bullet_Initialize();


	for (int i = 0; i < MAX_PLAYER; i++)
	{
		float x, y;
		x = SCREEN_WIDTH * 0.25f;
		y = SCREEN_HEIGHT * 0.5f;
		Player_Create(x, y);
	}
}

void Tutorial_Finalize(void)
{
}

void Tutorial_Update(void)
{
	if (!g_bEnd)
	{
		Player_Update();
		Bullet_Update();
		if (Keyboard_IsTrigger(DIK_RETURN))
		{
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_bEnd = true;
		}
	}
	else {
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_GAME);
		}
	}
}

void Tutorial_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_TUTORIAL, 0.0f, 0.0f, 0);
	Sprite_Draw(TEXTURE_INDEX_PRESSENTER, SCREEN_WIDTH - 250.0f, SCREEN_HEIGHT - 50.0f, 0);
	Sprite_Draw(TEXTURE_INDEX_NOWTUTORIAL, SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT - SCREEN_HEIGHT + 40.0f, 0);

	Bullet_Draw();
	Player_Draw();
}
