#include "stdafx.h"
#include "KOFPlayer.h"
#include "MovementComponent.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
#include "HealthComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"

#include "Iori.h"

Iori::Iori()
    : prevImageIndex(0) {
}

Iori::~Iori() {
}

void Iori::BeginPlay() {
}

void Iori::Initialize(const Vector& position, bool useCameraPosition, bool flip) {
  KOFPlayer::Initialize(position, useCameraPosition, flip);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(3);
  if (nullptr == pImage) {
    return;
  }
  SetCharacterScale(pImage->GetScale(7) * pRender_->GetLocalScale());

  // RENDERER
  pRender_->CreateAnimation(PAS_Idle, 3, 7, 15, 50, true, 7);              // 아이들
  pRender_->CreateAnimation(PAS_SeatDown, 3, 16, 23, 50, true, 18);        // 앉기. Down
  pRender_->CreateAnimation(PAS_SeatUp, 3, 24, 25, 50, false, 24);         // 앉기. Up
  pRender_->CreateAnimation(PAS_FrontWalk, 3, 27, 34, 50, true, 27);       // -> 걷기
  pRender_->CreateAnimation(PAS_BackWalk, 3, 35, 44, 50, true, 35);        // <- 뒤로가기
  pRender_->CreateAnimation(PAS_BackStep, 3, 45, 48, 50, false, 45);       // <- <- 백스탭
  pRender_->CreateAnimation(PAS_Run, 3, 49, 57, 50, true, 51);             // ->-> 뛰기 Start
  pRender_->CreateAnimation(PAS_RunEnd, 3, 58, 60, 50, false, 59);         // ->-> 뛰기 Stop
  pRender_->CreateAnimation(PAS_Jump, 3, 61, 69, 50, false, 61);           // 점프
  pRender_->CreateAnimation(PAS_HeavyKick, 3, 108, 117, 50, false, 108);   // 발차기
  pRender_->CreateAnimation(PAS_Skill1, 3, 223, 230, 50, false, 223);      // 커맨드 테스트.
  pRender_->CreateAnimation(IOAS_MONGTAN_1, 3, 99, 107, 50, false, 99);    // 커맨드 테스트.
  pRender_->CreateAnimation(IOAS_MONGTAN_2, 3, 159, 164, 50, false, 159);  // 커맨드 테스트.

  pRender_->CreateAnimation(-PAS_Idle, -3, 7, 15, 50, true, 7);             // 아이들
  pRender_->CreateAnimation(-PAS_SeatDown, -3, 16, 23, 50, true, 18);       // 앉기.
  pRender_->CreateAnimation(-PAS_FrontWalk, -3, 27, 34, 50, true, 27);      // -> 걷기
  pRender_->CreateAnimation(-PAS_BackWalk, -3, 35, 44, 50, true, 35);       // <- 뒤로가기
  pRender_->CreateAnimation(-PAS_BackStep, -3, 45, 48, 50, false, 45);      // <- <- 백스탭
  pRender_->CreateAnimation(-PAS_Run, -3, 49, 58, 50, true, 51);            // ->-> 뛰기
  pRender_->CreateAnimation(-PAS_Jump, -3, 61, 69, 50, false, 61);          // 점프
  pRender_->CreateAnimation(-PAS_HeavyKick, -3, 108, 117, 50, false, 108);  // 발차기
  pRender_->CreateAnimation(-PAS_Skill1, -3, 223, 230, 50, false, 223);     // 커맨드 테스트.

  pRender_->SetTransparentColor(ioriTransparentColor);

  //pRender_->ChangeAnimation(PAS_Idle * FacingRightFlag());
  ChangeAnimation(PAS_Idle * FacingRightFlag());

  // COMMAND
  if (false == pCommandComponent_->RegistCommend({CK_Left, CK_Down, CK_Right}, std::bind(&Iori::CommandSkill_1, this))) {
    return;
  }

  if (false == pCommandComponent_->RegistCommend({CK_Left, CK_Left}, std::bind(&Iori::CommandSkill_2, this))) {
    return;
  }

  if (false == pCommandComponent_->RegistCommend({CK_Right, CK_Right}, std::bind(&Iori::CommandSkill_3, this))) {
    return;
  }

  // PROJECTILE
  if (false == pProjectileComponent_->RegistProjectileInfo(1, 3, 239, 244, 20, true, {169, 139, 150, 0}, {35.0f, 0.0f}, {180.0f, 50.0f}, {1500.0f, 0.0f})) {
    return;
  }

  // GHOST EFFECT
  pGhostEffect_->SetTransparentColor(ioriTransparentColor);
}

