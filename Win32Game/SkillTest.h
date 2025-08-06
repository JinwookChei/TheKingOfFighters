#pragma once

enum SKILL_TYPE : unsigned long long {
  Skill_1 = 1ULL,
  Skill_2,
  Skill_3,
  Skill_4,
  Skill_5
};

enum SKILL_EVENT_TYPE : unsigned int {
  SkillEvent_None = 0,
  SkillEvent_DeactiveSkill,
  SkillEvent_UpdateSkillState,
  SkillEvent_MovementJump,
  SkillEvent_MovementDash,
  SkillEvent_MovementStopDash,
  SkillEvent_SpawnEffect,
  SkillEvent_FireProjectile,
  SkillEvent_CommandExecute,
  SkillEvent_SetPostionOppenentPlayer,
  SkillEvent_LockControlOppenentPlayer,
  SkillEvent_UnLockControlOppenentPlayer,
  SkillEvent_FreezeOppenentPlayer,
  SkillEvent_DefreezePlayers,
  SkillEvent_CameraShake,
  SkillEvent_FadeIn,
  SkillEvent_FadeOut,
  SkillEvent_FadeInout,
  SkillEvent_SoundPlay,
  SkillEvent_SetMiscTempTrue
};

enum SKILL_EVENT_CONDITION_TYPE : unsigned int {
  SkillEventCondition_None = 0,
  SkillEventCondition_AnimationEnd,
  SkillEventCondition_CheckInputDownA,
  SkillEventCondition_CheckInputDownB,
  SkillEventCondition_CheckInputDownC,
  SkillEventCondition_CheckInputDownD,
  SkillEventCondition_HasAttackCollition,
  SkillEventCondition_MiscTempTrue,
};

struct SkillEvnetParams {
  unsigned int changeStateIndex_ = 0;

  union{
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
  };
};

struct SkillEvent {
  SKILL_EVENT_TYPE evnetType_ = SkillEvent_None;

  bool hasExecuted_ = false;

  SkillEvnetParams eventParams_;

  std::vector<SKILL_EVENT_CONDITION_TYPE> conditionTypes_;

  void ResetHasExecutedFlag() {
    hasExecuted_ = false;
  }
};

struct SkillFrame {
  unsigned long long startIndex_ = 0;

  unsigned long long endIndex_ = 0;

  std::vector<SkillEvent> events;
};

struct SkillState {
  unsigned long long animState_ = 0;

  std::vector<SkillFrame> frames_;
};

struct Skill {
  unsigned long long skillTag_ = 0;

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
      ProjectileComponent* pProjectileComponent);

  bool RegistSkill(Skill skill);

  void UpdateSkill();

  void ActiveSkill(unsigned long long skillTag);

  void ResetEventExcutedFlags(Skill* pSkill);

  // -------------- Skill Evnet -------------
  void ExcuteAction(SKILL_EVENT_TYPE eventType, const SkillEvnetParams& params);

  void DeActiveSkill();

  void ChangeSkillState(const SkillEvnetParams& params);

  void ExcuteJump(const SkillEvnetParams& params);

  void ExcuteDash(const SkillEvnetParams& params);

  void ExcuteDashStop(const SkillEvnetParams& params);

  void ExcuteSpawnEffect(const SkillEvnetParams& params);

  void ExcuteFireProjectile(const SkillEvnetParams& params);

  void ExcuteCommand(const SkillEvnetParams& params);

  void SetPositionOppenentPlayer(const SkillEvnetParams& params);

  void LockControlOppenentPlayer(const SkillEvnetParams& params);

  void UnLockControlOppenentPlayer(const SkillEvnetParams& params);

  void FreezeOppenentPlayer(const SkillEvnetParams& params);

  void DefreezePlayers(const SkillEvnetParams& params);

  void ExcuteCameraShake(const SkillEvnetParams& params);

  void ExcuteFadeIn(const SkillEvnetParams& params);

  void ExcuteFadeOut(const SkillEvnetParams& params);

  void ExcuteFadeInout(const SkillEvnetParams& params);

  void ExcuteSoundPlay(const SkillEvnetParams& params);

  void ExcuteSetMiscTempTrue(const SkillEvnetParams& params);

  // -------------- Skill Evnet End-------------

  // -------------- Skill Condition -------------
  bool CheckEventCondition(SKILL_EVENT_CONDITION_TYPE eventCondition) const;

  bool GetMiscTemp() const;
  // -------------- Skill Condition End-------------

 private:
  KOFPlayer* pOwnerPlayer_;

  ImageRenderer* pOwnerRenderer_;

  MovementComponent* pOwnerMovementConponent_;

  InputController* pOwnerInputController_;

  CollisionComponent* pOwnerAttackCollision_;

  ProjectileComponent* pOwnerProjectileComponent_;

  HashTable skillTable_;

  Skill* activeSkill_;

  unsigned int curSkillStateIndex_ = 0;

  bool miscTemp_;
};
