#pragma once

class ImageController
    : public UIComponent {
 public:
  ImageController();
  ~ImageController();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  bool Initialize(ToolActor* actor);

  ToolActor* GetBindActor() const;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ToolActor* bindActor_;

  Vector prevMousePosition_;
};