void Iori::Tick(unsigned long long deltaTick) {
  CollisionPushUpdate();

  CollisionBoundUpdate();

  CommandUpdate();

  if (-1 != forcedReservedAnim_)
  {
    //pRender_->ChangeAnimation(forcedReservedAnim_ * FacingRightFlag());
    ChangeAnimation(forcedReservedAnim_ * FacingRightFlag());
    forcedReservedAnim_ = -1;
      return;
  }

  if (true == pRender_->IsPlayingLoopAnimation()) {
    InputUpdate(deltaTick);

    if (true == pCommandComponent_->isWaitingTask()) {
      pCommandComponent_->ExcuteTask();
    }

    //pRender_->ChangeAnimation(animState_ * FacingRightFlag());
    ChangeAnimation(animState_ * FacingRightFlag());
  }

  CollisionComponent* pTargetCollision = nullptr;
  if (CheckAttackCollision(&pTargetCollision)) {
    if (nullptr != pTargetCollision) {
      Actor* pTargetOwner = pTargetCollision->GetOwner();
      if (nullptr == pTargetOwner) {
        return;
      }
      KOFPlayer* pTargetPlayer = dynamic_cast<KOFPlayer*>(pTargetOwner);
      if (nullptr == pTargetPlayer) {
        return;
      }
      pTargetCollision->OnCollision();
      pTargetPlayer->HitEvent(50.0f, {50.0f, 80.0f});
      TimeManager::Instance()->OnFrameFreeze(200);

      // Calculate Effect Position.
      Vector collisionSectionLeftTop = {
          pAttackBox_->GetCollisionInfo().Left() > pTargetCollision->GetCollisionInfo().Left() ? pAttackBox_->GetCollisionInfo().Left() : pTargetCollision->GetCollisionInfo().Left(),
          pAttackBox_->GetCollisionInfo().Top() > pTargetCollision->GetCollisionInfo().Top() ? pAttackBox_->GetCollisionInfo().Top() : pTargetCollision->GetCollisionInfo().Top(),
      };

      Vector collisionSectionRightBottom = {
          pAttackBox_->GetCollisionInfo().Right() < pTargetCollision->GetCollisionInfo().Right() ? pAttackBox_->GetCollisionInfo().Right() : pTargetCollision->GetCollisionInfo().Right(),
          pAttackBox_->GetCollisionInfo().Bottom() < pTargetCollision->GetCollisionInfo().Bottom() ? pAttackBox_->GetCollisionInfo().Bottom() : pTargetCollision->GetCollisionInfo().Bottom(),
      };

      Vector effectPosition = {
          (collisionSectionRightBottom.X + collisionSectionLeftTop.X) / 2,
          (collisionSectionRightBottom.Y + collisionSectionLeftTop.Y) / 2};

      // 이펙트도 여기서 스폰.
      EffectManager::Instance()->SpawnEffect(GetLevel(), 2, effectPosition);
    }
  }

  TriggerEventAtAnimationIndex();

  CollisionPushUpdate();

  //CollisionReset();
}

