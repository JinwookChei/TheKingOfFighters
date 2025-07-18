#pragma once

class CrossHair final
    : public UIComponent {
 public:
  CrossHair();
  ~CrossHair();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void PlusRowOffSet();

  void MinusRowOffSet();

  void PlusColOffSet1();

  void MinusColOffSet1();

  void PlusColOffSet2();

  void MinusColOffSet2();

  void RowColReset();

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  float rowOffSet_;

  float colOffSet1_;
  float colOffSet2_;
};