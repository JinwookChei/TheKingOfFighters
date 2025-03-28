#pragma once

class ViewPortImage;

enum CollisionBoundCornerType {
  CBCT_Start,
  CBCT_End
};

class CollisionBoundCorner final
    : public UIComponent {
 public:
  CollisionBoundCorner();
  ~CollisionBoundCorner();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void Initialize(ViewPortImage* viewPortImage, CollisionBoundType boundType,CollisionBoundCornerType cornerType, const Color8Bit& color);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

private:
  ViewPortImage* bindViewPortImage_;

  CollisionBoundType boundType_;

  CollisionBoundCornerType cornerType_;

  Color8Bit color_;

  Vector prevMousePosition_;

  
};