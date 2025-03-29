#pragma once

class ViewPortImage;

class CreateCollisionButton final
    : public UIComponent
{
 public:
  CreateCollisionButton();
  ~CreateCollisionButton();

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