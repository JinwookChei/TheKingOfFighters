#pragma once

class AIBehaviorStateMachine;
class AIiori
    : public Iori {
 public:
  AIiori();
  ~AIiori();

  void Initialize(bool isPlayer1, const Vector& position, bool useCameraPosition, KOFPlayer* opponentPlayer) override;

  void Tick(unsigned long long deltaTick) override;

  void UpdateInput() override;

 private:
  AIBehaviorStateMachine* pAIBehaviorStateMachine_;

};