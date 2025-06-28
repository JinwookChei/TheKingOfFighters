#pragma once
#include "stdafx.h"

enum IMAGE_KEY
{
  IMGKEY_MouseImage = 1,
  IMGKEY_BackGoundImage,
  IMGKEY_BlackBoardImage,
  IMGKEY_WhiteBoardImage,
  IMGKEY_IoriImage,
  IMGKEY_ChangImage,
  IMGKEY_HealthBarImage,
  IMGKEY_HealthImage,
  IMGKEY_HitEffectImage,
  IMGKEY_CastingEffectImage
};

enum EFFECT_KEY
{
	EFKEY_None = 0,
	EFKEY_Hit_1 = 1,
	EFKEY_Hit_2,
	EFKEY_Hit_3,
	EFKEY_Casting_1,
	EFKEY_Casting_2,
	EFKEY_Casting_3,
	EFKEY_Casting_4,
	EFKEY_Casting_5,
	EFKEY_Casting_6,
	EFKEY_Iori_Explosion,
	EFKEY_Max
};


static Color8Bit ioriTransparentColor = Color8Bit{169, 139, 150, 0};
static Color8Bit changTransparentColor = Color8Bit{17, 91, 124, 0};