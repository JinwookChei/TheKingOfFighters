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
  playerKeySet_ = {4, 3, 2, 1, 'I', 'L', 'K', 'J'};  // D C B A UP RIGHT DONW LEFT
}

Chang::~Chang() {
}

void Chang::BeginPlay() {
}

void Chang::Initialize(const Vector& position, bool useCameraPosition, bool flip, KOFPlayer* opponentPlayer) {
  KOFPlayer::Initialize(position, useCameraPosition, flip, opponentPlayer);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(4);
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
  pRender_->ChangeAnimation(PAS_Idle * FacingRightFlag());

  // GHOST EFFECT
  pGhostEffect_->SetTransparentColor(changTransparentColor);
}

void Chang::Tick(unsigned long long deltaTick) {
  UpdateCollisionBoundScale();

  UpdateCollisionPush();

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

  // REGACY
  // UpdateCollisionPush();

  // UpdateCollisionBoundScale();

  //
  // if (pRender_->GetImageIndex() == 314 || pRender_->GetImageIndex() == 319)
  //{
  //  pRender_->ChangeAnimation(PAS_Idle * FacingRightFlag());
  //}

  ////pRender_->ChangeAnimation(PAS_Idle * FacingRightFlag());

  ////if (true == pRender_->IsPlayingLoopAnimation()) {
  //  //InputUpdate(deltaTick);

  //  //CommandUpdate();

  ////pRender_->ChangeAnimation(animState_ * FacingRightFlag());
  ////}

  // CollisionComponent* pTargetCollision = nullptr;
  // if (CheckAttackCollision(&pTargetCollision)) {
  //   if (nullptr != pTargetCollision) {
  //     Actor* pTargetOwner = pTargetCollision->GetOwner();
  //     if (nullptr == pTargetOwner) {
  //       return;
  //     }
  //     KOFPlayer* pTargetPlayer = dynamic_cast<KOFPlayer*>(pTargetOwner);
  //     if (nullptr == pTargetPlayer) {
  //       return;
  //     }
  //
  //     //
  //   }
  // }

  ////SkillUpdate();

  // CollisionReset();
}
