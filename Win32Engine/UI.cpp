#include "stdafx.h"
#include "UI.h"
#include "ImageRenderer.h"
#include "CollisionComponent.h"
#include "UIComponent.h"

UI::UI()
    : imageRenderer_(nullptr),
      collision_(nullptr),
      renderTexture_(nullptr),
      originColor_(Color8Bit::Black),
      currentColor_(Color8Bit::Black),
      isClick_(false),
      useMousePosition_(false),
      componentHead_(nullptr),
      componentTail_(nullptr) {
  Actor::isUI_ = true;
}

UI::~UI() {
  if (nullptr != renderTexture_) {
    renderTexture_->Release();
    renderTexture_ = nullptr;
  }

  while (componentHead_) {
    UIComponent* delComponent = (UIComponent*)componentHead_->item_;
    UnLinkFromLinkedList(&componentHead_, &componentTail_, delComponent->GetLinkUI());
    delete delComponent;
  }
}

void UI::BeginPlay() {
  SetDebugParameter({.on_ = true});
  SetActorGroup(ActorGroupEngineType::ActorGroupEngineType_UI);
  imageRenderer_ = CreateImageRender();
  imageRenderer_->SetAlpha(1.0f);

  // collision_ = CreateCollision();
}

void UI::Tick(unsigned long long curTick) {
  if (isClick_ && InputManager::Instance()->IsUp(VK_LBUTTON)) {
    isClick_ = false;
  }

  LINK_ITEM* pCur = componentHead_;
  while (pCur) {
    UIComponent* pUIComponent = (UIComponent*)pCur->item_;
    pCur = pCur->next_;

    pUIComponent->Tick(curTick);
  }

  if (false == isClick_ || false == useMousePosition_) {
    return;
  }

  Vector curMousePosition = GEngine->GetMousePosition();

  Vector deltaPosition = curMousePosition - prevMousePosition_;

  SetPosition(GetPosition() + deltaPosition);

  prevMousePosition_ = curMousePosition;
}

void UI::SetScale(const Vector& scale) {
  if (currentScale_ == scale) {
    return;
  }

  if (nullptr != renderTexture_) {
    renderTexture_->Release();
    renderTexture_ = nullptr;
  }

  renderTexture_ = GGraphicDevice->CreateRenderTexture(scale.IntergerX(), scale.IntergerY());

  imageRenderer_->SetImage(renderTexture_);

  if (nullptr != collision_) {
    collision_->SetScale(scale);
    collision_->SetLocalScale(imageRenderer_->GetLocalScale());
  }

  currentScale_ = scale;
}

const Vector& UI::GetScale() const {
  return currentScale_;
}

void UI::SetOriginColor(const Color8Bit& color) {
  if (originColor_.Color == currentColor_.Color) {
    currentColor_ = color;
  }

  originColor_ = color;
}

void UI::ClearColor(const Color8Bit& color) const {
  if (nullptr == renderTexture_) {
    return;
  }

  currentColor_ = color;

  renderTexture_->SetColor(currentColor_);
}

void UI::MakeCollision() {
  if (nullptr != collision_) {
    return;
  }

  collision_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_UI);

  collision_->SetScale(currentScale_);
  if (nullptr != imageRenderer_) {
    collision_->SetLocalScale(imageRenderer_->GetLocalScale());
  }

  collision_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 1.0f});
}

void UI::SetUseMousePosition(bool isOn) {
  useMousePosition_ = isOn;
}

const Color8Bit& UI::GetCurrentColor() const {
  return currentColor_;
}

void UI::Render(IRenderTexture* renderTexture) const {
  if (nullptr == renderTexture_ || nullptr == renderTexture) {
    return;
  }

  ClearColor(currentColor_);
  
  LINK_ITEM* pCur = componentHead_;
  while (pCur) {
    UIComponent* pUIComponent = (UIComponent*)pCur->item_;
    pCur = pCur->next_;

    pUIComponent->OnRender(renderTexture_);
  }

  // UI 가 가지고 있는 rederTexture 가 들어가고
  // Actor::Render 함수가 끝나면 UI 가 가지고 있는 renderTeture 를

  // 자식 루프 돌면서 자기의 RenderTexture 에 그린다.
}

void UI::CreateUIComponentInternal(UIComponent* newComponent) {
  UIComponent* actorComponent = newComponent;
  actorComponent->SetOwner(this);
  actorComponent->BeginPlay();
  LinkToLinkedListFIFO(&componentHead_, &componentTail_, actorComponent->GetLinkUI());
}

void UI::OnClickUpEvent() {
  ClearColor(Color8Bit::GreenAlpha);
}

void UI::OnClickDownEvent() {
  if (isClick_) {
    return;
  }

  isClick_ = true;

  prevMousePosition_ = GEngine->GetMousePosition();

  ClearColor(Color8Bit::BlueAlpha);

  LINK_ITEM* pCur = componentHead_;
  while (pCur) {
    UIComponent* pUIComponent = (UIComponent*)pCur->item_;
    pCur = pCur->next_;

    pUIComponent->ClickDownEvent();
  }
}

void UI::OnHoverEvent() {
  ClearColor(Color8Bit::GreenAlpha);
}

void UI::OnMouseExit() {
  ClearColor(originColor_);
}
