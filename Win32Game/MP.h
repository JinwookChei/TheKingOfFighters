#pragma once
class KOFPlayer;

class MP final
    : public UIComponent {
 public:
  MP();
  ~MP();
  
  void BeginPlay() override;

  bool Initialize(KOFPlayer* bindPlayer, unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent, const Vector& position, bool isFlip);

  void Tick(unsigned long long curTick) override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  KOFPlayer* pPlayer_;

  IImage* pImage_;

  bool isFlip_;

  unsigned int imageIndex_;

  Color8Bit colorTransparent_;

  Transform originComponentTransform_;

  Transform originRenderTransform_;

  Transform componentTransform_;

  Transform renderTransform_;

  float healthPercentage_;
};
