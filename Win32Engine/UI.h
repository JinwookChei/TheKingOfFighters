#pragma once

#include "Actor.h"

class UI final
    : public Actor {
  friend class Mouse;

 public:
  ENGINE_API UI();

  ENGINE_API ~UI();

  ENGINE_API void BeginPlay() override;

  ENGINE_API void Tick(unsigned long long curTick) override;

  ENGINE_API void SetScale(const Vector& scale);

  ENGINE_API const Vector& GetScale() const;

  ENGINE_API void SetOriginColor(const Color8Bit& color);

  ENGINE_API void ClearColor(const Color8Bit& color) const;

  ENGINE_API void MakeCollision();

  ENGINE_API void SetUseMousePosition(bool isOn);

  ENGINE_API void ChangeClearColor_(bool isOn);

  ENGINE_API const Color8Bit& GetCurrentColor() const;

  ENGINE_API ImageRenderer* GetImageRenderer() const;

  ENGINE_API CollisionComponent* GetCollisionComponent() const;

  template <typename ComponentType>
  ComponentType* CreateUIComponent() {
    ComponentType* newComponent = new ComponentType;
    CreateUIComponentInternal(newComponent);
    return newComponent;
  }

  ENGINE_API bool Save(std::string_view filePath);

  ENGINE_API bool IsClick() const;

 protected:
  ENGINE_API void Render(IRenderTexture* renderTexture) const override;

 private:
  ENGINE_API void CreateUIComponentInternal(class UIComponent* newComponent);

  void OnClickUpEvent();

  void OnClickDownEvent();

  void OnHoverEvent();

  void OnMouseExit();

  bool isClick_;

  bool useMousePosition_;

  bool changeClearColor_;

  ImageRenderer* imageRenderer_;

  CollisionComponent* collision_;

  IRenderTexture* renderTexture_;

  Vector currentScale_;

  Vector prevMousePosition_;

  Color8Bit originColor_;

  mutable Color8Bit currentColor_;

  LINK_ITEM* componentHead_;
  
  LINK_ITEM* componentTail_;
};