#include "stdafx.h"
#include "BlackBoard.h"

BlackBoard::BlackBoard()
    : pRender_(nullptr) {
}

BlackBoard::~BlackBoard() {
}

void BlackBoard::BeginPlay() {
  pRender_ = CreateImageRenderFIFO();
  pRender_->SetImage(ImgManager::GetIntance()->GetImg(IMGKEY_BlackBoardImage));
  pRender_->SetImageRenderType(ImageRenderType::LeftTop);
  pRender_->SetLocalScale({2.4f, 3.7f});
  SetActive(false);
}

void BlackBoard::Tick(unsigned long long curTick) {
}

