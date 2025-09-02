#pragma once

#include "SceneComponent.h"

enum CollisionGroupEngineType {
  CollisionGroupEngineType_Invalid = -1,
  CollisionGroupEngineType_UI,
  CollisionGroupEngineType_MOUSE,
  CollisionGroupEngineType_HitBoxTop,
  CollisionGroupEngineType_HitBoxBottom,
  CollisionGroupEngineType_AttackBox,
  CollisionGroupEngineType_PushBox,
  CollisionGroupEngineType_GrabBox,
  CollisionGroupEngineType_None,
  CollisionGroupEngineType_MAX
};

enum CollisionType {
  CollisionType_Point,
  CollisionType_Circle,
  CollisionType_Rect,
  CollisionType_Max
};

struct CollisionCheckParameter {
  unsigned int targetGroup = CollisionGroupEngineType::CollisionGroupEngineType_Invalid;
  CollisionType targetCollisionType = CollisionType::CollisionType_Point;
  CollisionType myCollisionType = CollisionType::CollisionType_Rect;
};

class CollisionComponent final
    : public SceneComponent {
  friend class Actor;
  friend class Level;

 public:
  ENGINE_API CollisionComponent();

  ENGINE_API ~CollisionComponent();

  ENGINE_API bool Collision(const CollisionCheckParameter& parameter, CollisionComponent** targetCollision = nullptr);

  ENGINE_API void ChangeCollisionGroup(unsigned int group);

  ENGINE_API int GetCollisionGroup() const;

  ENGINE_API CollisionInfo GetCollisionInfo() const;

  static bool CollisionPointToRect(const CollisionInfo& left, const CollisionInfo& right);

  ENGINE_API bool HasHit();

  ENGINE_API void MarkAsHit();

  ENGINE_API void ResetHit();

 protected:

  void CollisionRender(IRenderTexture* renderTexture) override;

  LINK_ITEM* GetCollisionActorLink();

  LINK_ITEM* GetCollisionLevelLink();

  void SetSearchHandle(void* searchHandle);

  void* GetSearchHandle();

 private:
  unsigned int collisionGroup_;

  void* searchHandle_;

  LINK_ITEM collisionActorLink_;
  LINK_ITEM collisionLevelLink_;

  bool hasHit_;
};