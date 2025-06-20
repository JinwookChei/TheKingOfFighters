#pragma once

class BlackBoard
    : public Actor {
 public:
  BlackBoard();

  ~BlackBoard();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  void FadeIn(float fadeDuration);

  void FadeOut(float fadeDuration);

 private:
  ImageRenderer* pRender_;

  float fadeDuration_;

  float fadeTimer_;

  float alpha_;

  bool onFadeIn_;

  bool onFadeOut_;
};