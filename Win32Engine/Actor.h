#pragma once

#include "ActorComponent.h"

class ImageRenderer;
class CollisionComponent;

enum ActorGroupEngineType {
  ActorGroupEngineType_Invalid = -1,
  ActorGroupEngineType_MOUSE,
  ActorGroupEngineType_Screen,
  ActorGroupEngineType_UI,
  ActorGroupEngineType_Effect,
  ActorGroupEngineType_Projectile,
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
  ENGINE_API Actor();

  ENGINE_API virtual ~Actor() = 0;

  ENGINE_API virtual void BeginPlay();

  ENGINE_API virtual void Tick(unsigned long long curTick);  

  ENGINE_API void SetPosition(const Vector& newPosition);

  ENGINE_API const Vector& GetPosition() const;

  ENGINE_API void SetDebugParameter(const ActorSetDebugParameter& parameter);

  ENGINE_API void SetUseCameraposition(bool use);

  ENGINE_API bool UseCameraposition() const;

  ENGINE_API void SetActive(bool isActive);

  ENGINE_API bool IsActive() const;

  ENGINE_API void SetEnableTick(bool enable);

  ENGINE_API bool EnableTick() const;

  ENGINE_API void SetDestroy();

  ENGINE_API bool IsDestroy() const;

  ENGINE_API int GetCollisionTag() const;

  ENGINE_API unsigned int GetActorGroup() const;

  ENGINE_API ImageRenderer* CreateImageRenderFIFO();

  ENGINE_API ImageRenderer* CreateImageRenderLIFO();

  ENGINE_API CollisionComponent* CreateCollision(unsigned int collisionGroup);

  ENGINE_API bool IsUI() const;

  ENGINE_API bool IsPlayer() const;

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

  ENGINE_API Level* GetLevel();

  ENGINE_API unsigned long long ActorId();

 protected:
  void OnBeginPlay();

  void OnTick(unsigned long long curTick);

  ENGINE_API void SetCollisionTag(int newCollisionTag);

  ENGINE_API void SetActorGroup(unsigned int actorGroup);

  ENGINE_API virtual void Render(IRenderTexture* renderTexture) const;

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

  bool isActive_;       // 랜더도 안보이게 됨.
   
  bool enableTick_;     // 틱만 설정.

  bool isDestroy_;

  bool useCameraPosition_;

  bool isUI_;

  bool isPlayer_;

  int collisionTag_;

  unsigned int actorGroup_;

  unsigned long long actorId_;
};