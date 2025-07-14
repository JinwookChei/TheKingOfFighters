#pragma once

class KOFPlayer;
class SkillPoint : public UIComponent {
 public:
  SkillPoint();
  ~SkillPoint();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  bool Initialize(KOFPlayer* bindPlayer, int skillPointIndex, unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  KOFPlayer* pPlayer_;

  int skillPointIndex_;

  bool onRender_;

  IImage* pImage_;

  Vector localeScale_;

  unsigned long long imageIndex_;

  Color8Bit colorTransparent_;
};
