#include "stdafx.h"
#include "SkillHandler.h"
#include "IoriSkillHandler.h"
#include "KOFLevel.h"
#include "ScreenMask.h"
#include "CameraTarget.h"

IoriSkillHandler::IoriSkillHandler() {
}

IoriSkillHandler::~IoriSkillHandler() {
}

bool IoriSkillHandler::RegistSkills() {
  if (nullptr == pOwnerSkillComponent_) {
    return false;
  }

  if (false == pOwnerSkillComponent_->RegistSkill(IORI_SKILL_GaishikiMutan, &IoriSkillHandler::GaishikiMutan, this)) {
    return false;
  }
  if (false == pOwnerSkillComponent_->RegistSkill(IORI_SKILL_108ShikiYamiBarai, &IoriSkillHandler::ShikiYamiBarai108, this)) {
    return false;
  }
  pOwnerSkillComponent_->RegistSkill(IORI_SKILL_HyakushikiOniyaki, &IoriSkillHandler::HyakushikiOniyaki, this);
  pOwnerSkillComponent_->RegistSkill(IORI_SKILL_127ShikiAoiHana, &IoriSkillHandler::ShikiAoiHana127, this);
  pOwnerSkillComponent_->RegistSkill(IORI_SKILL_1211ShikiYaOtome, &IoriSkillHandler::ShikiYaOtome1211, this);
  pOwnerSkillComponent_->RegistSkill(IORI_SKILL_Ura306shikiShika, &IoriSkillHandler::Ura306shikiShika, this);

  return true;
}

void IoriSkillHandler::GaishikiMutan() {
  if (true == pOwnerRenderer_->IsAnimationEnd()) {
    pOwnerSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pOwnerRenderer_->GetImageIndex();

  if (IORI_ANIMTYPE_GaishikiMutan_1 == pOwnerStateComponent_->GetCurAnimState()) {
    if (100 <= curImageIndex && 104 >= curImageIndex) {
      const std::bitset<8>& downBitSet = pOwnerPlayer_->InputDownBitSet();
      if (true == pOwnerPlayer_->IsContainInputBitSet(downBitSet, std::bitset<8>("00001000")) ||
          true == pOwnerPlayer_->IsContainInputBitSet(downBitSet, std::bitset<8>("00000010"))) {
        pOwnerSkillComponent_->SetMiscTemp(true);
      }
    }

    if (true == pOwnerAttackCollision_->HasHit() && 105 == curImageIndex && true == pOwnerSkillComponent_->GetMiscTemp()) {
      pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_GaishikiMutan_2);
    }
  }
}

