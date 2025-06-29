#include "stdafx.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"
#include "BackGroundMask.h"
#include "MovementComponent.h"
#include "AttackTable.h"
#include "SkillComponent.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
#include "HealthComponent.h"
#include "StateComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"
#include "Iori.h"

Iori::Iori() {
  playerKeySet_ = {'A', 'S', 'Z', 'X', VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT};  // D C B A UP RIGHT DONW LEFT
}

Iori::~Iori() {
}

void Iori::BeginPlay() {
}

void Iori::Initialize(const Vector& position, bool useCameraPosition, bool flip, KOFPlayer* opponentPlayer) {
  KOFPlayer::Initialize(position, useCameraPosition, flip, opponentPlayer);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(IMGTYPE_IoriImage);
  if (nullptr == pImage) {
    return;
  }
  SetCharacterScale(pImage->GetScale(7) * pRender_->GetLocalScale());

  // RENDERER
  bool debugFlag = true;
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_Idle | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 7, 15, 50, true, 7);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatDown | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 16, 23, 50, true, 18);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatUp | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 24, 25, 50, false, 24);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_FrontWalk | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 27, 34, 50, true, 27);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackWalk | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 35, 44, 50, true, 35);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackStep | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 45, 48, 50, false, 45);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_Run | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 49, 57, 50, true, 51);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_RunEnd | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 58, 60, 50, false, 59);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_Jump | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 61, 69, 50, false, 61);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 108, 117, 50, false, 108);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightKick | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 94, 98, 50, false, 94);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyPunch | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 99, 107, 50, false, 99);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightPunch | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 88, 93, 50, false, 88);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_108ShikiYamiBarai | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 223, 230, 50, false, 223);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_GaishikiMutan_1 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 99, 107, 50, false, 99);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_GaishikiMutan_2 | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 160, 164, 50, false, 160);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_Shinigami | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 136, 144, 50, false, 136);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_HyakushikiOniyaki| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 276, 291, 50, false, 276);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_1| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 255, 261, 50, false, 255);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_2| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 262, 268, 50, false, 262);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_3| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 269, 275, 50, false, 269);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_UltimateCasting | ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 344, 347, 100, false, 344);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_1| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 70, 77, 20, false, 70);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_2| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 118, 122, 20, false, 118);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_3| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 88, 92, 20, false, 88);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_4| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 128, 135, 20, false, 128);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_5| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 223, 229, 20, false, 223);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_6| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 99, 106, 20, false, 99);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_7| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 159, 163, 20, false, 159);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_8| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 99, 107, 20, false, 99);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_9| ANIMMOD_NONE), (IMGTYPE_IoriImage | IMGMOD_NONE), 347, 352, 250, false, 347);

  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_Idle | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 7, 15, 50, true, 7);      // ¾ÆÀÌµé
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatDown | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 16, 23, 50, true, 18);  // ¾É±â. Down
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatUp | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 24, 25, 50, false, 24);   // ¾É±â. Up
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_FrontWalk | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 27, 34, 50, true, 27);  // -> °È±â
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackWalk | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 35, 44, 50, true, 35);   // <- µÚ·Î°¡±â
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackStep | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 45, 48, 50, false, 45);  // <- <- ¹é½ºÅÇ
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_Run | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 49, 57, 50, true, 51);        // ->-> ¶Ù±â Start
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_RunEnd | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 58, 60, 50, false, 59);    // ->-> ¶Ù±â Stop
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_Jump | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 61, 69, 50, false, 61);      // Á¡ÇÁ
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 108, 117, 50, false, 108);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightKick | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 94, 98, 50, false, 94);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyPunch | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 99, 107, 50, false, 99);
  debugFlag = pRender_->CreateAnimation((PLAYER_ANIMTYPE_LightPunch | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 88, 93, 50, false, 88);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_108ShikiYamiBarai | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 223, 230, 50, false, 223);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_GaishikiMutan_1 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 99, 107, 50, false, 99);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_GaishikiMutan_2 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 160, 164, 50, false, 160);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_Shinigami | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 136, 144, 50, false, 136);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_HyakushikiOniyaki | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 276, 291, 50, false, 276);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_1 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 255, 261, 50, false, 255);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_2 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 262, 268, 50, false, 262);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_127ShikiAoiHana_3 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 269, 275, 50, false, 269);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_UltimateCasting | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 344, 347, 100, false, 344);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_1 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 70, 77, 20, false, 70);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_2 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 118, 122, 20, false, 118);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_3 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 88, 92, 20, false, 88);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_4 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 128, 135, 20, false, 128);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_5 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 223, 229, 20, false, 223);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_6 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 99, 106, 20, false, 99);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_7 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 159, 163, 20, false, 159);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_8 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 99, 107, 20, false, 99);
  debugFlag = pRender_->CreateAnimation((IORI_ANIMTYPE_1211ShikiYaOtome_9 | ANIMMOD_FLIPPED), (IMGTYPE_IoriImage | IMGMOD_FLIPPED), 347, 352, 250, false, 347);

  pRender_->SetTransparentColor(ioriTransparentColor);
  UpdateAnimState(PLAYER_ANIMTYPE_Idle);

  // STATE
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_Idle, PS_Idle, true, true);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatDown, PS_Seat, true, true);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatUp, PS_Seat, true, true);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_FrontWalk, PS_Move, true, true);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackWalk, PS_Move, true, true);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackStep, PS_Move, false, false);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_Run, PS_Move, true, true);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_RunEnd, PS_Move, false, false);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_Jump, PS_Jump, false, false);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightKick, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyPunch, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(PLAYER_ANIMTYPE_LightPunch, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_108ShikiYamiBarai, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_1, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_GaishikiMutan_2, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_Shinigami, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_HyakushikiOniyaki, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_1, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_2, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_127ShikiAoiHana_3, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_UltimateCasting, PS_None, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_1, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_2, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_3, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_4, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_5, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_6, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_7, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_8, PS_Attack, false, false);
  debugFlag = pStateComponent_->RegistState(IORI_ANIMTYPE_1211ShikiYaOtome_9, PS_Attack, false, false);

  // DAMAGE
  debugFlag = pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightKick, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyPunch, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_LightPunch, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 10.0f, {20.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_108ShikiYamiBarai, ATTYPE_NormalAttack, ELMTTYPE_BlueFire, EFKEY_Hit_2, 5.0f, {20.0f, 60.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {5.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_GaishikiMutan_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {20.0f, 40.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_Shinigami, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 15.0f, {20.0f, 80.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_HyakushikiOniyaki, ATTYPE_NormalAttack, ELMTTYPE_BlueFire, EFKEY_Hit_2, 20.0f, {40.0f, 80.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_1, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {10.0f, 00.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_2, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {10.0f, 00.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_127ShikiAoiHana_3, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {20.0f, 80.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_1, ATTYPE_LowAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_2, ATTYPE_HighAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_3, ATTYPE_HighAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_4, ATTYPE_HighAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_5, ATTYPE_LowAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_6, ATTYPE_LowAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_7, ATTYPE_HighAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_8, ATTYPE_LowAttack, ELMTTYPE_Normal, EFKEY_Hit_2, 5.0f, {0.0f, 0.0f});
  debugFlag = pAttackTable_->RegistAttackInfo(IORI_ANIMTYPE_1211ShikiYaOtome_9, ATTYPE_StrongAttack, ELMTTYPE_Normal, EFKEY_Iori_Explosion, 10.0f, {45.0f, 60.0f});

  // SKILL
  debugFlag = pSkillComponent_->RegistSkill(IORI_SKILL_GaishikiMutan, &Iori::GaishikiMutan, this);
  debugFlag = pSkillComponent_->RegistSkill(IORI_SKILL_108ShikiYamiBarai, &Iori::ShikiYamiBarai108, this);
  debugFlag = pSkillComponent_->RegistSkill(IORI_SKILL_Shinigami, &Iori::Shinigami, this);
  debugFlag = pSkillComponent_->RegistSkill(IORI_SKILL_HyakushikiOniyaki, &Iori::HyakushikiOniyaki, this);
  debugFlag = pSkillComponent_->RegistSkill(IORI_SKILL_127ShikiAoiHana, &Iori::ShikiAoiHana127, this);
  debugFlag = pSkillComponent_->RegistSkill(IORI_SKILL_1211ShikiYaOtome, &Iori::ShikiYaOtome1211, this);

  // COMMAND
 debugFlag = pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_A}, std::bind(&Iori::Command_1, this));
 debugFlag = pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_B}, std::bind(&Iori::Command_1, this));
 debugFlag = pCommandComponent_->RegistCommand({CK_Left, CK_Left}, std::bind(&Iori::Command_2, this));
 debugFlag = pCommandComponent_->RegistCommand({CK_Right, CK_Right}, std::bind(&Iori::Command_3, this));
 debugFlag = pCommandComponent_->RegistCommand({CK_Right, CK_Down, CK_Right, CK_A}, std::bind(&Iori::Command_4, this));
 debugFlag = pCommandComponent_->RegistCommand({CK_Right, CK_Down, CK_Right, CK_C}, std::bind(&Iori::Command_4, this));
 debugFlag = pCommandComponent_->RegistCommand({CK_Down, CK_Left, CK_A}, std::bind(&Iori::Command_5, this));
 debugFlag = pCommandComponent_->RegistCommand({CK_Down, CK_Left, CK_C}, std::bind(&Iori::Command_5, this));
 debugFlag = pCommandComponent_->RegistCommand({CK_Down, CK_Right, CK_Down, CK_Left, CK_A}, std::bind(&Iori::Command_6, this));
 debugFlag = pCommandComponent_->RegistCommand({CK_Down, CK_Right, CK_Down, CK_Left, CK_C}, std::bind(&Iori::Command_6, this));

  // PROJECTILE
  pProjectileComponent_->RegistProjectileInfo(IORI_PROJECTILE_108ShikiYamiBarai, IMGTYPE_IoriImage, 239, 244, 20, true, {169, 139, 150, 0}, {35.0f, 0.0f}, {180.0f, 50.0f}, {1500.0f, 0.0f});
  pProjectileComponent_->RegistProjectileInfo(IORI_PROJECTILE_HyakushikiOniyaki_Low, IMGTYPE_IoriImage, 292, 301, 50, false, {169, 139, 150, 0}, {0.0f, -7.0f}, {50.0f, -30.0f}, {0.0f, 0.0f});
  pProjectileComponent_->RegistProjectileInfo(IORI_PROJECTILE_HyakushikiOniyaki_High, IMGTYPE_IoriImage, 302, 311, 40, false, {169, 139, 150, 0}, {0.0f, -7.0f}, {-80.0f, -200.0f}, {0.0f, 0.0f});

  // GHOST EFFECT
  pGhostEffect_->SetTransparentColor(ioriTransparentColor);
}

void Iori::CompareInputBitset() {
  if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00000000")) &&
      true == IsEqualInputBitSet(inputUpBitSet_, std::bitset<8>("00000000"))) {
  } else {
    // LEFT UP PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10010000"))) {
      if (FacingRight()) {
        UpdateAnimState(PLAYER_ANIMTYPE_Jump);
        pMovementComponent_->JumpForward(false, false);
        return;
      } else {
        if (PLAYER_ANIMTYPE_Run == pStateComponent_->GetCurAnimState()) {
          UpdateAnimState(PLAYER_ANIMTYPE_Jump);
          pMovementComponent_->JumpForward(false, true);
          pGhostEffect_->On();
          return;
        }
        UpdateAnimState(PLAYER_ANIMTYPE_Jump);
        pMovementComponent_->JumpForward(false, false);
        return;
      }
    }

    // RIGHT UP PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00110000"))) {
      if (FacingRight()) {
        if (PLAYER_ANIMTYPE_Run == pStateComponent_->GetCurAnimState()) {
          UpdateAnimState(PLAYER_ANIMTYPE_Jump);
          pMovementComponent_->JumpForward(true, true);
          pGhostEffect_->On();
          return;
        }
        UpdateAnimState(PLAYER_ANIMTYPE_Jump);
        pMovementComponent_->JumpForward(true, false);
        return;
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_Jump);
        pMovementComponent_->JumpForward(true, false);
        return;
      }
    }

    // RIGHT A - PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00101000"))) {
      if (FacingRight()) {
        UpdateAnimState(IORI_ANIMTYPE_GaishikiMutan_1);
        pSkillComponent_->ActivateSkill(IORI_SKILL_GaishikiMutan);
        return;
      }
    }

    // RIGHT B - PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100100"))) {
      if (FacingRight()) {
        UpdateAnimState(IORI_ANIMTYPE_Shinigami);
        pSkillComponent_->ActivateSkill(IORI_SKILL_Shinigami);
        return;
      }
    }

    // LEFT PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
      if (FacingRight()) {
        UpdateAnimState(PLAYER_ANIMTYPE_BackWalk);
        pMovementComponent_->MoveBack(FacingRight());
        return;
      } else {
        if (PLAYER_ANIMTYPE_Run == animState_) {
          pMovementComponent_->Run(false);
          return;
        }
        UpdateAnimState(PLAYER_ANIMTYPE_FrontWalk);
        pMovementComponent_->Move(FacingRight());
        return;
      }
    }
    // LEFT UP
    if (true == IsEqualInputBitSet(inputUpBitSet_, std::bitset<8>("10000000"))) {
    }

    // DOWN PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("01000000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_SeatDown);
      return;
    }

    // DOWN UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("01000000"))) {
    }

    // RIGHT PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100000"))) {
      if (FacingRight()) {
        if (PLAYER_ANIMTYPE_Run == animState_) {
          pMovementComponent_->Run(true /*, pPushBox_->HasHit()*/);
          return;
        }
        UpdateAnimState(PLAYER_ANIMTYPE_FrontWalk);
        pMovementComponent_->Move(FacingRight() /*, pPushBox_->HasHit()*/);
        return;
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_BackWalk);
        pMovementComponent_->MoveBack(FacingRight() /*, pPushBox_->HasHit()*/);
        return;
      }
    }

    // RIGHT UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00100000"))) {
      if (FacingRight()) {
      }
    }

    // UP PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00010000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_Jump);
      pMovementComponent_->Jump();
      return;
    }

    // UP UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00010000"))) {
    }

    // A PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch);
      return;
    }

    // A UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00001000"))) {
    }

    // B PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000100"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick);
      return;
    }

    // B UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00000100"))) {
    }

    // C PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch);
      return;
    }

    // C UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00000010"))) {
    }

    // D PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000001"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick);
      return;
    }

    // D UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00000001"))) {
    }
  }

  ///////////////////////////// Else
  if (PLAYER_ANIMTYPE_SeatDown == pStateComponent_->GetCurAnimState()) {
    UpdateAnimState(PLAYER_ANIMTYPE_SeatUp);
    return;
  }

  if (PLAYER_ANIMTYPE_Run == pStateComponent_->GetCurAnimState()) {
    UpdateAnimState(PLAYER_ANIMTYPE_RunEnd);
    return;
  }

  UpdateAnimState(PLAYER_ANIMTYPE_Idle);
  return;
}

