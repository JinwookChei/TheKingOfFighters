#pragma once

class ViewPortImage;

enum BoundCornerType {
  BCT_Start,
  BCT_End
};

class CollisionBoundCorner final
    : public UIComponent {
 public:
  CollisionBoundCorner();
  ~CollisionBoundCorner();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void Initialize(ViewPortImage* viewPortImage, BoundCornerType cornerType, const Color8Bit& color);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

private:
  ViewPortImage* bindViewPortImage_;

  BoundCornerType cornerType_;

  Color8Bit color_;

  Vector prevMousePosition_;

  
};