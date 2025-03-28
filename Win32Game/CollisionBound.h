#pragma once

enum CollisionBoundType {
  CBT_HitBoxTop,
  CBT_HitBoxBottom,
  CBT_AttackBox,
  CBT_PushBox,
  CBT_GrabBox
};

class CollisionBoundCorner;

class CollisionBound
    : public UIComponent {
 public:
  CollisionBound();
  ~CollisionBound();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void ClickExit() override;

  void Initialize(ViewPortImage* viewPortImage, CollisionBoundType boundType);


 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ViewPortImage* bindViewPortImage_;

  CollisionBoundCorner* bindCornerStart_;

  CollisionBoundCorner* bindCornerEnd_;

  CollisionBoundType boundType_;

  Color8Bit color_;

  Vector prevMousePosition_;
};