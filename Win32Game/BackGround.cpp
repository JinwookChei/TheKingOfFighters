#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
    : pRender_(nullptr) {
}

BackGround::~BackGround() {
}

void BackGround::BeginPlay() {
  pRender_ = CreateImageRender();
  pRender_->CreateAnimation(1, 2, 0, 7, 500, true);

  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->ChangeAnimation(1);
  pRender_->SetLocalScale({2.6f, 4.1f});
}

void BackGround::Tick(unsigned long long curTick) {
}
