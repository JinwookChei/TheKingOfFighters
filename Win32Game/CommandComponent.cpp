#include "stdafx.h"
#include "CommandComponent.h"


CommandComponent::CommandComponent()
    : pRootNode_(new CommandNode()),
      pCurNode_(pRootNode_),
      inputTimer_(0),
      inputTimeThreshold_(0),
      reservedTaskTimer_(0),
      reservedTaskTimeThreshold_(0),
      reservedTask_(nullptr),
      isMiscOn_ (false),
      miscOnTimer_ (0),
      miscOnDuration_ (0){
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

void CommandComponent::Tick(unsigned long long deltaTick) {
  inputTimer_ += deltaTick;
  if (inputTimer_ >= inputTimeThreshold_) {
    ResetNode();
  }

  if (nullptr == reservedTask_) {
    reservedTaskTimer_ = 0;
  } else {
    reservedTaskTimer_ += deltaTick;
    if (reservedTaskTimer_ >= reservedTaskTimeThreshold_) {
      reservedTask_ = nullptr;
    }
  }

  UpdateMiscOnTimer(deltaTick);
}

bool CommandComponent::isWaitingTask() const {
  if (nullptr != reservedTask_) {
    return true;
  }
  return false;
}

void CommandComponent::ExcuteTask() {
  if (nullptr != reservedTask_) {
    reservedTask_();
    reservedTask_ = nullptr;
  }
}

void CommandComponent::JumpNode(CommandKey key) {
  inputTimer_ = 0;

  if (nullptr == pCurNode_){
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

  if (nullptr != pCurNode_->Task_) {
    Actor* owner = GetOwner();
    if (nullptr == owner) {
      return;
    }

    reservedTask_ = pCurNode_->Task_;

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
