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

class CommandComponent
    : public ActorComponent {
  friend struct CommandNode;

 public:
  CommandComponent();
  ~CommandComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  template<typename T>
  bool RegistCommand(std::initializer_list<CommandKey> command, void (T::* funcPtr)(), T* owner) {
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
    
      pCur->Task_ = std::bind(funcPtr, owner);
    
      return true;
  }

  
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
