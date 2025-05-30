#pragma once
#include <initializer_list>
#include "KOFPlayer.h"
#include <functional>

enum CommandKey {
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
      : Task_(nullptr) {
    for (int i = 0; i < CommandKey::CK_MAX; ++i) {
      pSubNodes[i] = nullptr;
    }
  }

  ~CommandNode() {
    if (nullptr != pSubNodes) {
      for (int i = 0; i < CommandKey::CK_MAX; ++i) {
        delete pSubNodes[i];
      }
    }
  }

  CommandNode* pSubNodes[CommandKey::CK_MAX];

  std::function<void()> Task_;
};

// TODO : 커맨드 버퍼 시스템을 만들어야함.
class CommandComponent
    : public ActorComponent {
  friend struct CommandNode;

 public:
  CommandComponent();
  ~CommandComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  bool RegistCommend(std::initializer_list<CommandKey> command, std::function<void()> func);

  bool isWaitingTask() const;

  void ExcuteTask();

  void JumpNode(CommandKey key);

  void SetTimeOutThreshold(unsigned long long inputTimeThreshold, unsigned long long reservedTaskTimeThreshold);

  void ResetNode();

 private:
  CommandNode* const pRootNode_;

  CommandNode* pCurNode_;

  unsigned long long inputTimeout_;

  unsigned long long inputTimeThreshold_;

  unsigned long long reservedTaskTimeout_;

  unsigned long long reservedTaskTimeThreshold_;

  std::function<void()> reservedTask_;
};
