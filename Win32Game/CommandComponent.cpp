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
  for (int i = 0; i < CommandKey::CK_MAX; ++i) {
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

bool CommandComponent::RegistCommand(std::initializer_list<CommandKey> commandKeys, Command command) {
  if (nullptr == pRootNode_) {
    return false;
  }

  CommandNode* pCur;
  pCur = pRootNode_;

  for (auto iter = commandKeys.begin(); iter != commandKeys.end(); ++iter) {
    if (nullptr == pCur->pSubNodes[*iter]) {
      pCur->pSubNodes[*iter] = new CommandNode();
    }
    pCur = pCur->pSubNodes[*iter];
  }

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

void CommandComponent::JumpNode(CommandKey key) {
  inputTimer_ = 0;

  if (nullptr == pCurNode_) {
    return;
  }

  if (nullptr == pCurNode_->pSubNodes[key]) {
    pCurNode_ = nullptr;
    return;
  } else {
    pCurNode_ = pCurNode_->pSubNodes[key];
  }

  if (nullptr == pCurNode_) {
    return;
  }

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
  for (int i = 0; i < CommandKey::CK_MAX; ++i) {

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
