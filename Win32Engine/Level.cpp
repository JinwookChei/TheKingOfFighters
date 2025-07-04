#include "stdafx.h"
#include "Level.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "Mouse.h"

Level::Level()
    : isDebugRender_(false),
      isCollisionRender_(false),
      useCameraPosition_(false),
      cameraPosition_({0.0f, 0.0f}),
      actorGroupHead_(nullptr),
      actorGroupTail_(nullptr),
      collisionGroupHead_(nullptr),
      collisionGroupTail_(nullptr) {
}

Level::~Level() {
  while (actorGroupHead_) {
    ActorContainer* delContainer = (ActorContainer*)actorGroupHead_->item_;
    UnLinkFromLinkedList(&actorGroupHead_, &actorGroupTail_, &delContainer->link_);

    while (delContainer->actorHead_) {
      Actor* delActor = (Actor*)delContainer->actorHead_->item_;
      UnLinkFromLinkedList(&delContainer->actorHead_, &delContainer->actorTail_, delActor->GetLink());

      --delContainer->actorCount_;
      delete delActor;
    }
    delete delContainer;
  }
  while (collisionGroupHead_) {
    CollisionContainer* delContainer = (CollisionContainer*)collisionGroupHead_->item_;
    UnLinkFromLinkedList(&collisionGroupHead_, &collisionGroupTail_, &delContainer->link_);

    delete delContainer;
  }
}

void Level::SetDebugRender(bool isOn) {
  isDebugRender_ = isOn;
}

bool Level::GetDebugRender() const {
  return isDebugRender_;
}

void Level::SetCollisionRender(bool isOn) {
  isCollisionRender_ = isOn;
}

bool Level::GetCollisionRender() const {
  return isCollisionRender_;
}

Mouse* Level::SpawnMouse() {
  Mouse* newMouse = new Mouse;
  SpawnActorInternal(newMouse, ActorGroupEngineType::ActorGroupEngineType_MOUSE);
  return newMouse;
}

void Level::SetCameraPosition(const Vector& position) {
  cameraPosition_ = position;
}

void Level::AddCameraPosition(const Vector& addPosition) {
  cameraPosition_ += addPosition;
}

const Vector& Level::GetCameraPosition() const {
  return cameraPosition_;
}

bool Level::UseCameraPostion() const {
  return useCameraPosition_;
}

void Level::RegisterCollision(CollisionComponent* newCollision, bool bFocus /*= false*/) {
  if (nullptr == newCollision) {
    return;
  }

  CollisionContainer* collisionContainer = GetCollisionContainer(newCollision->GetCollisionGroup());

  if (false == bFocus) {
    LinkToLinkedListFIFO(&collisionContainer->collisionHead_, &collisionContainer->collisionTail_, newCollision->GetCollisionLevelLink());
  } else {
    LinkToLinkedList(&collisionContainer->collisionHead_, &collisionContainer->collisionTail_, newCollision->GetCollisionLevelLink());
  }
  ++collisionContainer->collisionCount_;
}

void Level::UnRegisterCollision(CollisionComponent* delCollision) {
  if (nullptr == delCollision) {
    return;
  }

  CollisionContainer* collisionContainer = GetCollisionContainer(delCollision->GetCollisionGroup());

  UnLinkFromLinkedList(&collisionContainer->collisionHead_, &collisionContainer->collisionTail_, delCollision->GetCollisionLevelLink());
  --collisionContainer->collisionCount_;
}

void Level::RegisterActor(Actor* actor, bool bFocus /*= false*/) {
  if (nullptr == actor) {
    return;
  }

  ActorContainer* actorContainer = GetActorContainer(actor->GetActorGroup());

  if (false == bFocus) {
    LinkToLinkedList(&actorContainer->actorHead_, &actorContainer->actorTail_, actor->GetLink());
  } else {
    LinkToLinkedListFIFO(&actorContainer->actorHead_, &actorContainer->actorTail_, actor->GetLink());
  }
  ++actorContainer->actorCount_;
}

void Level::UnRegisterActor(Actor* actor) {
  if (nullptr == actor) {
    return;
  }

  ActorContainer* actorContainer = GetActorContainer(actor->GetActorGroup());

  UnLinkFromLinkedList(&actorContainer->actorHead_, &actorContainer->actorTail_, actor->GetLink());
  --actorContainer->actorCount_;
}

bool Level::GetCollisionGroup(unsigned int collisionGroup, LINK_ITEM** head, LINK_ITEM** tail) {
  if (nullptr == head || nullptr == tail) {
    return false;
  }

  LINK_ITEM* pCur = collisionGroupHead_;
  while (pCur) {
    CollisionContainer* pCollisionContainer = (CollisionContainer*)pCur->item_;
    pCur = pCur->next_;

    if (pCollisionContainer->collisionGroup_ == collisionGroup) {
      *head = pCollisionContainer->collisionHead_;
      *tail = pCollisionContainer->collisionTail_;
      return true;
    }
  }

  return false;
}

void Level::SetUseCameraPosition(bool use) {
  useCameraPosition_ = use;
}

void Level::OnBeginPlay() {
  BeginPlay();
}