void IoriSkillHandler::ShikiYamiBarai108() {
  if (true == pOwnerRenderer_->IsAnimationEnd()) {
    pOwnerSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pOwnerRenderer_->GetImageIndex();
  unsigned int prevImageIndex = pOwnerPlayer_->prevImageIndex_;
  if (prevImageIndex == curImageIndex) {
    return;
  }

  if (225 == curImageIndex) {
    Level* curLevel = pOwnerPlayer_->GetLevel();
    Vector curPosition = pOwnerPlayer_->GetPosition();
    if (pOwnerPlayer_->FacingRight()) {
      EffectManager::Instance()->SpawnEffect(curLevel, (EFTYPE_Iori_Casting_YamiBarai | EFMOD_NONE), {curPosition.X - 40.0f, curPosition.Y - 70.0f});
    } else {
      EffectManager::Instance()->SpawnEffect(curLevel, (EFTYPE_Iori_Casting_YamiBarai | EFMOD_FLIPPED), {curPosition.X + 40.0f, curPosition.Y - 70.0f});
    }
  }

  if (226 == curImageIndex) {
    pOwnerProjectileComponent_->FireProjectile(IORI_PROJECTILE_YamiBarai);
  }
}

void IoriSkillHandler::HyakushikiOniyaki() {
  if (true == pOwnerRenderer_->IsAnimationEnd()) {
    pOwnerSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pOwnerRenderer_->GetImageIndex();
  unsigned int prevImageIndex = pOwnerPlayer_->prevImageIndex_;
  if (prevImageIndex == curImageIndex) {
    return;
  }

  if (276 == curImageIndex) {
    pOwnerMovementComponent_->Dash(pOwnerPlayer_->FacingRight(), 150.0f, 150.0f);
  }

  if (281 == curImageIndex) {
    pOwnerMovementComponent_->Jump(pOwnerPlayer_->FacingRight(), {0.4f, -4.5f});
    pOwnerProjectileComponent_->FireProjectile(IORI_PROJECTILE_HyakushikiOniyaki_Low);
  }

  if (284 == curImageIndex) {
    pOwnerProjectileComponent_->FireProjectile(IORI_PROJECTILE_HyakushikiOniyaki_High);
  }
}

void IoriSkillHandler::ShikiAoiHana127() {
  if (true == pOwnerRenderer_->IsAnimationEnd()) {
    pOwnerSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pOwnerRenderer_->GetImageIndex();
  unsigned int prevImageIndex = pOwnerPlayer_->prevImageIndex_;
  if (prevImageIndex == curImageIndex) {
    return;
  }

  if (curImageIndex == 257) {
    pOwnerMovementComponent_->Dash(pOwnerPlayer_->FacingRight(), 150.0f, 80.0f);
  }

  if (curImageIndex == 262) {
    pOwnerMovementComponent_->Dash(pOwnerPlayer_->FacingRight(), 150.0f, 80.0f);
  }

  if (curImageIndex == 269) {
    pOwnerMovementComponent_->Jump(pOwnerPlayer_->FacingRight(), {0.6f, 60.0f});
  }

  if (IORI_ANIMTYPE_127ShikiAoiHana_1 == pOwnerStateComponent_->GetCurAnimState()) {
    if (257 <= curImageIndex && 260 >= curImageIndex) {
      const std::bitset<8> inputDownBitset = pOwnerPlayer_->InputDownBitSet();
      if (true == pOwnerPlayer_->IsContainInputBitSet(inputDownBitset, std::bitset<8>("00001000")) ||
          true == pOwnerPlayer_->IsContainInputBitSet(inputDownBitset, std::bitset<8>("00000010"))) {
        pOwnerSkillComponent_->SetMiscTemp(true);
      }

      if (pOwnerAttackCollision_->HasHit() && pOwnerSkillComponent_->GetMiscTemp() == true) {
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_127ShikiAoiHana_2);
        pOwnerSkillComponent_->SetMiscTemp(false);
      }
    }
  }

  if (IORI_ANIMTYPE_127ShikiAoiHana_2 == pOwnerStateComponent_->GetCurAnimState()) {
    if (IORI_ANIMTYPE_127ShikiAoiHana_2 == pOwnerStateComponent_->GetCurAnimState() && 264 <= curImageIndex && 267 >= curImageIndex) {
      const std::bitset<8> inputDownBitset = pOwnerPlayer_->InputDownBitSet();
      if (true == pOwnerPlayer_->IsContainInputBitSet(inputDownBitset, std::bitset<8>("00001000")) ||
          true == pOwnerPlayer_->IsContainInputBitSet(inputDownBitset, std::bitset<8>("00000010"))) {
        pOwnerSkillComponent_->SetMiscTemp(true);
      }

      if (pOwnerAttackCollision_->HasHit() && true == pOwnerSkillComponent_->GetMiscTemp()) {
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_127ShikiAoiHana_3);
      }
    }
  }
}

void IoriSkillHandler::ShikiYaOtome1211() {
  if (true == pOwnerRenderer_->IsAnimationEnd()) {
    pOwnerSkillComponent_->DeactivateSkill();
    return;
  }

  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }

  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  ScreenMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  unsigned int curImageIndex = pOwnerRenderer_->GetImageIndex();
  unsigned int prevImageIndex = pOwnerPlayer_->prevImageIndex_;
  if (prevImageIndex == curImageIndex) {
    return;
  }

  switch (pOwnerStateComponent_->GetCurAnimState()) {
    case PLAYER_ANIMTYPE_UltimateCasting: {
      if (347 == curImageIndex) {
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_1);
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
        pOwnerMovementComponent_->Dash(pOwnerPlayer_->FacingRight(), 250.0f, 1000.0f);
        break;
      }

      if (pOwnerAttackCollision_->HasHit()) {
        pOwnerMovementComponent_->Dash(pOwnerPlayer_->FacingRight(), 250.0f, 1000.0f);

        if (pOwnerPlayer_->GetCloseDistance() - 100.0f > std::fabs(pOwnerPlayer_->GetPosition().X - pOwnerPlayer_->GetOpponentPlayer()->GetPosition().X)) {
          pOwnerPlayer_->GetOpponentPlayer()->SetControlLocked(true);
          pOwnerMovementComponent_->StopDash();
          pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_2);
        }
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_2: {
      if (pOwnerPlayer_->GetOpponentPlayer()->GetPosition().X - pOwnerPlayer_->GetPosition().X <= 300.0f * pOwnerPlayer_->FacingRightFlag()) {
        pOwnerMovementComponent_->StopDash();
      }

      if (120 == curImageIndex) {
        pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
        break;
      }

      if (122 == curImageIndex) {
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_3);
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
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_4);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_4: {
      if (135 == curImageIndex) {
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_5);
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
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_6);
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
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_7);
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
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_8);
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
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_1211ShikiYaOtome_9);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_1211ShikiYaOtome_9: {
      if (348 == curImageIndex) {
        pOwnerPlayer_->GetOpponentPlayer()->UpdateAnimState(PLAYER_ANIMTYPE_NeckGrab);
        break;
      }

      if (349 == curImageIndex) {
        const Vector& ioriPosition = pOwnerPlayer_->GetPosition();
        const Vector& targetPosition = ioriPosition + Vector{100.0f * pOwnerPlayer_->FacingRightFlag(), -50.0f};
        pOwnerPlayer_->GetOpponentPlayer()->SetPosition(targetPosition);
        // soundChannel_ = SoundManager::Instance()->SoundPlay(SOUNDTYPE_IORI_1211ShikiYaOtome03);
        SoundManager::Instance()->SoundPlay(SOUNDTYPE_IORI_1211ShikiYaOtome03);
        break;
      }
      if (351 == curImageIndex) {
        pOwnerCommandComponent_->ExcuteTask();
        if (true == pOwnerSkillComponent_->GetMiscTemp()) {
          ActiveUra306shikiShika();
        } else {
          pBackGroundMask->FadeInOut(IMGTYPE_WhiteBoardImage, 50);
          pKOFLevel->GetCameraTarget()->OnCameraShake(300);
        }
        break;
      }
      if (352 == curImageIndex) {
        pOwnerPlayer_->GetOpponentPlayer()->SetControlLocked(false);
        break;
      }
      break;
    }
    default:
      break;
  }
}

