#include "stdafx.h"
#include "CommandComponent.h"
#include "SkillComponent.h"
#include "ProjectileComponent.h"
#include "MovementComponent.h"
#include "StateComponent.h"
#include "AttackTable.h"
#include "HealthComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"

KOFPlayer::KOFPlayer()
    : pRender_(nullptr),
      pMovementComponent_(nullptr),
      pAttackTable_(nullptr),
      pHealthComponent_(nullptr),
      pStateComponent_(nullptr),
      pHitBoxTop_(nullptr),
      pHitBoxBottom_(nullptr),
      pAttackBox_(nullptr),
      pPushBox_(nullptr),
      pGrabBox_(nullptr),
      pSkillComponent_(nullptr),
      pCommandComponent_(nullptr),
      pProjectileComponent_(nullptr),
      pGhostEffect_(nullptr),
      characterScale_({0.0f, 0.0f}),
      isPlayer1_(true),
      animState_(PLAYER_ANIMTYPE_Idle),
      prevImageIndex_(0),
      isPlayerOnLeft_(true),
      isFacingRight_(true),
      isAtMapEdge_(false),
      pOpponentPlayer_(nullptr),
      isControlLocked_(false) {
}

KOFPlayer::~KOFPlayer() {
}

void KOFPlayer::BeginPlay() {
}

void KOFPlayer::Tick(unsigned long long deltaTick) {
  UpdateCollisionBoundScale();

  CheckPushCollision();

  if (true == pStateComponent_->ContainPlayerState({PS_Attack})) {
    UpdateAttack();
  }

  if (false == isControlLocked_) {
    UpdateCommand();

    if (true == pRender_->IsAnimationEnd()) {
      pCommandComponent_->ExcuteTask();
    }

    ResetInputBitSet();

    UpdateInput();

    // TODO
    if (pStateComponent_->ContainPlayerState({PS_Jump})) {
      if (false == pMovementComponent_->EqualMovementState({MOVSTATE_Jump})) {
          UpdateAnimState(PLAYER_ANIMTYPE_Idle, ANIMMOD_NONE);
      }
    }
    // END

    if (true == pStateComponent_->CanInput() || true == pRender_->IsAnimationEnd()) {
      CompareInputBitset();
    }

    if (pProjectileComponent_->GetActiveProjectilesCount() > 0) {
      pStateComponent_->AddState({PS_Attack});
    }

    pSkillComponent_->UpdateActiveSkill();
  }

  UpdatePrevAnimationIndex();
}

void KOFPlayer::Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) {
  SetPosition(position);
  SetUseCameraposition(useCameraPosition);
  isPlayer1_ = isPlayer1;

  if (true == isPlayer1_) {
    playerKeySet_ = {'A', 'S', 'Z', 'X', VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT};  // D C B A UP RIGHT DONW LEFT
    // playerKeySet_ = {'1', '2', '3', '4', VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT};  // D C B A UP RIGHT DONW LEFT
  } else {
    playerKeySet_ = {'E', 'R', 'D', 'F', 'I', 'L', 'K', 'J'};  // D C B A UP RIGHT DONW LEFT
    // playerKeySet_ = {'1', '2', '3', '4', 'S', 'C', 'X', 'Z'};  // D C B A UP RIGHT DONW LEFT
  }

  // RENDERER
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetLocalScale({4.2f, 4.2f});
  pRender_->SetAlpha(1.0f);

  // MOVEMENT
  pMovementComponent_ = CreateComponent<MovementComponent>();
  if (false == pMovementComponent_->Initialize(position)) {
    return;
  }

  // DAMAGE
  pAttackTable_ = CreateComponent<AttackTable>();
  if (false == pAttackTable_->Initailize()) {
    return;
  }

  // HEALTH
  pHealthComponent_ = CreateComponent<HealthComponent>();
  if (false == pHealthComponent_->Initialize(100.0f)) {
    return;
  }

  // STATE
  pStateComponent_ = CreateComponent<StateComponent>();
  if (false == pStateComponent_->Initialize()) {
    return;
  }

  // COLLISION
  pHitBoxTop_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop);
  pHitBoxBottom_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom);
  pAttackBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_AttackBox);
  pPushBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_PushBox);
  pGrabBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_GrabBox);

  // SKILL
  pSkillComponent_ = CreateComponent<SkillComponent>();
  if (false == pSkillComponent_->Initialize()) {
    return;
  }

  // COMMEND
  pCommandComponent_ = CreateComponent<CommandComponent>();
  pCommandComponent_->SetTimeOutThreshold(150, 400);

  // PROJECTILE
  pProjectileComponent_ = CreateComponent<ProjectileComponent>();
  if (false == pProjectileComponent_->Initialize(GetLevel())) {
    return;
  }

  // GHOST EFFECT
  pGhostEffect_ = CreateComponent<GhostEffect>();
  if (false == pGhostEffect_->Initialize(pRender_, 4, 30, 0.7f)) {
    return;
  }

  // INPUT BIT SET
  ResetInputBitSet();

  // OPPONENT PLAYER
  if (nullptr == opponentPlayer) {
    return;
  }
  pOpponentPlayer_ = opponentPlayer;

  // DBUG SETTING
  SetDebugParameter({.on_ = true, .linethickness_ = 2.0f});
  pRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Cyan});
  pHitBoxTop_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pHitBoxBottom_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  pAttackBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Red});
  pPushBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::White});
  pGrabBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Yellow});
}

