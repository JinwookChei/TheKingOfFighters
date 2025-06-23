#include "stdafx.h"
#include "KOFPlayer.h"
#include "KOFLevel.h"
#include "BlackBoard.h"
#include "MovementComponent.h"
#include "DamageSystem.h"
#include "SkillComponent.h"
#include "CommandComponent.h"
#include "ProjectileComponent.h"
#include "HealthComponent.h"
#include "StateComponent.h"
#include "GhostEffect.h"
#include "CollisionBox.h"
#include "Iori.h"

Iori::Iori() {
}

Iori::~Iori() {
}

void Iori::BeginPlay() {
}

void Iori::Initialize(const Vector& position, bool useCameraPosition, bool flip, KOFPlayer* opponentPlayer) {
  KOFPlayer::Initialize(position, useCameraPosition, flip, opponentPlayer);

  // CHARACTER SETTING
  IImage* pImage = ImgManager::GetIntance()->GetImg(3);
  if (nullptr == pImage) {
    return;
  }
  SetCharacterScale(pImage->GetScale(7) * pRender_->GetLocalScale());

  // RENDERER
  if(false == pRender_->CreateAnimation(PAS_Idle, IMGKEY_IoriImage, 7, 15, 50, true, 7)) return;                      // ¾ÆÀÌµé
  if(false == pRender_->CreateAnimation(PAS_SeatDown, IMGKEY_IoriImage, 16, 23, 50, true, 18)) return;                // ¾É±â. Down
  if(false == pRender_->CreateAnimation(PAS_SeatUp, IMGKEY_IoriImage, 24, 25, 50, false, 24)) return;                 // ¾É±â. Up
  if(false == pRender_->CreateAnimation(PAS_FrontWalk, IMGKEY_IoriImage, 27, 34, 50, true, 27)) return;               // -> °È±â
  if(false == pRender_->CreateAnimation(PAS_BackWalk, IMGKEY_IoriImage, 35, 44, 50, true, 35)) return;                // <- µÚ·Î°¡±â
  if(false == pRender_->CreateAnimation(PAS_BackStep, IMGKEY_IoriImage, 45, 48, 50, false, 45)) return;               // <- <- ¹é½ºÅÇ
  if(false == pRender_->CreateAnimation(PAS_Run, IMGKEY_IoriImage, 49, 57, 50, true, 51)) return;                     // ->-> ¶Ù±â Start
  if(false == pRender_->CreateAnimation(PAS_RunEnd, IMGKEY_IoriImage, 58, 60, 50, false, 59)) return;                 // ->-> ¶Ù±â Stop
  if(false == pRender_->CreateAnimation(PAS_Jump, IMGKEY_IoriImage, 61, 69, 50, false, 61)) return;                   // Á¡ÇÁ
  if(false == pRender_->CreateAnimation(PAS_HeavyKick, IMGKEY_IoriImage, 108, 117, 50, false, 108)) return;           // ¹ßÂ÷±â
  if(false == pRender_->CreateAnimation(IOAS_108ShikiYamiBarai, IMGKEY_IoriImage, 223, 230, 50, false, 223)) return;  // Ä¿¸Çµå Å×½ºÆ®.
  if(false == pRender_->CreateAnimation(IOAS_GaishikiMutan_1, IMGKEY_IoriImage, 99, 107, 50, false, 99)) return;      // ¿Ü½Ä ¸ùÅº_1
  if(false == pRender_->CreateAnimation(IOAS_GaishikiMutan_2, IMGKEY_IoriImage, 160, 164, 50, false, 160)) return;    // ¿Ü½Ä ¸ùÅº_2
  if(false == pRender_->CreateAnimation(IOAS_Shinigami, IMGKEY_IoriImage, 136, 144, 50, false, 136)) return;          // ¿Ü½Ä ±¤ºÎ À½ "»ç½Å"
  if(false == pRender_->CreateAnimation(IOAS_HyakushikiOniyaki, IMGKEY_IoriImage, 276, 291, 50, false, 276)) return;  // ¹é½Ä ±Í½Å ÅÂ¿ì±â
  if(false == pRender_->CreateAnimation(IOAS_127ShikiAoiHana_1, IMGKEY_IoriImage, 255, 261, 50, false, 255)) return;  // ¹é½Ä ±Í½Å ÅÂ¿ì±â
  if(false == pRender_->CreateAnimation(IOAS_127ShikiAoiHana_2, IMGKEY_IoriImage, 262, 268, 50, false, 262)) return;  // ¹é½Ä ±Í½Å ÅÂ¿ì±â
  if(false == pRender_->CreateAnimation(IOAS_127ShikiAoiHana_3, IMGKEY_IoriImage, 269, 275, 50, false, 269)) return;  // ¹é½Ä ±Í½Å ÅÂ¿ì±â
  if(false == pRender_->CreateAnimation(IOAS_UltimateCasting, IMGKEY_IoriImage, 344, 347, 50, false, 344)) return;    // ±Ã±Ø±â Ä³½ºÆÃ

  if (false == pRender_->CreateAnimation(-PAS_Idle, -IMGKEY_IoriImage, 7, 15, 50, true, 7)) return;                      // ¾ÆÀÌµé
  if (false == pRender_->CreateAnimation(-PAS_SeatDown, -IMGKEY_IoriImage, 16, 23, 50, true, 18)) return;                // ¾É±â.
  if (false == pRender_->CreateAnimation(-PAS_FrontWalk, -IMGKEY_IoriImage, 27, 34, 50, true, 27)) return;               // -> °È±â
  if (false == pRender_->CreateAnimation(-PAS_BackWalk, -IMGKEY_IoriImage, 35, 44, 50, true, 35)) return;                // <- µÚ·Î°¡±â
  if (false == pRender_->CreateAnimation(-PAS_BackStep, -IMGKEY_IoriImage, 45, 48, 50, false, 45)) return;               // <- <- ¹é½ºÅÇ
  if (false == pRender_->CreateAnimation(-PAS_Run, -IMGKEY_IoriImage, 49, 58, 50, true, 51)) return;                     // ->-> ¶Ù±â
  if (false == pRender_->CreateAnimation(-PAS_Jump, -IMGKEY_IoriImage, 61, 69, 50, false, 61)) return;                   // Á¡ÇÁ
  if (false == pRender_->CreateAnimation(-PAS_HeavyKick, -IMGKEY_IoriImage, 108, 117, 50, false, 108)) return;           // ¹ßÂ÷±â
  if (false == pRender_->CreateAnimation(-IOAS_108ShikiYamiBarai, -IMGKEY_IoriImage, 223, 230, 50, false, 223)) return;  // Ä¿¸Çµå Å×½ºÆ®.
  pRender_->SetTransparentColor(ioriTransparentColor);
  UpdateAnimState(PAS_Idle);

  // STATE
  if (false == pStateComponent_->RegistState(PAS_Idle, PS_Idle, true, true)) return;
  if (false == pStateComponent_->RegistState(PAS_SeatDown, PS_Seat, true, true)) return;
  if (false == pStateComponent_->RegistState(PAS_SeatUp, PS_Seat, true, true)) return;
  if (false == pStateComponent_->RegistState(PAS_FrontWalk, PS_Move, true, true)) return;
  if (false == pStateComponent_->RegistState(PAS_BackWalk, PS_Move, true, true)) return;
  if (false == pStateComponent_->RegistState(PAS_BackStep, PS_Move, false, false)) return;
  if (false == pStateComponent_->RegistState(PAS_Run, PS_Move, true, true)) return;
  if (false == pStateComponent_->RegistState(PAS_RunEnd, PS_Move, false, false)) return;
  if (false == pStateComponent_->RegistState(PAS_Jump, PS_Jump, false, false)) return;
  if (false == pStateComponent_->RegistState(PAS_HeavyKick, PS_Attack, false, false)) return;
  if (false == pStateComponent_->RegistState(IOAS_108ShikiYamiBarai, PS_Attack, false, false)) return;
  if (false == pStateComponent_->RegistState(IOAS_GaishikiMutan_1, PS_Attack, false, false)) return;
  if (false == pStateComponent_->RegistState(IOAS_GaishikiMutan_2, PS_Attack, false, false)) return;
  if (false == pStateComponent_->RegistState(IOAS_Shinigami, PS_Attack, false, false)) return;
  if (false == pStateComponent_->RegistState(IOAS_HyakushikiOniyaki, PS_Attack, false, false)) return;
  if (false == pStateComponent_->RegistState(IOAS_127ShikiAoiHana_1, PS_Attack, false, false)) return;
  if (false == pStateComponent_->RegistState(IOAS_127ShikiAoiHana_2, PS_Attack, false, false)) return;
  if (false == pStateComponent_->RegistState(IOAS_127ShikiAoiHana_3, PS_Attack, false, false)) return;
  if (false == pStateComponent_->RegistState(IOAS_UltimateCasting, PS_Attack, false, false)) return;

  // DAMAGE
  if (false == pDamageSystem_->RegistDamageInfo(PAS_HeavyKick, 10.0f, {20.0f, 0.0f})) return;
  if (false == pDamageSystem_->RegistDamageInfo(IOAS_108ShikiYamiBarai, 5.0f, {20.0f, 60.0f})) return;
  if (false == pDamageSystem_->RegistDamageInfo(IOAS_GaishikiMutan_1, 5.0f, {5.0f, 0.0f})) return;
  if (false == pDamageSystem_->RegistDamageInfo(IOAS_GaishikiMutan_2, 5.0f, {20.0f, 40.0f})) return;
  if (false == pDamageSystem_->RegistDamageInfo(IOAS_Shinigami, 15.0f, {20.0f, 80.0f})) return;
  if (false == pDamageSystem_->RegistDamageInfo(IOAS_HyakushikiOniyaki, 20.0f, {40.0f, 80.0f})) return;
  if (false == pDamageSystem_->RegistDamageInfo(IOAS_127ShikiAoiHana_1, 5.0f, {10.0f, 00.0f})) return;
  if (false == pDamageSystem_->RegistDamageInfo(IOAS_127ShikiAoiHana_2, 5.0f, {10.0f, 00.0f})) return;
  if (false == pDamageSystem_->RegistDamageInfo(IOAS_127ShikiAoiHana_3, 5.0f, {20.0f, 80.0f})) return;

  // SKILL
  if (false == pSkillComponent_->RegistSkill(IOSK_GaishikiMutan, &Iori::GaishikiMutan, this)) return;
  if (false == pSkillComponent_->RegistSkill(IOSK_108ShikiYamiBarai, &Iori::ShikiYamiBarai108, this)) return;
  if (false == pSkillComponent_->RegistSkill(IOSK_Shinigami, &Iori::Shinigami, this)) return;
  if (false == pSkillComponent_->RegistSkill(IOSK_HyakushikiOniyaki, &Iori::HyakushikiOniyaki, this)) return;
  if (false == pSkillComponent_->RegistSkill(IOSK_127ShikiAoiHana, &Iori::ShikiAoiHana127, this)) return;
  if (false == pSkillComponent_->RegistSkill(IOSK_1211ShikiYaOtome, &Iori::ShikiYaOtome1211, this)) return;
  

  // COMMAND
  if (false == pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_A}, std::bind(&Iori::Command_1, this))) return;
  if (false == pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_B}, std::bind(&Iori::Command_1, this))) return;
  if (false == pCommandComponent_->RegistCommand({CK_Left, CK_Left}, std::bind(&Iori::Command_2, this))) return;
  if (false == pCommandComponent_->RegistCommand({CK_Right, CK_Right}, std::bind(&Iori::Command_3, this))) return;
  if (false == pCommandComponent_->RegistCommand({CK_Right, CK_Down, CK_Right, CK_A}, std::bind(&Iori::Command_4, this))) return;
  if (false == pCommandComponent_->RegistCommand({CK_Right, CK_Down, CK_Right, CK_C}, std::bind(&Iori::Command_4, this))) return;
  if (false == pCommandComponent_->RegistCommand({CK_Down, CK_Left, CK_A}, std::bind(&Iori::Command_5, this))) return;
  if (false == pCommandComponent_->RegistCommand({CK_Down, CK_Left, CK_C}, std::bind(&Iori::Command_5, this))) return;
  if (false == pCommandComponent_->RegistCommand({CK_Down, CK_Right, CK_Down, CK_Left, CK_A}, std::bind(&Iori::Command_6, this))) return;
  if (false == pCommandComponent_->RegistCommand({CK_Down, CK_Right, CK_Down, CK_Left, CK_C}, std::bind(&Iori::Command_6, this))) return;


  // PROJECTILE
  if (false == pProjectileComponent_->RegistProjectileInfo(1, IMGKEY_IoriImage, 239, 244, 20, true, {169, 139, 150, 0}, {35.0f, 0.0f}, {180.0f, 50.0f}, {1500.0f, 0.0f})) return;
  if (false == pProjectileComponent_->RegistProjectileInfo(2, IMGKEY_IoriImage, 292, 301, 50, false, {169, 139, 150, 0}, {0.0f, -7.0f}, {50.0f, -30.0f}, {0.0f, 0.0f})) return;
  if (false == pProjectileComponent_->RegistProjectileInfo(3, IMGKEY_IoriImage, 302, 311, 40, false, {169, 139, 150, 0}, {0.0f, -7.0f}, {-80.0f, -200.0f}, {0.0f, 0.0f})) return;

  // GHOST EFFECT
  pGhostEffect_->SetTransparentColor(ioriTransparentColor);

  
}

