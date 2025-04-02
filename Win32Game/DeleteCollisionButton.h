#pragma once

class ToolActor;

class DeleteCollisionButton final
    : public UIComponent {
 public:
  DeleteCollisionButton();
  ~DeleteCollisionButton();

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