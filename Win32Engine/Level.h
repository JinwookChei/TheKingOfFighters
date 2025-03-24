#pragma once

class Actor;
class Mouse;
struct ActorContainer {
  unsigned int actorGroup_;
  unsigned int actorCount_;
  LINK_ITEM* actorHead_;
  LINK_ITEM* actorTail_;
  LINK_ITEM link_;
};
struct CollisionContainer {
  unsigned int collisionGroup_;
  unsigned int collisionCount_;
  LINK_ITEM* collisionHead_;
  LINK_ITEM* collisionTail_;
  LINK_ITEM link_;
};

class Level {
  friend class EngineCore;
  friend class CollisionComponent;

 public:
  JO_API Level();

  JO_API virtual ~Level() = 0;

  JO_API virtual void BeginPlay() = 0;

  JO_API virtual void Tick(unsigned long long deltaTime) = 0;

  JO_API Actor* Collision(const Actor* actor, int targetCollisionTag);

  JO_API void SetDebugRender(bool isOn);

  JO_API bool GetDebugRender() const;

  JO_API Mouse* SpawnMouse();

  template <typename ActorType>
  ActorType* SpawnActor(unsigned int actorGroup = 0xffffffff) {
    ActorType* newActor = new ActorType;
    SpawnActorInternal(newActor, actorGroup);
    return newActor;
  }

  JO_API void SetCameraPosition(const Vector& position);

  JO_API void AddCameraPosition(const Vector& addPosition);

  JO_API const Vector& GetCameraPosition() const;

  JO_API bool UseCameraPostion() const;

  void RegisterCollision(class CollisionComponent* newCollision, bool bFocus = false);

  void UnRegisterCollision(class CollisionComponent* delCollision);

  void RegisterActor(Actor* actor, bool bFocus = false);

  void UnRegisterActor(Actor* actor);

  bool GetCollisionGroup(unsigned int collisionGroup, LINK_ITEM** head, LINK_ITEM** tail);

 protected:
  JO_API void SetUseCameraPosition(bool use);

 private:
  void OnBeginPlay();

  void OnTick(unsigned long long deltaTime);

  void OnRender();

  JO_API void SpawnActorInternal(Actor* actor, unsigned int actorGroup = 0xffffffff);

  ActorContainer* GetActorContainer(unsigned int group);

  CollisionContainer* GetCollisionContainer(unsigned int group);

  bool isDebugRender_;

  bool useCameraPosition_;

  Vector cameraPosition_;

  LINK_ITEM* actorGroupHead_;
  LINK_ITEM* actorGroupTail_;

  LINK_ITEM* collisionGroupHead_;
  LINK_ITEM* collisionGroupTail_;
};