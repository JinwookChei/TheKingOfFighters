#include "stdafx.h"
#include "KOFPlayer.h"
#include "SkillComponent.h"
#include "MovementComponent.h"
#include "CommandComponent.h"

CommandComponent::CommandComponent()
    : pOwnerPlayer_(nullptr),
      pOwnerSkillComponent_(nullptr),
      pOwnerMovementComponent_(nullptr),
      pRootNode_(new CommandNode()),
      pCurNode_(pRootNode_),
      inputTimer_(0),
      inputTimeThreshold_(0),
      reservedTaskTimer_(0),
      reservedTaskTimeThreshold_(0),
      reservedCommand_(nullptr),
      isMiscOn_(false),
      miscOnTimer_(0),
      miscOnDuration_(0) {
  for (int i = 0; i < COMMAND_KEY::CK_MAX; ++i) {
    pRootNode_->pSubNodes[i] = new CommandNode();
  }
}

CommandComponent::~CommandComponent() {
  CleanUpCommands(pRootNode_);

  if (nullptr != pRootNode_) {
    delete pRootNode_;
    pRootNode_ = nullptr;
  }
}

void CommandComponent::BeginPlay() {
}

void CommandComponent::Tick(unsigned long long deltaTick) {
  inputTimer_ += deltaTick;
  if (inputTimer_ >= inputTimeThreshold_) {
    ResetNode();
  }

  if (nullptr == reservedCommand_) {
    reservedTaskTimer_ = 0;
  } else {
    reservedTaskTimer_ += deltaTick;
    if (reservedTaskTimer_ >= reservedTaskTimeThreshold_) {
      reservedCommand_ = nullptr;
    }
  }

  UpdateMiscOnTimer(deltaTick);
}

bool CommandComponent::Initialize(KOFPlayer* pOwnerPlayer, SkillComponent* pSkillComponent, MovementComponent* pMovementComponent) {
  if (nullptr == pOwnerPlayer) {
    return false;
  }
  if (nullptr == pSkillComponent) {
    return false;
  }
  if (nullptr == pMovementComponent) {
    return false;
  }

  pOwnerPlayer_ = pOwnerPlayer;
  pOwnerSkillComponent_ = pSkillComponent;
  pOwnerMovementComponent_ = pMovementComponent;

  return true;
}

// Command 등록.
bool CommandComponent::RegistCommand(std::initializer_list<COMMAND_KEY> commandKeys, const Command& command) {
  if (nullptr == pRootNode_) {
    __debugbreak();
    return false;
  }

  CommandNode* pCur;
  pCur = pRootNode_;

  // commandKeys 순서대로 트리 탐색
  // 각 키에 해당하는 자식 노드가 없으면 새 노드를 생성
  for (auto iter = commandKeys.begin(); iter != commandKeys.end(); ++iter) {
    if (nullptr == pCur->pSubNodes[*iter]) {
      pCur->pSubNodes[*iter] = new CommandNode();
    }
    // pCur를 다음 키의 자식 노드로 이동
    pCur = pCur->pSubNodes[*iter];
  }

  // Command 생성하여 최종 말단 노드의 command_에서 참조.
  Command* newCommand = new Command;
  newCommand->commandTag_ = command.commandTag_;
  newCommand->actions_ = command.actions_;

  pCur->command_ = newCommand;
  return true;
}

bool CommandComponent::isWaitingCommand() const {
  if (nullptr == reservedCommand_) {
    return false;
  }
  return true;
}

void CommandComponent::ExcuteCommand() {
  if (false == isWaitingCommand()) {
    return;
  }

  for (int i = 0; i < reservedCommand_->actions_.size(); ++i) {
    ExcuteCommandAction(reservedCommand_->actions_[i]);
  }

  reservedCommand_ = nullptr;
}