void KOFPlayer::CallCreateAnimation(unsigned long long animationTag, unsigned long long imageIndex, unsigned int startIndex, unsigned int endIndex, unsigned long long interval, bool loop, unsigned long long loopStartFrame) {
  if (nullptr == pRender_) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_NONE, imageIndex | IMGMOD_NONE, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_FLIPPED, imageIndex | IMGMOD_FLIPPED, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_BLUEFLAME, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME, startIndex, endIndex, interval, loop, loopStartFrame)) {
    return;
  }
}

void KOFPlayer::CallCreateAnimation(unsigned long long animationTag, unsigned long long imageIndex, const std::vector<unsigned int>& indices, unsigned long long interval, bool loop, unsigned long long loopStartFrame) {
  if (nullptr == pRender_) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_NONE, imageIndex | IMGMOD_NONE, indices, interval, loop, loopStartFrame)) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_FLIPPED, imageIndex | IMGMOD_FLIPPED, indices, interval, loop, loopStartFrame)) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_BLUEFLAME, indices, interval, loop, loopStartFrame)) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME, indices, interval, loop, loopStartFrame)) {
    return;
  }
}

void KOFPlayer::CallCreateAnimation(unsigned long long animationTag, unsigned long long imageIndex, const std::vector<unsigned int>& indices, const std::vector<unsigned long long> intervals, bool loop, unsigned long long loopStartFrame) {
  if (nullptr == pRender_) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_NONE, imageIndex | IMGMOD_NONE, indices, intervals, loop, loopStartFrame)) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_FLIPPED, imageIndex | IMGMOD_FLIPPED, indices, intervals, loop, loopStartFrame)) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_BLUEFLAME, indices, intervals, loop, loopStartFrame)) {
    return;
  }
  if (false == pRender_->CreateAnimation(animationTag | ANIMMOD_FLIPPED | ANIMMOD_BLUEFLAME, imageIndex | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME, indices, intervals, loop, loopStartFrame)) {
    return;
  }
}

void KOFPlayer::UpdateAnimState(unsigned long long animState, PLAYER_ANIM_MODIFIER modifier /* = ANIMMOD_NONE*/, int startFrame /*= 0*/, unsigned long long time /*= 0.0f*/) {
  animState_ = animState;
  if (true == PlayerOnLeft()) {
    isFacingRight_ = true;
    pRender_->ChangeAnimation((animState_ | modifier), startFrame, time);
  } else {
    isFacingRight_ = false;
    pRender_->ChangeAnimation((animState_ | modifier | ANIMMOD_FLIPPED), startFrame, time);
  }

  pStateComponent_->ChangeState(animState_);

  CollisionReset();
}

const HealthComponent* KOFPlayer::GetHealthComponent() const {
  return pHealthComponent_;
}

