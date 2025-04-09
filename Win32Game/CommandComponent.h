#pragma once
#include <initializer_list>

// inline void

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
      :  // key_(CommendKey::CK_None),
        task_(0) {
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

  // void (*Task)();
  int task_;
};

class CommandComponent
    : public ActorComponent {
  friend struct CommandNode;

 public:
  CommandComponent();
  ~CommandComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  bool RegistCommend(std::initializer_list<CommandKey> command, int task);

  int GetTask() const;

  void JumpNode(CommandKey key);

  void SetTimeOutThreshold(unsigned long long threshold);

  void ResetNode();

 private:
  CommandNode* const pRootNode_;

  CommandNode* pCurNode_;

  unsigned long long timeOut_;

  unsigned long long timeOutThreshold_;
};
