#include "stdafx.h"
#include "HitBoxButton.h"


ResizeCornerComponent::ResizeCornerComponent() {
}

ResizeCornerComponent::~ResizeCornerComponent() {
}

void ResizeCornerComponent::BeginPlay() {
  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  ImageRenderer* ownerRenderer = owner->GetImageRenderer();
  if (nullptr == ownerRenderer) {
    return;
  }

  IImage* ownerImage = ownerRenderer->GetImage();
  if (nullptr == ownerImage || true == ownerImage->IsRenderTexture()) {
    return;
  }
  unsigned int imageIndex = ownerRenderer->GetImageIndex();
  IFileImage* ownerFileImage = (IFileImage*)ownerImage;

  Vector ownerPosition = owner->GetPosition();
  Vector imageOffSet = ownerFileImage->GetImagePositionOffSet(imageIndex);
  Vector hitBoxStart = ownerFileImage->GetHitBoxStart(imageIndex);

  // SetPosition(ownerPosition + imageOffSet + hitBoxStart);
  SetPosition({1000.0f, 1000.0f});

  SetScale({100.0f, 100.0f});

  //SetPosition({owner->GetScale().HalfX(), owner->GetScale().HalfY()});
}

void ResizeCornerComponent::Tick(unsigned long long curTick) {
}

void ResizeCornerComponent::ClickDownEvent() {
}

void ResizeCornerComponent::ClickExit() {
}

void ResizeCornerComponent::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  ImageRenderer* ownerRenderer = owner->GetImageRenderer();
  if (nullptr == ownerRenderer)
  {
    return;
  }

  IImage* ownerImage = ownerRenderer->GetImage();
  if (nullptr == ownerImage || true == ownerImage->IsRenderTexture())
  {
    return;
  }

  IFileImage* ownerFileImage = (IFileImage*)ownerImage;
  ownerFileImage->GetHitBoxStart(ownerRenderer->GetImageIndex());

  const Transform& transform = GetTransform();
  
  renderTexture->DrawRectagle({1000.0f, 1000.0f}, Color8Bit::RedAlpha, 10.0f);
  renderTexture->SetAlpha(1.0f, transform, true, owner->GetCurrentColor());
  
}



HitBoxButton::HitBoxButton()
    : bindUI_(nullptr) {
}

HitBoxButton::~HitBoxButton() {
}

void HitBoxButton::BeginPlay() {
}

void HitBoxButton::Tick(unsigned long long curTick) {
}

void HitBoxButton::ClickDownEvent() {

  if (nullptr == bindUI_) {
    return;
  }
  ResizeCornerComponent* corner = bindUI_->CreateUIComponent<ResizeCornerComponent>();

}

void HitBoxButton::ClickExit() {
}

void HitBoxButton::BindUI(UI* ui) {
  if (nullptr == ui) {
    return;
  }

  bindUI_ = ui;
}

void HitBoxButton::Render(IRenderTexture* renderTexture) {
}
