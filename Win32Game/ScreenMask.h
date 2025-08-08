#pragma once

class ScreenMask
    : public Actor {
 public:
  ScreenMask();

  ~ScreenMask();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void FadeIn(unsigned long long fadeDuration);

  void FadeOut(IMAGE_TYPE image, unsigned long long fadeDuration);

  void FadeInOut(IMAGE_TYPE image, unsigned long long fadeInOutDuration);

  void InitAlpha(float alpha);

  float GetCurrentAlpha() const;

 private:
  ImageRenderer* pRender_;

  unsigned long long fadeDuration_;

  unsigned long long fadeTimer_;

  float alpha_;

  bool onFadeIn_;

  bool onFadeOut_;

  bool onFadeInOut_;
};