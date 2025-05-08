#pragma once

struct HitPacket {
  float damage_ = 0.0f;
  Vector knockBackForce_ = Vector{0.0f, 0.0f};
};

class HealthComponent;
class MovementComponent;

class HitHandlerComponent final
    : public ActorComponent {
 public:
  HitHandlerComponent();
  ~HitHandlerComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  bool Initialize(HealthComponent* ownerHealthComponent, MovementComponent* pOwnerMovementComponent_);

  //HitPacket GetHitInfo() const;

  void BroadcastHitPacket(const HitPacket& hitPacket);

  private:
  //HitPacket hitPacket_;

  HealthComponent* pOwnerHealthComponent_;

  MovementComponent* pOwnerMovementComponent_;
};