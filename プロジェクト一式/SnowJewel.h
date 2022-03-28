#pragma once

#include "collision.h"


#define SNOW_JEWEL_W (120.0f) 
#define SNOW_JEWEL_H (120.0f) 

#define MAX_SNOW_JEWEL (1)

typedef struct SnowJewel_tag
{
	float posx;
	float posy;
	bool	enable;
	int	 HpColor;
	int  Life;

	CIRCLE	col_circle;
}SNOWJEWEL;

void SnowJewel_Initialize(void);
void SnowJewel_Update(void);
void SnowJewel_Draw(void);

void SnowJewel_Create(float x, float y);
void SnowJewel_Destroy(int index);
void SnowJewel_Delete(int index);
bool SnowJewel_IsEnable(int index);
CIRCLE* SnowJewel_GetCircle(int index);
SNOWJEWEL* GetSnowJewel();

