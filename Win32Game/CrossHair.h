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

  void PlusColOffSet();

  void MinusColOffSet();

  void RowColReset();

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  float rowOffSet;

  float colOffSet;
};