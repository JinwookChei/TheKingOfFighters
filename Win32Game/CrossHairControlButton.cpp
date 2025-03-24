#include "stdafx.h"
#include "CrossHairControlButton.h"
#include "CrossHair.h"

CrossHairControlButton::CrossHairControlButton()
    : crossHair_(nullptr),
    controlType_(CrossHairControlType_None){
}

CrossHairControlButton::~CrossHairControlButton() {
}

void CrossHairControlButton::BeginPlay() {
  //UI* owner = GetOwner();

  //SetScale(owner->GetScale());
  //SetPosition({owner->GetScale().HalfX(), owner->GetScale().HalfY()});
}

void CrossHairControlButton::Tick(unsigned long long curTick) {
}

void CrossHairControlButton::ClickDownEvent() {

  switch (controlType_) {
    case CrossHairControlType_PlusRow:
      crossHair_->PlusRowOffSet();
      break;
    case CrossHairControlType_MinusRow:
      crossHair_->MinusRowOffSet();
      break;
    case CrossHairControlType_PlusCol:
      crossHair_->PlusColOffSet();
      break;
    case CrossHairControlType_MinusCol:
      crossHair_->MinusColOffSet();
      break;
    case CrossHairControlType_Reset:
      crossHair_->RowColReset();
      break;    
    default:
      break;
  }
}

void CrossHairControlButton::SetControlType(CrossHairControlType controlType) {
  controlType_ = controlType;
}

void CrossHairControlButton::SetCrossHair(CrossHair* crossHair) {
    crossHair_ = crossHair;
}

void CrossHairControlButton::Render(IRenderTexture* renderTexture) {
  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }
  //const Transform transform = GetTransform();
  //renderTexture->DrawRectagle(transform.GetScale(), Color8Bit::RedAlpha, 10.0f);
}
