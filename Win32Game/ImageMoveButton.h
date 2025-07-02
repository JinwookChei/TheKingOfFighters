#pragma once


enum ImageMoveDirType {
  IMD_None = -1,
  IMD_PlusRow,
  IMD_SuperPlusRow,
  IMD_MinusRow,
  IMD_SuperMinusRow,
  IMD_PlusCol,
  IMD_SuperPlusCol,
  IMD_MinusCol,
  IMD_SuperMinusCol,
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

  ToolActor* GetBindObject() const;

  void BindObject(ToolActor* toolActor);

  ImageMoveDirType GetImageMoveDirType() const;

  void SetImageMoveDirType(ImageMoveDirType moveDirType);

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  ToolActor* bindToolActor_;

  ImageMoveDirType imageMoveDirType_;
};