void KOFPlayer::HitEvent(const AttackInfo* damageInfo) {
  if (true == pStateComponent_->ContainPlayerState({PS_Guard})) {
    pHealthComponent_->TakeDamage(damageInfo->damage_ * 0.1f);
    pMovementComponent_->KnockBack(FacingRight(), {damageInfo->knockBackForce_.X * 0.9f, 0.0f});
  } else if (pMovementComponent_->ContainMovementState({MOVSTATE_Jump})) {
    pHealthComponent_->TakeDamage(damageInfo->damage_ * 0.1f);
    pMovementComponent_->KnockBack(FacingRight(), {35.0f, 50.0f});
    UpdateAnimState(PLAYER_ANIMTYPE_Hit_Jump);
  } else if (true == pStateComponent_->ContainPlayerState({PS_Seat})) {
    pHealthComponent_->TakeDamage(damageInfo->damage_ * 0.1f);
    pMovementComponent_->KnockBack(FacingRight(), {damageInfo->knockBackForce_.X * 0.9f, 0.0f});
    UpdateAnimState(PLAYER_ANIMTYPE_Hit_Seat);
  } else {
    pHealthComponent_->TakeDamage(damageInfo->damage_);
    switch (damageInfo->attackType_) {
      case ATTYPE_HighAttack: {
        if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
          UpdateAnimState(PLAYER_ANIMTYPE_HitHigh, ANIMMOD_BLUEFLAME);
        } else {
          UpdateAnimState(PLAYER_ANIMTYPE_HitHigh);
        }
        pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
      } break;

      case ATTYPE_LowAttack: {
        if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
          UpdateAnimState(PLAYER_ANIMTYPE_HitLow, ANIMMOD_BLUEFLAME);
        } else {
          UpdateAnimState(PLAYER_ANIMTYPE_HitLow);
        }
        pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
      } break;
      case ATTYPE_StrongAttack: {
        if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
          UpdateAnimState(PLAYER_ANIMTYPE_HitStrong, ANIMMOD_BLUEFLAME);
        } else {
          UpdateAnimState(PLAYER_ANIMTYPE_HitStrong);
        }
        pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
      } break;
      case ATTYPE_NormalAttack: {
        if (pHitBoxTop_->HasHit()) {
          if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
            UpdateAnimState(PLAYER_ANIMTYPE_HitHigh, ANIMMOD_BLUEFLAME);
            pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
          } else {
            UpdateAnimState(PLAYER_ANIMTYPE_HitHigh);
            pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
          }
        }

        if (pHitBoxBottom_->HasHit()) {
          if (ELMTTYPE_BlueFlame == damageInfo->elementType_) {
            UpdateAnimState(PLAYER_ANIMTYPE_HitLow, ANIMMOD_BLUEFLAME);
            pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
          } else {
            UpdateAnimState(PLAYER_ANIMTYPE_HitLow);
            pMovementComponent_->KnockBack(FacingRight(), damageInfo->knockBackForce_);
          }
        }
      } break;
      default:
        break;
    }
  }
}

void KOFPlayer::UpdateInput() {
  // InputBitSet :
  // Left : 10000000
  // Down : 01000000
  // Right: 00100000
  // Up :   00010000
  // A  :   00001000
  // B  :   00000100
  // C  :   00000010
  // D  :   00000001

  bool anyKeyActive = false;
  for (int key : playerKeySet_) {
    if (InputManager::Instance()->IsPress(key) ||
        InputManager::Instance()->IsUp(key)) {
      anyKeyActive = true;
      break;
    }
  }

  if (false == anyKeyActive) {
    return;
  }

  // LEFT PRESS
  if (InputManager::Instance()->IsPress(playerKeySet_[7])) {
    if (PlayerOnLeft()) {
      inputPressBitSet_.set(7);
    } else {
      inputPressBitSet_.set(5);
    }
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[7])) {
    if (PlayerOnLeft()) {
      inputUpBitSet_.set(7);
    } else {
      inputUpBitSet_.set(5);
    }
  }
  // DOWN
  if (InputManager::Instance()->IsPress(playerKeySet_[6])) {
    inputPressBitSet_.set(6);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[6])) {
    inputUpBitSet_.set(6);
  }
  // RIGHT
  if (InputManager::Instance()->IsPress(playerKeySet_[5])) {
    if (PlayerOnLeft()) {
      inputPressBitSet_.set(5);
    } else {
      inputPressBitSet_.set(7);
    }
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[5])) {
    if (PlayerOnLeft()) {
      inputUpBitSet_.set(5);
    } else {
      inputUpBitSet_.set(7);
    }
  }
  // UP
  if (InputManager::Instance()->IsPress(playerKeySet_[4])) {
    inputPressBitSet_.set(4);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[4])) {
    inputUpBitSet_.set(4);
  }
  // A
  if (InputManager::Instance()->IsPress(playerKeySet_[3])) {
    inputPressBitSet_.set(3);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[3])) {
    inputUpBitSet_.set(3);
  }
  // B
  if (InputManager::Instance()->IsPress(playerKeySet_[2])) {
    inputPressBitSet_.set(2);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[2])) {
    inputUpBitSet_.set(2);
  }
  // C
  if (InputManager::Instance()->IsPress(playerKeySet_[1])) {
    inputPressBitSet_.set(1);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[1])) {
    inputUpBitSet_.set(1);
  }
  // D
  if (InputManager::Instance()->IsPress(playerKeySet_[0])) {
    inputPressBitSet_.set(0);
  }
  if (InputManager::Instance()->IsUp(playerKeySet_[0])) {
    inputUpBitSet_.set(0);
  }
}