void Iori::Command_1() {
  UpdateAnimState(IORI_ANIMTYPE_108ShikiYamiBarai);
  pSkillComponent_->ActivateSkill(IORI_SKILL_108ShikiYamiBarai);
}

void Iori::Command_2() {
  UpdateAnimState(PLAYER_ANIMTYPE_BackStep);
  pMovementComponent_->BackStep((FacingRight()));
}

void Iori::Command_3() {
  UpdateAnimState(PLAYER_ANIMTYPE_Run);
}

void Iori::Command_4() {
  UpdateAnimState(IORI_ANIMTYPE_HyakushikiOniyaki);
  pSkillComponent_->ActivateSkill(IORI_SKILL_HyakushikiOniyaki);
}

void Iori::Command_5() {
  UpdateAnimState(IORI_ANIMTYPE_127ShikiAoiHana_1);
  pSkillComponent_->ActivateSkill(IORI_SKILL_127ShikiAoiHana);
}

void Iori::Command_6() {
  Level* pLevel = GetLevel();
  if (nullptr == pLevel) {
    return;
  }

  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  BackGroundMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  UpdateAnimState(IORI_ANIMTYPE_UltimateCasting);
  pSkillComponent_->ActivateSkill(IORI_SKILL_1211ShikiYaOtome);

  EffectManager::Instance()->SpawnEffect(pKOFLevel, EFKEY_Casting_1, GetPosition() + Vector{0.0f, -250.0f});
  EffectManager::Instance()->SpawnEffect(pKOFLevel, EFKEY_Casting_2, GetPosition() + Vector{0.0f, -250.0f});
  pKOFLevel->FreezeActors({pOpponentPlayer_}, true);
  pBackGroundMask->FadeOut(IMGTYPE_BlackBoardImage, 50.0f);
}

