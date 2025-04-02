#pragma once

class ToolActor;
class ImageController;

enum CollisionBoxCornerType {
  CBCT_Start,
  CBCT_End
};

class CollisionBoxCorner final
    : public UIComponent {
 public:
  CollisionBoxCorner();
  ~CollisionBoxCorner();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void Initialize(ToolActor* bindActor, ImageController* imageController, CollisionBoxType collisionBoxType, CollisionBoxCornerType cornerType, const Color8Bit& color);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

private:
  void MoveWithDrag();

private:
  ToolActor* bindToolActor_;

  ImageController* bindImageController_;

  CollisionBoxType collisionBoxType_;

  CollisionBoxCornerType cornerType_;

  Color8Bit color_;

  Vector prevMousePosition_;

  
};