void KOFPlayer::UpdateCommand() {
  if (InputManager::Instance()->IsDown(playerKeySet_[7])) {
    if (PlayerOnLeft()) {
      pCommandComponent_->JumpNode(CK_Left);
    } else {
      pCommandComponent_->JumpNode(CK_Right);
    }
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[6])) {
    pCommandComponent_->JumpNode(CK_Down);
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[5])) {
    if (PlayerOnLeft()) {
      pCommandComponent_->JumpNode(CK_Right);
    } else {
      pCommandComponent_->JumpNode(CK_Left);
    }
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[4])) {
    pCommandComponent_->JumpNode(CK_Up);
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[3])) {
    pCommandComponent_->JumpNode(CK_A);
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[2])) {
    pCommandComponent_->JumpNode(CK_B);
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[1])) {
    pCommandComponent_->JumpNode(CK_C);
  }

  if (InputManager::Instance()->IsDown(playerKeySet_[0])) {
    pCommandComponent_->JumpNode(CK_D);
  }
}

void KOFPlayer::UpdateCollisionBoundScale() {
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

void KOFPlayer::UpdateAttack() {
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

      Level* pLevel = GetLevel();
      if (nullptr == pLevel) {
        return;
      }
      KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
      if (nullptr == pKOFLevel) {
        return;
      }

      AttackInfo* pAttackInfo;
      if (false == pAttackTable_->SearchAttackInfo(animState_, &pAttackInfo)) {
        return;
      }

      if (true == pAttackInfo->isProjectileAttack_) {
        return;
      }

      pTargetPlayer->HitEvent(pAttackInfo);
      /* if (pOpponentPlayer_->IsAtMapEdge()) {
       pMovementComponent_->KnockBack(FacingRight(), {pAttackInfo->knockBackForce_.X, 0.0f});
     }*/

      pKOFLevel->FreezeActors({this, pTargetPlayer}, false, pAttackInfo->freezeTime_);

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

      // TODO EFFECT ·ÎÁ÷
      if (pAttackInfo->effectType_ == EFTYPE_Iori_Explosion) {
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X + 150.0f, effectPosition.Y + 90.0f});
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X - 50.0f, effectPosition.Y + 110.0f});
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X - 30.0f, effectPosition.Y - 170.0f});
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X + 170.0f, effectPosition.Y - 190.0f});
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X + 110.0f, effectPosition.Y + 80.0f});
        EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, {effectPosition.X + 130.0f, effectPosition.Y - 200.0f});
        return;
      }

      // Spawn Effect
      if (true == pTargetPlayer->GetPlayerStateComponent()->ContainPlayerState({PS_Guard})) {
        if (true == FacingRight()) {
          EffectManager::Instance()->SpawnEffect(GetLevel(), EFTYPE_Guard_1, effectPosition);
        } else {
          EffectManager::Instance()->SpawnEffect(GetLevel(), EFTYPE_Guard_1 | EFMOD_FLIPPED, effectPosition);
        }
      } else {
        if (true == FacingRight()) {
          EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_, effectPosition);
        } else {
          EffectManager::Instance()->SpawnEffect(GetLevel(), pAttackInfo->effectType_ | EFMOD_FLIPPED, effectPosition);
        }
      }
    }
  }
}
bool KOFPlayer::CheckAttackCollision(CollisionComponent** outTargetCollision) {
  if (true == pAttackBox_->HasHit()) {
    return false;
  }
  CollisionComponent* pTargetCollision_Top = nullptr;
  if (true == pAttackBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetCollision_Top)) {
    *outTargetCollision = pTargetCollision_Top;
    pTargetCollision_Top->MarkAsHit();
    pAttackBox_->MarkAsHit();
    return true;
  }

  CollisionComponent* pTargetCollision_Bottom = nullptr;
  if (true == pAttackBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetCollision_Bottom)) {
    *outTargetCollision = pTargetCollision_Bottom;
    pTargetCollision_Bottom->MarkAsHit();
    pAttackBox_->MarkAsHit();
    return true;
  }

  *outTargetCollision = nullptr;
  return false;
}