void Iori::GaishikiMutan() {
  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (IORI_ANIMTYPE_GaishikiMutan_1 == pStateComponent_->GetCurAnimState()) {
    if (100 <= curImageIndex && 104 >= curImageIndex) {
      if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000"))) {
        pSkillComponent_->SetMiscTemp(true);
      }
    }

    if (true == pAttackBox_->HasHit() && 105 == curImageIndex && true == pSkillComponent_->GetMiscTemp()) {
      UpdateAnimState(IORI_ANIMTYPE_GaishikiMutan_2);
    }
  }
}

void Iori::ShikiYamiBarai108() {
  if (nullptr == pRender_) {
    return;
  }

  if (nullptr != pRender_ && true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (prevImageIndex_ == curImageIndex) {
    return;
  }

  if (226 == curImageIndex) {
    pProjectileComponent_->FireProjectile(IORI_PROJECTILE_108ShikiYamiBarai, FacingRight());
  }
}

void Iori::Shinigami() {
  if (nullptr == pRender_) {
    return;
  }

  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }
}

void Iori::HyakushikiOniyaki() {
  if (nullptr == pRender_) {
    return;
  }

  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (prevImageIndex_ == curImageIndex) {
    return;
  }

  if (276 == curImageIndex) {
    pMovementComponent_->Dash(FacingRight(), 150.0f, 150.0f);
  }

  if (281 == curImageIndex) {
    pMovementComponent_->Jump(FacingRight(), {0.3f, 60.0f});
    pProjectileComponent_->FireProjectile(IORI_PROJECTILE_HyakushikiOniyaki_Low, FacingRight());
  }

  if (284 == curImageIndex) {
    pProjectileComponent_->FireProjectile(IORI_PROJECTILE_HyakushikiOniyaki_High, FacingRight());
  }
}

