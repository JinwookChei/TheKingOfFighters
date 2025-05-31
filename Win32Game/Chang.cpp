#include "stdafx.h"
#include "KOFPlayer.h"
#include "Chang.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"

Chang::Chang()
    : prevImageIndex(0) {
}

Chang::~Chang() {
}

void Chang::BeginPlay() {
}

void Chang::Initialize(const Vector& position, bool useCameraPosition, bool flip) {
  KOFPlayer::Initialize(position, useCameraPosition, flip);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(4);
  if (nullptr == pImage) {
    return;
  }
  SetCharacterScale(pImage->GetScale(8) * pRender_->GetLocalScale());

  pRender_->CreateAnimation(PAS_Idle, 4, 8, 13, 50, true, 8);           // ¾ÆÀÌµé
  pRender_->CreateAnimation(PAS_SeatDown, 4, 14, 20, 50, true, 16);     // ¾É±â.
  pRender_->CreateAnimation(PAS_FrontWalk, 4, 23, 32, 50, true, 23);    // -> °È±â
  pRender_->CreateAnimation(PAS_BackWalk, 4, 32, 23, 50, true, 32);     // <- µÚ·Î°¡±â
  pRender_->CreateAnimation(PAS_BackStep, 4, 33, 35, 50, false, 0);     // <- <- ¹é½ºÅÇ
  pRender_->CreateAnimation(PAS_Run, 4, 23, 32, 20, true, 23);          // ->-> ¶Ù±â
  pRender_->CreateAnimation(PAS_Jump, 4, 36, 42, 50, false, 0);         // Á¡ÇÁ
  pRender_->CreateAnimation(PAS_HeavyKick, 4, 82, 89, 50, false, 0);    // ¹ßÂ÷±â
  pRender_->CreateAnimation(PAS_HitTop, 4, 310, 314, 50, false, 0);     //
  pRender_->CreateAnimation(PAS_HitBottom, 4, 315, 319, 50, false, 0);  //
  pRender_->CreateAnimation(PAS_HitStrong, 4,
                            {339, 335, 336, 337, 338, 335, 336, 337, 338, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350},
                            {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 50, 50, 50, 50},
                            false, 0);
  pRender_->CreateAnimation(PAS_HitWhileJumping, 4, {339, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350}, 50, false, 0);

  pRender_->CreateAnimation(-PAS_Idle, -4, 8, 13, 50, true, 8);           // ¾ÆÀÌµé
  pRender_->CreateAnimation(-PAS_SeatDown, -4, 14, 20, 50, true, 16);         // ¾É±â.
  pRender_->CreateAnimation(-PAS_FrontWalk, -4, 23, 32, 50, true, 23);    // -> °È±â
  pRender_->CreateAnimation(-PAS_BackWalk, -4, 32, 23, 50, true, 32);     // <- µÚ·Î°¡±â
  pRender_->CreateAnimation(-PAS_BackStep, -4, 33, 35, 50, false, 0);     // <- <- ¹é½ºÅÇ
  pRender_->CreateAnimation(-PAS_Run, -4, 23, 32, 20, true, 23);          // ->-> ¶Ù±â
  pRender_->CreateAnimation(-PAS_Jump, -4, 36, 42, 50, false, 0);         // Á¡ÇÁ
  pRender_->CreateAnimation(-PAS_HeavyKick, -4, 82, 89, 50, false, 0);    // ¹ßÂ÷±â
  pRender_->CreateAnimation(-PAS_HitTop, -4, 310, 314, 50, false, 0);     //
  pRender_->CreateAnimation(-PAS_HitBottom, -4, 315, 319, 50, false, 0);  //
  pRender_->CreateAnimation(-PAS_HitStrong, -4,
                            {339, 335, 336, 337, 338, /*335, 336, 337, 338,*/ 340, 341, 342, 343, 345, 346, 347, 348, 349, 350},
                            {80, 80, 80, 80, 80, 80, /*50, 50, 50, 50,*/ 80, 80, 80, 80, 80, 80, 80, 80, 80},
                            false, 0);
  pRender_->CreateAnimation(-PAS_HitWhileJumping, -4, {339, 340, 341, 342, 343, 345, 346, 347, 348, 349, 350}, 50, false, 0);

  pRender_->SetTransparentColor(changTransparentColor);
  pRender_->ChangeAnimation(PAS_Idle * FacingRightFlag());




  // GHOST EFFECT
  pGhostEffect_->SetTransparentColor(changTransparentColor);
}

