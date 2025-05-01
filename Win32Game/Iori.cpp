#include "stdafx.h"
#include "Player.h"
#include "MovementComponent.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
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
  Player::Initialize(position, useCameraPosition, flip);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(3);
  if (nullptr == pImage) {
    return;
  }
  SetCharacterScale(pImage->GetScale(7) * pRender_->GetLocalScale());

  // RENDERER
  pRender_->CreateAnimation(PAS_Idle, 3, 7, 15, 50, true, 7);             // ���̵�
  pRender_->CreateAnimation(PAS_Seat, 3, 16, 23, 50, true, 18);           // �ɱ�.
  pRender_->CreateAnimation(PAS_FrontWalk, 3, 27, 34, 50, true, 27);      // -> �ȱ�
  pRender_->CreateAnimation(PAS_BackWalk, 3, 35, 44, 50, true, 35);       // <- �ڷΰ���
  pRender_->CreateAnimation(PAS_BackStep, 3, 45, 48, 50, false, 45);      // <- <- �齺��
  pRender_->CreateAnimation(PAS_Run, 3, 49, 58, 50, true, 51);           // ->-> �ٱ�
  pRender_->CreateAnimation(PAS_Jump, 3, 61, 69, 50, false, 61);          // ����
  pRender_->CreateAnimation(PAS_HeavyKick, 3, 108, 117, 50, false, 108);  // ������
  pRender_->CreateAnimation(PAS_LightKick, 3, 136, 146, 50, false, 136);  // Ŀ�ǵ� �׽�Ʈ.

  pRender_->CreateAnimation(-PAS_Idle, -3, 7, 15, 50, true, 7);             // ���̵�
  pRender_->CreateAnimation(-PAS_Seat, -3, 16, 23, 50, true, 18);           // �ɱ�.
  pRender_->CreateAnimation(-PAS_FrontWalk, -3, 27, 34, 50, true, 27);      // -> �ȱ�
  pRender_->CreateAnimation(-PAS_BackWalk, -3, 35, 44, 50, true, 35);       // <- �ڷΰ���
  pRender_->CreateAnimation(-PAS_BackStep, -3, 45, 48, 50, false, 45);      // <- <- �齺��
  pRender_->CreateAnimation(-PAS_Run, -3, 49, 58, 50, true, 51);            // ->-> �ٱ�
  pRender_->CreateAnimation(-PAS_Jump, -3, 61, 69, 50, false, 61);          // ����
  pRender_->CreateAnimation(-PAS_HeavyKick, -3, 108, 117, 50, false, 108);  // ������
  pRender_->CreateAnimation(-PAS_LightKick, -3, 136, 146, 50, false, 136);  // Ŀ�ǵ� �׽�Ʈ.

  pRender_->SetTransparentColor(Color8Bit{169, 139, 150, 0});
  pRender_->ChangeAnimation(PAS_Idle * isFlip_);

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
  if (false == pProjectileComponent_->RegistProjectileInfo(1, 3, 239, 244, 20, true, {169, 139, 150, 0}, {25.0f, 0.0f}, {200.0f, 0.0f}, {1500.0f, 0.0f})) {
    return;
  }
}

void Iori::Tick(unsigned long long deltaTick) {
  CollisionPushUpdate();

  if (true == CollisionHitUpdate()) {
    pRender_->ChangeAnimation(animState_ * isFlip_);
  }

  if (true == pRender_->IsPlayingLoopAnimation()) {
    InputUpdate(deltaTick);

    CommendUpdate();

    pRender_->ChangeAnimation(animState_ * isFlip_);
  }

  CollisionBoundUpdate();

  CollisionAttackUpdate();

  SkillUpdate();

  CollisionPushUpdate();

  CollisionReset();
}

