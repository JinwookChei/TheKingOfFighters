#pragma once
#include "RestrictionComponent.h"

enum SKILL_TYPE : unsigned int {
  SKILL_0 = 0,
  SKILL_1,
  SKILL_2,
  SKILL_3,
  SKILL_4,
  SKILL_5,
  SKILL_6
};

enum SKILL_CASTING_CONDITION_TYPE : unsigned int {
  SKILL_CAST_COND_None = 0,
  SKILL_CAST_COND_HasSkillPoint,
};

enum SKILL_CASTING_ACTION_TYPE : unsigned int {
  SKILL_CAST_ACTION_None = 0,
  SKILL_CAST_ACTION_ReduceSkillPoint
};

enum SKILL_FRAME_ACTION_CONDITION_TYPE : unsigned int {
  SKILL_FRAME_ACTION_COND_None = 0,
  SKILL_FRAME_ACTION_COND_AnimationEnd,
  SKILL_FRAME_ACTION_COND_CheckInputDownA,
  SKILL_FRAME_ACTION_COND_CheckInputDownB,
  SKILL_FRAME_ACTION_COND_CheckInputDownC,
  SKILL_FRAME_ACTION_COND_CheckInputDownD,
  SKILL_FRAME_ACTION_COND_HasAttackCollition,
  SKILL_FRAME_ACTION_COND_IsStateMiscFlagTrue,
  SKILL_FRAME_ACTION_COND_IsOpponentWithinDistanceThresHold
};

enum SKILL_FRAME_ACTION_TYPE : unsigned int {
  SKILL_FRAME_ACTION_None = 0,
  SKILL_FRAME_ACTION_DeactiveSkill,
  SKILL_FRAME_ACTION_ChangeSkillState,
  SKILL_FRAME_ACTION_MovementJump,
  SKILL_FRAME_ACTION_MovementDash,
  SKILL_FRAME_ACTION_MovementStopDash,
  SKILL_FRAME_ACTION_SpawnEffect,
  SKILL_FRAME_ACTION_FireProjectile,
  SKILL_FRAME_ACTION_CommandExecute,
  SKILL_FRAME_ACTION_ChangeOpponentAnimState,
  SKILL_FRAME_ACTION_SetPostionOpponentPlayer,
  SKILL_FRAME_ACTION_InflictRestrictionOpponentPlayer,
  SKILL_FRAME_ACTION_ReleaseRestrictionOpponentPlayer,
  SKILL_FRAME_ACTION_ClearRestrictionOpponentPlayer,
  /*SKILL_FRAME_ACTION_InflictStunOpponentPlayer,
  SKILL_FRAME_ACTION_ReleaseStunOpponentPlayer,
  SKILL_FRAME_ACTION_FreezeOpponentPlayer,
  SKILL_FRAME_ACTION_DefreezeOpponentPlayer,*/
  SKILL_FRAME_ACTION_CameraShake,
  SKILL_FRAME_ACTION_FadeIn,
  SKILL_FRAME_ACTION_FadeOut,
  SKILL_FRAME_ACTION_FadeInOut,
  SKILL_FRAME_ACTION_SoundPlay,
  SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue
};

struct SkillFrameActionParams {
  SkillFrameActionParams()
      : Restriction{0}
  {
    // memset(this, 0, sizeof(SkillFrameActionParams));
  }
  union {
    struct {
      unsigned int changeStateIndex_;
    } ChangeSkillState;

    struct {
      Vector jumpForce_;
    } MovementJump;

    struct {
      unsigned long long dashDuration_;

      float dashDistance_;
    } MovementDash;

    struct {
      Vector spawnEffectPos_;

      EFFECT_TYPE effectType_;
    } SpawnEffect;

    struct {
      PROJECTILE_TYPE projectileType_;
    } FireProjectile;

    struct {
      unsigned long long opponentAnimState_;
    } ChangeOpponentAnimState;

    struct {
      Vector opponentForcedPosition_;
    } SetPostionOpponentPlayer;

    struct {
      unsigned long long cameraShakeDuration_;
    } CameraShake;

    struct {
      IMAGE_TYPE fadeImageType_;

      unsigned long long fadeDuration_;
    } Fade;

    struct {
      SOUND_TYPE soundType_;
    } SoundPlay;

    struct {
      bool isInfinite_;

      unsigned long long restrictDuration_;

      std::bitset<PR_Max> restrictions_;

    } Restriction;
  };
};

struct SkillFrameActionConditionParams {
  float opponentDistanceThreshold = 0.0f;
};

struct SkillFrameActionConditionData {
  SKILL_FRAME_ACTION_CONDITION_TYPE conditionType_ = SKILL_FRAME_ACTION_COND_None;

  SkillFrameActionConditionParams conditionParams_;
};

struct SkillFrameActionData {
  SKILL_FRAME_ACTION_TYPE actionType_ = SKILL_FRAME_ACTION_None;

  SkillFrameActionParams actionParams_;
};

struct SkillFrameAction {
  std::vector<SkillFrameActionConditionData> conditionDatas_;

