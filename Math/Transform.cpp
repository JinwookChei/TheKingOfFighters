#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
    : position_({0.0f, 0.0f}),
      scale_({1.0f, 1.0f}) {
}

Transform::Transform(const Vector& position, const Vector& scale)
    : position_(position),
      scale_(scale) {
}

Transform::~Transform() {
}

void Transform::SetScale(const Vector& newScale) {
  scale_ = newScale;
}

void Transform::AddScale(const Vector& addScale) {
  scale_ += addScale;
}

MATH_API const Vector& Transform::GetScale() const {
  return scale_;
}

void Transform::SetPosition(const Vector& newPosition) {
  position_ = newPosition;
}

void Transform::AddPostion(const Vector& addPosition) {
  position_ += addPosition;
}

const Vector& Transform::GetPosition() const {
  return position_;
}

float Transform::Left() const {
  return position_.X - (scale_.X * 0.5f);
}

float Transform::Right() const {
  return position_.X + (scale_.X * 0.5f);
}

float Transform::Top() const {
  return position_.Y - (scale_.Y * 0.5f);
}

float Transform::Bottom() const {
  return position_.Y + (scale_.Y * 0.5f);
}

int Transform::IntergerLeft() const {
  return (int)Left();
}

int Transform::IntergerRight() const {
  return (int)Right();
}

int Transform::IntergerTop() const {
  return (int)Top();
}

int Transform::IntergerBottom() const {
  return (int)Bottom();
}
