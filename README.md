# King of Fighters 2003 (모작)

상용 엔진 없이 C/C++와 Win32 API로 간단한 2D 게임 프레임워크를 제작하고, 그 위에서 동작하는 King of Fighters 2003을 모작한 개인 프로젝트입니다.

![main](./docs/images/main.png)

- **Tech Stack** : C/C++, Win32 API
- **Team Size** : 개인 프로젝트
- **Dev Period** : 2025.03 ~ 2025.08
- **Demo** : [결과 영상](https://youtu.be/rZeRdkoJKsQ?si=B5Ez7J7bEngthRr9)

<br>

## 주요 구현 내용

1. [Atlas Animation](#1-atlas-animation)
2. [Animation FSM](#2-animation-fsm)
3. [Collision](#3-collision)
4. [Command](#4-command)

<br>

## 1. Atlas Animation

스프라이트 아틀라스를 사용해 애니메이션을 구현했습니다.
단일 텍스처에서 UV 좌표를 계산하고, 원하는 이미지 인덱스로 전환하는 방식입니다.

![atlas](./docs/images/atlas.png)

### UV 좌표 계산

**문제**
리소스 사이트에서 받은 Atlas 이미지의 상하좌우 Padding이 일정하지 않아, 각 프레임의 UV 값을 개별로 계산해야 했습니다.

**해결**
보조선을 그리고, 보조선 내부 범위에서 BoundBox UV 좌표를 얻었습니다.

![uv](./docs/images/uv.png)

### 애니메이션 중심점(Pivot) 보정

**문제**
BoundBox UV 좌표로 애니메이션을 재생하면 프레임마다 Pivot이 바뀌어 발이 미끄러지는 현상이 있었습니다.

**해결**
Animation Pivot Offset을 조정하는 툴을 제작했습니다.
조정한 Offset 값은 CSV로 저장되고, 게임 시작 시 불러옵니다.

![pivot](./docs/images/pivot.png)

- [Pivot Offset 툴 영상](https://youtube.com/shorts/CDv2IbMH8_U?si=uwe0s13LtzgfGdS4)

<br>

## 2. Animation FSM

**문제**
점프 동작을 단일 애니메이션으로 구현해, 실제 움직임과 애니메이션 상태가 일치하지 않았습니다.
(점프 중 상승과 착지가 구분되지 않음)

**해결**
FSM(Finite State Machine)을 구현해 점프를 `JumpUp` → `JumpDown` → `JumpLand`로 나누었습니다.

![fsm](./docs/images/fsm.png)

### 구조

- `AnimStateTransMachine` 컴포넌트가 HashTable로 `AnimTransState`를 관리합니다.
- 현재 AnimState를 Key로 `AnimTransState`를 찾고, 그 안의 `AnimTransRule`의 전이 조건을 검사합니다.
- 조건을 만족하면 애니메이션 상태 전이가 발생합니다.
- 전이 조건은 비트마스크로 관리합니다.

```cpp
enum E_ANIM_TRANS_COND {
    None                          = 0,
    AnimationEnd                  = 1 << 0,
    MovementRising                = 1 << 1,
    MovementFalling               = 1 << 2,
    MovementOnGround              = 1 << 3,
    OpponentPlayerAttackFinished  = 1 << 4,
};

struct AnimTransRule {
    unsigned int transCondition_ = ANIM_TRANS_COND::None;
    unsigned long long toAnimState_ = 0;
};

struct AnimTransState {
    unsigned long long fromAnimState_ = 0;
    std::vector<AnimTransRule> animTransRules_;
    void* searchHandle_ = nullptr;
};
```

### 사용 예시

```cpp
AnimTransRule animTransRule_JumpUp;
animTransRule_JumpUp.transCondition_ = ANIM_TRANS_COND::MovementFalling;
animTransRule_JumpUp.toAnimState_ = PLAYER_ANIMTYPE_JumpDown;

AnimTransState animState_JumpUp;
animState_JumpUp.fromAnimState_ = PLAYER_ANIMTYPE_JumpUp;
animState_JumpUp.animTransRules_.push_back(animTransRule_JumpUp);

pAnimStateTransMachine_->RegistAnimTransition(animState_JumpUp);
```

<br>

## 3. Collision

### AABB 충돌

플레이어 간 충돌 처리를 위해 AABB(사각형) 충돌을 구현했습니다.

```cpp
static bool CollisionRectToRect(const CollisionInfo& left, const CollisionInfo& right) {
    if (left.Bottom() < right.Top())   return false;
    if (left.Top()    > right.Bottom()) return false;
    if (left.Left()   > right.Right())  return false;
    if (left.Right()  < right.Left())   return false;
    return true;
}
```

### 충돌 에디터 툴

애니메이션마다 충돌 범위를 지정하기 위해 충돌 에디터 툴을 제작했습니다.

![collision](./docs/images/collision.png)

<br>

## 4. Command

King of Fighters 2003은 지정된 커맨드를 입력하면 스킬이 나가는 커맨드 입력 시스템이 있습니다.
커맨드 검색을 위해 Tree 구조로 커맨드 기능을 구현했습니다.

![command](./docs/images/command_tree.png)

### 동작 방식

- `RegistCommand` : 키 입력 순서대로 트리를 탐색하고, 노드가 없으면 새로 생성한 뒤 마지막 노드에 Command를 연결합니다.
- `JumpNode` : 입력된 키에 해당하는 자식 노드로 이동합니다. 자식 노드가 없으면 루트로 돌아갑니다.
- 이동한 노드에 Command가 있으면 해당 Command를 예약하고 루트로 돌아갑니다.
- 입력 간격이 임계값을 넘으면 루트로 초기화됩니다.

```cpp
struct CommandNode {
    CommandNode* pSubNodes[COMMAND_KEY::CK_MAX];
    Command* pCommand_;
};
```

### 사용 예시

```cpp
CommandAction CM2_Action0;
CM2_Action0.action_ = COMMAND_ACTION_ExecuteSkill;
CM2_Action0.params_.ExecuteSkill.skillTag_ = SKILL_1;

Command command2;
command2.commandTag_ = COMMAND_2;
command2.actions_.push_back(CM2_Action0);

pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_A}, command2);
pCommandComponent_->RegistCommand({CK_Left, CK_Down, CK_Right, CK_B}, command2);
```