  std::vector<SkillFrameActionData> actionDatas_;

  bool HasExecuted() const {
    return hasExecuted_;
  }
  void SetHasExcuted(bool flag) {
    hasExecuted_ = flag;
  }
  void ResetHasExecutedFlag() {
    hasExecuted_ = false;
  }

 private:
  bool hasExecuted_ = false;
};

struct SkillFrame {
  unsigned long long startIndex_ = 0;

  unsigned long long endIndex_ = 0;

  std::vector<SkillFrameAction> actions_;
};

struct SkillState {
  unsigned long long animState_ = 0;

  std::vector<SkillFrame> frames_;

  bool MiscFlag() const {
    return miscFlag_;
  }

  void SetMiscFlag(bool flag) {
    miscFlag_ = flag;
  }

 private:
  bool miscFlag_ = false;
};

struct Skill {
  unsigned long long skillTag_ = 0;

  SKILL_CASTING_CONDITION_TYPE castCondition_ = SKILL_CAST_COND_None;

  SKILL_CASTING_ACTION_TYPE castAction_ = SKILL_CAST_ACTION_None;

  std::vector<SkillState> skillStates_;

  void* searchHandle_ = nullptr;
};

class SkillComponent
    : public ActorComponent {
 public:
  SkillComponent();

  ~SkillComponent() override;

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(
      KOFPlayer* pOwnerPlayer,
      ImageRenderer* pRenderer,
      MovementComponent* pMovementComponent,
      InputController* pInputController,
      CollisionComponent* pAttackCollision,
      ProjectileComponent* pProjectileComponent,
      MPComponent* pMPComponent);

  bool RegistSkill(Skill skill);

  void UpdateSkill();

  void ExecuteSkill(unsigned long long skillTag);

  bool IsSkillExecuting();

  void ResetEventExcutedFlags(Skill* pSkill);

  void ResetStateMiscFlags(Skill* pSkill);

  // -------------- Skill Casting Condition Check -----
  bool CheckCastingCondition(SKILL_CASTING_CONDITION_TYPE castCondition);

  bool HasSkillPoint() const;
  // --------------------------------------------------

  // -------------- Skill Casting Action --------------
  void ExcuteCastingAction(SKILL_CASTING_ACTION_TYPE castAction);

  void ReduceSkillPoint();
  // --------------------------------------------------

  // -------------- Skill Condition -------------------
  bool CheckFrameActionCondition(SKILL_FRAME_ACTION_CONDITION_TYPE actionCondition, const SkillFrameActionConditionParams& params) const;

  bool GetCurStateMiscFlag() const;

  bool IsOpponentWithinDistanceThresHold(const SkillFrameActionConditionParams& params) const;
  // --------------------------------------------------

  // -------------- Skill Frame Action -------------
  void ExcuteSkillFrameAction(SKILL_FRAME_ACTION_TYPE actionType, const SkillFrameActionParams& params);

  void DeActiveSkill();

  void ChangeSkillState(const SkillFrameActionParams& params);

  void ExcuteJump(const SkillFrameActionParams& params);

  void ExcuteDash(const SkillFrameActionParams& params);

  void ExcuteDashStop(const SkillFrameActionParams& params);

  void ExcuteSpawnEffect(const SkillFrameActionParams& params);

  void ExcuteFireProjectile(const SkillFrameActionParams& params);

  void ExcuteCommand(const SkillFrameActionParams& params);

  void ChangeOpponentAnimState(const SkillFrameActionParams& params);

  void SetPositionOpponentPlayer(const SkillFrameActionParams& params);

  /*void InflictStunOpponentPlayer(const SkillFrameActionParams& params);

  void ReleaseStunOpponentPlayer(const SkillFrameActionParams& params);

  void FreezeOpponentPlayer(const SkillFrameActionParams& params);

  void DefreezeOpponentPlayer(const SkillFrameActionParams& params);*/
  void InflictRestrictionOpponentPlayer(const SkillFrameActionParams& params);

  void ReleaseRestrictionOpponentPlayer(const SkillFrameActionParams& params);

  void ClearRestrictionOpponentPlayer(const SkillFrameActionParams& params);

  void ExcuteCameraShake(const SkillFrameActionParams& params);

  void ExcuteFadeIn(const SkillFrameActionParams& params);

  void ExcuteFadeOut(const SkillFrameActionParams& params);

  void ExcuteFadeInOut(const SkillFrameActionParams& params);

  void ExcuteSoundPlay(const SkillFrameActionParams& params);

  void SetCurStateMiscFlagTrue(const SkillFrameActionParams& params);

  // --------------------------------------------------

 private:
  KOFPlayer* pOwnerPlayer_;

  ImageRenderer* pOwnerRenderer_;

  MovementComponent* pOwnerMovementConponent_;

  InputController* pOwnerInputController_;

  CollisionComponent* pOwnerAttackCollision_;

  ProjectileComponent* pOwnerProjectileComponent_;

  MPComponent* pOwnerMPComponent_;

  HashTable skillTable_;

  Skill* executingSkill_;

  unsigned int curSkillStateIndex_ = 0;
};
