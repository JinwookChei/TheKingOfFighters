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
  JO_API ActorComponent();

  JO_API virtual ~ActorComponent();

  JO_API Actor* GetOwner() const;

  JO_API virtual void BeginPlay();

  JO_API virtual void Tick(unsigned long long curTick);

  JO_API virtual bool IsActive() const;

  JO_API void SetActive(bool active);

  JO_API void SetDebugParameter(const ActorComponentSetDebugParameter& parameter);

  JO_API const ActorComponentSetDebugParameter& GetDebugParameter() const;

 protected:
  ActorComponentSetDebugParameter parameter_ = {.on_ = false};

  JO_API virtual void DebugRender([[maybe_unused]] struct IRenderTexture* renderTexture);

  JO_API virtual void CollisionRender(IRenderTexture* renderTexture);

 private:
  JO_API void OnBeginPlay();

  void OnTick(unsigned long long curTick);

  JO_API void SetOwner(Actor* owner);

  JO_API LINK_ITEM* GetActorLink();

  bool isActive_;

  Actor* owner_;

  LINK_ITEM actorLink_;
};