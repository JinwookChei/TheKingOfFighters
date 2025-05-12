#pragma once

#include "ActorComponent.h"

class SceneComponent
    : public ActorComponent {
  friend class Actor;

 public:
  JO_API SceneComponent();

  JO_API virtual ~SceneComponent();

  JO_API void SetPosition(const Vector& newPosition);

  JO_API const Vector& GetPosition() const;

  JO_API const Vector& GetScale() const;

  JO_API Transform GetBackBufferTransform() const;

  JO_API Transform GetWorldTransform() const;

  JO_API void SetScale(const Vector& scale);

  JO_API void SetLocalScale(const Vector& localScale);

  JO_API const Vector& GetLocalScale() const;

 private:
  Vector localScale_;

  Transform transform_;
};