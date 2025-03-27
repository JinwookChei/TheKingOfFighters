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

  ViewPortObject* GetBindObject() const;

  void BindObject(ViewPortObject* object);

  void SetNextImageType(NextImageType nextImageType);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ViewPortObject* bindObject_;

  NextImageType nextImageType_;
};



