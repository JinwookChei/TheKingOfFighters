#pragma once

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
};

enum SKILL_FRAME_ACTION_TYPE : unsigned int {
  SKILL_FRAME_ACTION_None = 0,
  SKILL_FRAME_ACTION_DeactiveSkill,
  SKILL_FRAME_ACTION_UpdateSkillState,
  SKILL_FRAME_ACTION_MovementJump,
  SKILL_FRAME_ACTION_MovementDash,
  SKILL_FRAME_ACTION_MovementStopDash,
  SKILL_FRAME_ACTION_SpawnEffect,
  SKILL_FRAME_ACTION_FireProjectile,
  SKILL_FRAME_ACTION_CommandExecute,
  SKILL_FRAME_ACTION_SetPostionOppenentPlayer,
  SKILL_FRAME_ACTION_LockControlOppenentPlayer,
  SKILL_FRAME_ACTION_UnLockControlOppenentPlayer,
  SKILL_FRAME_ACTION_FreezeOppenentPlayer,
  SKILL_FRAME_ACTION_DefreezePlayers,
  SKILL_FRAME_ACTION_CameraShake,
  SKILL_FRAME_ACTION_FadeIn,
  SKILL_FRAME_ACTION_FadeOut,
  SKILL_FRAME_ACTION_FadeInout,
  SKILL_FRAME_ACTION_SoundPlay,
  SKILL_FRAME_ACTION_SetCurStateMiscFlagTrue
};

struct SkillFrameActionParams {
  unsigned int changeStateIndex_ = 0;

  union {
    EFFECT_TYPE effectType_ = EFFECT_TYPE::EFTYPE_None;

    PROJECTILE_TYPE projectileType_;
  };

  union {
    Vector jumpForce_{0.0f, 0.0f};
    Vector spawnEffectPos_;
    struct {
      float dashDuration_;
      float dashDistance_;
      float pad1_;
      float pad2_;
    };
    struct {
      float fadeDuration_;
      float pad1_;
      float pad2_;
      float pad3_;
    };
  };
};

struct SkillFrameActionData {
  SKILL_FRAME_ACTION_TYPE actionType_ = SKILL_FRAME_ACTION_None;

  SkillFrameActionParams actionParams_;
};

struct SkillFrameAction {
  std::vector<SKILL_FRAME_ACTION_CONDITION_TYPE> actionConditions_;

  std::vector<SkillFrameActionData> actionDatas;

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

class SkillTest
    : public ActorComponent {
 public:
  SkillTest();

  ~SkillTest() override;

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
  // --------------------------------------------------


  // -------------- Skill Condition -------------------
  bool CheckFrameActionCondition(SKILL_FRAME_ACTION_CONDITION_TYPE actionCondition) const;

  bool GetCurStateMiscFlag() const;
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

  void SetPositionOppenentPlayer(const SkillFrameActionParams& params);

  void LockControlOppenentPlayer(const SkillFrameActionParams& params);

  void UnLockControlOppenentPlayer(const SkillFrameActionParams& params);

  void FreezeOppenentPlayer(const SkillFrameActionParams& params);

  void DefreezePlayers(const SkillFrameActionParams& params);

  void ExcuteCameraShake(const SkillFrameActionParams& params);

  void ExcuteFadeIn(const SkillFrameActionParams& params);

  void ExcuteFadeOut(const SkillFrameActionParams& params);

  void ExcuteFadeInout(const SkillFrameActionParams& params);

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
