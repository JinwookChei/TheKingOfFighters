#pragma once

class WriteButton final
    : public UIComponent {
 public:
  WriteButton();
  ~WriteButton();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void ClickDownEvent() override;

  void BindObject(ToolActor* toolActor);
  
  void SetFilePath(const std::string& filePath);

  void WriteData();

protected:
  void Render(struct IRenderTexture* renderTexture) override;

 private:

  std::string filePath_;

  ToolActor* bindToolActor_;
};