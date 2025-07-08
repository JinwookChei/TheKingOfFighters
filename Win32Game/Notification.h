#pragma once

class Notification
    : public UIComponent {
 public:
  Notification();
  ~Notification();

  void BeginPlay() override;

  bool Initialize(unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent);

  void Tick(unsigned long long curTick) override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  IImage* pImage_;

  Vector localeScale_;

  unsigned long long imageIndex_;

  Color8Bit colorTransparent_;


};