void Iori::ShikiAoiHana127() {
  if (nullptr == pRender_) {
    return;
  }

  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();
  if (prevImageIndex_ == curImageIndex) {
    return;
  }

  if (curImageIndex == 257) {
    pMovementComponent_->Dash(FacingRight(), 150.0f, 80.0f);
  }

  if (curImageIndex == 262) {
    pMovementComponent_->Dash(FacingRight(), 150.0f, 80.0f);
  }

  if (curImageIndex == 269) {
    pMovementComponent_->Jump(FacingRight(), {0.6f, 60.0f});
  }

  if (IORI_ANIMTYPE_127ShikiAoiHana_1 == pStateComponent_->GetCurAnimState()) {
    if (257 <= curImageIndex && 260 >= curImageIndex) {
      if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000")) ||
          true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
        pSkillComponent_->SetMiscTemp(true);
      }

      if (pAttackBox_->HasHit() && pSkillComponent_->GetMiscTemp() == true) {
        UpdateAnimState(IORI_ANIMTYPE_127ShikiAoiHana_2);
        pSkillComponent_->SetMiscTemp(false);
      }
    }
  }

  if (IORI_ANIMTYPE_127ShikiAoiHana_2 == pStateComponent_->GetCurAnimState()) {
    if (IORI_ANIMTYPE_127ShikiAoiHana_2 == pStateComponent_->GetCurAnimState() && 264 <= curImageIndex && 267 >= curImageIndex) {
      if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000")) ||
          true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
        pSkillComponent_->SetMiscTemp(true);
      }

      if (pAttackBox_->HasHit() && true == pSkillComponent_->GetMiscTemp()) {
        UpdateAnimState(IORI_ANIMTYPE_127ShikiAoiHana_3);
      }
    }
  }
}

