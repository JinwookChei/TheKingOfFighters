#include "stdafx.h"
#include "BlackBoard.h"

BlackBoard::BlackBoard()
    : pRender_(nullptr) {
}

BlackBoard::~BlackBoard() {
}

void BlackBoard::BeginPlay() {
  //pRender_ = CreateImageRenderFIFO();
  //pRender_->CreateAnimation(1, IMGKEY_BackGoundImage, 0, 7, 500, true, 0);

  //pRender_->SetImageRenderType(ImageRenderType::Center);
  //pRender_->ChangeAnimation(1);
  //pRender_->SetLocalScale({4.5f, 4.5f});
}

void BlackBoard::Tick(unsigned long long curTick) {
}
