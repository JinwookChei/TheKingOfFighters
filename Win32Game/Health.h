#pragma once

class Player;

class Health final
    : public UIComponent {
 public:
  Health();
  ~Health();

  void BeginPlay() override;

  bool Initialize(Player* bindPlayer);

  void Tick(unsigned long long curTick) override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
};
