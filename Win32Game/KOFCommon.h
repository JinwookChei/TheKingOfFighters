#pragma once
#include "stdafx.h"

enum IMAGE_TYPE : unsigned long long
{
  IMGTYPE_MouseImage = 1ULL,
  IMGTYPE_BackGoundImage,
  IMGTYPE_BlackBoardImage,
  IMGTYPE_WhiteBoardImage,
  IMGTYPE_IoriImage,
  IMGTYPE_ChangImage,
  IMGTYPE_HealthBarImage,
  IMGTYPE_HealthImage,
  IMGTYPE_HitEffectImage,
  IMGTYPE_CastingEffectImage,
};

enum IMAGE_MODIFIER : unsigned long long {
  IMGMOD_NONE = 0,
  IMGMOD_FLIPPED = 1ULL << 63,
  IMGMOD_COLOR_CHANGED = 1ULL << 62
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



unsigned long long MakeKey(unsigned long long type, unsigned long long modify) {
  return type | modify;
}