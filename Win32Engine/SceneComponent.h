#pragma once

#include "ActorComponent.h"

class SceneComponent
    : public ActorComponent {
  friend class Actor;

 public:
  ENGINE_API SceneComponent();

  ENGINE_API virtual ~SceneComponent();

  ENGINE_API void SetPosition(const Vector& newPosition);

  ENGINE_API const Vector& GetPosition() const;

  ENGINE_API const Vector& GetScale() const;

  ENGINE_API Transform GetViewTransform() const;

  ENGINE_API Transform GetWorldTransform() const;

  ENGINE_API void SetScale(const Vector& scale);

  ENGINE_API void SetLocalScale(const Vector& localScale);

  ENGINE_API const Vector& GetLocalScale() const;

 private:
  Vector localScale_;

  Transform transform_;
};