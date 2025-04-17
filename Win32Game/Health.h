#pragma once

class Player;

class Health final
    : public UIComponent {
 public:
  Health();
  ~Health();

  void BeginPlay() override;

  bool Initialize(Player* bindPlayer, unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent, const Vector& position, bool isFlip);

  void Tick(unsigned long long curTick) override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  Player* pPlayer_;

  IImage* pImage_;

  bool isFlip_;

  unsigned int imageIndex_;

  Color8Bit colorTransparent_;

  Transform originComponentTransform_;

  Transform originImageTransform_;

  float healthPercentage_;
};
