#include "stdafx.h"
#include "Object.h"

Object::Object()
    : imageRender_(nullptr),
      moveOffSet_({0.0f, 0.0f}) {
}

Object::~Object() {
}

void Object::BeginPlay() {
  SetDebugParameter({.on_ = true, .linethickness_ = 1.0f, .color_ = Color8Bit::Red});
  imageRender_ = CreateImageRender();

  IImage* pFind = ImgManager::GetIntance()->GetImg(1);

  imageRender_->SetImage(pFind, 0);
  imageRender_->SetTransparentColor(Color8Bit{17, 91, 124, 0});
  imageRender_->SetImageRenderType(ImageRenderType::Center);
  imageRender_->SetLocalScale({4.0f, 4.0f});
  imageRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 1.0f, .color_ = Color8Bit::Green});
}

void Object::Tick(unsigned long long curTick) {
}

void Object::MoveOffset(Vector addPosition) {
  Vector calcPosition = GetPosition();
  calcPosition += addPosition;
  SetPosition(calcPosition);
  moveOffSet_ += addPosition;
  
}

ImageRenderer* Object::GetImageRenderer() const {
  return imageRender_;
}
