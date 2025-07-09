#pragma once

class AIBehaviorStateMachine;
class AIiori
    : public Iori {
 public:
  AIiori();
  ~AIiori();

  void Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) override;

  void Tick(unsigned long long deltaTick) override;

private:
  void Idle();

  void MoveFront();

  void MoveBack();

  void AttackPunch();

  void AttackKick();

  void ActiveShikiYamiBarai108();

 private:
  AIBehaviorStateMachine* pAIBehaviorStateMachine_;

};