#include "stdafx.h"
#include "Mouse.h"
#include "ImageRenderer.h"
#include "CollisionComponent.h"
#include "EngineCore.h"
#include "UI.h"
#include "Level.h"

Mouse::Mouse()
    : collision_(nullptr),
      imageRener_(nullptr),
      prevHoverCollision_(nullptr) {
}

Mouse::~Mouse() {
  GEngine->SetShowCursor(true);
}

void Mouse::BeginPlay() {
  imageRener_ = CreateImageRender();
  imageRener_->SetImageRenderType(ImageRenderType::Top);

  collision_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_MOUSE);

  SetDebugParameter({.on_ = true, .linethickness_ = 2.0f});
  imageRener_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Cyan});
  collision_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Black});
}

void Mouse::Tick(unsigned long long curTick) {
  if (nullptr == collision_) {
    return;
  }
  SetPosition(GEngine->GetMousePosition());

  bool isMouseUp = InputManager::Instance()->IsUp(VK_LBUTTON);
  bool isMouseDown = InputManager::Instance()->IsDown(VK_LBUTTON);

  CollisionComponent* targetCollision = nullptr;
  collision_->Collision({.targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_UI, .targetCollisionType = CollisionType::CollisionType_Rect, .myCollisionType = CollisionType::CollisionType_Point}, &targetCollision);

  do {
    if (nullptr == targetCollision) {
      break;
    }
    Actor* owner = targetCollision->GetOwner();
    if (false == owner->IsUI()) {
      targetCollision = nullptr;
      break;
    }
    UI* pUI = (UI*)owner;

    if (nullptr != prevHoverCollision_ &&
        prevHoverCollision_ != targetCollision) {
      Actor* prevOwner = prevHoverCollision_->GetOwner();
      if (prevOwner->IsUI()) {
        UI* prevUI = (UI*)prevOwner;
        prevUI->OnMouseExit();
      }
      prevHoverCollision_ = nullptr;
    }

    if (isMouseUp || isMouseDown) {
      if (prevHoverCollision_ != targetCollision) {
        pUI->OnHoverEvent();
      }
      if (isMouseUp) {
        pUI->OnClickUpEvent();
      } else if (isMouseDown) {
        pUI->OnClickDownEvent();

        Level* level = pUI->GetLevel();
        level->UnRegisterActor(pUI);
        level->RegisterActor(pUI, true);
        level->UnRegisterCollision(targetCollision);
        level->RegisterCollision(targetCollision, true);
      }

      prevHoverCollision_ = targetCollision;
    } else {
      // hover
      if (prevHoverCollision_ != targetCollision) {
        pUI->OnHoverEvent();
      }
      prevHoverCollision_ = targetCollision;
    }
  } while (false);

  if (nullptr == targetCollision && nullptr != prevHoverCollision_) {
    Actor* prevOwner = prevHoverCollision_->GetOwner();
    if (prevOwner->IsUI()) {
      UI* prevUI = (UI*)prevOwner;
      prevUI->OnMouseExit();
    }
    prevHoverCollision_ = nullptr;
  }
}

void Mouse::SetImage(IImage* image) {
  imageRener_->SetImage(image);
}

void Mouse::SetAlpha(float alpha) {
  imageRener_->SetAlpha(alpha);
}

void Mouse::SetTransparentColor(const Color8Bit& color) {
  imageRener_->SetTransparentColor(color);
}

void Mouse::SetRenderLocalScale(const Vector& scale) {
  imageRener_->SetLocalScale(scale);
}

void Mouse::SetRenderPosition(const Vector& position) {
  imageRener_->SetPosition(position);
}

void Mouse::ShowCursor(bool show) {
  GEngine->SetShowCursor(show);
}