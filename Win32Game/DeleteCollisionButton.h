#pragma once

class ViewPortImage;

class DeleteCollisionButton final
    : public UIComponent {
 public:
  DeleteCollisionButton();
  ~DeleteCollisionButton();

  void Initialize(ViewPortImage* bindViewPortImage, CollisionBoundType boundType);

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ViewPortImage* bindViewPortImage_;

  CollisionBoundType boundType_;
};