#include "stdafx.h"
#include "TextComponent.h"
#include "UI.h"

TextComponent::TextComponent()
    : /*localPosition_({0.0f, 0.0f}),*/
      textColor_(Color8Bit::Black),
      font_(L"±Ã¼­"),
      text_(L""),
      fontSize_(10) {
}

TextComponent::~TextComponent() {
}

void TextComponent::BeginPlay() {
}

void TextComponent::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  renderTexture->Text(font_, text_, fontSize_, {0.0f, 0.0f} /*localPosition_*/, textColor_);
}

// void TextComponent::SetLocalPosition(const Vector& localPosition) {
//   localPosition_ = localPosition;
// }

void TextComponent::SetText(const wchar_t* text, unsigned __int64 size, const Color8Bit& color) {

  text_ = text;
  if (nullptr == text_) {
    text_ = L"";
  }
  fontSize_ = size;
  textColor_ = color;
}

void TextComponent::SetFont(const wchar_t* font) {
  font_ = font;
  if (nullptr == font_) {
    font_ = L"±Ã¼­";
  }
}
