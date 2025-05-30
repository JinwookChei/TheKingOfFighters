#include "stdafx.h"
#include "CollisionComponent.h"
#include "Actor.h"
#include "Level.h"

static bool (*CollisionFunctionPtr[CollisionType::CollisionType_Max][CollisionType::CollisionType_Max])(const CollisionInfo& left, const CollisionInfo& right);

// point
static bool CollisionPointToPoint(const CollisionInfo& left, const CollisionInfo& right) {
  return left.position_ == right.position_;
}
static bool CollisionPointToCircle(const CollisionInfo& left, const CollisionInfo& right) {
  Vector delta = left.position_ - right.position_;
  float length = delta.Size();
  float circleRadius = right.scale_.HalfX();
  return circleRadius >= length;
}
static bool CollisionPointToRect(const CollisionInfo& left, const CollisionInfo& right) {
  if (right.Bottom() < left.position_.Y) {
    return false;
  }
  if (right.Top() > left.position_.Y) {
    return false;
  }
  if (right.Left() > left.position_.X) {
    return false;
  }
  if (right.Right() < left.position_.X) {
    return false;
  }
  return true;
}

// circle
static bool CollisionCircleToPoint(const CollisionInfo& left, const CollisionInfo& right) {
  return CollisionPointToCircle(right, left);
}
static bool CollisionCircleToCircle(const CollisionInfo& left, const CollisionInfo& right) {
  Vector delta = left.position_ - right.position_;
  float length = delta.Size();
  float circleRadius = left.scale_.HalfX() + right.scale_.HalfX();
  return circleRadius >= length;
}
static bool CollisionCircleToRect(const CollisionInfo& left, const CollisionInfo& right) {
  if (right.Left() <= left.position_.IntergerX() && left.position_.IntergerX() <= right.Right() ||
      right.Top() <= left.position_.IntergerY() && left.position_.IntergerY() <= right.Bottom()) {
    return CollisionPointToRect(left, {.position_ = right.position_, .scale_ = right.scale_ + left.scale_.X});
  }

  if (CollisionPointToCircle({.position_ = {right.Left(), right.Top()}}, left)) {
    return true;
  }
  if (CollisionPointToCircle({.position_ = {right.Left(), right.Bottom()}}, left)) {
    return true;
  }
  if (CollisionPointToCircle({.position_ = {right.Right(), right.Top()}}, left)) {
    return true;
  }
  if (CollisionPointToCircle({.position_ = {right.Right(), right.Bottom()}}, left)) {
    return true;
  }
  return false;
}

// rect
static bool CollisionRectToPoint(const CollisionInfo& left, const CollisionInfo& right) {
  return CollisionPointToRect(right, left);
}
static bool CollisionRectToCircle(const CollisionInfo& left, const CollisionInfo& right) {
  return CollisionCircleToRect(right, left);
}
static bool CollisionRectToRect(const CollisionInfo& left, const CollisionInfo& right) {
  if (left.Bottom() < right.Top()) {
    return false;
  }
  if (left.Top() > right.Bottom()) {
    return false;
  }
  if (left.Left() > right.Right()) {
    return false;
  }
  if (left.Right() < right.Left()) {
    return false;
  }
  return true;
}

struct CollisionFunctionInit {
  CollisionFunctionInit() {
    CollisionFunctionPtr[CollisionType::CollisionType_Point][CollisionType::CollisionType_Point] = &CollisionPointToPoint;
    CollisionFunctionPtr[CollisionType::CollisionType_Point][CollisionType::CollisionType_Circle] = &CollisionPointToCircle;
    CollisionFunctionPtr[CollisionType::CollisionType_Point][CollisionType::CollisionType_Rect] = &CollisionPointToRect;

    CollisionFunctionPtr[CollisionType::CollisionType_Circle][CollisionType::CollisionType_Point] = &CollisionCircleToPoint;
    CollisionFunctionPtr[CollisionType::CollisionType_Circle][CollisionType::CollisionType_Circle] = &CollisionCircleToCircle;
    CollisionFunctionPtr[CollisionType::CollisionType_Circle][CollisionType::CollisionType_Rect] = &CollisionCircleToRect;

    CollisionFunctionPtr[CollisionType::CollisionType_Rect][CollisionType::CollisionType_Point] = &CollisionRectToPoint;
    CollisionFunctionPtr[CollisionType::CollisionType_Rect][CollisionType::CollisionType_Circle] = &CollisionRectToCircle;
    CollisionFunctionPtr[CollisionType::CollisionType_Rect][CollisionType::CollisionType_Rect] = &CollisionRectToRect;
  }

  ~CollisionFunctionInit() {
  }
};

CollisionFunctionInit functionInit;

