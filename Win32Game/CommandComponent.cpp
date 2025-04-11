#include "stdafx.h"
#include "CommandComponent.h"

CommandComponent::CommandComponent()
    : pRootNode_(new CommandNode()),
      pCurNode_(pRootNode_),
      timeOut_(0),
      timeOutThreshold_(0) {
  for (int i = 0; i < CommandKey::CK_MAX; ++i) {
    pRootNode_->pSubNodes[i] = new CommandNode();
  }
}

CommandComponent::~CommandComponent() {
  if (nullptr != pRootNode_) {
    delete pRootNode_;
  }
}

void CommandComponent::BeginPlay() {
}

void CommandComponent::Tick(unsigned long long curTick) {
  timeOut_ += curTick;
  if (timeOut_ > timeOutThreshold_) {
    ResetNode();
  }
}

bool CommandComponent::RegistCommend(std::initializer_list<CommandKey> command, void (Player::*Task)()) {
  if (nullptr == pRootNode_) {
    return false;
  }

  CommandNode* pCur;
  pCur = pRootNode_;

  for (auto iter = command.begin(); iter != command.end(); ++iter) {
    if (nullptr == pCur->pSubNodes[*iter]) {
      pCur->pSubNodes[*iter] = new CommandNode();
    }
    pCur = pCur->pSubNodes[*iter];
  }

  pCur->Task_ = Task;

  return true;
}

void* CommandComponent::GetTask() const {
  if (nullptr == pCurNode_) {
    return 0;
  }

  return &pCurNode_->Task_;
}

void CommandComponent::JumpNode(CommandKey key) {
  timeOut_ = 0;

  if (nullptr == pCurNode_->pSubNodes[key]) {
    pCurNode_ = pRootNode_->pSubNodes[key];
    return;
  } else {
    pCurNode_ = pCurNode_->pSubNodes[key];
  }

  if (nullptr == pCurNode_) {
    return;
  }

  if (nullptr != pCurNode_->Task_) {
    Actor* owner = GetOwner();
    if (nullptr == owner) {
      return;
    }

    pCurNode_->ExcuteTask((Player*)owner);
    ResetNode();
  }
}

void CommandComponent::SetTimeOutThreshold(unsigned long long threshold) {
  timeOutThreshold_ = threshold;
}

void CommandComponent::ResetNode() {
  if (nullptr == pRootNode_) {
    return;
  }

  pCurNode_ = pRootNode_;
  timeOut_ = 0;
}
