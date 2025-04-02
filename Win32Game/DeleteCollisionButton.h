#pragma once

class ViewPortImage;

class DeleteCollisionButton final
    : public UIComponent {
 public:
  DeleteCollisionButton();
  ~DeleteCollisionButton();

  void Initialize(ViewPortImage* bindViewPortImage, CollisionBox* bindCollisionBox, CollisionBoxType collisionBoxType);

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ViewPortImage* bindViewPortImage_;

  CollisionBox* bindCollisionBox_;

  CollisionBoxType collisionBoxType_;
};