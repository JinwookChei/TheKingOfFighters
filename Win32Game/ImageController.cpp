#include "stdafx.h"
#include "ToolActor.h"
#include "ImageController.h"

ImageController::ImageController()
    : bindActor_(nullptr),
      prevMousePosition_({0.0f, 0.0f}) {
}

ImageController::~ImageController() {
}

void ImageController::BeginPlay() {
}

void ImageController::Tick(unsigned long long curTick) {
  // Drag Move
  Vector curMousePosition = GEngineCore->GetMousePosition();
  if (IsMouseClick()) {
    //Vector deltaPosition = curMousePosition - prevMousePosition_;

    //bindActor_->AddPositionOffSet(deltaPosition);
  }

  // SetPosition
  IImage* pImage = bindActor_->GetImage();
  unsigned int imageIndex = bindActor_->GetImageIndex();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;
  const Vector& imageOffset = pFileImage->GetImagePositionOffSet(imageIndex);

  UI* ownerUI = GetOwner();
  const Vector& ownerScale = ownerUI->GetScale();
  Vector newPosition = {ownerScale.HalfX() + imageOffset.X, ownerScale.HalfY() + imageOffset.Y};
  SetPosition(newPosition);

  prevMousePosition_ = curMousePosition;
}

void ImageController::ClickDownEvent() {
}

bool ImageController::Initialize(ToolActor* actor) {
  if (nullptr == actor) {
    return false;
  }

  bindActor_ = actor;

  UI* ownerUI = GetOwner();
  if (nullptr == ownerUI) {
    return false;
  }

  Vector ownerScale = ownerUI->GetScale();
  SetPosition(Vector(ownerScale.HalfX(), ownerScale.HalfY()));

  ImageRenderer* pImageRenderer = bindActor_->GetImageRenderer();
  if (nullptr == pImageRenderer) {
    return false;
  }

  IImage* pImage = pImageRenderer->GetImage();
  Vector imageLocalScale = pImageRenderer->GetLocalScale();
  unsigned int imageIndex = pImageRenderer->GetImageIndex();

  Vector imageScale = pImage->GetScale(imageIndex);
  SetScale(imageScale * imageLocalScale);

  return true;
}

ToolActor* ImageController::GetBindActor() const {
  return bindActor_;
}

void ImageController::Render(IRenderTexture* renderTexture) {
}
