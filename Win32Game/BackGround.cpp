#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
    : pRender_(nullptr) {
}

BackGround::~BackGround() {
}

void BackGround::BeginPlay() {
  pRender_ = CreateImageRenderFIFO();
  pRender_->CreateAnimation(1, IMGTYPE_BackGoundImage, 0, 7, 500, true, 0);
  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->ChangeAnimation(1);
  pRender_->SetLocalScale({4.5f, 4.5f});
}

void BackGround::Tick(unsigned long long curTick) {
}
