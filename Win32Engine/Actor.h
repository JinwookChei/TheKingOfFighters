#pragma once

#include "ActorComponent.h"

class ImageRenderer;
class CollisionComponent;

enum ActorGroupEngineType {
  ActorGroupEngineType_Invalid = -1,
  ActorGroupEngineType_MOUSE,
  ActorGroupEngineType_UI,
  ActorGroupEngineType_Effect,
  ActorGroupEngineType_None,
  ActorGroupEngineType_BackGround,
  ActorGroupEngineType_MAX
};

struct ActorSetDebugParameter {
  bool on_ = false;
  float linethickness_ = 1.0f;
  Color8Bit color_ = Color8Bit::Black;
};

class Actor {
 private:
  friend class GameEngine;
  friend class Level;
  friend class Player;
  friend class UI;

 public:
  JO_API Actor();

  JO_API virtual ~Actor() = 0;

  JO_API virtual void BeginPlay();

  JO_API virtual void Tick(unsigned long long curTick);

  // JO_API wchar_t GetRenderCharacter() const;

  JO_API void SetPosition(const Vector& newPosition);

  JO_API const Vector& GetPosition() const;

  JO_API void SetDebugParameter(const ActorSetDebugParameter& parameter);

  JO_API void SetUseCameraposition(bool use);

  JO_API bool UseCameraposition() const;

  JO_API void SetActive(bool isActive);

  JO_API bool IsActive() const;

  JO_API void SetDestroy();

  JO_API bool IsDestroy() const;

  JO_API int GetCollisionTag() const;

  JO_API unsigned int GetActorGroup() const;

  JO_API ImageRenderer* CreateImageRenderFIFO();

  JO_API ImageRenderer* CreateImageRenderLIFO();

  JO_API CollisionComponent* CreateCollision(unsigned int collisionGroup);

  JO_API bool IsUI() const;

  JO_API bool IsPlayer() const;

  template <typename ComponentType>
  ComponentType* CreateComponent() {
    ComponentType* newComponent = new ComponentType;
    ActorComponent* actorComponent = newComponent;
    actorComponent->SetOwner(this);
    actorComponent->SetActive(true);
    actorComponent->OnBeginPlay();

    LinkToLinkedListFIFO(&componentHead_, &componentTail_, actorComponent->GetActorLink());

    return newComponent;
  }

  JO_API Level* GetLevel();

 protected:
  void OnBeginPlay();

  void OnTick(unsigned long long curTick);

  JO_API void SetCollisionTag(int newCollisionTag);

  JO_API void SetActorGroup(unsigned int actorGroup);

  JO_API virtual void Render(IRenderTexture* renderTexture) const;

 private:
  void OnRender(IRenderTexture* renderTexture) const;

  void OnDebugRender(IRenderTexture* renderTexture) const;

  void OnCollisionRender(IRenderTexture* renderTexture) const;

  void SetLevel(Level* level);

  LINK_ITEM* GetLink();

  ActorSetDebugParameter debugParameter = {.on_ = false};

  Level* currentLevel_;

  LINK_ITEM* renderHead_;
  LINK_ITEM* renderTail_;

  LINK_ITEM* collisionHead_;
  LINK_ITEM* collisionTail_;

  LINK_ITEM* componentHead_;
  LINK_ITEM* componentTail_;

  Vector position_;

  LINK_ITEM link_;

  bool isActive_;

  bool isDestroy_;

  bool useCameraPosition_;

  bool isUI_;

  bool isPlayer_;

  int collisionTag_;

  unsigned int actorGroup_;
};