void Iori::Tick(unsigned long long deltaTick) {

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

  UpdateInput(deltaTick);

  if (true == pStateComponent_->CanInput() || true == pRender_->IsAnimationEnd()) {
    CompareInputBitset(deltaTick);
  }
  

  pSkillComponent_->UpdateActiveSkill();

  //  TODO : ¼öÁ¤»çÇ×
   unsigned int curImageIndex = pRender_->GetImageIndex();
   if (prevImageIndex_ != curImageIndex && curImageIndex == 69) {
     pGhostEffect_->Off();
   }
  //  TODO END

  UpdatePrevAnimationIndex();
}

void Iori::UpdateInput(unsigned long long curTick) {
  // InputBitSet :
  // Left : 10000000
  // Down : 01000000
  // Right: 00100000
  // Up :   00010000
  // A  :   00001000
  // B  :   00000100
  // C  :   00000010
  // D  :   00000001

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
    return;
  }

  if (InputManager::Instance()->IsPress(VK_LEFT) || InputManager::Instance()->IsPress(VK_LEFT)) {
    inputPressBitSet_.set(7);
  }

  if (InputManager::Instance()->IsUp(VK_LEFT) || InputManager::Instance()->IsUp(VK_LEFT)) {
    inputUpBitSet_.set(7);
  }

  if (InputManager::Instance()->IsPress(VK_DOWN) || InputManager::Instance()->IsPress(VK_DOWN)) {
    inputPressBitSet_.set(6);
  }

  if (InputManager::Instance()->IsUp(VK_DOWN) || InputManager::Instance()->IsUp(VK_DOWN)) {
    inputUpBitSet_.set(6);
  }

  if (InputManager::Instance()->IsPress(VK_RIGHT) || InputManager::Instance()->IsPress(VK_RIGHT)) {
    inputPressBitSet_.set(5);
  }

  if (InputManager::Instance()->IsUp(VK_RIGHT) || InputManager::Instance()->IsUp(VK_RIGHT)) {
    inputUpBitSet_.set(5);
  }

  if (InputManager::Instance()->IsPress(VK_UP) || InputManager::Instance()->IsPress(VK_UP)) {
    inputPressBitSet_.set(4);
  }
  if (InputManager::Instance()->IsUp(VK_UP) || InputManager::Instance()->IsUp(VK_UP)) {
    inputUpBitSet_.set(4);
  }

  // A
  if (InputManager::Instance()->IsPress('X') || InputManager::Instance()->IsPress('x')) {
    inputPressBitSet_.set(3);
  }
  if (InputManager::Instance()->IsUp('X') || InputManager::Instance()->IsUp('x')) {
    inputUpBitSet_.set(3);
  }

  // B
  if (InputManager::Instance()->IsPress('Z') || InputManager::Instance()->IsPress('z')) {
    inputPressBitSet_.set(2);
  }
  if (InputManager::Instance()->IsUp('Z') || InputManager::Instance()->IsUp('z')) {
    inputUpBitSet_.set(2);
  }

  // C
  if (InputManager::Instance()->IsPress('S') || InputManager::Instance()->IsPress('s')) {
    inputPressBitSet_.set(1);
  }
  if (InputManager::Instance()->IsUp('S') || InputManager::Instance()->IsUp('s')) {
    inputUpBitSet_.set(1);
  }

  // D
  if (InputManager::Instance()->IsPress('A') || InputManager::Instance()->IsPress('a')) {
    inputPressBitSet_.set(0);
  }
  if (InputManager::Instance()->IsUp('A') || InputManager::Instance()->IsUp('a')) {
    inputUpBitSet_.set(0);
  }
}

