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
  ENGINE_API Level();

  ENGINE_API virtual ~Level() = 0;

  ENGINE_API virtual void BeginPlay() = 0;

  ENGINE_API virtual void Tick(unsigned long long deltaTime) = 0;

  ENGINE_API void SetDebugRender(bool isOn);

  ENGINE_API bool GetDebugRender() const;

  ENGINE_API void SetCollisionRender(bool isOn);

  ENGINE_API bool GetCollisionRender() const;

  ENGINE_API Mouse* SpawnMouse();

  template <typename ActorType>
  ActorType* SpawnActor(unsigned int actorGroup = 0xffffffff) {
    ActorType* newActor = new ActorType;
    SpawnActorInternal(newActor, actorGroup);
    return newActor;
  }

  ENGINE_API void SetCameraPosition(const Vector& position);

  ENGINE_API void AddCameraPosition(const Vector& addPosition);

  ENGINE_API const Vector& GetCameraPosition() const;

  ENGINE_API bool UseCameraPostion() const;

  ENGINE_API void RegisterCollision(class CollisionComponent* newCollision, bool bFocus = false);

  ENGINE_API void UnRegisterCollision(class CollisionComponent* delCollision);

  ENGINE_API void RegisterActor(Actor* actor, bool bFocus = false);

  ENGINE_API void UnRegisterActor(Actor* actor);

  ENGINE_API bool GetCollisionGroup(unsigned int collisionGroup, LINK_ITEM** head, LINK_ITEM** tail);

 protected:
  ENGINE_API void SetUseCameraPosition(bool use);

 private:
  void OnBeginPlay();

  void OnTick(unsigned long long deltaTime);

  void OnRender();

  ENGINE_API void SpawnActorInternal(Actor* actor, unsigned int actorGroup = 0xffffffff);

  ActorContainer* GetActorContainer(unsigned int group);

  CollisionContainer* GetCollisionContainer(unsigned int group);

  bool isDebugRender_;

  bool isCollisionRender_;

  bool useCameraPosition_;

  Vector cameraPosition_;

  LINK_ITEM* actorGroupHead_;
  LINK_ITEM* actorGroupTail_;

  LINK_ITEM* collisionGroupHead_;
  LINK_ITEM* collisionGroupTail_;

  unsigned long long nextActorId_;
};