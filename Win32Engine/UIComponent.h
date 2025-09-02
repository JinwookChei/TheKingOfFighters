#pragma once

class UI;
class UIComponent {
  friend class UI;

 public:
  ENGINE_API UIComponent();

  ENGINE_API virtual ~UIComponent() = 0;

  ENGINE_API virtual UI* GetOwner() const;

  ENGINE_API virtual void BeginPlay();

  ENGINE_API virtual void Tick(unsigned long long curTick);
  
  ENGINE_API bool EnableTick() const;

  ENGINE_API void SetEnableTick(bool enableTick);

  ENGINE_API bool EnableRender() const;

  ENGINE_API void SetEnableRender(bool enableRender);


  ENGINE_API virtual void ClickDownEvent();

  ENGINE_API virtual void ClickExit();
  
  ENGINE_API bool IsMouseClick();

  ENGINE_API void SetPosition(const Vector& position);

  ENGINE_API void AddPosition(const Vector& addMove);

  ENGINE_API Vector GetPosition() const;

  ENGINE_API void SetScale(const Vector& scale);

  ENGINE_API Vector GetScale() const;

  ENGINE_API const Transform& GetTransform() const;

  ENGINE_API bool GetEnableCollision();

  ENGINE_API void EnableCollision(bool isOn);


 protected:
  ENGINE_API virtual void Render(struct IRenderTexture* renderTexture) = 0;

  ENGINE_API virtual void PostRender();

 private:
  void OnRender(struct IRenderTexture* renderTexture);

  void OnClickDownEvent();

  void OnClickExit();

  void SetOwner(class UI* owner);

  LINK_ITEM* GetLinkUI();

  UI* owner_;

  bool enableTick_;

  bool enableRender_;

  float angle_;

  bool isMouseClick_;

  Transform transform_;

  LINK_ITEM linkUI_;

  bool enableCollision_; 

  
};