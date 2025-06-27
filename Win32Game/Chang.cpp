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
  //playerKeySet_ = {'4', '3', '2', '1', 'I', 'L', 'K', 'J'};  // D C B A UP RIGHT DONW LEFT
  playerKeySet_ = {'E', 'R', 'D', 'F', 'I', 'L', 'K', 'J'};  // D C B A UP RIGHT DONW LEFT
}

Chang::~Chang() {
}

void Chang::BeginPlay() {
}

void Chang::Initialize(const Vector& position, bool useCameraPosition, bool flip, KOFPlayer* opponentPlayer) {
  KOFPlayer::Initialize(position, useCameraPosition, flip, opponentPlayer);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(IMGKEY_ChangImage);
  if (nullptr == pImage) {
    return;
  }
  SetCharacterScale(pImage->GetScale(8) * pRender_->GetLocalScale());

  pRender_->CreateAnimation(PAS_Idle, IMGKEY_ChangImage, 8, 13, 50, true, 8);           // 아이들
  pRender_->CreateAnimation(PAS_SeatDown, IMGKEY_ChangImage, 14, 20, 50, true, 16);     // 앉기.
  pRender_->CreateAnimation(PAS_FrontWalk, IMGKEY_ChangImage, 23, 32, 50, true, 23);    // -> 걷기
  pRender_->CreateAnimation(PAS_BackWalk, IMGKEY_ChangImage, 32, 23, 50, true, 32);     // <- 뒤로가기
  pRender_->CreateAnimation(PAS_BackStep, IMGKEY_ChangImage, 33, 35, 50, false, 0);     // <- <- 백스탭
  pRender_->CreateAnimation(PAS_Run, IMGKEY_ChangImage, 23, 32, 20, true, 23);          // ->-> 뛰기
  pRender_->CreateAnimation(PAS_Jump, IMGKEY_ChangImage, 36, 42, 50, false, 0);         // 점프
  pRender_->CreateAnimation(PAS_HeavyKick, IMGKEY_ChangImage, 82, 89, 50, false, 0);    // 발차기
  pRender_->CreateAnimation(PAS_HitTop, IMGKEY_ChangImage, 310, 314, 50, false, 0);     //
  pRender_->CreateAnimation(PAS_HitBottom, IMGKEY_ChangImage, 315, 319, 50, false, 0);  //
  pRender_->CreateAnimation(PAS_HitStrong, IMGKEY_ChangImage,
                            {339, 335, 336, 337, 338, 335, 336, 337, 338, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350},
                            {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 50, 50, 50, 50},
                            false, 0);
  pRender_->CreateAnimation(PAS_HitWhileJumping, 4, {339, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350}, 50, false, 0);

  pRender_->CreateAnimation(-PAS_Idle, -IMGKEY_ChangImage, 8, 13, 50, true, 8);           // 아이들
  pRender_->CreateAnimation(-PAS_SeatDown, -IMGKEY_ChangImage, 14, 20, 50, true, 16);     // 앉기.
  pRender_->CreateAnimation(-PAS_FrontWalk, -IMGKEY_ChangImage, 23, 32, 50, true, 23);    // -> 걷기
  pRender_->CreateAnimation(-PAS_BackWalk, -IMGKEY_ChangImage, 32, 23, 50, true, 32);     // <- 뒤로가기
  pRender_->CreateAnimation(-PAS_BackStep, -IMGKEY_ChangImage, 33, 35, 50, false, 0);     // <- <- 백스탭
  pRender_->CreateAnimation(-PAS_Run, -IMGKEY_ChangImage, 23, 32, 20, true, 23);          // ->-> 뛰기
  pRender_->CreateAnimation(-PAS_Jump, -IMGKEY_ChangImage, 36, 42, 50, false, 0);         // 점프
  pRender_->CreateAnimation(-PAS_HeavyKick, -IMGKEY_ChangImage, 82, 89, 50, false, 0);    // 발차기
  pRender_->CreateAnimation(-PAS_HitTop, -IMGKEY_ChangImage, 310, 314, 50, false, 0);     //
  pRender_->CreateAnimation(-PAS_HitBottom, -IMGKEY_ChangImage, 315, 319, 50, false, 0);  //
  pRender_->CreateAnimation(-PAS_HitStrong, -IMGKEY_ChangImage,
                            {339, 335, 336, 337, 338, /*335, 336, 337, 338,*/ 340, 341, 342, 343, 345, 346, 347, 348, 349, 350},
                            {80, 80, 80, 80, 80, 80, /*50, 50, 50, 50,*/ 80, 80, 80, 80, 80, 80, 80, 80, 80},
                            false, 0);
  pRender_->CreateAnimation(-PAS_HitWhileJumping, -IMGKEY_ChangImage, {339, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350}, 50, false, 0);

  pRender_->SetTransparentColor(changTransparentColor);
  UpdateAnimState(PAS_Idle);

  // STATE
  if (false == pStateComponent_->RegistState(PAS_Idle, PS_Idle, true, true)) {
    return;
  }
  if (false == pStateComponent_->RegistState(PAS_SeatDown, PS_Seat, true, true)) {
    return;
  }
  if (false == pStateComponent_->RegistState(PAS_SeatUp, PS_Seat, true, true)) {
    return;
  }
  if (false == pStateComponent_->RegistState(PAS_FrontWalk, PS_Move, true, true)) {
    return;
  }
  if (false == pStateComponent_->RegistState(PAS_BackWalk, PS_Move, true, true)) {
    return;
  }
  if (false == pStateComponent_->RegistState(PAS_BackStep, PS_Move, false, false)) {
    return;
  }
  if (false == pStateComponent_->RegistState(PAS_Run, PS_Move, true, true)) {
    return;
  }
  if (false == pStateComponent_->RegistState(PAS_RunEnd, PS_Move, false, false)) {
    return;
  }
  if (false == pStateComponent_->RegistState(PAS_Jump, PS_Jump, false, false)) {
    return;
  }
  if (false == pStateComponent_->RegistState(PAS_HeavyKick, PS_Attack, false, false)) {
    return;
  }

  // DAMAGE
  if (false == pAttackTable_->RegistAttackInfo(PAS_HeavyKick, ATTYPE_NormalAttack, ELMTTYPE_Normal, 10.0f, {20.0f, 0.0f})) {
    return;
  }

  // GHOST EFFECT
  pGhostEffect_->SetTransparentColor(changTransparentColor);
}

