#pragma once

#include "SceneComponent.h"

enum class ImageRenderType {
  Center,
  Left,
  Right,
  Top,
  Bottom,
  LeftTop,
  LeftBottom,
  RightTop,
  RightBottom
};

struct AnimationInfo {
  IImage* image_ = nullptr;
  unsigned long long animationTag_ = 0;
  unsigned long long curFrame_ = 0;
  long long curTime_ = 0;
  bool loop_ = false;
  bool isEnd_ = false;
  std::vector<unsigned long long> times_;
  std::vector<unsigned int> indices_;
  void* searchHandle_ = nullptr;

  unsigned int Update(unsigned long long curTick);
};

class ImageRenderer
    : public SceneComponent {
  friend class Actor;

 public:
  JO_API ImageRenderer();

  JO_API ~ImageRenderer();

  JO_API void BeginPlay() override;

  JO_API void Tick(unsigned long long curTick) override;

  JO_API void SetImage(IImage* image, unsigned int index = 0);

  JO_API IImage* GetImage() const;

  JO_API unsigned int GetImageIndex() const;

  JO_API void SetAngle(float angle);

  JO_API float GetAngle() const;

  JO_API void SetAlpha(float alpha);

  JO_API void SetTransparentColor(const Color8Bit& color);

  JO_API void SetImageRenderType(ImageRenderType newType);

  void Render(IRenderTexture* renderTexture);

  LINK_ITEM* GetSceneLink();

  LINK_ITEM* GetRenderActorLink();

  JO_API bool CreateAnimation(unsigned long long animationTag, unsigned long long imageIndex, unsigned int startIndex, unsigned int endIndex, unsigned long long interval, bool loop = true);

  JO_API bool CreateAnimation(unsigned long long animationTag, unsigned long long imageIndex, const std::vector<unsigned int>& indices, unsigned long long interval, bool loop = true);

  JO_API bool CreateAnimation(unsigned long long animationTag, unsigned long long imageIndex, const std::vector<unsigned int>& indices, const std::vector<unsigned long long> intervals, bool loop = true);

  JO_API bool ChangeAnimation(unsigned long long animationTag, int startFrame = 0, unsigned long long time = 0.0f);

 protected:
  void DebugRender([[maybe_unused]] struct IRenderTexture* renderTexture) override;

  void CollisionRender(IRenderTexture* renderTexture) override;

 private:
  IImage* image_;

  unsigned int imageIndex_;

  LINK_ITEM sceneLink_;

  LINK_ITEM renderActorLink_;
  
  ImageRenderType imageRenderType_;

  float alpha_;

  float angle_;

  Color8Bit transparentColor_;

  bool isAlpha_;

  HashTable animations_;

  AnimationInfo* pCurAnimation_;
};