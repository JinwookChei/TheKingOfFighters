#pragma once

class ViewPortObject final
    : public UIComponent {
 public:
  ViewPortObject();
  ~ViewPortObject();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  IImage* GetImage() const;

  void ChangeImage();

  unsigned int GetImageIndex() const;

  void SetImageIndex(unsigned int index);

  void AddPositionOffSet(const Vector& offSet);

  void ResetPostionOffset();

  Vector GetPositionOffSet() const;

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  UI* owner_;

  IImage* image_;

  unsigned int imageIndex_;

  Vector localeScale_;

  Color8Bit TransColor_;
};
