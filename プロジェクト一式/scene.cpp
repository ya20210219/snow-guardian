#include "scene.h"

//全シーンのヘッダーをインクルード
#include "title.h"
#include "Tutorial.h"
#include "game.h"
#include "result.h"


static SCENE_INDEX g_SceneIndex;		//現在実行されているシーン
static SCENE_INDEX g_SceneNextIndex;	//切り替え先(次のシーン)シーン


void Scene_Initialize(SCENE_INDEX index)
{
	g_SceneNextIndex = g_SceneIndex = index;		//右側から代入されていく
	
	switch (g_SceneIndex) {

	case SCENE_INDEX_TITLE:
		Title_Initialize();
		break;

	case SCENE_INDEX_TUTORIAL:
		Tutorial_Initialize();
		break;

	case SCENE_INDEX_GAME:
		Game_Initialize();
		break;

	case SCENE_INDEX_RESULT:
		Result_Initialize();
		break;
	}
}

void Scene_Finalize(void)
{
	switch( g_SceneIndex ) {

	case SCENE_INDEX_TITLE:
		Title_Finalize();
		break;

	case SCENE_INDEX_TUTORIAL:
		Tutorial_Finalize();
		break;

	case SCENE_INDEX_GAME:
		Game_Finalize();
		break;

	case SCENE_INDEX_RESULT:
		Result_Finalize();
		break;
	}
}

void Scene_Update(void)
{
	switch( g_SceneIndex ) {

	case SCENE_INDEX_TITLE:
		Title_Update();
		break;

	case SCENE_INDEX_TUTORIAL:
		Tutorial_Update();
		break;

	case SCENE_INDEX_GAME:
		Game_Update();
		break;

	case SCENE_INDEX_RESULT:
		Result_Update();
		break;
	}
}

void Scene_Draw(void)
{
	switch( g_SceneIndex ) {

	case SCENE_INDEX_TITLE:
		Title_Draw();
		break;

	case SCENE_INDEX_TUTORIAL:
		Tutorial_Draw();
		break;

	case SCENE_INDEX_GAME:
		Game_Draw();
		break;

	case SCENE_INDEX_RESULT:
		Result_Draw();
		break;
	}
}

void Scene_Check(void)
{
	if( g_SceneIndex != g_SceneNextIndex ) {
		Scene_Finalize();
		Scene_Initialize(g_SceneNextIndex);
	}
}

void Scene_Change(SCENE_INDEX index)
{
	g_SceneNextIndex = index;
}

