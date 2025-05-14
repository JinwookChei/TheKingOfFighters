#include "stdafx.h"
#include "SceneComponent.h"
#include "Actor.h"

SceneComponent::SceneComponent()
    : localScale_({1.0f, 1.0f}) {
}

SceneComponent::~SceneComponent() {
}

void SceneComponent::SetPosition(const Vector& newPosition) {
  transform_.SetPosition(newPosition);
}

const Vector& SceneComponent::GetPosition() const {
  return transform_.GetPosition();
}

const Vector& SceneComponent::GetScale() const {
  return transform_.GetScale();
}

Transform SceneComponent::GetViewTransform() const {
  Transform newTransform = transform_;

  Actor* owner = GetOwner();
  if (nullptr != owner) {
    Vector actorPosition = owner->GetPosition();

    if (owner->UseCameraposition()) {
      actorPosition = GCamera->GetRenderPosition(actorPosition);
    }

    newTransform.AddPostion(actorPosition);
  }

  newTransform.SetScale(newTransform.GetScale() * localScale_);

  return newTransform;
}

Transform SceneComponent::GetWorldTransform() const {
  Transform newTransform = transform_;

  Actor* owner = GetOwner();
  if (nullptr != owner) {
    Vector actorPosition = owner->GetPosition();

    newTransform.AddPostion(actorPosition);
  }

  newTransform.SetScale(newTransform.GetScale() * localScale_);

  return newTransform;
}

void SceneComponent::SetScale(const Vector& scale) {
  transform_.SetScale(scale);
}

void SceneComponent::SetLocalScale(const Vector& localScale) {
  localScale_ = localScale;
}

const Vector& SceneComponent::GetLocalScale() const {
  return localScale_;
}