bool KOFPlayer::CheckPushCollision() {
  CollisionComponent* pTargetPushCollision = nullptr;
  if (true == pPushBox_->Collision(
                  {
                      .targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_PushBox,
                      .targetCollisionType = CollisionType::CollisionType_Rect,
                      .myCollisionType = CollisionType::CollisionType_Rect,
                  },
                  &pTargetPushCollision)) {
    pPushBox_->MarkAsHit();

    Actor* pTarget = pTargetPushCollision->GetOwner();
    if (nullptr == pTarget) {
      return false;
    }

    KOFPlayer* pTargetPlayer = dynamic_cast<KOFPlayer*>(pTarget);
    if (nullptr == pTargetPlayer) {
      return false;
    }

    Vector TargetPostion = pTargetPlayer->GetPosition();
    Vector myPosition = GetPosition();

    float absPlayerDistance = std::abs(TargetPostion.X - myPosition.X);
    float pushTriggerDistance = pMovementComponent_->GetPushTriggerDistance();
    if (absPlayerDistance <= pushTriggerDistance) {
      pMovementComponent_->ApplyPushWeight(0.3f);
      pTargetPlayer->SetPosition({(myPosition.X + pushTriggerDistance * FacingRightFlag()), TargetPostion.Y});
    }
  }

  pPushBox_->ResetHit();
  return false;
}

void KOFPlayer::CollisionReset() {
  pHitBoxTop_->ResetHit();
  pHitBoxBottom_->ResetHit();
  pAttackBox_->ResetHit();
  pPushBox_->ResetHit();
  pGrabBox_->ResetHit();
}

void KOFPlayer::UpdatePrevAnimationIndex() {
  if (nullptr == pRender_) {
    return;
  }
  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (curImageIndex != prevImageIndex_) {
    prevImageIndex_ = curImageIndex;
  }
}

Vector KOFPlayer::CharacterScale() const {
  return characterScale_;
}

void KOFPlayer::SetCharacterScale(const Vector& scale) {
  characterScale_ = scale;
}

void KOFPlayer::PushOverlappingPlayer() {
}

void KOFPlayer::SetPlayerOnLeft(bool isPlayerOnLeft) {
  isPlayerOnLeft_ = isPlayerOnLeft;
}

bool KOFPlayer::PlayerOnLeft() const {
  return isPlayerOnLeft_;
}

int KOFPlayer::FacingRightFlag() const {
  if (isFacingRight_) {
    return 1;
  }

  return -1;
}

bool KOFPlayer::FacingRight() const {
  return isFacingRight_;
}

void KOFPlayer::SetFacingRight(bool isFacingRight) {
  isFacingRight_ = isFacingRight;
}

void KOFPlayer::SetIsAtMapEdge(bool isAtEdge) {
  isAtMapEdge_ = isAtEdge;
}

bool KOFPlayer::IsAtMapEdge() const {
  return isAtMapEdge_;
}

void KOFPlayer::CompareInputBitset() {
}

void KOFPlayer::ResetInputBitSet() {
  inputPressBitSet_.reset();
  inputUpBitSet_.reset();
}

bool KOFPlayer::IsEqualInputBitSet(const std::bitset<8>& myBitSet, const std::bitset<8>& compareTarget) {
  return myBitSet == compareTarget;
}

bool KOFPlayer::IsContainInputBitSet(const std::bitset<8>& myBitSet, const std::bitset<8>& compareTarget) {
  return (myBitSet & compareTarget) == compareTarget;
}

KOFPlayer* KOFPlayer::GetOpponentPlayer() const {
  return pOpponentPlayer_;
}

StateComponent* KOFPlayer::GetPlayerStateComponent() const {
  return pStateComponent_;
}

MovementComponent* KOFPlayer::GetMovementComponent() const {
  return pMovementComponent_;
}

bool KOFPlayer::IsControlLocked() const {
  return isControlLocked_;
}

void KOFPlayer::SetControlLocked(bool bLocked) {
  isControlLocked_ = bLocked;
}

void KOFPlayer::ReceiveClampedWidthOffset(float clampOffset) {
  if (true == pStateComponent_->ContainPlayerState({PS_EnableClampOffset})) {
    pMovementComponent_->ApplyClampedWidthOffset(clampOffset);
  }
}
