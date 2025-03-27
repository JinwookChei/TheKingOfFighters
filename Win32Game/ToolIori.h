#pragma once

class ToolIori
    : public Actor {
 public:
  ToolIori();

  ~ToolIori();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  bool Initialize(Color8Bit TransparentColor, unsigned int imagePtrIndex, unsigned int imageIndex = 0);

  unsigned int GetImagePtrIndex() const;

  void SetImagePtrIndex(unsigned int ptrIndex);

  unsigned int GetImageIndex() const;

  void SetImageIndex(unsigned int index);


 private:
  ImageRenderer* pRender_;

  unsigned int imagePtrIndex_;

  unsigned int imageIndex_;

};