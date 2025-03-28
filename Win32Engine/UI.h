#pragma once

#include "Actor.h"

class UI final
    : public Actor {
  friend class Mouse;

 public:
  JO_API UI();

  JO_API ~UI();

  JO_API void BeginPlay() override;

  JO_API void Tick(unsigned long long curTick) override;

  JO_API void SetScale(const Vector& scale);

  JO_API const Vector& GetScale() const;

  JO_API void SetOriginColor(const Color8Bit& color);

  JO_API void ClearColor(const Color8Bit& color) const;

  JO_API void MakeCollision();

  JO_API void SetUseMousePosition(bool isOn);

  JO_API void ChangeClearColor_(bool isOn);

  JO_API const Color8Bit& GetCurrentColor() const;

  JO_API ImageRenderer* GetImageRenderer() const;

  template <typename ComponentType>
  ComponentType* CreateUIComponent() {
    ComponentType* newComponent = new ComponentType;
    CreateUIComponentInternal(newComponent);
    return newComponent;
  }

  JO_API bool Save(std::string_view filePath);

  JO_API bool IsClick() const;

 protected:
  JO_API void Render(IRenderTexture* renderTexture) const override;

 private:
  JO_API void CreateUIComponentInternal(class UIComponent* newComponent);

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