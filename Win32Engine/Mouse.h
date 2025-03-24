#pragma once

#include "Actor.h"

class Mouse
    : public Actor {
 public:
  Mouse();

  ~Mouse();

  void BeginPlay() override;

  void Tick(unsigned long long curTick) override;

  JO_API void SetImage(IImage* image);

  JO_API void SetAlpha(float alpha);

  JO_API void SetTransparentColor(const Color8Bit& color);

  JO_API void SetRenderLocalScale(const Vector& scale);

  JO_API void SetRenderPosition(const Vector& position);

  JO_API void ShowCursor(bool show);

 private:
  ImageRenderer* imageRener_;

  CollisionComponent* collision_;

  CollisionComponent* prevHoverCollision_;
};