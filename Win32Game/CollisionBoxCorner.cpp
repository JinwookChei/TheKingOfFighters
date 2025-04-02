#include "stdafx.h"
#include "CollisionBox.h"
#include "ToolActor.h"
#include "ImageController.h"
#include "CollisionBoxCorner.h"

CollisionBoxCorner::CollisionBoxCorner()
    : bindToolActor_(nullptr),
      bindImageController_(nullptr),
      collisionBoxType_(CollisionBoxType::CBT_HitBoxTop),
      cornerType_(CollisionBoxCornerType::CBCT_Start),
      color_(Color8Bit::BlackAlpha),
      prevMousePosition_({0.0f, 0.0f}) {
}

CollisionBoxCorner::~CollisionBoxCorner() {
}

void CollisionBoxCorner::BeginPlay() {
  SetScale({15.0f, 15.0f});
  EnableCollision(false);
}

void CollisionBoxCorner::Tick(unsigned long long curTick) {
  IImage* pImage = bindToolActor_->GetImage();
  unsigned int imageIndex = bindToolActor_->GetImageIndex();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;

  CollisionInfo* pCollisionInfo;
  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo) || false == pCollisionInfo->hasCollision_) {
    return;
  }

  const Vector& collisionPosition = pCollisionInfo->position_;
  const Vector& collisionScale = pCollisionInfo->scale_;

  const Transform& controllerTransform = bindImageController_->GetTransform();
  const Vector& controllerPosition = controllerTransform.GetPosition();

  UI* ownerUI = GetOwner();
  if (nullptr == ownerUI) {
    return;
  }
  const Vector& ownerScale = ownerUI->GetScale();

  if (CollisionBoxCornerType::CBCT_Start == cornerType_) {
    Vector newPosition = {collisionPosition.X + ownerScale.HalfX() - collisionScale.HalfX(), collisionPosition.Y + ownerScale.HalfY() - collisionScale.HalfY()};
    SetPosition(newPosition);
  } else {
    Vector newPosition = {collisionPosition.X + ownerScale.HalfX() + collisionScale.HalfX(), collisionPosition.Y + ownerScale.HalfY() + collisionScale.HalfY()};
    SetPosition(newPosition);
  }

  MoveWithDrag();
}

void CollisionBoxCorner::ClickDownEvent() {
}

void CollisionBoxCorner::Initialize(ToolActor* bindActor_, ImageController* imageController, CollisionBoxType boundType, CollisionBoxCornerType cornerType, const Color8Bit& color) {
  bindToolActor_ = bindActor_;
  bindImageController_ = imageController;
  collisionBoxType_ = boundType;
  cornerType_ = cornerType;
  color_ = color;
}

void CollisionBoxCorner::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  if (nullptr == bindToolActor_) {
    return;
  }

  // 이미지의 Collisioninfo.hasCollision이 False면 Render 안함.
  unsigned int imageIndex = bindToolActor_->GetImageIndex();
  IImage* pImage = bindToolActor_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;
  CollisionInfo* pCollisionInfo;

  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo) || false == pCollisionInfo->hasCollision_) {
    return;
  }
  // --

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Transform& transform = GetTransform();

  renderTexture->DrawCircle(transform.GetScale(), color_, 2.0f);
  renderTexture->SetAlpha(1.0f, transform, true, owner->GetCurrentColor());
}

void CollisionBoxCorner::MoveWithDrag() {
  Vector curMousePosition = GEngineCore->GetMousePosition();

  if (nullptr == bindToolActor_) {
    return;
  }

  unsigned int imageIndex = bindToolActor_->GetImageIndex();
  IImage* pImage = bindToolActor_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;

  CollisionInfo* pCollisionInfo;
  if (false == pFileImage->GetCollisionBoxInfo(imageIndex, collisionBoxType_, &pCollisionInfo)) {
    return;
  }

  if (IsMouseClick()) {
    Vector deltaPosition = curMousePosition - prevMousePosition_;
    if (false == pCollisionInfo->hasCollision_) {
      return;
    }

    if (cornerType_ == CollisionBoxCornerType::CBCT_Start) {
      pCollisionInfo->position_ = Vector{pCollisionInfo->position_.X + deltaPosition.HalfX(), pCollisionInfo->position_.Y + deltaPosition.HalfY()};
      pCollisionInfo->scale_ = Vector{pCollisionInfo->scale_.X - deltaPosition.X, pCollisionInfo->scale_.Y - deltaPosition.Y};
    } else {
      pCollisionInfo->position_ = Vector{pCollisionInfo->position_.X + deltaPosition.HalfX(), pCollisionInfo->position_.Y + deltaPosition.HalfY()};
      pCollisionInfo->scale_ = Vector{pCollisionInfo->scale_.X + deltaPosition.X, pCollisionInfo->scale_.Y + deltaPosition.Y};
    }
  }
  prevMousePosition_ = curMousePosition;
}
