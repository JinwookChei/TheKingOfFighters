#pragma once

class Actor;
struct ActorComponentSetDebugParameter {
  bool on_ = false;
  bool withRectangle_ = false;
  bool withCircle_ = false;
  float linethickness_ = 1.0f;
  Color8Bit color_ = Color8Bit::Black;
};

class ActorComponent {
 private:
  friend class Actor;

 public:
  ENGINE_API ActorComponent();

  ENGINE_API virtual ~ActorComponent();

  ENGINE_API Actor* GetOwner() const;

  ENGINE_API virtual void BeginPlay();

  ENGINE_API virtual void Tick(unsigned long long deltaTick);

  ENGINE_API bool IsActive() const;

  ENGINE_API void SetActive(bool active);

  ENGINE_API void SetEnableTick(bool enable);

  ENGINE_API bool EnableTick() const;

  ENGINE_API void SetDebugParameter(const ActorComponentSetDebugParameter& parameter);

  ENGINE_API const ActorComponentSetDebugParameter& GetDebugParameter() const;

 protected:
  ActorComponentSetDebugParameter parameter_ = {.on_ = false};

  ENGINE_API virtual void DebugRender([[maybe_unused]] struct IRenderTexture* renderTexture);

  ENGINE_API virtual void CollisionRender(IRenderTexture* renderTexture);

 private:
  ENGINE_API void OnBeginPlay();

  void OnTick(unsigned long long curTick);

  ENGINE_API void SetOwner(Actor* owner);

  ENGINE_API LINK_ITEM* GetActorLink();

  bool isActive_;

  bool enableTick_;

  Actor* owner_;

  LINK_ITEM actorLink_;
};