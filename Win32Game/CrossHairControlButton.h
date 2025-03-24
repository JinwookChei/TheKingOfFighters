#pragma once

enum CrossHairControlType {
  CrossHairControlType_None = -1,
  CrossHairControlType_PlusRow,
  CrossHairControlType_MinusRow,
  CrossHairControlType_PlusCol,
  CrossHairControlType_MinusCol,
  CrossHairControlType_Reset,
  CrossHairControlType_MAX
};

class CrossHair;
class CrossHairControlButton final
    : public UIComponent {
 public:
  CrossHairControlButton();
  ~CrossHairControlButton();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void SetControlType(CrossHairControlType controlType);

  void SetCrossHair(CrossHair* crossHair);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:

  CrossHairControlType controlType_;

  CrossHair* crossHair_;
};