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
      changeClearColor_(true),
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
  SetDebugParameter({.on_ = true, .linethickness_ = 5.0f});
  SetActorGroup(ActorGroupEngineType::ActorGroupEngineType_UI);
  imageRenderer_ = CreateImageRender();
  imageRenderer_->SetAlpha(1.0f);
  imageRenderer_->SetImageRenderType(ImageRenderType::Center);

  // collision_ = CreateCollision();
}

void UI::Tick(unsigned long long curTick) {
  // UI ��Ŭ�� �� �巡�׷� UI ��ǥ �̵�. START
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

  // UI ��Ŭ�� �� �巡�׷� UI ��ǥ �̵�. END
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

  if (true == changeClearColor_) {
    currentColor_ = color;
  }

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

void UI::ChangeClearColor_(bool isOn) {
  changeClearColor_ = isOn;
}

const Color8Bit& UI::GetCurrentColor() const {
  return currentColor_;
}

ImageRenderer* UI::GetImageRenderer() const {
  return imageRenderer_;
}

bool UI::Save(std::string_view filePath) {
  if (nullptr == renderTexture_) {
    return false;
  }
  return renderTexture_->Save(filePath);
}

bool UI::IsClick() const {
  return isClick_;
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

  // UI �� ������ �ִ� rederTexture �� ����
  // Actor::Render �Լ��� ������ UI �� ������ �ִ� renderTeture ��

  // �ڽ� ���� ���鼭 �ڱ��� RenderTexture �� �׸���.
}

void UI::CreateUIComponentInternal(UIComponent* newComponent) {
  UIComponent* actorComponent = newComponent;
  actorComponent->SetOwner(this);
  actorComponent->BeginPlay();
  LinkToLinkedListFIFO(&componentHead_, &componentTail_, actorComponent->GetLinkUI());
}

void UI::OnClickUpEvent() {
  ClearColor(Color8Bit::GreenAlpha);
  LINK_ITEM* pCur = componentHead_;
  while (pCur) {
    UIComponent* pUIComponent = (UIComponent*)pCur->item_;
    pCur = pCur->next_;

    if (false == pUIComponent->IsMouseClick()) {
      continue;
    }

    pUIComponent->OnClickExit();
  }
}

void UI::OnClickDownEvent() {
  if (isClick_) {
    return;
  }
  isClick_ = true;

  prevMousePosition_ = GEngine->GetMousePosition();
  CollisionInfo mousePoint{.position_ = prevMousePosition_, .scale_ = {1.0f, 1.0f}};

  const Vector& ownerPosition = GetPosition();
  const Vector& ownerScale = GetScale();

  ClearColor(Color8Bit::BlueAlpha);

  LINK_ITEM* pCur = componentHead_;

  UIComponent* pTempComponent = nullptr;
  while (pCur) {
    UIComponent* pUIComponent = (UIComponent*)pCur->item_;
    pCur = pCur->next_;

    const Transform& uiComTrans = pUIComponent->GetTransform();

    Vector ownerPositionLeftTop = ownerPosition - (ownerScale * 0.5f);
    Vector centerPosition = uiComTrans.GetPosition();

    // prevMousePosition_ // ��
    CollisionInfo uiCollisionInfo{.position_ = ownerPositionLeftTop + centerPosition, .scale_ = uiComTrans.GetScale()};

    float l = uiCollisionInfo.Left();
    float t = uiCollisionInfo.Top();
    float r = uiCollisionInfo.Right();
    float b = uiCollisionInfo.Bottom();
    if (false == CollisionComponent::CollisionPointToRect(mousePoint, uiCollisionInfo)) {
      if (pUIComponent->IsMouseClick()) {
        pUIComponent->ClickExit();
      }
      continue;
    }

    if (false == pUIComponent->GetEnableCollision()) {
      continue;
    }
    // UI Component �� ��ġ ũ��
    // ���콺�� ��ġ
    // �浹�˻�

    pTempComponent = pUIComponent;
  }

  // UI Component List �߿� ���� ���������� Collition�� Component�� ClickEvent
  // �ߺ� �浹 ����.
  if (nullptr != pTempComponent) {
    pTempComponent->OnClickDownEvent();
  }
}

void UI::OnHoverEvent() {
  ClearColor(Color8Bit::GreenAlpha);
}

void UI::OnMouseExit() {
  ClearColor(originColor_);

  LINK_ITEM* pCur = componentHead_;
  while (pCur) {
    UIComponent* pUIComponent = (UIComponent*)pCur->item_;
    pCur = pCur->next_;

    if (false == pUIComponent->IsMouseClick()) {
      continue;
    }

    pUIComponent->OnClickExit();
  }
}
