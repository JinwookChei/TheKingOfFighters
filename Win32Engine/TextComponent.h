#pragma once

#include "UIComponent.h"

class TextComponent final
    : public UIComponent {
 public:
  JO_API TextComponent();

  JO_API  ~TextComponent();

  void BeginPlay() override;

  void Render(struct IRenderTexture* renderTexture) override;

  //JO_API void SetLocalPosition(const Vector& localPosition);

  JO_API void SetText(const wchar_t* text, unsigned __int64 size, const Color8Bit& color);

  JO_API void SetFont(const wchar_t* font);

 private:
  //Vector localPosition_;

  Color8Bit textColor_;

  const wchar_t* font_;

  const wchar_t* text_;

  unsigned __int64 fontSize_;
};