void Iori::InputUpdate(unsigned long long curTick) {
  if (false == InputManager::Instance()->IsPress('A') && false == InputManager::Instance()->IsPress('a') &&
      false == InputManager::Instance()->IsPress('D') && false == InputManager::Instance()->IsPress('d') &&
      false == InputManager::Instance()->IsPress('W') && false == InputManager::Instance()->IsPress('w') &&
      false == InputManager::Instance()->IsPress('S') && false == InputManager::Instance()->IsPress('s') &&
      false == InputManager::Instance()->IsPress('F') && false == InputManager::Instance()->IsPress('f') &&
      false == InputManager::Instance()->IsPress('Q') && false == InputManager::Instance()->IsPress('q') &&
      false == InputManager::Instance()->IsPress('E') && false == InputManager::Instance()->IsPress('e')) {
    animState_ = PAS_Idle;
    return;
  }

  // Vector moveDir = {0.0f, 0.0f};

  if (InputManager::Instance()->IsPress('A') || InputManager::Instance()->IsPress('a')) {
    animState_ = PAS_BackWalk;
    pMovementComponent_->Move(curTick, false, pPushBox_->IsHit());
  }
  if (InputManager::Instance()->IsPress('D') || InputManager::Instance()->IsPress('d')) {
    if (animState_ == PAS_Run) {
      pMovementComponent_->Run(curTick, pPushBox_->IsHit());
    } else {
      animState_ = PAS_FrontWalk;
      pMovementComponent_->Move(curTick, true, pPushBox_->IsHit());
    }
  }
  if (InputManager::Instance()->IsPress('W') || InputManager::Instance()->IsPress('w')) {
    animState_ = PAS_Jump;
    pMovementComponent_->Jump();
  }
  if (InputManager::Instance()->IsPress('S') || InputManager::Instance()->IsPress('s')) {
    animState_ = PAS_Seat;
  }
  if (InputManager::Instance()->IsPress('F') || InputManager::Instance()->IsPress('f')) {
    animState_ = PAS_HeavyKick;
  }
  if (InputManager::Instance()->IsPress('Q') || InputManager::Instance()->IsPress('q')) {
  }
  if (InputManager::Instance()->IsPress('E') || InputManager::Instance()->IsPress('e')) {
  }
}

void Iori::CommendUpdate() {
  if (InputManager::Instance()->IsDown('A') || InputManager::Instance()->IsDown('a')) {
    pCommandComponent_->JumpNode(CK_Left);
  }

  if (InputManager::Instance()->IsDown('D') || InputManager::Instance()->IsDown('d')) {
    pCommandComponent_->JumpNode(CK_Right);
  }

  if (InputManager::Instance()->IsDown('W') || InputManager::Instance()->IsDown('w')) {
    pCommandComponent_->JumpNode(CK_Up);
  }

  if (InputManager::Instance()->IsDown('S') || InputManager::Instance()->IsDown('s')) {
    pCommandComponent_->JumpNode(CK_Down);
  }
}

void Iori::SkillUpdate() {
  if (nullptr == pRender_) {
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (prevImageIndex == curImageIndex) {
    return;
  }

  switch (curImageIndex) {
    case (115):
      pProjectileComponent_->FireProjectile(1);
      break;
    default:
      break;
  }

  prevImageIndex = curImageIndex;
}

void Iori::CollisionBoundUpdate() {
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

bool Iori::CollisionHitUpdate() {
  if (pHitBoxTop_->IsHit()) {
    animState_ = PAS_Idle;
    pHitBoxTop_->OffHit();
    return true;
  }

  if (pHitBoxBottom_->IsHit()) {
    animState_ = PAS_Idle;
    pHitBoxTop_->OffHit();
    return true;
  }

  return false;
}

void Iori::CommandSkill_1() {
  animState_ = PAS_LightKick;
}

void Iori::CommandSkill_2() {
  animState_ = PAS_BackStep;
  pMovementComponent_->BackStep();
}

void Iori::CommandSkill_3() {
  animState_ = PAS_Run;
}
