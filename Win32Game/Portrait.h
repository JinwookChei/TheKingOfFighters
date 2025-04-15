#pragma once

class Portrait final
    : public UIComponent {
 public:
  Portrait();
  ~Portrait();

  void BeginPlay() override;

  bool Initialize(unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent);

  void Tick(unsigned long long curTick) override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  IImage* pImage_;

  unsigned long long imageIndex_;

  Color8Bit colorTransparent_;
};
