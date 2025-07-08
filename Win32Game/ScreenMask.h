#pragma once

class ScreenMask
    : public Actor {
 public:
  ScreenMask();

  ~ScreenMask();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void FadeIn(float fadeDuration);

  void FadeOut(IMAGE_TYPE image, float fadeDuration);

  void FadeInOut(IMAGE_TYPE image, float fadeInOutDuration);

  void InitAlpha(float alpha);

  float GetCurrentAlpha() const;

 private:
  ImageRenderer* pRender_;

  float fadeDuration_;

  float fadeTimer_;

  float alpha_;

  bool onFadeIn_;

  bool onFadeOut_;

  bool onFadeInOut_;
};