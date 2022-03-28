#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "main.h"
#include "texture.h"
#include "fade.h"
#include "sound.h"
#include <d3d9.h>

static bool g_bEnd = false;


void Title_Initialize(void)
{
	PlaySound(SOUND_LABEL_BGM000);
	g_bEnd = false;
}

void Title_Finalize(void)
{
	StopSound(SOUND_LABEL_BGM000);
}

void Title_Update(void)
{
	if( !g_bEnd ) { 
		if( Keyboard_IsTrigger(DIK_RETURN) ) {
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));//255,255,255,255Ç»ÇÁèôÅXÇ…îíÇ≠Ç»Ç¡ÇƒÇ¢Ç≠
			g_bEnd = true;
		}
	}
	else{
		if( !Fade_IsFade() ) {
			Scene_Change(SCENE_INDEX_TUTORIAL);
		}
	}
}

void Title_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_TITLE, 0.0f, 0.0f, 0);
	Sprite_Draw(TEXTURE_INDEX_PRESSENTER, SCREEN_WIDTH - 250.0f, SCREEN_HEIGHT - 50.0f, 0);
}
