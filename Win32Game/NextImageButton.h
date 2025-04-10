#pragma once

enum NextImageType {
  NextImage_Next,
  NextImage_Prev,
  NextImage_SuperNext,
  NextImage_SuperPrev
};

class NextImageButton final
    : public UIComponent {
 public:
  NextImageButton();
  ~NextImageButton();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  ToolActor* GetBindObject() const;

  void BindObject(ToolActor* toolActor);

  void SetNextImageType(NextImageType nextImageType);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ToolActor* bindToolActor_;

  NextImageType nextImageType_;
};



