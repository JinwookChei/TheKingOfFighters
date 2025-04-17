#pragma once

class Player;

class Health final
    : public UIComponent {
 public:
  Health();
  ~Health();

  void BeginPlay() override;

  bool Initialize(Player* bindPlayer, unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent);

  void Tick(unsigned long long curTick) override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  Player* pPlayer_;

  IImage* pImage_;

  unsigned int imageIndex_;

  Color8Bit colorTransparent_;
};