void CommandComponent::JumpNode(COMMAND_KEY key) {
  // JumpNode시 InputTimer 초기화. -> InputTimer가 임계를 넘을 시 ResetNode() 실행 (다른 로직에서 처리)
  inputTimer_ = 0;

  // Key에 해당하는 자식 노드가 존재하지 않으면 ResetNode()
  if (nullptr == pCurNode_->pSubNodes[key]) {
    ResetNode();        // ResetNode : pCurNode가 다시 pRootNode를 참조하게 됨.
    return;
  } else {
    // Key에 해당하는 자식 노드가 존재하면 pCurNode를 자식 노드로 이동.
    pCurNode_ = pCurNode_->pSubNodes[key];
  }

  // pCurNode_가 가르키고있는 노드에서 Command가 존재하면 Command를 예약하고, ResetNode() 실행.
  if (nullptr != pCurNode_->command_) {
    reservedCommand_ = pCurNode_->command_;
    ResetNode();
  }
}

void CommandComponent::SetTimeOutThreshold(unsigned long long threshold, unsigned long long reservedTaskTimeThreshold) {
  inputTimeThreshold_ = threshold;
  reservedTaskTimeThreshold_ = reservedTaskTimeThreshold;
}

void CommandComponent::ResetNode() {
  if (nullptr == pRootNode_) {
    return;
  }

  pCurNode_ = pRootNode_;
  inputTimer_ = 0;
}

bool CommandComponent::IsMiscOn() const {
  return isMiscOn_;
}

void CommandComponent::TurnOnMisc(unsigned long long miscOnDuration) {
  isMiscOn_ = true;
  miscOnTimer_ = 0;
  miscOnDuration_ = miscOnDuration;
}

void CommandComponent::TurnOffMisc() {
  isMiscOn_ = false;
}

void CommandComponent::UpdateMiscOnTimer(unsigned long long deltaTick) {
  if (true == IsMiscOn()) {
    miscOnTimer_ += deltaTick;
    if (miscOnTimer_ >= miscOnDuration_) {
      TurnOffMisc();
    }
  }
}

void CommandComponent::ExcuteCommandAction(const CommandAction& action) {
  switch (action.action_) {
    case COMMAND_ACTION_TYPE::COMMAND_ACTION_ExecuteSkill:
      ExecuteSkill(action.params_);
      break;
    case COMMAND_ACTION_TYPE::COMMAND_ACTION_UpdateAnimState:
      ExecuteUpdateAnimState(action.params_);
      break;
    case COMMAND_ACTION_TYPE::COMMAND_ACTION_MovementBackStep:
      ExecuteBackStep(action.params_);
      break;
    case COMMAND_ACTION_TYPE::COMMAND_ACTION_TurnOnMisc:
      ExecuteTurnOnMisc(action.params_);
      break;
    default:
      break;
  }
}

void CommandComponent::ExecuteSkill(const CommandActionParam& params) {
  if (nullptr == pOwnerSkillComponent_) {
    return;
  }
  unsigned long long skillTag = params.ExecuteSkill.skillTag_;

  pOwnerSkillComponent_->ExecuteSkill(skillTag);
}

void CommandComponent::ExecuteUpdateAnimState(const CommandActionParam& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }

  unsigned long long animStateTag = params.UpdateAnimState.animStateTag_;

  pOwnerPlayer_->UpdateAnimState(animStateTag);
}

void CommandComponent::ExecuteBackStep(const CommandActionParam& params) {
  if (nullptr == pOwnerPlayer_) {
    return;
  }
  if (nullptr == pOwnerMovementComponent_) {
    return;
  }
  bool facingRight = pOwnerPlayer_->FacingRight();

  pOwnerMovementComponent_->BackStep(facingRight);
}

void CommandComponent::ExecuteTurnOnMisc(const CommandActionParam& params) {
  unsigned long long miscOnDuration = params.TurnOnMisc.miscOnDuration_;
  TurnOnMisc(miscOnDuration);
}

void CommandComponent::CleanUpCommands(CommandNode* rootNode) {
  for (int i = 0; i < COMMAND_KEY::CK_MAX; ++i) {

    CommandNode* pNode = rootNode->pSubNodes[i];

    if (nullptr == pNode) {
      continue;
    }

    CleanUpCommands(pNode);
  }

  if (nullptr != rootNode->command_) {
    delete rootNode->command_;
    rootNode->command_ = nullptr;
  }
}
