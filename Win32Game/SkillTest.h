#pragma once

enum SkillType : unsigned long long {
  TEST = 1ULL,
};

enum SkillEventType : unsigned int {
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

enum SkillEventConditionType : unsigned int {
  SkillEventCondition_None = 0,
  SkillEventCondition_AnimationEnd,
  SkillEventCondition_CheckInputDownA,
  SkillEventCondition_CheckInputDownB,
  SkillEventCondition_CheckInputDownC,
  SkillEventCondition_CheckInputDownD,
  SkillEventCondition_HasAttackCollition,
  SkillEventCondition_MiscTempTrue,
};

struct SkillEvent {
  SkillEventType evnetType_ = SkillEvent_None;

  std::vector<int> eventParams_;

  std::vector<SkillEventConditionType> conditionTypes_;
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

  std::vector<SkillState> animStates_;

  void* searchHandle_ = nullptr;
};

class SkillTest
    : public ActorComponent {
 public:
  SkillTest();

  ~SkillTest() override;

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(KOFPlayer* pOwnerPlayer, ImageRenderer* pRenderer, MovementComponent* pMovementComponent);

  bool RegistSkill(Skill skill);

  void UpdateSkill();

  void ActiveSkill(unsigned long long skillTag);

  // -------------- Action -------------
  void ExcuteAction(SkillEventType eventType, const std::vector<int>& params);

  void DeActiveSkill();
  
  void ChangeSkillState(const std::vector<int>& params);

  void ExcuteJump(const std::vector<int>& params);
  // -------------- Action End-------------


  // -------------- Condition -------------
  bool CheckEventCondition(SkillEventConditionType eventCondition) const;

  // -------------- Condition End-------------
  

 private:
  KOFPlayer* pOwnerPlayer_;

  ImageRenderer* pOwnerRenderer_;

  MovementComponent* pOwnerMovementConponent_;

  HashTable skillTable_;

  Skill* activeSkill_;

  size_t currentAnimStateIndex_ = 0;

  bool miscTemp_;
};