CollisionComponent::CollisionComponent()
    : collisionGroup_(CollisionGroupEngineType::CollisionGroupEngineType_Invalid),
      searchHandle_(nullptr),
      collisionActorLink_({nullptr, nullptr, this}),
      collisionLevelLink_({nullptr, nullptr, this}),
      isCollided_(false) {
}

CollisionComponent::~CollisionComponent() {
}

bool CollisionComponent::Collision(const CollisionCheckParameter& parameter, CollisionComponent** targetCollision /*= nullptr*/) {

  if ((unsigned int)CollisionType::CollisionType_Max <= parameter.myCollisionType) {
    return false;
  }
  if ((unsigned int)CollisionType::CollisionType_Max <= parameter.targetCollisionType) {
    return false;
  }
  if (false == IsActive()) {
    return false;
  }
  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return false;
  }
  if (false == owner->IsActive()) {
    return false;
  }
  Level* level = owner->GetLevel();
  if (nullptr == level) {
    return false;
  }

  CollisionInfo myCollisionInfo = GetCollisionInfo();

  //CollisionComponent* collision[10] = {
  //    nullptr,
  //};

  unsigned int startIndex = 0;
  unsigned int selectCount = 0;

  LINK_ITEM* head = nullptr;
  LINK_ITEM* tail = nullptr;
  if (false == level->GetCollisionGroup(parameter.targetGroup, &head, &tail)) {
    return false;
  }

  LINK_ITEM* pCur = head;
  while (pCur) {
    CollisionComponent* otherCollision = (CollisionComponent*)pCur->item_;
    pCur = pCur->next_;
    if (nullptr == otherCollision) {
      continue;
    }
    if (otherCollision == this) {
      continue;
    }
    if (false == otherCollision->IsActive()) {
      continue;
    }
    Actor* otherOwner = otherCollision->GetOwner();
    if (false == otherOwner->IsActive()) {
      continue;
    }
    if (owner == otherCollision->GetOwner()) {
      continue;
    }

    CollisionInfo otherCollisionInfo = otherCollision->GetCollisionInfo();

    if (CollisionFunctionPtr[parameter.myCollisionType][parameter.targetCollisionType](myCollisionInfo, otherCollisionInfo)) {
      if (nullptr != targetCollision) {
        *targetCollision = otherCollision;
      }
      return true;
    }
  }

  return false;
}

void CollisionComponent::ChangeCollisionGroup(unsigned int group) {
  group = group == CollisionGroupEngineType::CollisionGroupEngineType_Invalid ? CollisionGroupEngineType::CollisionGroupEngineType_None : group;

  if (collisionGroup_ == group) {
    return;
  }

  Actor* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }
  Level* currentLevel = owner->GetLevel();
  if (nullptr == currentLevel) {
    return;
  }

  if (collisionGroup_ != CollisionGroupEngineType::CollisionGroupEngineType_Invalid) {
    currentLevel->UnRegisterCollision(this);
  }

  collisionGroup_ = group;

  currentLevel->RegisterCollision(this);
}

int CollisionComponent::GetCollisionGroup() const {
  return collisionGroup_;
}

CollisionInfo CollisionComponent::GetCollisionInfo() const {
  Transform transform = GetWorldTransform();
  return CollisionInfo{.position_ = transform.GetPosition(), .scale_ = transform.GetScale(), .hasCollision_ = IsActive()};
}

bool CollisionComponent::CollisionPointToRect(const CollisionInfo& left, const CollisionInfo& right) {
  return ::CollisionPointToRect(left, right);
}

bool CollisionComponent::IsCollided() {
  return isCollided_;
}

void CollisionComponent::OnCollision() {
  isCollided_ = true;
}

void CollisionComponent::OffCollision() {
  isCollided_ = false;
}


void CollisionComponent::CollisionRender(IRenderTexture* renderTexture) {
  if (!parameter_.on_ || nullptr == renderTexture || false == IsActive()) {
    return;
  }

  Transform transform = GetViewTransform();

  GGraphicDevice->RenderImgStart(transform, 0.0f, renderTexture);

  renderTexture->DrawPoint(parameter_.color_, parameter_.linethickness_);

  if (parameter_.withRectangle_) {
    renderTexture->DrawRectagle(transform.GetScale(), parameter_.color_, parameter_.linethickness_);
  }
  if (parameter_.withCircle_) {
    renderTexture->DrawCircle(transform.GetScale(), parameter_.color_, parameter_.linethickness_);
  }

  GGraphicDevice->RenderImgEnd(renderTexture);
}

LINK_ITEM* CollisionComponent::GetCollisionActorLink() {
  return &collisionActorLink_;
}

LINK_ITEM* CollisionComponent::GetCollisionLevelLink() {
  return &collisionLevelLink_;
}

void CollisionComponent::SetSearchHandle(void* searchHandle) {
  searchHandle_ = searchHandle;
}

void* CollisionComponent::GetSearchHandle() {
  return searchHandle_;
}
