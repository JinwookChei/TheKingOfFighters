#pragma once

class Player;

class HealthBar final
    : public UIComponent {
 public:
  HealthBar();
  ~HealthBar();

  void BeginPlay() override;

  bool Initialize(Player* bindPlayer);

  void Tick(unsigned long long curTick) override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  
};