void Iori::ShikiYaOtome1211() {
  if (nullptr == pRender_) {
    return;
  }
  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  Level* pLevel = GetLevel();
  if (nullptr == pLevel) {
    return;
  }

  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  BackGroundMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  switch (pStateComponent_->GetCurAnimState()) {
    case IORI_ANIMTYPE_UltimateCasting: {
      if (347 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_1);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_1: {
      if (70 == curImageIndex) {
        pKOFLevel->DefreezeActors();
        pBackGroundMask->FadeIn(50);
        break;
      }

      if (72 == curImageIndex) {
        pMovementComponent_->Dash(FacingRight(), 250.0f, 1000.0f);
        break;
      }

      if (pAttackBox_->HasHit()) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_2);
        pOpponentPlayer_->SetControlLocked(true);
        pMovementComponent_->Dash(FacingRight(), 250.0f, 1000.0f);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_2: {
      if (pOpponentPlayer_->GetPosition().X - GetPosition().X <= 300.0f * FacingRightFlag()) {
        pMovementComponent_->StopDash();
      }

      if (120 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }

      if (122 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_3);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_3: {
      if (90 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      if (92 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_4);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_4: {
      if (135 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_5);
        break;
      }

      if (138 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_5: {
      if (227 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }

      if (229 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_6);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_6: {
      if (102 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      if (106 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_7);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_7: {
      if (161 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      if (163 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_8);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_8: {
      if (102 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      if (106 == curImageIndex) {
        UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_9);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_9: {
      if (349 == curImageIndex) {
        const Vector& ioriPosition = GetPosition();
        pOpponentPlayer_->SetPosition(ioriPosition + Vector{100.0f * FacingRightFlag(), -50.0f});
        break;
      }
      if (351 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }
      if (352 == curImageIndex) {
        pOpponentPlayer_->SetControlLocked(false);
        break;
      }
      break;
    }
    default:
      break;
  }
}
