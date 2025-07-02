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
#include "Chang.h"

Chang::Chang() {
  // playerKeySet_ = {'4', '3', '2', '1', 'I', 'L', 'K', 'J'};  // D C B A UP RIGHT DONW LEFT
  //playerKeySet_ = {'E', 'R', 'D', 'F', 'I', 'L', 'K', 'J'};  // D C B A UP RIGHT DONW LEFT
}

Chang::~Chang() {
}

void Chang::BeginPlay() {
}

void Chang::Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) {
  KOFPlayer::Initialize(isPlayer1, position, useCameraPosition, opponentPlayer);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(IMGTYPE_ChangImage);
  if (nullptr == pImage) {
    return;
  }
  SetCharacterScale(pImage->GetScale(8) * pRender_->GetLocalScale());

  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Idle | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), 8, 13, 50, true, 8);         // ¾ÆÀÌµé
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatDown | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), 14, 20, 50, true, 16);   // ¾É±â.
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_FrontWalk | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), 23, 32, 50, true, 23);  // -> °È±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackWalk | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), 32, 23, 50, true, 32);   // <- µÚ·Î°¡±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackStep | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), 33, 35, 50, false, 0);   // <- <- ¹é½ºÅÇ
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Run | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), 23, 32, 20, true, 23);        // ->-> ¶Ù±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Jump | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), 36, 42, 50, false, 0);       // Á¡ÇÁ
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), 82, 89, 50, false, 0);  // ¹ßÂ÷±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitHigh | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), 310, 314, 50, false, 0);  //
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitLow | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), 315, 319, 50, false, 0);   //
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitStrong | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE),
                            {339, 335, 336, 337, 338, 335, 336, 337, 338, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350},
                            {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 50, 50, 50, 50},
                            false, 0);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitWhileJumping | ANIMMOD_NONE), (IMGTYPE_ChangImage | IMGMOD_NONE), {339, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350}, 50, false, 0);

  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Idle | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), 8, 13, 50, true, 8);         // ¾ÆÀÌµé
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatDown | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), 14, 20, 50, true, 16);   // ¾É±â.
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_FrontWalk | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), 23, 32, 50, true, 23);  // -> °È±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackWalk | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), 32, 23, 50, true, 32);   // <- µÚ·Î°¡±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackStep | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), 33, 35, 50, false, 0);   // <- <- ¹é½ºÅÇ
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Run | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), 23, 32, 20, true, 23);        // ->-> ¶Ù±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Jump | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), 36, 42, 50, false, 0);       // Á¡ÇÁ
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), 82, 89, 50, false, 0);  // ¹ßÂ÷±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitHigh | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), 310, 314, 50, false, 0);  //
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitLow | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), 315, 319, 50, false, 0);   //
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitStrong | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED),
                            {339, 335, 336, 337, 338, 335, 336, 337, 338, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350},
                            {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 50, 50, 50, 50},
                            false, 0);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitWhileJumping | ANIMMOD_FLIPPED), (IMGTYPE_ChangImage | IMGMOD_FLIPPED), {339, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350}, 50, false, 0);

  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_Idle | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), 8, 13, 50, true, 8)) {
    return;
  }
  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatDown | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), 14, 20, 50, true, 16)) {
    return;
  }
  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_FrontWalk | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), 23, 32, 50, true, 23)) {
    return;
  }
  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackWalk | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), 32, 23, 50, true, 32)) {
    return;
  }

  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackStep | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), 33, 35, 50, false, 0)) {
    return;
  }
  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_Run | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), 23, 32, 20, true, 23)) {
    return;
  }
  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_Jump | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), 36, 42, 50, false, 0)) {
    return;
  }
  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), 82, 89, 50, false, 0)) {
    return;
  }
  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitHigh | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), 310, 314, 50, false, 0)) {
    return;
  }
  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitLow | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), 315, 319, 50, false, 0)) {
    return;
  }
  if( false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitStrong | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME),
                            {339, 335, 336, 337, 338, 335, 336, 337, 338, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350},
                            {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 50, 50, 50, 50},
                                         false, 0)) {
    return;
  }
  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitWhileJumping | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME), { 339, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350 }, 50, false, 0)) {
    return;
  }


  if (false == pRender_->CreateAnimation((PLAYER_ANIMTYPE_Idle | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), 8, 13, 50, true, 8)) {
    return;
  }
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_SeatDown | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), 14, 20, 50, true, 16);   // ¾É±â.
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_FrontWalk | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), 23, 32, 50, true, 23);  // -> °È±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackWalk | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), 32, 23, 50, true, 32);   // <- µÚ·Î°¡±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_BackStep | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), 33, 35, 50, false, 0);   // <- <- ¹é½ºÅÇ
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Run | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), 23, 32, 20, true, 23);        // ->-> ¶Ù±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_Jump | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), 36, 42, 50, false, 0);       // Á¡ÇÁ
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HeavyKick | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), 82, 89, 50, false, 0);  // ¹ßÂ÷±â
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitHigh | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), 310, 314, 50, false, 0);  //
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitLow | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), 315, 319, 50, false, 0);   //
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitStrong | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME),
                            {339, 335, 336, 337, 338, 335, 336, 337, 338, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350},
                            {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 50, 50, 50, 50},
                            false, 0);
  pRender_->CreateAnimation((PLAYER_ANIMTYPE_HitWhileJumping | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME), (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME), {339, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350}, 50, false, 0);

  UpdateAnimState(PLAYER_ANIMTYPE_Idle);

  // STATE
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Idle, {PS_Idle}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatDown, {PS_Seat}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_SeatUp, {PS_Seat}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_FrontWalk, {PS_Move}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackWalk, {PS_Move}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_BackStep, {PS_Move}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Run, {PS_Move}, true);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_RunEnd, {PS_Move}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_Jump, {PS_Jump}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HeavyKick, {PS_Attack}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HitHigh, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HitLow, {PS_Hit}, false);
  pStateComponent_->RegistState(PLAYER_ANIMTYPE_HitStrong, {PS_Hit}, false);

  // DAMAGE
  pAttackTable_->RegistAttackInfo(PLAYER_ANIMTYPE_HeavyKick, ATTYPE_NormalAttack, ELMTTYPE_Normal, EFTYPE_Hit_2, false, 10.0f, {20.0f, 0.0f});
}

