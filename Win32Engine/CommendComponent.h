#pragma once
#include "ActorComponent.h"
#include <initializer_list>

// inline void

enum CommendKey {
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

struct CommendNode {
  CommendNode()
      : //key_(CommendKey::CK_None),
        task_(0){
    for (int i = 0; i < CommendKey::CK_MAX; ++i) {
      pSubNodes[i] = nullptr;
    }
  }

  ~CommendNode() {
    if (nullptr != pSubNodes) {
      for (int i = 0; i < CommendKey::CK_MAX; ++i) {
        delete pSubNodes[i];
      }
    }
  }

  CommendNode* pSubNodes[CommendKey::CK_MAX];

  //void (*Task)();
  int task_;
  
};

class CommendComponent
    : public ActorComponent {
  friend struct CommendNode;

 public:
  JO_API CommendComponent();
  JO_API ~CommendComponent();

  JO_API void BeginPlay() override;

  JO_API void Tick(unsigned long long curTick) override;

  JO_API bool RegistCommend(std::initializer_list<CommendKey> commend, int task);

  JO_API int GetTask() const;

  JO_API void JumpNode(CommendKey key);

  JO_API void SetTimeOutThreshold(unsigned long long threshold);

  JO_API void ResetNode();

 private:
  CommendNode* const pRootNode_;

  CommendNode* pCurNode_;

  unsigned long long timeOut_;

  unsigned long long timeOutThreshold_;
};
