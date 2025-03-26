#include "stdafx.h"
#include "HitBoxButton.h"


ResizeCornerComponent::ResizeCornerComponent() {
}

ResizeCornerComponent::~ResizeCornerComponent() {
}

void ResizeCornerComponent::BeginPlay() {
  UI* owner = GetOwner();

  SetScale(owner->GetScale());
  SetPosition({owner->GetScale().HalfX(), owner->GetScale().HalfY()});
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

  const Transform& transform = GetTransform();
  renderTexture->DrawRectagle(transform.GetScale(), Color8Bit::RedAlpha, 10.0f);
  renderTexture->DrawLine(Color8Bit::BlackAlpha, {0, -owner->GetScale().HalfY()}, {0, owner->GetScale().HalfY()}, 1.0f);
  renderTexture->DrawLine(Color8Bit::BlackAlpha, {-owner->GetScale().HalfX(), 0}, {owner->GetScale().HalfX(), 0}, 1.0f);
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
  ResizeCornerComponent* temp1 = bindUI_->CreateUIComponent<ResizeCornerComponent>();
  //temp1->SetPosition({0.0f, 0.0f});
  //temp1->SetScale({100.0f, 100.0f});
  //temp1->

  /*CollisionPoint* temp2 = bindUI_->CreateUIComponent<CollisionPoint>();
  temp2->SetPosition({500.0f, 600.0f});
  temp2->SetScale({10.0f, 10.0f});

  temp1->SetPair(temp2);
  temp2->SetPair(temp1);*/

  // temp2->SetPosition()
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
