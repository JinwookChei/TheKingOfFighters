#pragma once
#include "KOFPlayer.h"
#include "AnimationHandler.h"
#include "SkillComponent.h"
#include "StateComponent.h"
#include "ProjectileComponent.h"
#include "MovementComponent.h"
#include "CommandComponent.h"
#include "MPComponent.h"

//enum SKILL_EVENT : unsigned int {
//    MovementJump = 0,
//    MovementDash,
//  MovementStopDash,
//  SpwanEffect,
//  FireProjectile,
//  CommandExcute,
//  SetPostionOppenentPlayer,
//  LockControlOppenentPlayer,
//  UnLockControlOppenentPlayer,
//  FreezeOppenentPlayer,
//  DefreezePlayers,
//  CameraShake,
//  FadeIn,
//  FadeOut,
//  FadeInout,
//  SoundPlay,
//  
//
//};
//
//struct SkillEvent {
//  unsigned long long imageIndex_ = 0;
//
//  std::vector<SKILL_EVENT> events_;
//};
//
//struct SkillState
//{
//  unsigned long long animState_ = 0;
//  
//  unsigned int transCondition_ = 0;
//
//  std::vector<SkillEvent> events;
//};
//
//struct SkillData
//{
//  unsigned long long skillTag_ = 0;
//
//  std::vector<SkillState> skillStates_;
//
//};



class SkillHandler
    : public ActorComponent {
 public:
  SkillHandler();
  ~SkillHandler() override;

  bool Initialize(KOFPlayer* ownerPlayer,
                  SkillComponent* ownerSkillComponent,
                  ImageRenderer* ownerRenderer,
                  AnimationHandler* pAnimationHandler,
                  MovementComponent* ownerMovementComponent,
                  StateComponent* ownerStateComponent,
                  CollisionComponent* ownerAttackCollision,
                  CommandComponent* ownerCommandComponent,
                  ProjectileComponent* ownerProjectileComponent,
                  MPComponent* ownerMPComponent);

  virtual bool RegistSkills() = 0;

 protected:
  KOFPlayer* pOwnerPlayer_;

  SkillComponent* pOwnerSkillComponent_;

  ImageRenderer* pOwnerRenderer_;

  AnimationHandler* pOwnerAnimationHandler_;

  MovementComponent* pOwnerMovementComponent_;

  StateComponent* pOwnerStateComponent_;

  CollisionComponent* pOwnerAttackCollision_;

  CommandComponent* pOwnerCommandComponent_;

  ProjectileComponent* pOwnerProjectileComponent_;

  MPComponent* pOwnerMPComponent_;
};
