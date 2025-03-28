#include "stdafx.h"
#include "ViewPortImage.h"
#include "HitBoxButton.h"

ResizeCornerComponent::ResizeCornerComponent()
    : bindViewPortImage_(nullptr),
      prevMousePosition_({0.0f, 0.0f}) {
}

ResizeCornerComponent::~ResizeCornerComponent() {
}

void ResizeCornerComponent::BeginPlay() {
}

void ResizeCornerComponent::Tick(unsigned long long curTick) {
  Vector curMousePosition = GEngineCore->GetMousePosition();

  if (nullptr == bindViewPortImage_) {
    return;
  }

  unsigned int imageIndex = bindViewPortImage_->GetImageIndex();
  IImage* pImage = bindViewPortImage_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;

  
  if (IsMouseClick()) {
    Vector deltaPosition = curMousePosition - prevMousePosition_;

    pFileImage->AddHitBoxStartPosition(imageIndex, deltaPosition);
  }

  Vector imageOffSet = pFileImage->GetImagePositionOffSet(imageIndex);
  Vector hitBoxStart = pFileImage->GetHitBoxStart(imageIndex);

  SetPosition(imageOffSet + hitBoxStart);

  prevMousePosition_ = curMousePosition;
}

void ResizeCornerComponent::ClickDownEvent() {
}

void ResizeCornerComponent::ClickExit() {
}

void ResizeCornerComponent::BindViewPortImage(ViewPortImage* viewPortImage) {
  bindViewPortImage_ = viewPortImage;

  if (nullptr == bindViewPortImage_) {
    return;
  }

  unsigned int imageIndex = bindViewPortImage_->GetImageIndex();
  IImage* pImage = bindViewPortImage_->GetImage();

  if (true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;

  Vector imageOffSet = pFileImage->GetImagePositionOffSet(imageIndex);
  Vector hitBoxStart = pFileImage->GetHitBoxStart(imageIndex);

  SetPosition(imageOffSet + hitBoxStart);

  SetScale({10.0f, 10.0f});
}

void ResizeCornerComponent::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  UI* onwer = GetOwner();

  const Transform& transform = GetTransform();
  Vector buttonScale = GetScale();
  renderTexture->DrawRectagle(buttonScale, Color8Bit::RedAlpha, 2.0f);
  renderTexture->SetAlpha(1.0f, transform, true, onwer->GetCurrentColor());
}

HitBoxButton::HitBoxButton()
    : bindUI_(nullptr),
      bindViewPortImage_(nullptr) {
}

HitBoxButton::~HitBoxButton() {
}

void HitBoxButton::BeginPlay() {
}

void HitBoxButton::Tick(unsigned long long curTick) {
}

void HitBoxButton::ClickDownEvent() {
  if (nullptr == bindUI_ || nullptr == bindViewPortImage_) {
    return;
  }
  ResizeCornerComponent* corner = bindUI_->CreateUIComponent<ResizeCornerComponent>();
  corner->BindViewPortImage(bindViewPortImage_);
}

void HitBoxButton::ClickExit() {
}

void HitBoxButton::BindUI(UI* ui) {
  bindUI_ = ui;
}

void HitBoxButton::BindViewPortImage(ViewPortImage* viewPortImage) {
  bindViewPortImage_ = viewPortImage;
}

void HitBoxButton::Render(IRenderTexture* renderTexture) {
}