void Iori::InputUpdate(unsigned long long curTick) {
  if (false == InputManager::Instance()->IsPress(VK_LEFT) &&
      false == InputManager::Instance()->IsUp(VK_LEFT) &&
      false == InputManager::Instance()->IsPress(VK_DOWN) &&
      false == InputManager::Instance()->IsUp(VK_DOWN) &&
      false == InputManager::Instance()->IsPress(VK_RIGHT) &&
      false == InputManager::Instance()->IsUp(VK_RIGHT) &&
      false == InputManager::Instance()->IsPress(VK_UP) &&
      false == InputManager::Instance()->IsUp(VK_UP) &&
      false == InputManager::Instance()->IsPress('A') && false == InputManager::Instance()->IsPress('a') &&
      false == InputManager::Instance()->IsUp('A') && false == InputManager::Instance()->IsUp('a') &&
      false == InputManager::Instance()->IsPress('S') && false == InputManager::Instance()->IsPress('s') &&
      false == InputManager::Instance()->IsUp('S') && false == InputManager::Instance()->IsUp('s') &&
      false == InputManager::Instance()->IsPress('Z') && false == InputManager::Instance()->IsPress('z') &&
      false == InputManager::Instance()->IsUp('Z') && false == InputManager::Instance()->IsUp('z') &&
      false == InputManager::Instance()->IsPress('X') && false == InputManager::Instance()->IsPress('x') &&
      false == InputManager::Instance()->IsUp('X') && false == InputManager::Instance()->IsUp('x')) {
    animState_ = PAS_Idle;
    return;
  }

  if (InputManager::Instance()->IsPress(VK_LEFT) || InputManager::Instance()->IsPress(VK_LEFT)) {
    if (FacingRight()) {
      animState_ = PAS_BackWalk;
      pMovementComponent_->Move(curTick, false, pPushBox_->IsHit());
    } else {
      if (animState_ == PAS_Run) {
        pMovementComponent_->Run(curTick, false, pPushBox_->IsHit());
      } else {
        animState_ = PAS_FrontWalk;
        pMovementComponent_->Move(curTick, false, pPushBox_->IsHit());
      }
    }
  }

  if (InputManager::Instance()->IsUp(VK_LEFT) || InputManager::Instance()->IsUp(VK_LEFT)) {
    if (FacingRight()) {
    }
  }

  if (InputManager::Instance()->IsPress(VK_RIGHT) || InputManager::Instance()->IsPress(VK_RIGHT)) {
    if (FacingRight()) {
      if (animState_ == PAS_Run) {
        pMovementComponent_->Run(curTick, true, pPushBox_->IsHit());
      } else {
        animState_ = PAS_FrontWalk;
        pMovementComponent_->Move(curTick, true, pPushBox_->IsHit());
      }
    } else {
      animState_ = PAS_BackWalk;
      pMovementComponent_->Move(curTick, true, pPushBox_->IsHit());
    }
  }

  if (InputManager::Instance()->IsUp(VK_RIGHT) || InputManager::Instance()->IsUp(VK_RIGHT)) {
    if (FacingRight()) {
      if (PAS_Run == animState_) {
        animState_ = PAS_RunEnd;
      }
    }
  }

  if (InputManager::Instance()->IsPress(VK_UP) || InputManager::Instance()->IsPress(VK_UP)) {
    if (PAS_FrontWalk == animState_) {
      pMovementComponent_->JumpForward(FacingRight(), false);
      animState_ = PAS_Jump;
    } else if (PAS_Run == animState_) {
      pMovementComponent_->JumpForward(FacingRight(), true);
      animState_ = PAS_Jump;
      pGhostEffect_->On();
    } else if (PAS_BackWalk == animState_) {
      pMovementComponent_->JumpForward(!FacingRight(), false);
      animState_ = PAS_Jump;
    } else {
      pMovementComponent_->Jump();
      animState_ = PAS_Jump;
    }
  }
  if (InputManager::Instance()->IsPress(VK_DOWN) || InputManager::Instance()->IsPress(VK_DOWN)) {
    animState_ = PAS_SeatDown;
  }

  if (InputManager::Instance()->IsUp(VK_DOWN) || InputManager::Instance()->IsUp(VK_DOWN)) {
    if (PAS_SeatDown == animState_) {
      animState_ = PAS_SeatUp;
    }
  }
  if (InputManager::Instance()->IsPress('A') || InputManager::Instance()->IsPress('a')) {
    animState_ = PAS_HeavyKick;
  }
  if (InputManager::Instance()->IsPress('S') || InputManager::Instance()->IsPress('s')) {
  }
  if (InputManager::Instance()->IsPress('Z') || InputManager::Instance()->IsPress('z')) {
  }
  if (InputManager::Instance()->IsPress('X') || InputManager::Instance()->IsPress('x')) {
    if (animState_ == PAS_FrontWalk) {
      animState_ = IOAS_MONGTAN_1;
    }

    if (animState_ == IOAS_MONGTAN_1)
    {
      forcedReservedAnim_ = IOAS_MONGTAN_2;
    }
  }
}

