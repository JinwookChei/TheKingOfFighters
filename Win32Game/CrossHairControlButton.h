#pragma once

enum CrossHairControlType {
  CrossHairControlType_None = -1,
  CrossHairControlType_PlusRow,
  CrossHairControlType_SuperPlusRow,
  CrossHairControlType_MinusRow,
  CrossHairControlType_SuperMinusRow,
  CrossHairControlType_PlusCol1,
  CrossHairControlType_SuperPlusCol1,
  CrossHairControlType_MinusCol1,
  CrossHairControlType_SuperMinusCol1,
  CrossHairControlType_PlusCol2,
  CrossHairControlType_SuperPlusCol2,
  CrossHairControlType_MinusCol2,
  CrossHairControlType_SuperMinusCol2,
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