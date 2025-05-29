#include "stdafx.h"
#include "CommandComponent.h"
#include <functional>

CommandComponent::CommandComponent()
    : pRootNode_(new CommandNode()),
      pCurNode_(pRootNode_),
      inputTimeout_(0),
      inputTimeThreshold_(0),
      waitingTaskTimeout_(0),
      waitingTaskTimeThreshold_(0),
      waitingTask_(nullptr) {
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
  inputTimeout_ += curTick;
  if (inputTimeout_ > inputTimeThreshold_) {
    ResetNode();
  }

  if (nullptr == waitingTask_) {
    waitingTaskTimeout_ = 0;
  } else {
    waitingTaskTimeout_ += curTick;
    if (waitingTaskTimeout_ > waitingTaskTimeThreshold_) {
      waitingTask_ = nullptr;
    }
  }
}

bool CommandComponent::RegistCommend(std::initializer_list<CommandKey> command, std::function<void()> func) {
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

  pCur->Task_ = func;

  return true;
}

bool CommandComponent::isWaitingTask() const {
  if (nullptr != waitingTask_) {
    return true;
  }
  return false;
}

void CommandComponent::ExcuteTask() {
  if (nullptr != waitingTask_) {
    waitingTask_();
    waitingTask_ = nullptr;
  }
}

void CommandComponent::JumpNode(CommandKey key) {
  inputTimeout_ = 0;

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

    waitingTask_ = pCurNode_->Task_;

    ResetNode();
  }
}

void CommandComponent::SetTimeOutThreshold(unsigned long long threshold, unsigned long long waitingTaskTimeThreshold) {
  inputTimeThreshold_ = threshold;
  waitingTaskTimeThreshold_ = waitingTaskTimeThreshold;
}

void CommandComponent::ResetNode() {
  if (nullptr == pRootNode_) {
    return;
  }

  pCurNode_ = pRootNode_;
  inputTimeout_ = 0;
}