void Iori::CompareInputBitset(unsigned long long curTick) {
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
      if (FacingRight()) {
        UpdateAnimState(IOAS_GaishikiMutan_1);
        pSkillComponent_->ActivateSkill(IOSK_GaishikiMutan);
        return;
      }
    }

    // RIGHT B - PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("00100100"))) {
      if (FacingRight()) {
        UpdateAnimState(IOAS_Shinigami);
        pSkillComponent_->ActivateSkill(IOSK_Shinigami);
        return;
      }
    }

    // LEFT PRESS
    if (true == IsEqualInputBitSet(inputPressBitSet_, std::bitset<8>("10000000"))) {
      if (FacingRight()) {
        UpdateAnimState(PAS_BackWalk);
        pMovementComponent_->MoveBack(curTick, FacingRight(), pPushBox_->IsCollided());
        return;
      } else {
        if (PAS_Run == animState_) {
          pMovementComponent_->Run(curTick, false, pPushBox_->IsCollided());
          return;
        }
        UpdateAnimState(PAS_FrontWalk);
        pMovementComponent_->Move(curTick, FacingRight(), pPushBox_->IsCollided());
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
          pMovementComponent_->Run(curTick, true, pPushBox_->IsCollided());
          return;
        }
        UpdateAnimState(PAS_FrontWalk);
        pMovementComponent_->Move(curTick, FacingRight(), pPushBox_->IsCollided());
        return;
      } else {
        UpdateAnimState(PAS_BackWalk);
        pMovementComponent_->MoveBack(curTick, FacingRight(), pPushBox_->IsCollided());
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

void Iori::UpdateCommand() {
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

void Iori::Command_1() {
  UpdateAnimState(IOAS_108ShikiYamiBarai);
  pSkillComponent_->ActivateSkill(IOSK_108ShikiYamiBarai);
}

void Iori::Command_2() {
  UpdateAnimState(PAS_BackStep);
  pMovementComponent_->BackStep((FacingRight()));
}

void Iori::Command_3() {
  UpdateAnimState(PAS_Run);
}

void Iori::Command_4() {
  UpdateAnimState(IOAS_HyakushikiOniyaki);
  pSkillComponent_->ActivateSkill(IOSK_HyakushikiOniyaki);
}

void Iori::Command_5() {
  UpdateAnimState(IOAS_127ShikiAoiHana_1);
  pSkillComponent_->ActivateSkill(IOSK_127ShikiAoiHana);
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

  BlackBoard* pBlackBoard = pKOFLevel->GetBlackBoard();
  if (nullptr == pBlackBoard) {
    return;
  }

  UpdateAnimState(IOAS_UltimateCasting);
  pSkillComponent_->ActivateSkill(IOSK_1211ShikiYaOtome);
  pBlackBoard->FadeOut(1000.0f);
}

void Iori::GaishikiMutan() {
  if (true == pRender_->IsAnimationEnd()) {
    pSkillComponent_->DeactivateSkill();
    return;
  }

  unsigned int curImageIndex = pRender_->GetImageIndex();

  if (IOAS_GaishikiMutan_1 == pStateComponent_->GetCurAnimState()) {
    if (100 <= curImageIndex && 104 >= curImageIndex) {
      if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000"))) {
        pSkillComponent_->SetMiscTemp(true);
      }
    }

    if (true == pAttackBox_->IsCollided() && 105 == curImageIndex && true == pSkillComponent_->GetMiscTemp()) {
      UpdateAnimState(IOAS_GaishikiMutan_2);
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
    pProjectileComponent_->FireProjectile(1);
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
    pProjectileComponent_->FireProjectile(2);
  }

  if (284 == curImageIndex) {
    pProjectileComponent_->FireProjectile(3);
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

  if (IOAS_127ShikiAoiHana_1 == pStateComponent_->GetCurAnimState()) {
    if (257 <= curImageIndex && 260 >= curImageIndex) {
      if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000")) ||
          true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
        pSkillComponent_->SetMiscTemp(true);
      }

      if (pAttackBox_->IsCollided() && pSkillComponent_->GetMiscTemp() == true) {
        UpdateAnimState(IOAS_127ShikiAoiHana_2);
        pSkillComponent_->SetMiscTemp(false);
      }
    }
  }

  if (IOAS_127ShikiAoiHana_2 == pStateComponent_->GetCurAnimState()) {
    if (IOAS_127ShikiAoiHana_2 == pStateComponent_->GetCurAnimState() && 264 <= curImageIndex && 267 >= curImageIndex) {
      if (true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00001000")) ||
          true == IsContainInputBitSet(inputPressBitSet_, std::bitset<8>("00000010"))) {
        pSkillComponent_->SetMiscTemp(true);
      }

      if (pAttackBox_->IsCollided() && true == pSkillComponent_->GetMiscTemp()) {
        UpdateAnimState(IOAS_127ShikiAoiHana_3);
      }
    }
  }
}


void Iori::ShikiYaOtome1211() {
  //pRender_->SetEnableTick(false);
}
