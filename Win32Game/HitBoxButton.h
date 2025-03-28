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

  void BindViewPortImage(ViewPortImage* viewPortImage);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;  


private:
  ViewPortImage* bindViewPortImage_;

  Vector prevMousePosition_;


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

  void BindViewPortImage(ViewPortImage* viewPortImage);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  UI* bindUI_;

  ViewPortImage* bindViewPortImage_;

  
};