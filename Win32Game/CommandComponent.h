#pragma once
#include "KOFPlayer.h"

enum COMMAND_ACTION_TYPE : unsigned int {
  COMMAND_ACTION_ExecuteSkill = 0,
  COMMAND_ACTION_UpdateAnimState,
  COMMAND_ACTION_MovementBackStep,
  COMMAND_ACTION_TurnOnMisc,
  COMMAND_ACTION_Max
};

struct CommandActionParam {
  CommandActionParam()
      : ExecuteSkill(0) {
  }

  union {
    struct {
      unsigned long long skillTag_;
    } ExecuteSkill;

    struct {
      unsigned long long animStateTag_;
    } UpdateAnimState;

    struct {
      unsigned long long miscOnDuration_;
    } TurnOnMisc;
  };
};

struct CommandAction {
  COMMAND_ACTION_TYPE action_;

  CommandActionParam params_;
};

struct Command {
  unsigned long long commandTag_;

  std::vector<CommandAction> actions_;
};

enum COMMAND_TYPE : unsigned long long {
  COMMAND_0 = 0ULL,
  COMMAND_1,
  COMMAND_2,
  COMMAND_3,
  COMMAND_4,
  COMMAND_5,
  COMMAND_6,
  COMMAND_7,
  COMMAND_Max,
};

enum COMMAND_KEY {
  CK_None = -1,
  CK_Left = 0,
  CK_Up,
  CK_Right,
  CK_Down,
  CK_A,
  CK_B,
  CK_C,
  CK_D,
  CK_MAX
};

struct CommandNode {
  CommandNode()
      : command_(nullptr) {
    for (int i = 0; i < COMMAND_KEY::CK_MAX; ++i) {
      pSubNodes[i] = nullptr;
    }
  }

  ~CommandNode() {
    if (nullptr != pSubNodes) {
      for (int i = 0; i < COMMAND_KEY::CK_MAX; ++i) {
        delete pSubNodes[i];
        pSubNodes[i] = nullptr;
      }
    }
  }

  CommandNode* pSubNodes[COMMAND_KEY::CK_MAX];

  Command* command_;
};

class CommandComponent
    : public ActorComponent {
  friend struct CommandNode;

 public:
  CommandComponent();
  ~CommandComponent();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(KOFPlayer* pOwnerPlayer, SkillComponent* pSkillComponent, MovementComponent* pMovementComponent);

  bool RegistCommand(std::initializer_list<COMMAND_KEY> commandKeys, const Command& command);

  bool isWaitingCommand() const;

  void ExcuteCommand();

  void JumpNode(COMMAND_KEY key);

  void SetTimeOutThreshold(unsigned long long inputTimeThreshold, unsigned long long reservedTaskTimeThreshold);

  void ResetNode();

  bool IsMiscOn() const;

  void TurnOnMisc(unsigned long long miscOnDuration);

  void TurnOffMisc();

  void UpdateMiscOnTimer(unsigned long long deltaTick);

  void ExcuteCommandAction(const CommandAction& action);

  // --------------- Execute Action -----------------------------

  void ExecuteSkill(const CommandActionParam& params);

  void ExecuteUpdateAnimState(const CommandActionParam& params);

  void ExecuteBackStep(const CommandActionParam& params);

  void ExecuteTurnOnMisc(const CommandActionParam& params);

  // -----------------------------------------------------------

 private:
  void CleanUpCommands(CommandNode* rootNode);

  KOFPlayer* pOwnerPlayer_;

  SkillComponent* pOwnerSkillComponent_;

  MovementComponent* pOwnerMovementComponent_;

  CommandNode* pRootNode_;

  CommandNode* pCurNode_;

  unsigned long long inputTimer_;

  unsigned long long inputTimeThreshold_;

  unsigned long long reservedTaskTimer_;

  unsigned long long reservedTaskTimeThreshold_;

  bool isMiscOn_;

  unsigned long long miscOnTimer_;

  unsigned long long miscOnDuration_;

  Command* reservedCommand_;
};
