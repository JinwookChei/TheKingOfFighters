#pragma once

#include "Actor.h"

class Mouse
    : public Actor {
 public:
  Mouse();

  ~Mouse();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  ENGINE_API void SetImage(IImage* image);

  ENGINE_API void SetAlpha(float alpha);

  ENGINE_API void SetTransparentColor(const Color8Bit& color);

  ENGINE_API void SetRenderLocalScale(const Vector& scale);

  ENGINE_API void SetRenderPosition(const Vector& position);

  ENGINE_API void ShowCursor(bool show);

 private:
  ImageRenderer* imageRener_;

  CollisionComponent* collision_;

  CollisionComponent* prevHoverCollision_;
};