void Level::OnTick(unsigned long long deltaTime) {
  Tick(deltaTime);

  LINK_ITEM* pContainerCur = actorGroupHead_;
  while (pContainerCur) {
    ActorContainer* pActorContainer = (ActorContainer*)pContainerCur->item_;
    pContainerCur = pContainerCur->next_;

    LINK_ITEM* pCur = pActorContainer->actorHead_;
    while (pCur) {
      Actor* pActor = (Actor*)pCur->item_;
      pCur = pCur->next_;

      if (pActor->IsDestroy()) {
        UnLinkFromLinkedList(&pActorContainer->actorHead_, &pActorContainer->actorTail_, pActor->GetLink());
        --pActorContainer->actorCount_;
        delete pActor;
        continue;
      }

      if (false == pActor->IsActive()) {
        continue;
      }

      if (false == pActor->EnableTick()) {
        continue;
      }
      pActor->OnTick(deltaTime);
    }
  }
}

void Level::OnRender() {
  LINK_ITEM* pContainerCur = actorGroupHead_;
  while (pContainerCur) {
    ActorContainer* pActorContainer = (ActorContainer*)pContainerCur->item_;
    pContainerCur = pContainerCur->next_;

    LINK_ITEM* pCur = pActorContainer->actorHead_;
    while (pCur) {
      Actor* pActor = (Actor*)pCur->item_;
      pCur = pCur->next_;

      if (false == pActor->IsActive()) {
        continue;
      }

      pActor->OnRender(GGraphicDevice->GetBackBuffer());
    }
  }

  if (isDebugRender_) {
    pContainerCur = actorGroupHead_;
    while (pContainerCur) {
      ActorContainer* pActorContainer = (ActorContainer*)pContainerCur->item_;
      pContainerCur = pContainerCur->next_;

      LINK_ITEM* pCur = pActorContainer->actorHead_;
      while (pCur) {
        Actor* pActor = (Actor*)pCur->item_;
        pCur = pCur->next_;

        if (false == pActor->IsActive()) {
          continue;
        }

        pActor->OnDebugRender(GGraphicDevice->GetBackBuffer());
      }
    }
  }

  if (isCollisionRender_) {
    pContainerCur = actorGroupHead_;
    while (pContainerCur) {
      ActorContainer* pActorContainer = (ActorContainer*)pContainerCur->item_;
      pContainerCur = pContainerCur->next_;

      LINK_ITEM* pCur = pActorContainer->actorHead_;
      while (pCur) {
        Actor* pActor = (Actor*)pCur->item_;
        pCur = pCur->next_;

        if (false == pActor->IsActive()) {
          continue;
        }

        pActor->OnCollisionRender(GGraphicDevice->GetBackBuffer());
      }
    }
  }
}

void Level::SpawnActorInternal(Actor* actor, unsigned int actorGroup /*= 0xffffffff*/) {
  if (nullptr == actor) {
    return;
  }

  actor->SetActive(true);
  actor->SetLevel(this);
  actor->SetActorGroup(actorGroup);
  actor->OnBeginPlay();

  if (actor->GetActorGroup() == ActorGroupEngineType::ActorGroupEngineType_Invalid) {
    actor->SetActorGroup(ActorGroupEngineType::ActorGroupEngineType_None);
  }
}

ActorContainer* Level::GetActorContainer(unsigned int group) {
  LINK_ITEM* pCur = actorGroupHead_;
  while (pCur) {
    ActorContainer* pActorContainer = (ActorContainer*)pCur->item_;
    pCur = pCur->next_;

    if (pActorContainer->actorGroup_ == group) {
      return pActorContainer;
    }
  }

  ActorContainer* newContainer = new ActorContainer;
  newContainer->actorGroup_ = group;
  newContainer->actorCount_ = 0;
  newContainer->actorHead_ = nullptr;
  newContainer->actorTail_ = nullptr;
  newContainer->link_.prev_ = nullptr;
  newContainer->link_.next_ = nullptr;
  newContainer->link_.item_ = newContainer;

  pCur = actorGroupHead_;
  while (pCur) {
    ActorContainer* pActorContainer = (ActorContainer*)pCur->item_;

    if (group < pActorContainer->actorGroup_) {
      pCur = pCur->next_;
      continue;
    }

    LINK_ITEM* pPrev = pCur->prev_;
    LINK_ITEM* pNext = pCur->next_;

    if (nullptr == pPrev) {  // Head
      actorGroupHead_ = &newContainer->link_;
    } else {
      pPrev->next_ = &newContainer->link_;
      newContainer->link_.prev_ = pPrev;
    }

    pCur->prev_ = &newContainer->link_;
    newContainer->link_.next_ = pCur;

    return newContainer;
  }

  LinkToLinkedListFIFO(&actorGroupHead_, &actorGroupTail_, &newContainer->link_);

  return newContainer;
}

CollisionContainer* Level::GetCollisionContainer(unsigned int group) {
  LINK_ITEM* pCur = collisionGroupHead_;
  while (pCur) {
    CollisionContainer* pCollisionContainer = (CollisionContainer*)pCur->item_;
    pCur = pCur->next_;

    if (pCollisionContainer->collisionGroup_ == group) {
      return pCollisionContainer;
    }
  }

  // 기존 Group에 콜리전 Group이 없으면 GroupContainer 새로 생성.
  CollisionContainer* newContainer = new CollisionContainer;
  newContainer->collisionGroup_ = group;
  newContainer->collisionCount_ = 0;
  newContainer->collisionHead_ = nullptr;
  newContainer->collisionTail_ = nullptr;
  newContainer->link_.prev_ = nullptr;
  newContainer->link_.next_ = nullptr;
  newContainer->link_.item_ = newContainer;

  LinkToLinkedListFIFO(&collisionGroupHead_, &collisionGroupTail_, &newContainer->link_);

  return newContainer;
}