void IoriSkillHandler::ActiveUra306shikiShika() {
  if (nullptr == pOwnerMPComponent_) {
    return;
  }
  if (0 >= pOwnerMPComponent_->SkillPoint()) {
    return;
  }

  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }

  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  ScreenMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_Ura306shikiShika_1, ANIMMOD_NONE, true);
  pOwnerSkillComponent_->ActivateSkill(IORI_SKILL_Ura306shikiShika);
  pOwnerMPComponent_->ReduceSkillPoint();
}

void IoriSkillHandler::Ura306shikiShika() {
  if (true == pOwnerRenderer_->IsAnimationEnd()) {
    pOwnerSkillComponent_->DeactivateSkill();
    return;
  }

  Level* pLevel = pOwnerPlayer_->GetLevel();
  if (nullptr == pLevel) {
    return;
  }

  KOFLevel* pKOFLevel = dynamic_cast<KOFLevel*>(pLevel);
  if (nullptr == pKOFLevel) {
    return;
  }

  ScreenMask* pBackGroundMask = pKOFLevel->GetBackGroundMask();
  if (nullptr == pBackGroundMask) {
    return;
  }

  unsigned int curImageIndex = pOwnerRenderer_->GetImageIndex();
  unsigned int prevImageIndex = pOwnerPlayer_->prevImageIndex_;
  if (prevImageIndex == curImageIndex) {
    return;
  }

  switch (pOwnerStateComponent_->GetCurAnimState()) {
    case IORI_ANIMTYPE_Ura306shikiShika_1: {
      if (355 == curImageIndex) {
        EffectManager::Instance()->SpawnEffect(pKOFLevel, EFTYPE_Casting_1, pOwnerPlayer_->GetPosition() + Vector{0.0f, -250.0f});
        EffectManager::Instance()->SpawnEffect(pKOFLevel, EFTYPE_Casting_2, pOwnerPlayer_->GetPosition() + Vector{0.0f, -250.0f});
        pKOFLevel->FreezeActors({pOwnerPlayer_, pOwnerPlayer_->GetOpponentPlayer()}, false, 500);
        pBackGroundMask->FadeOut(IMGTYPE_BlackBoardImage, 50.0f);
      }
      if (356 == curImageIndex) {
        pKOFLevel->FreezeActors({pOwnerPlayer_->GetOpponentPlayer()}, true);
      }
      if (360 == curImageIndex) {
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_Ura306shikiShika_2);
        pBackGroundMask->FadeIn(50.0f);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_Ura306shikiShika_2: {
      if (363 == curImageIndex) {
        break;
      }
      if (364 == curImageIndex) {
        break;
      }
      if (365 == curImageIndex) {
        break;
      }
      if (366 == curImageIndex) {
        pOwnerAttackCollision_->ResetHit();
        pKOFLevel->DefreezeActors();
        // pOpponentPlayer_->SetControlLocked(false);
        break;
      }

      if (370 == curImageIndex) {
        pOwnerPlayer_->UpdateAnimState(IORI_ANIMTYPE_Ura306shikiShika_3);
        break;
      }
      break;
    }
    case IORI_ANIMTYPE_Ura306shikiShika_3: {
      if (381 == curImageIndex) {
        pOwnerProjectileComponent_->FireProjectile(IORI_PROJECTILE_Ura306Shiki);
        break;
      }
      if (386 == curImageIndex) {
        pOwnerPlayer_->GetOpponentPlayer()->SetControlLocked(false);
      }

      break;
    }
    default:
      break;
  }
}
