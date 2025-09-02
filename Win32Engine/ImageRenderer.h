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
  unsigned long long loopStartFrame_ = 0;
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
  ENGINE_API ImageRenderer();

  ENGINE_API virtual ~ImageRenderer();

  ENGINE_API void BeginPlay() override;

  ENGINE_API void Tick(unsigned long long curTick) override;

  ENGINE_API void SetImage(IImage* image, unsigned int index = 0);

  ENGINE_API IImage* GetImage() const;

  ENGINE_API unsigned int GetImageIndex() const;

  ENGINE_API AnimationInfo* GetCurAnimationInfo() const;

  ENGINE_API void SetImageIndex(unsigned int imageIndex);

  ENGINE_API void SetAngle(float angle);

  ENGINE_API float GetAngle() const;

  ENGINE_API void SetAlpha(float alpha);

  ENGINE_API Color8Bit GetTransparentColor() const;

  ENGINE_API void SetTransparentColor(const Color8Bit& color);

  ENGINE_API ImageRenderType GetImageRenderType() const;

  ENGINE_API void SetImageRenderType(ImageRenderType newType);

  void Render(IRenderTexture* renderTexture);

  LINK_ITEM* GetSceneLink();

  LINK_ITEM* GetRenderActorLink();

  ENGINE_API bool CreateAnimation(
      unsigned long long animationTag,
      unsigned long long imageIndex,
      unsigned int startIndex,
      unsigned int endIndex,
      unsigned long long interval,
      bool loop,
      unsigned long long loopStartFrame);

  ENGINE_API bool CreateAnimation(
      unsigned long long animationTag,
      unsigned long long imageIndex,
      const std::vector<unsigned int>& indices,
      unsigned long long interval,
      bool loop,
      unsigned long long loopStartFrame);

  ENGINE_API bool CreateAnimation(
      unsigned long long animationTag,
      unsigned long long imageIndex,
      const std::vector<unsigned int>& indices,
      const std::vector<unsigned long long> intervals,
      bool loop,
      unsigned long long loopStartFrame);

  ENGINE_API bool ChangeAnimation(unsigned long long animationTag, bool isForce = false, int startFrame = 0, unsigned long long time = 0.0f);

  ENGINE_API bool IsAnimationEnd() const;

  ENGINE_API bool HasIndexChange() const;

 protected:
  void DebugRender([[maybe_unused]] struct IRenderTexture* renderTexture) override;

 private:
  IImage* image_;

  unsigned int imageIndex_;

  bool hasIndexChanged_;

  LINK_ITEM sceneLink_;

  LINK_ITEM renderActorLink_;

  ImageRenderType imageRenderType_;

  float alpha_;

  float angle_;

  Color8Bit transparentColor_;

  bool isAlpha_;

  HashTable animations_;

  AnimationInfo* pCurAnimInfo_;
};