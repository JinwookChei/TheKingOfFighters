#pragma once

class ReadButton final
    : public UIComponent {
 public:
  ReadButton();
  ~ReadButton();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void BindObject(ViewPortImage* object);

  void SetFilePath(const std::string& filePath);

  void ReadData();

 protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:
  std::string filePath_;

  ViewPortImage* bindObject_;
};