#include "stdafx.h"
#include "Button.h"
#include "Player.h"

Button::Button()
    : image_(nullptr),
      player_(nullptr),
      dir_({0.0f, 0.0f}) {
}

Button::~Button() {
}

void Button::BeginPlay() {
  image_ = ImgManager::GetIntance()->GetImg(0);

  UI* owner = GetOwner();

  SetScale(owner->GetScale() * 0.5);
  SetPosition({owner->GetScale().HalfX(), owner->GetScale().HalfY()});
}

void Button::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture || nullptr == image_) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Transform& transform = GetTransform();

  renderTexture->Transparent(image_, 0, transform.GetScale(), Color8Bit::White);
  renderTexture->SetAlpha(1.0f, transform, true, owner->GetCurrentColor());

  renderTexture->DrawLine(Color8Bit::BlackAlpha, {0.0f, -owner->GetScale().HalfY()}, {0.0f, owner->GetScale().HalfY()}, 2.0f);
  renderTexture->DrawLine(Color8Bit::BlackAlpha, {-owner->GetScale().HalfX(), 0.0f}, {owner->GetScale().HalfX(), 0.0f}, 2.0f);
}

void Button::ClickDownEvent() {
  if (player_) {
  }
}

void Button::SetPlayer(Player* player) {
  player_ = player;
}

void Button::SetDir(const Vector& dir) {
  dir_ = dir;
}