void Iori::CommandUpdate() {
  if (InputManager::Instance()->IsDown(VK_LEFT) || InputManager::Instance()->IsDown(VK_LEFT)) {
    if (FacingRight()) {
      pCommandComponent_->JumpNode(CK_Left);
    } else {
      pCommandComponent_->JumpNode(CK_Right);
    }
  }

  if (InputManager::Instance()->IsDown(VK_RIGHT) || InputManager::Instance()->IsDown(VK_RIGHT)) {
    if (FacingRight()) {
      pCommandComponent_->JumpNode(CK_Right);
    } else {
      pCommandComponent_->JumpNode(CK_Left);
    }
  }

  if (InputManager::Instance()->IsDown(VK_UP) || InputManager::Instance()->IsDown(VK_UP)) {
    pCommandComponent_->JumpNode(CK_Up);
  }

  if (InputManager::Instance()->IsDown(VK_DOWN) || InputManager::Instance()->IsDown(VK_DOWN)) {
    pCommandComponent_->JumpNode(CK_Down);
  }

  if (InputManager::Instance()->IsDown('A') || InputManager::Instance()->IsDown('a')) {
    pCommandComponent_->JumpNode(CK_D);
  }

  if (InputManager::Instance()->IsDown('S') || InputManager::Instance()->IsDown('s')) {
    pCommandComponent_->JumpNode(CK_C);
  }

  if (InputManager::Instance()->IsDown('Z') || InputManager::Instance()->IsDown('z')) {
    pCommandComponent_->JumpNode(CK_B);
  }

  if (InputManager::Instance()->IsDown('X') || InputManager::Instance()->IsDown('x')) {
    pCommandComponent_->JumpNode(CK_A);
  }
}