void Chang::CompareInputBitset() {

  if (pStateComponent_->EqualPlayerState({PS_Jump})) {
    // A | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_Jump);
      return;
    }
    // B | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000100"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick_Jump);
      return;
    }
    // C | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_Jump);
      return;
    }
    // D | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000001"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_Jump);
      return;
    }

    if (true == pRender_->IsAnimationEnd()) {
      UpdateAnimState(PLAYER_ANIMTYPE_Idle);
      return;
    }
    return;
  }

  if (pStateComponent_->ContainPlayerState({PS_Seat})) {
    // A | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01001000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch_Seat);
      return;
    }
    // B | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000100"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick_Seat);
      return;
    }
    // C | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000010"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch_Seat);
      return;
    }
    // D | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000001"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick_Seat);
      return;
    }
    // DOWN | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_SeatDown, ANIMMOD_NONE, 18, 50);
      return;
    }

    UpdateAnimState(PLAYER_ANIMTYPE_SeatUp);
    return;
  }

  if (pStateComponent_->EqualPlayerState({PS_Guard})) {
    if (false == pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
      UpdateAnimState(PLAYER_ANIMTYPE_GuardEnd);
      return;
    }
  }

  if (pStateComponent_->ContainPlayerState({PS_Run})) {
    if (false == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00100000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_RunEnd);
      return;
    }
  }

  if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00000000")) &&
      true == IsEqualInputBitSet(inputUpBitSet_, std::bitset<8>("00000000"))) {
    UpdateAnimState(PLAYER_ANIMTYPE_Idle);
    return;
  } else {
    // LEFT | PRESS Contain
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
      if (pOpponentPlayer_->GetPlayerStateComponent()->ContainPlayerState({PS_Attack})) {
        UpdateAnimState(PLAYER_ANIMTYPE_Guard);
        return;
      }
    }

    // RIGHT | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100000"))) {
      if (true == pStateComponent_->ContainPlayerState({PS_Run})) {
        pMovementComponent_->Run(FacingRight());
        return;
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_FrontWalk);
        pMovementComponent_->Move(FacingRight());
        return;
      }
    }

    // LEFT | PRESS Equal
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_BackWalk);
      pMovementComponent_->MoveBack(FacingRight());
      return;
    }

    // DOWN | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("01000000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_SeatDown);
      return;
    }

    // RIGHT UP | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00110000"))) {
      if (true == pStateComponent_->ContainPlayerState({PS_Run})) {
        UpdateAnimState(PLAYER_ANIMTYPE_Jump);
        pMovementComponent_->JumpForward(FacingRight(), true);
        pGhostEffect_->On();
        return;
      } else {
        UpdateAnimState(PLAYER_ANIMTYPE_Jump);
        pMovementComponent_->JumpForward(FacingRight(), false);
        return;
      }
    }

    // LEFT UP | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10010000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_Jump);
      pMovementComponent_->JumpForward(!FacingRight(), false);
      return;
    }

    // UP | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00010000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_Jump);
      pMovementComponent_->Jump();
      return;
    }

    // A B LEFT | PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10001100"))) {
      UpdateAnimState((PLAYER_ANIMTYPE_RollingBack));
      pMovementComponent_->Dash(!FacingRight(), 300.0f, 400.0f);
      pGhostEffect_->On();
      return;
    }

    // A B | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001100"))) {
      UpdateAnimState((PLAYER_ANIMTYPE_Dash));
      pMovementComponent_->Dash(FacingRight(), 300.0f, 500.0f);
      pGhostEffect_->On();
      return;
    }

    //// RIGHT A | PRESS
    //if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00101000"))) {
    //  UpdateAnimState(IORI_ANIMTYPE_GaishikiMutan_1);
    //  pSkillComponent_->ActivateSkill(IORI_SKILL_GaishikiMutan);
    //  return;
    //}

    //// RIGHT B | PRESS
    //if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100100"))) {
    //  UpdateAnimState(IORI_ANIMTYPE_Shinigami);
    //  pSkillComponent_->ActivateSkill(IORI_SKILL_Shinigami);
    //  return;
    //}

    // A | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightPunch);
      return;
    }

    // B | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000100"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_LightKick);
      return;
    }

    // C | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyPunch);
      return;
    }

    // D | PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000001"))) {
      UpdateAnimState(PLAYER_ANIMTYPE_HeavyKick);
      return;
    }

    UpdateAnimState(PLAYER_ANIMTYPE_Idle);
    return;
  }
}
