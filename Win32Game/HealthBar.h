#pragma once

class Player;

class HealthBar final
    : public UIComponent {
 public:
  HealthBar();
  ~HealthBar();

  void BeginPlay() override;

  bool Initialize(unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent);

  void Tick(unsigned long long curTick) override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  IImage* pImage_;

  unsigned int imageIndex_;

  Color8Bit colorTransparent_;
};
