#pragma once


enum ImageMoveDirType {
  IMD_None = -1,
  IMD_PlusRow,
  IMD_MinusRow,
  IMD_PlusCol,
  IMD_MinusCol,
  IMD_Reset,
  IMD_MAX
};

class ImageMoveButton final
    : public UIComponent {
 public:
  ImageMoveButton();
  ~ImageMoveButton();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  ViewPortImage* GetBindObject() const;

  void BindObject(ViewPortImage* object);

  ImageMoveDirType GetImageMoveDirType() const;

  void SetImageMoveDirType(ImageMoveDirType moveDirType);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ViewPortImage* bindObject_;

  ImageMoveDirType imageMoveDirType_;
};