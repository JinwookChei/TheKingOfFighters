#pragma once

class BackGroundMask
    : public Actor {
 public:
  BackGroundMask();

  ~BackGroundMask();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void FadeIn(float fadeDuration);

  void FadeOut(IMAGE_TYPE image, float fadeDuration);

  void FadeInOut(IMAGE_TYPE image, float fadeInOutDuration);

 private:
  ImageRenderer* pRender_;

  float fadeDuration_;

  float fadeTimer_;

  float alpha_;

  bool onFadeIn_;

  bool onFadeOut_;

  bool onFadeInOut_;
};