void Chang::Tick(unsigned long long deltaTick) {
  UpdateCollisionBoundScale();

  CheckPushCollision();

  if (PS_Attack == pStateComponent_->GetPlayerState()) {
    UpdateAttack();
  }

  UpdateCommand();

  if (true == pRender_->IsAnimationEnd()) {
    pCommandComponent_->ExcuteTask();
  }

  ResetInputBitSet();

  UpdateInput();

  if (true == pStateComponent_->CanInput() || true == pRender_->IsAnimationEnd()) {
    CompareInputBitset();
  }

  pSkillComponent_->UpdateActiveSkill();

  //  TODO : 수정사항
  unsigned int curImageIndex = pRender_->GetImageIndex();
  if (prevImageIndex_ != curImageIndex && curImageIndex == 69) {
    pGhostEffect_->Off();
  }
  //  TODO END

  UpdatePrevAnimationIndex();
}

void Chang::CompareInputBitset() {
  if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00000000")) &&
      true == IsEqualInputBitSet(inputUpBitSet_, std::bitset<8>("00000000"))) {
  } else {
    // LEFT UP PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10010000"))) {
      if (FacingRight()) {
        UpdateAnimState(PAS_Jump);
        pMovementComponent_->JumpForward(false, false);
        return;
      } else {
        if (PAS_Run == pStateComponent_->GetCurAnimState()) {
          UpdateAnimState(PAS_Jump);
          pMovementComponent_->JumpForward(false, true);
          pGhostEffect_->On();
          return;
        }
        UpdateAnimState(PAS_Jump);
        pMovementComponent_->JumpForward(false, false);
        return;
      }
    }

    // RIGHT UP PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00110000"))) {
      if (FacingRight()) {
        if (PAS_Run == pStateComponent_->GetCurAnimState()) {
          UpdateAnimState(PAS_Jump);
          pMovementComponent_->JumpForward(true, true);
          pGhostEffect_->On();
          return;
        }
        UpdateAnimState(PAS_Jump);
        pMovementComponent_->JumpForward(true, false);
        return;
      } else {
        UpdateAnimState(PAS_Jump);
        pMovementComponent_->JumpForward(true, false);
        return;
      }
    }

    // RIGHT A - PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00101000"))) {
    }

    // RIGHT B - PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100100"))) {

    }

    // LEFT PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
      if (FacingRight()) {
        UpdateAnimState(PAS_BackWalk);
        pMovementComponent_->MoveBack(FacingRight()/*, pPushBox_->HasHit()*/);
        return;
      } else {
        if (PAS_Run == animState_) {
          pMovementComponent_->Run(false/*, pPushBox_->HasHit()*/);
          return;
        }
        UpdateAnimState(PAS_FrontWalk);
        pMovementComponent_->Move(FacingRight()/*, pPushBox_->HasHit()*/);
        return;
      }
    }
    // LEFT UP
    if (true == IsEqualInputBitSet(inputUpBitSet_, std::bitset<8>("10000000"))) {
    }

    // DOWN PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("01000000"))) {
      UpdateAnimState(PAS_SeatDown);
      return;
    }

    // DOWN UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("01000000"))) {
    }

    // RIGHT PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100000"))) {
      if (FacingRight()) {
        if (PAS_Run == animState_) {
          pMovementComponent_->Run(true/*, pPushBox_->HasHit()*/);
          return;
        }
        UpdateAnimState(PAS_FrontWalk);
        pMovementComponent_->Move(FacingRight()/*, pPushBox_->HasHit()*/);
        return;
      } else {
        UpdateAnimState(PAS_BackWalk);
        pMovementComponent_->MoveBack(FacingRight()/*, pPushBox_->HasHit()*/);
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
      UpdateAnimState(PAS_Jump);
      pMovementComponent_->Jump();
      return;
    }

    // UP UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00010000"))) {
    }

    // A PRESS
    if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000"))) {
      UpdateAnimState(PAS_HeavyKick);
    }

    // A UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00001000"))) {
    }

    // B PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00000100"))) {
    }

    // B UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00000100"))) {
    }

    // C PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
    }

    // C UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00000010"))) {
    }

    // D PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00000001"))) {
      UpdateAnimState(PAS_HeavyKick);
      return;
    }

    // D UP
    if (true == IsContainInputBitSet(inputUpBitSet_, std::bitset<8>("00000001"))) {
    }
  }

  ///////////////////////////// Else
  if (PAS_SeatDown == pStateComponent_->GetCurAnimState()) {
    UpdateAnimState(PAS_SeatUp);
    return;
  }

  if (PAS_Run == pStateComponent_->GetCurAnimState()) {
    UpdateAnimState(PAS_RunEnd);
    return;
  }

  UpdateAnimState(PAS_Idle);
  return;
}
