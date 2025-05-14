#pragma once

struct GhostInfo {
  GhostInfo()
      : image_(nullptr),
        imageIndex_(0),
        worldPosition_({0.0f, 0.0f}) {
  }

  ~GhostInfo() {
  }

  IImage* image_;

  int imageIndex_;

  Vector worldPosition_;
};

class GhostBuffer {
 public:
  GhostBuffer()
      : pBuffer_(nullptr),
        size_(0),
        front_(0),
        rear_(-1) {
  }

  ~GhostBuffer() {
    if (nullptr != pBuffer_) {
      delete[] pBuffer_;
      pBuffer_ = nullptr;
    }
  }

  bool Initialize(int bufferSize) {
    size_ = bufferSize;
    pBuffer_ = new GhostInfo[size_];

    if (size_ < 0 || nullptr == pBuffer_) {
      return false;
    }
    return true;
  }

  void Update(const GhostInfo& info) {
    if (-1 == rear_) {
      rear_ = (rear_ + 1) % size_;
      pBuffer_[rear_] = info;
      return;
    }

    rear_ = (rear_ + 1) % size_;
    if (rear_ == front_) {
      front_ = (front_ + 1) % size_;
    }

    pBuffer_[rear_] = info;
  }

  bool Get(int index, GhostInfo** outInfo) {
    if (index < 0 || index >= size_) {
      return false;
    }

    int finalIndex = (front_ + index) % size_;

    *outInfo = &pBuffer_[finalIndex];

    return true;
  }



 private:
  GhostInfo* pBuffer_;
  int size_;
  int front_;
  int rear_;
};

class GhostEffect final
    : public ActorComponent {
 public:
  GhostEffect();
  ~GhostEffect();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

  bool Initialize(ImageRenderer* ownerRenderer, int ghostNum, unsigned long long updateTime);

  void SetTransparentColor(const Color8Bit& transColor);

  void On();

  void Off();

 private:
  Actor* owner_;
  
  ImageRenderer* pOwnerRenderer_;

  ImageRenderer** ppGhostRenderers_;

  GhostBuffer ghostBuffer_;

  int ghostNum_;

  unsigned long long updateTime_;

  unsigned long long accumulTime_;
};