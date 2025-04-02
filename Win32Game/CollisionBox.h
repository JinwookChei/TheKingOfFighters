#pragma once

enum CollisionBoxType {
  CBT_HitBoxTop,
  CBT_HitBoxBottom,
  CBT_AttackBox,
  CBT_PushBox,
  CBT_GrabBox,
  CBT_Max
};

class CollisionBoxCorner;
class ViewPortImage;

class CollisionBox
    : public UIComponent {
 public:
  CollisionBox();
  ~CollisionBox();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void ClickExit() override;

  void Initialize(ViewPortImage* viewPortImage, CollisionBoxType collisionBoxType);

  CollisionBoxCorner* GetCornerStart();

  CollisionBoxCorner* GetCornerEnd();


 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ViewPortImage* bindViewPortImage_;

  CollisionBoxCorner* bindCornerStart_;

  CollisionBoxCorner* bindCornerEnd_;

  CollisionBoxType collisionBoxType_;

  Color8Bit color_;

  Vector prevMousePosition_;
};