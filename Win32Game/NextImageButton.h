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

  Object* GetBindObject() const;

  void BindObject(Object* object);

  void SetNextImageType(NextImageType nextImageType);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  Object* bindObject_;

  NextImageType nextImageType_;
};



