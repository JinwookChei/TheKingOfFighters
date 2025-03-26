#pragma once


class ResizeCornerComponent
    : public UIComponent {
 public:
  ResizeCornerComponent();
  ~ResizeCornerComponent();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void ClickExit() override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;
};


class HitBoxButton final
    : public UIComponent {
 public:
  HitBoxButton();
  ~HitBoxButton();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void ClickExit() override;

  void BindUI(UI* ui);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  UI* bindUI_;
};