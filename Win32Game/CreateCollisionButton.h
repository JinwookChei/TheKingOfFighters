#pragma once

class ToolActor;

class CreateCollisionButton final
    : public UIComponent {
 public:
  CreateCollisionButton();
  ~CreateCollisionButton();

  void Initialize(ToolActor* bindActor, CollisionBox* bindCollisionBox, CollisionBoxType collisionBoxType);

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ToolActor* bindToolActor_;

  CollisionBox* bindCollisionBox_;

  CollisionBoxType collisionBoxType_;
};