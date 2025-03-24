#include "stdafx.h"
#include "UIComponent.h"
#include "UI.h"

UIComponent::UIComponent()
    : owner_(nullptr),
      angle_(0.0f),
      isMouseClick_(false),
      transform_({0.0f, 0.0f}, {1.0f, 1.0f}),
      linkUI_({nullptr, nullptr, this}) {
}

UIComponent::~UIComponent() {
}

UI* UIComponent::GetOwner() const {
  return owner_;
}

void UIComponent::BeginPlay() {
}

void UIComponent::Tick(unsigned long long curTick) {
}

void UIComponent::ClickDownEvent() {
}

void UIComponent::ClickExit() {
}

bool UIComponent::IsMouseClick() {
  return isMouseClick_;
}

void UIComponent::SetPosition(const Vector& position) {
  transform_.SetPosition(position);
}

void UIComponent::AddPosition(const Vector& addMove) {
  transform_.AddPostion(addMove);
}

void UIComponent::SetScale(const Vector& scale) {
  transform_.SetScale(scale);
}

const Transform& UIComponent::GetTransform() const {
  return transform_;
}

void UIComponent::PostRender() {
}

void UIComponent::OnRender(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  GGraphicDevice->RenderImgStart(transform_, angle_, renderTexture);

  Render(renderTexture);

  GGraphicDevice->RenderImgEnd(renderTexture);
}

void UIComponent::OnClickDownEvent() {
  isMouseClick_ = true;

  ClickDownEvent();
}

void UIComponent::OnClickExit() {
  isMouseClick_ = false;

  ClickExit();
}

void UIComponent::SetOwner(UI* owner) {
  owner_ = owner;
}

LINK_ITEM* UIComponent::GetLinkUI() {
  return &linkUI_;
}
