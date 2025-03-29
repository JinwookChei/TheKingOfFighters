#pragma once

enum NextImageType {
  NextImage_Next,
  NextImage_Prev
};

class NextImageButton final
    : public UIComponent {
 public:
  NextImageButton();
  ~NextImageButton();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  ViewPortImage* GetBindObject() const;

  void BindObject(ViewPortImage* object);

  void SetNextImageType(NextImageType nextImageType);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ViewPortImage* bindObject_;

  NextImageType nextImageType_;
};



