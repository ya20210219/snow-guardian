#pragma once

enum SCENE_INDEX
{
	SCENE_INDEX_TITLE,
	SCENE_INDEX_TUTORIAL,
	SCENE_INDEX_GAME,
	SCENE_INDEX_RESULT,

	SCENE_INDEX_MAX
};

void Scene_Initialize(SCENE_INDEX index);
void Scene_Finalize(void);
void Scene_Update(void);
void Scene_Draw(void);
void Scene_Check(void);
void Scene_Change(SCENE_INDEX index);

