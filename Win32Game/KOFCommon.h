#pragma once
#include "stdafx.h"

enum IMAGE_TYPE : unsigned long long {
  IMGTYPE_MouseImage = 1ULL,
  IMGTYPE_BackGoundImage,
  IMGTYPE_BlackBoardImage,
  IMGTYPE_WhiteBoardImage,
  IMGTYPE_IoriImage,
  IMGTYPE_IoriImage_BlueFlame,
  IMGTYPE_ChangImage,
  IMGTYPE_ChangImage_BlueFlame,
  IMGTYPE_HealthBarImage,
  IMGTYPE_HealthImage,
  IMGTYPE_HitEffectImage,
  IMGTYPE_GuardEffectImage01,
  IMGTYPE_CastingEffectImage,
};

enum IMAGE_MODIFIER : unsigned long long {
  IMGMOD_NONE = 0,
  IMGMOD_FLIPPED = 1ULL << 63,
  IMGMOD_BLUEFLAME = 1ULL << 62
};

enum PLAYER_ANIM_TYPE : unsigned long long {
  PLAYER_ANIMTYPE_None = 0ULL,
  PLAYER_ANIMTYPE_Start,
  PLAYER_ANIMTYPE_Idle,
  PLAYER_ANIMTYPE_SeatDown,
  PLAYER_ANIMTYPE_SeatUp,
  PLAYER_ANIMTYPE_FrontWalk,
  PLAYER_ANIMTYPE_BackWalk,
  PLAYER_ANIMTYPE_BackStep,
  PLAYER_ANIMTYPE_Run,
  PLAYER_ANIMTYPE_RunEnd,
  PLAYER_ANIMTYPE_Jump,
  PLAYER_ANIMTYPE_Dash,
  PLAYER_ANIMTYPE_RollingBack,
  PLAYER_ANIMTYPE_Guard,
  PLAYER_ANIMTYPE_GuardEnd,
  PLAYER_ANIMTYPE_HeavyPunch,
  PLAYER_ANIMTYPE_LightPunch,
  PLAYER_ANIMTYPE_HeavyKick,
  PLAYER_ANIMTYPE_LightKick,
  PLAYER_ANIMTYPE_HeavyPunch_Seat,
  PLAYER_ANIMTYPE_LightPunch_Seat,
  PLAYER_ANIMTYPE_HeavyKick_Seat,
  PLAYER_ANIMTYPE_LightKick_Seat,
  PLAYER_ANIMTYPE_HeavyPunch_Jump,
  PLAYER_ANIMTYPE_LightPunch_Jump,
  PLAYER_ANIMTYPE_HeavyKick_Jump,
  PLAYER_ANIMTYPE_LightKick_Jump,
  PLAYER_ANIMTYPE_HitHigh,
  PLAYER_ANIMTYPE_HitLow,
  PLAYER_ANIMTYPE_HitStrong,
  PLAYER_ANIMTYPE_HitWhileJumping,
  PLAYER_ANIMTYPE_Max
};

enum IORI_ANIM_TYPE : unsigned long long {
  IORI_ANIMTYPE_108ShikiYamiBarai = PLAYER_ANIMTYPE_Max + 1ULL,
  IORI_ANIMTYPE_GaishikiMutan_1,
  IORI_ANIMTYPE_GaishikiMutan_2,
  IORI_ANIMTYPE_Shinigami,
  IORI_ANIMTYPE_HyakushikiOniyaki,
  IORI_ANIMTYPE_127ShikiAoiHana_1,
  IORI_ANIMTYPE_127ShikiAoiHana_2,
  IORI_ANIMTYPE_127ShikiAoiHana_3,
  IORI_ANIMTYPE_UltimateCasting,
  IORI_ANIMTYPE_1211ShikiYaOtome_1,
  IORI_ANIMTYPE_1211ShikiYaOtome_2,
  IORI_ANIMTYPE_1211ShikiYaOtome_3,
  IORI_ANIMTYPE_1211ShikiYaOtome_4,
  IORI_ANIMTYPE_1211ShikiYaOtome_5,
  IORI_ANIMTYPE_1211ShikiYaOtome_6,
  IORI_ANIMTYPE_1211ShikiYaOtome_7,
  IORI_ANIMTYPE_1211ShikiYaOtome_8,
  IORI_ANIMTYPE_1211ShikiYaOtome_9
};

enum PLAYER_ANIM_MODIFIER : unsigned long long {
  ANIMMOD_NONE = 0,
  ANIMMOD_FLIPPED = 1ULL << 63,
  ANIMMOD_BLUEFLAME = 1ULL << 62
};

enum IORI_SKILL {
  IORI_SKILL_None = -1,
  IORI_SKILL_108ShikiYamiBarai = 0,
  IORI_SKILL_GaishikiMutan,
  IORI_SKILL_Shinigami,
  IORI_SKILL_HyakushikiOniyaki,
  IORI_SKILL_127ShikiAoiHana,
  IORI_SKILL_1211ShikiYaOtome,
  IORI_SKILL_Max
};

enum PROJECTILE_TYPE {
  IORI_PROJECTILE_YamiBarai = 0,
  IORI_PROJECTILE_HyakushikiOniyaki_Low,
  IORI_PROJECTILE_HyakushikiOniyaki_High,
};

enum EFFECT_TYPE : unsigned long long {
  EFTYPE_None = 0ULL,
  EFTYPE_Hit_1 = 1ULL,
  EFTYPE_Hit_2,
  EFTYPE_Hit_3,
  EFTYPE_Guard_1,
  EFTYPE_Guard_2,
  EFTYPE_Guard_3,
  EFTYPE_Guard_4,
  EFTYPE_Guard_5,
  EFTYPE_Casting_1,
  EFTYPE_Casting_2,
  EFTYPE_Casting_3,
  EFTYPE_Casting_4,
  EFTYPE_Casting_5,
  EFTYPE_Casting_6,
  EFTYPE_Iori_Explosion,
  EFTYPE_Iori_Casting_YamiBarai,
  EFTYPE_Max
};

enum EFFECT_MOD : unsigned long long {
  EFMOD_NONE = 0ULL,
  EFMOD_FLIPPED = 1ULL << 63,
  EFMOD_BLUEFLAME = 1ULL << 62
};

static Color8Bit ioriTransparentColor = Color8Bit{169, 139, 150, 0};
static Color8Bit changTransparentColor = Color8Bit{17, 91, 124, 0};

unsigned long long MakeKey(unsigned long long type, unsigned long long modify) {
  return type | modify;
}