#include "stdafx.h"
#include "KOFPlayer.h"
#include "Chang.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
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

  pRender_->CreateAnimation(PAS_Idle, 4, 8, 13, 50, true, 8);  // 아이들
  pRender_->CreateAnimation(PAS_HitTop, 4, 38, 42, 50, false, 38);
  pRender_->CreateAnimation(PAS_HitBottom, 4, 43, 47, 50, false, 43);

  pRender_->CreateAnimation(-PAS_Idle, -4, 8, 13, 50, true, 8);  // 아이들
  pRender_->CreateAnimation(-PAS_HitTop, -4, 38, 42, 50, false, 38);
  pRender_->CreateAnimation(-PAS_HitBottom, -4, 43, 47, 50, false, 43);

  pRender_->SetTransparentColor(Color8Bit{17, 91, 124, 0});
  pRender_->ChangeAnimation(PAS_Idle*FacingRightFlag());

}

void Chang::Tick(unsigned long long deltaTick) {
  CollisionPushUpdate();

  if (true == CollisionHitUpdate()) {
    pRender_->ChangeAnimation(animState_ * FacingRightFlag());
  }

  if (true == pRender_->IsPlayingLoopAnimation()) {
    InputUpdate(deltaTick);

    CommendUpdate();

    pRender_->ChangeAnimation(animState_ * FacingRightFlag());
  }

  CollisionBoundUpdate();

  Actor* pTarget;
  if (CollisionAttackUpdate(&pTarget)) {
    if (nullptr != pTarget) {
      KOFPlayer* pTargetPlayer = dynamic_cast<KOFPlayer*>(pTarget);
      if (nullptr != pTargetPlayer) {
        pTargetPlayer->GetHealthComponent()->TakeDamage(50.0f);
      }
    }
  }

  SkillUpdate();

  CollisionPushUpdate();

  CollisionReset();

}

void Chang::InputUpdate(unsigned long long deltaTick) {
  if (false == InputManager::Instance()->IsPress('J') && false == InputManager::Instance()->IsPress('j') 
      && false == InputManager::Instance()->IsPress('L') && false == InputManager::Instance()->IsPress('l') 
      && false == InputManager::Instance()->IsPress('I') && false == InputManager::Instance()->IsPress('i') 
      && false == InputManager::Instance()->IsPress('K') && false == InputManager::Instance()->IsPress('k')) {
    animState_ = PAS_Idle;
    return;
  }

  Vector moveDir = {0.0f, 0.0f};

  if (InputManager::Instance()->IsPress('J') || InputManager::Instance()->IsPress('j')) {
    //animState_ = PAS_
    pMovementComponent_->Move(deltaTick, false, pPushBox_->IsHit());
  }
  if (InputManager::Instance()->IsPress('L') || InputManager::Instance()->IsPress('l')) {
    // animState_ = CHAS_Idel;
    pMovementComponent_->Move(deltaTick, true, pPushBox_->IsHit());
  }
  if (InputManager::Instance()->IsPress('I') || InputManager::Instance()->IsPress('i')) {
    pMovementComponent_->Jump();
  }
  if (InputManager::Instance()->IsPress('K') || InputManager::Instance()->IsPress('k')) {
  }
  if (InputManager::Instance()->IsPress('F') || InputManager::Instance()->IsPress('f')) {
  }

  if (InputManager::Instance()->IsPress('U') || InputManager::Instance()->IsPress('u')) {
    // pRender_->SetFlipRendering(true);
  }
  if (InputManager::Instance()->IsPress('O') || InputManager::Instance()->IsPress('o')) {
    // pRender_->SetFlipRendering(false);
  }

  if (moveDir == Vector(0.0f, 0.0f)) {
    // pRender_->ChangeAnimation(1);
  }

  Vector newPosition = moveDir + GetPosition();
  SetPosition(newPosition);
}

void Chang::CommendUpdate() {
}

void Chang::SkillUpdate() {
}

void Chang::CollisionBoundUpdate() {
  if (nullptr == pHitBoxTop_ || nullptr == pHitBoxBottom_ || nullptr == pAttackBox_ || nullptr == pPushBox_ || nullptr == pGrabBox_) {
    return;
  }

  unsigned int imageIndex = pRender_->GetImageIndex();
  IImage* pImage = pRender_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  CollisionInfo* pCollisionInfo;

  Vector actorPosition = GetPosition();
  Vector imagePosition = pFileImage->RenderTransform(imageIndex).GetPosition();
  Vector imageScale = pFileImage->GetScale(imageIndex);

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_HitBoxTop, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pHitBoxTop_->SetActive(true);
      pHitBoxTop_->SetPosition(pCollisionInfo->position_);
      pHitBoxTop_->SetScale(pCollisionInfo->scale_);
    } else {
      pHitBoxTop_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_HitBoxBottom, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pHitBoxBottom_->SetActive(true);
      pHitBoxBottom_->SetPosition(pCollisionInfo->position_);
      pHitBoxBottom_->SetScale(pCollisionInfo->scale_);
    } else {
      pHitBoxBottom_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_AttackBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pAttackBox_->SetActive(true);
      pAttackBox_->SetPosition(pCollisionInfo->position_);
      pAttackBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pAttackBox_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_PushBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pPushBox_->SetActive(true);
      pPushBox_->SetPosition(pCollisionInfo->position_);
      pPushBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pPushBox_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_GrabBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pGrabBox_->SetActive(true);
      pGrabBox_->SetPosition(pCollisionInfo->position_);
      pGrabBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pGrabBox_->SetActive(false);
    }
  }
}

bool Chang::CollisionHitUpdate() {
  if (pHitBoxTop_->IsHit()) {
    animState_ = PAS_HitTop;
    pMovementComponent_->BackStep((FacingRightFlag()));
    return true;
  }

  if (pHitBoxBottom_->IsHit()) {
    animState_ = PAS_HitBottom;
    pMovementComponent_->BackStep((FacingRightFlag()));
    return true;
  }

  return false;
}
