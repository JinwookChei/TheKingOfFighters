#include "stdafx.h"
#include "Button.h"
#include "Player.h"

Button::Button()
    : capture_(false),
      image_(nullptr),
      player_(nullptr),
      dir_({0.0f, 0.0f}) {
}

Button::~Button() {
}

void Button::BeginPlay() {
  image_ = ImgManager::GetIntance()->GetImg(0);

  UI* owner = GetOwner();

  Vector scale = image_->GetScale();

  SetScale(scale);
  SetPosition({scale.HalfX(), scale.HalfY()});
}

void Button::PostRender() {
  if (false == capture_) {
    return;
  }
  capture_ = false;

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }
  Path cur("..\\ContentsResource\\Test.bmp");
  owner->Save(cur.GetPathString());
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

  //renderTexture->DrawLine(Color8Bit::BlackAlpha, {0.0f, -owner->GetScale().HalfY()}, {0.0f, owner->GetScale().HalfY()}, 2.0f);
  //renderTexture->DrawLine(Color8Bit::BlackAlpha, {-owner->GetScale().HalfX(), 0.0f}, {owner->GetScale().HalfX(), 0.0f}, 2.0f);
}

void Button::Tick(unsigned long long curTick) {
  if (false == IsMouseClick()) {
    return;
  }

  const Vector curMousePosition = GEngineCore->GetMousePosition();
  Vector moveDir = GEngineCore->GetMousePosition() - mousePosition_;

  AddPosition(moveDir);

  mousePosition_ = curMousePosition;
}

void Button::ClickDownEvent() {
  mousePosition_ = GEngineCore->GetMousePosition();

  capture_ = true;
}

void Button::SetPlayer(Player* player) {
  player_ = player;
}

void Button::SetDir(const Vector& dir) {
  dir_ = dir;
}
