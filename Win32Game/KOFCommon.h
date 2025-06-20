#pragma once
#include "stdafx.h"

enum IMAGE_KEY
{
  IMGKEY_MouseImage = 1,
  IMGKEY_BackGoundImage,
  IMGKEY_BlackBoardImage,
  IMGKEY_IoriImage,
  //IMGKEY_ReverseIoriImage,
  IMGKEY_ChangImage,
  //IMGKEY_ReverseChangImage,
  IMGKEY_HealthBarImage,
  //IMGKEY_ReverseHealthBarImage,
  IMGKEY_HealthImage,
  IMGKEY_EffectImage
};


static Color8Bit ioriTransparentColor = Color8Bit{169, 139, 150, 0};
static Color8Bit changTransparentColor = Color8Bit{17, 91, 124, 0};