#include "stdafx.h"
#include "Actor.h"
#include "ImageRenderer.h"
#include "CollisionComponent.h"
#include "Level.h"
#include "UIComponent.h"


Actor::Actor()
    : position_({0.0f, 0.0f}),
      currentLevel_(nullptr),
      renderHead_(nullptr),
      renderTail_(nullptr),
      collisionHead_(nullptr),
      collisionTail_(nullptr),
      componentHead_(nullptr),
      componentTail_(nullptr),
      isUI_(false),
      isPlayer_(false),
      useCameraPosition_(false),
      isActive_(false),
      enableTick_(true),
      isDestroy_(false),
      collisionTag_(0),
      actorGroup_(ActorGroupEngineType::ActorGroupEngineType_Invalid) {
  link_.prev_ = nullptr;
  link_.next_ = nullptr;
  link_.item_ = this;
}

Actor::~Actor() {
  while (renderHead_) {
    ImageRenderer* render = (ImageRenderer*)renderHead_->item_;
    UnLinkFromLinkedList(&renderHead_, &renderTail_, render->GetRenderActorLink());
  }
  while (collisionHead_) {
    CollisionComponent* collision = (CollisionComponent*)collisionHead_->item_;
    UnLinkFromLinkedList(&collisionHead_, &collisionTail_, collision->GetCollisionActorLink());
    if (nullptr != currentLevel_) {
      currentLevel_->UnRegisterCollision(collision);
    }
  }
  while (componentHead_) {
    ActorComponent* actorComponent = (ActorComponent*)componentHead_->item_;
    UnLinkFromLinkedList(&componentHead_, &componentTail_, actorComponent->GetActorLink());
    delete actorComponent;
  }
}

void Actor::BeginPlay() {
}

void Actor::Tick(unsigned long long curTick) {
}

void Actor::SetPosition(const Vector& newPosition) {
  position_ = newPosition;
}

const Vector& Actor::GetPosition() const {
  return position_;
}

void Actor::SetDebugParameter(const ActorSetDebugParameter& parameter) {
  debugParameter = parameter;
  debugParameter.color_.A = 255;
}

void Actor::SetUseCameraposition(bool use) {
  useCameraPosition_ = use;
}

bool Actor::UseCameraposition() const {
  return useCameraPosition_;
}
void Actor::SetActive(bool isActive) {
  isActive_ = isActive;
}
bool Actor::IsActive() const {
  return isActive_ && false == isDestroy_;
}
void Actor::SetEnableTick(bool enable) {
  enableTick_ = enable;
}
bool Actor::EnableTick() const {
  return enableTick_;
}
void Actor::SetDestroy() {
  isDestroy_ = true;
}

bool Actor::IsDestroy() const {
  return isDestroy_;
}

int Actor::GetCollisionTag() const {
  return collisionTag_;
}

unsigned int Actor::GetActorGroup() const {
  return actorGroup_;
}

ImageRenderer* Actor::CreateImageRenderFIFO() {
  ImageRenderer* newImage = CreateComponent<ImageRenderer>();

  LinkToLinkedListFIFO(&renderHead_, &renderTail_, newImage->GetRenderActorLink());

  return newImage;
}

ImageRenderer* Actor::CreateImageRenderLIFO() {
  ImageRenderer* newImage = CreateComponent<ImageRenderer>();

  LinkToLinkedList(&renderHead_, &renderTail_, newImage->GetRenderActorLink());
  return newImage;
}

CollisionComponent* Actor::CreateCollision(unsigned int collisionGroup) {
  CollisionComponent* newCollision = CreateComponent<CollisionComponent>();

  LinkToLinkedListFIFO(&collisionHead_, &collisionTail_, newCollision->GetCollisionActorLink());

  newCollision->ChangeCollisionGroup(collisionGroup);

  return newCollision;
}

bool Actor::IsUI() const {
  return isUI_;
}

bool Actor::IsPlayer() const {
  return isPlayer_;
}

void Actor::OnBeginPlay() {
  BeginPlay();
}

void Actor::OnTick(unsigned long long curTick) {
  LINK_ITEM* pCur = componentHead_;
  while (pCur) {
    ActorComponent* pCom = (ActorComponent*)pCur->item_;
    pCur = pCur->next_;
   

    if (false == pCom->IsActive()) {
      continue;
    }

    if (false == pCom->EnableTick()) {
      continue;
    }

    pCom->OnTick(curTick);
  }

  Tick(curTick);
}

void Actor::SetCollisionTag(int newCollisionTag) {
  collisionTag_ = newCollisionTag;
}

void Actor::SetActorGroup(unsigned int actorGroup) {
  actorGroup = actorGroup == ActorGroupEngineType::ActorGroupEngineType_Invalid ? ActorGroupEngineType::ActorGroupEngineType_None : actorGroup;

  if (actorGroup_ == actorGroup) {
    return;
  }

  if (actorGroup_ != ActorGroupEngineType::ActorGroupEngineType_Invalid) {
    currentLevel_->UnRegisterActor(this);
  }

  actorGroup_ = actorGroup;

  currentLevel_->RegisterActor(this);
}

Level* Actor::GetLevel() {
  return currentLevel_;
}

void Actor::Render(IRenderTexture* renderTexture) const {
  if (nullptr == renderTexture) {
    return;
  }
}

void Actor::OnRender(IRenderTexture* renderTexture) const {
  if (nullptr == renderTexture) {
    return;
  }

  Render(renderTexture);

  LINK_ITEM* pCur = renderHead_;
  while (pCur) {
    ImageRenderer* pRender = (ImageRenderer*)pCur->item_;
    pCur = pCur->next_;

    if (pRender->IsActive()) {
      pRender->Render(renderTexture);
    }
  }
}

void Actor::OnDebugRender(IRenderTexture* renderTexture) const {
  if (nullptr == renderTexture) {
    return;
  }

  LINK_ITEM* pCur = componentHead_;
  while (pCur) {
    ActorComponent* pItem = (ActorComponent*)pCur->item_;
    pCur = pCur->next_;
    pItem->DebugRender(renderTexture);
  }

  if (!debugParameter.on_) {
    return;
  }

  Transform transform;
  transform.SetPosition(position_);

  GGraphicDevice->RenderImgStart(transform, 0.0f, renderTexture);

  renderTexture->DrawPoint(debugParameter.color_, debugParameter.linethickness_);

  GGraphicDevice->RenderImgEnd(renderTexture);
}

void Actor::OnCollisionRender(IRenderTexture* renderTexture) const {
  if (nullptr == renderTexture) {
    return;
  }

  LINK_ITEM* pCur = componentHead_;
  while (pCur) {
    ActorComponent* pItem = (ActorComponent*)pCur->item_;
    pCur = pCur->next_;
    pItem->CollisionRender(renderTexture);
  }
}

void Actor::SetLevel(Level* level) {
  currentLevel_ = level;
}

LINK_ITEM* Actor::GetLink() {
  return &link_;
}