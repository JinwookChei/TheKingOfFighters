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

  JO_API virtual void ClickExit();
  
  JO_API bool IsMouseClick();

  JO_API void SetPosition(const Vector& position);

  JO_API void AddPosition(const Vector& addMove);

  JO_API Vector GetPosition() const;

  JO_API void SetScale(const Vector& scale);

  JO_API Vector GetScale() const;

  JO_API const Transform& GetTransform() const;

  JO_API bool GetEnableCollision();

  JO_API void EnableCollision(bool isOn);

 protected:
  JO_API virtual void Render(struct IRenderTexture* renderTexture) = 0;

  JO_API virtual void PostRender();

 private:
  void OnRender(struct IRenderTexture* renderTexture);

  void OnClickDownEvent();

  void OnClickExit();

  void SetOwner(class UI* owner);

  LINK_ITEM* GetLinkUI();

  UI* owner_;

  float angle_;

  bool isMouseClick_;

  Transform transform_;

  LINK_ITEM linkUI_;

  bool enableCollision_; 

  
};