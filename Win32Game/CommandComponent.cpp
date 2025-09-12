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
      pReservedCommand_(nullptr),
      inputTimer_(0),
      inputTimeThreshold_(0),
      reservedTaskTimer_(0),
      reservedTaskTimeThreshold_(0),
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

  if (nullptr == pReservedCommand_) {
    reservedTaskTimer_ = 0;
  } else {
    reservedTaskTimer_ += deltaTick;
    if (reservedTaskTimer_ >= reservedTaskTimeThreshold_) {
      pReservedCommand_ = nullptr;
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

// Command ���.
bool CommandComponent::RegistCommand(std::initializer_list<COMMAND_KEY> commandKeys, const Command& command) {
  if (nullptr == pRootNode_) {
    __debugbreak();
    return false;
  }

  CommandNode* pCur;
  pCur = pRootNode_;

  // commandKeys ������� Ʈ�� Ž��
  // �� Ű�� �ش��ϴ� �ڽ� ��尡 ������ �� ��带 ����
  for (auto iter = commandKeys.begin(); iter != commandKeys.end(); ++iter) {
    if (nullptr == pCur->pSubNodes[*iter]) {
      pCur->pSubNodes[*iter] = new CommandNode();
    }
    // pCur�� ���� Ű�� �ڽ� ���� �̵�
    pCur = pCur->pSubNodes[*iter];
  }

  // Command �����Ͽ� ���� ���� ����� command_���� ����.
  Command* newCommand = new Command;
  newCommand->commandTag_ = command.commandTag_;
  newCommand->actions_ = command.actions_;

  pCur->pCommand_ = newCommand;
  return true;
}

bool CommandComponent::isWaitingCommand() const {
  if (nullptr == pReservedCommand_) {
    return false;
  }
  return true;
}

void CommandComponent::ExcuteCommand() {
  if (false == isWaitingCommand()) {
    return;
  }

  for (int i = 0; i < pReservedCommand_->actions_.size(); ++i) {
    ExcuteCommandAction(pReservedCommand_->actions_[i]);
  }

  pReservedCommand_ = nullptr;
}

void CommandComponent::JumpNode(COMMAND_KEY key) {
  // JumpNode�� InputTimer �ʱ�ȭ. -> InputTimer�� �Ӱ踦 ���� �� ResetNode() ���� (�ٸ� �������� ó��)
  inputTimer_ = 0;

  // Key�� �ش��ϴ� �ڽ� ��尡 �������� ������ ResetNode()
  if (nullptr == pCurNode_->pSubNodes[key]) {
    ResetNode();        // ResetNode : pCurNode�� �ٽ� pRootNode�� �����ϰ� ��.
    return;
  } else {
    // Key�� �ش��ϴ� �ڽ� ��尡 �����ϸ� pCurNode�� �ڽ� ���� �̵�.
    pCurNode_ = pCurNode_->pSubNodes[key];
  }

  // pCurNode_�� ����Ű���ִ� ��忡�� Command�� �����ϸ� Command�� �����ϰ�, ResetNode() ����.
  if (nullptr != pCurNode_->pCommand_) {
    pReservedCommand_ = pCurNode_->pCommand_;
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

void CommandComponent::CleanUpCommands(CommandNode* pRootNode) {
  for (int i = 0; i < COMMAND_KEY::CK_MAX; ++i) {

    CommandNode* pNode = pRootNode->pSubNodes[i];

    if (nullptr == pNode) {
      continue;
    }

    CleanUpCommands(pNode);
  }

  if (nullptr != pRootNode->pCommand_) {
    delete pRootNode->pCommand_;
    pRootNode->pCommand_ = nullptr;
  }
}