void Chang::Tick(unsigned long long deltaTick) {


  CollisionPushUpdate();

  CollisionBoundScaleUpdate();

  //if (true == pRender_->IsPlayingLoopAnimation()) {
  //  InputUpdate(deltaTick);

  //  CommandUpdate();

  //  pRender_->ChangeAnimation(animState_ * FacingRightFlag());
  //}

  

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
      
      //
    }
  }

  SkillUpdate();

  CollisionPushUpdate();

  CollisionReset();
}

void Chang::HitEvent(float damage, const Vector& knockBackForce) {
  pHealthComponent_->TakeDamage(damage);

  if (pHitBoxTop_->IsCollided()) {
    animState_ = PAS_HitStrong;
    pRender_->ChangeAnimation(animState_ * FacingRightFlag());
    pMovementComponent_->KnockBack(FacingRight(), knockBackForce);
  }

  if (pHitBoxBottom_->IsCollided()) {
    animState_ = PAS_HitStrong;
    pRender_->ChangeAnimation(animState_ * FacingRightFlag());
    pMovementComponent_->KnockBack(FacingRight(), knockBackForce);
  }
}

void Chang::InputUpdate(unsigned long long curTick) {
  if (false == InputManager::Instance()->IsPress('J') && false == InputManager::Instance()->IsPress('j') &&
      false == InputManager::Instance()->IsPress('L') && false == InputManager::Instance()->IsPress('l') &&
      false == InputManager::Instance()->IsPress('I') && false == InputManager::Instance()->IsPress('i') &&
      false == InputManager::Instance()->IsPress('K') && false == InputManager::Instance()->IsPress('k') &&
      false == InputManager::Instance()->IsPress('H') && false == InputManager::Instance()->IsPress('h') &&
      false == InputManager::Instance()->IsPress('U') && false == InputManager::Instance()->IsPress('u') &&
      false == InputManager::Instance()->IsPress('O') && false == InputManager::Instance()->IsPress('o')) {
    animState_ = PAS_Idle;
    return;
  }

  if (InputManager::Instance()->IsPress('J') || InputManager::Instance()->IsPress('j')) {
    if (FacingRight()) {
      animState_ = PAS_BackWalk;
      pMovementComponent_->Move(curTick, false, pPushBox_->IsCollided());
    } else {
      if (animState_ == PAS_Run) {
        pMovementComponent_->Run(curTick, false, pPushBox_->IsCollided());
      } else {
        animState_ = PAS_FrontWalk;
        pMovementComponent_->Move(curTick, false, pPushBox_->IsCollided());
      }
    }
  }
  if (InputManager::Instance()->IsPress('L') || InputManager::Instance()->IsPress('l')) {
    if (FacingRight()) {
      if (animState_ == PAS_Run) {
        pMovementComponent_->Run(curTick, true, pPushBox_->IsCollided());
      } else {
        animState_ = PAS_FrontWalk;
        pMovementComponent_->Move(curTick, true, pPushBox_->IsCollided());
      }
    } else {
      animState_ = PAS_BackWalk;
      pMovementComponent_->Move(curTick, true, pPushBox_->IsCollided());
    }
  }
  if (InputManager::Instance()->IsPress('I') || InputManager::Instance()->IsPress('i')) {
    if (PAS_FrontWalk == animState_) {
      pMovementComponent_->JumpForward(FacingRight(), false);
      animState_ = PAS_Jump;
    } else if (PAS_Run == animState_) {
      pMovementComponent_->JumpForward(FacingRight(), true);
      animState_ = PAS_Jump;
    } else if (PAS_BackWalk == animState_) {
      pMovementComponent_->JumpForward(!FacingRight(), false);
      animState_ = PAS_Jump;
    } else {
      pMovementComponent_->Jump();
      animState_ = PAS_Jump;
    }
  }
  if (InputManager::Instance()->IsPress('K') || InputManager::Instance()->IsPress('k')) {
    animState_ = PAS_SeatDown;
  }

  if (InputManager::Instance()->IsPress('H') || InputManager::Instance()->IsPress('h')) {
    animState_ = PAS_HeavyKick;
  }
  if (InputManager::Instance()->IsPress('Q') || InputManager::Instance()->IsPress('q')) {
  }
  if (InputManager::Instance()->IsPress('E') || InputManager::Instance()->IsPress('e')) {
  }
}

void Chang::CommandUpdate() {
}

void Chang::SkillUpdate() {
}