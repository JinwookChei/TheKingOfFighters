#pragma once

class UI;
class UIComponent {
  friend class UI;

 public:
  JO_API UIComponent();

  JO_API virtual ~UIComponent() = 0;

  JO_API virtual UI* GetOwner() const;

  JO_API virtual void BeginPlay();

  JO_API virtual void Tick(unsigned long long curTick);

  JO_API virtual void ClickDownEvent();

  JO_API void SetPosition(const Vector& position);

  JO_API void SetScale(const Vector& scale);

  JO_API const Transform& GetTransform() const;

 protected:
  JO_API virtual void Render(struct IRenderTexture* renderTexture) = 0;

 private:
  void OnRender(struct IRenderTexture* renderTexture);

  void SetOwner(class UI* owner);

  LINK_ITEM* GetLinkUI();

  UI* owner_;

  float angle_;

  Transform transform_;

  LINK_ITEM linkUI_;
};