void Iori::TriggerEventAtAnimationIndex() {
  if (nullptr == pRender_) {
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (prevImageIndex == curImageIndex) {
    return;
  }

  switch (curImageIndex) {
    case (69):
      pGhostEffect_->Off();
      break;
    case (226):
      pProjectileComponent_->FireProjectile(1);
      break;
    default:
      break;
  }

  prevImageIndex = curImageIndex;
}

void Iori::CommandSkill_1() {
  animState_ = PAS_Skill1;
}

void Iori::CommandSkill_2() {
  animState_ = PAS_BackStep;
  pMovementComponent_->BackStep((FacingRight()));
}

void Iori::CommandSkill_3() {
  animState_ = PAS_Run;
}

// TEMP INPUT UPDATE

// if (false == InputManager::Instance()->IsPress('A') && false == InputManager::Instance()->IsPress('a') &&
//     false == InputManager::Instance()->IsUp('A') && false == InputManager::Instance()->IsUp('a') &&
//     false == InputManager::Instance()->IsPress('D') && false == InputManager::Instance()->IsPress('d') &&
//     false == InputManager::Instance()->IsUp('D') && false == InputManager::Instance()->IsUp('d') &&
//     false == InputManager::Instance()->IsPress('W') && false == InputManager::Instance()->IsPress('w') &&
//     false == InputManager::Instance()->IsUp('W') && false == InputManager::Instance()->IsUp('w') &&
//     false == InputManager::Instance()->IsPress('S') && false == InputManager::Instance()->IsPress('s') &&
//     false == InputManager::Instance()->IsUp('S') && false == InputManager::Instance()->IsUp('s') &&
//     false == InputManager::Instance()->IsPress('F') && false == InputManager::Instance()->IsPress('f') &&
//     false == InputManager::Instance()->IsUp('F') && false == InputManager::Instance()->IsUp('f') &&
//     false == InputManager::Instance()->IsPress('Q') && false == InputManager::Instance()->IsPress('q') &&
//     false == InputManager::Instance()->IsUp('Q') && false == InputManager::Instance()->IsUp('q') &&
//     false == InputManager::Instance()->IsPress('E') && false == InputManager::Instance()->IsPress('e') &&
//     false == InputManager::Instance()->IsUp('E') && false == InputManager::Instance()->IsUp('e')) {
//   animState_ = PAS_Idle;
//   return;
// }

// if (InputManager::Instance()->IsPress('A') || InputManager::Instance()->IsPress('a')) {
//   if (FacingRight()) {
//     animState_ = PAS_BackWalk;
//     pMovementComponent_->Move(curTick, false, pPushBox_->IsHit());
//   } else {
//     if (animState_ == PAS_Run) {
//       pMovementComponent_->Run(curTick, false, pPushBox_->IsHit());
//     } else {
//       animState_ = PAS_FrontWalk;
//       pMovementComponent_->Move(curTick, false, pPushBox_->IsHit());
//     }
//   }
// }

// if (InputManager::Instance()->IsUp('A') || InputManager::Instance()->IsUp('a')) {
//   if (FacingRight()) {
//   }
// }

// if (InputManager::Instance()->IsPress('D') || InputManager::Instance()->IsPress('d')) {
//   if (FacingRight()) {
//     if (animState_ == PAS_Run) {
//       pMovementComponent_->Run(curTick, true, pPushBox_->IsHit());
//     } else {
//       animState_ = PAS_FrontWalk;
//       pMovementComponent_->Move(curTick, true, pPushBox_->IsHit());
//     }
//   } else {
//     animState_ = PAS_BackWalk;
//     pMovementComponent_->Move(curTick, true, pPushBox_->IsHit());
//   }
// }

// if (InputManager::Instance()->IsUp('D') || InputManager::Instance()->IsUp('d')) {
//   if (FacingRight()) {
//     if (PAS_Run == animState_) {
//       animState_ = PAS_RunEnd;
//     }
//   }
// }

// if (InputManager::Instance()->IsPress('W') || InputManager::Instance()->IsPress('w')) {
//   if (PAS_FrontWalk == animState_) {
//     pMovementComponent_->JumpForward(FacingRight(), false);
//     animState_ = PAS_Jump;
//   } else if (PAS_Run == animState_) {
//     pMovementComponent_->JumpForward(FacingRight(), true);
//     animState_ = PAS_Jump;
//     pGhostEffect_->On();
//   } else if (PAS_BackWalk == animState_) {
//     pMovementComponent_->JumpForward(!FacingRight(), false);
//     animState_ = PAS_Jump;
//   } else {
//     pMovementComponent_->Jump();
//     animState_ = PAS_Jump;
//   }
// }
// if (InputManager::Instance()->IsPress('S') || InputManager::Instance()->IsPress('s')) {
//   animState_ = PAS_SeatDown;
// }

// if (InputManager::Instance()->IsUp('S') || InputManager::Instance()->IsUp('s')) {
//   if (PAS_SeatDown == animState_) {
//     animState_ = PAS_SeatUp;
//   }
// }
// if (InputManager::Instance()->IsPress('F') || InputManager::Instance()->IsPress('f')) {
//   animState_ = PAS_HeavyKick;
// }
// if (InputManager::Instance()->IsPress('Q') || InputManager::Instance()->IsPress('q')) {
// }
// if (InputManager::Instance()->IsPress('E') || InputManager::Instance()->IsPress('e')) {
// }

// COMMENT TEMP
// void Iori::CommendUpdate() {
//  if (InputManager::Instance()->IsDown('A') || InputManager::Instance()->IsDown('a')) {
//    if (FacingRight()) {
//      pCommandComponent_->JumpNode(CK_Left);
//    } else {
//      pCommandComponent_->JumpNode(CK_Right);
//    }
//  }
//
//  if (InputManager::Instance()->IsDown('D') || InputManager::Instance()->IsDown('d')) {
//    if (FacingRight()) {
//      pCommandComponent_->JumpNode(CK_Right);
//    } else {
//      pCommandComponent_->JumpNode(CK_Left);
//    }
//  }
//
//  if (InputManager::Instance()->IsDown('W') || InputManager::Instance()->IsDown('w')) {
//    pCommandComponent_->JumpNode(CK_Up);
//  }
//
//  if (InputManager::Instance()->IsDown('S') || InputManager::Instance()->IsDown('s')) {
//    pCommandComponent_->JumpNode(CK_Down);
//  }
//}