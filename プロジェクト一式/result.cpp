#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include "sound.h"
#include "main.h"
#include "Score.h"


void Result_Initialize(void)
{
	PlaySound(SOUND_LABEL_BGM000);
	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void Result_Finalize(void)
{
	StopSound();
}

void Result_Update(void)
{
	if( Keyboard_IsTrigger(DIK_RETURN) ) {
		Scene_Change(SCENE_INDEX_TITLE);
	}
	Score_Update();
}

void Result_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_RESULT, 0.0f, 0.0f, 0);
	Sprite_Draw(TEXTURE_INDEX_PRESSENTER, SCREEN_WIDTH - 250.0f, SCREEN_HEIGHT - 50.0f, 0);
	Score_Draw();

}

