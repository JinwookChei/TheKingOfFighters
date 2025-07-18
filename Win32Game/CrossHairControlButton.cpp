#include "stdafx.h"
#include "CrossHairControlButton.h"
#include "CrossHair.h"

CrossHairControlButton::CrossHairControlButton()
    : crossHair_(nullptr),
      controlType_(CrossHairControlType_None) {
}

CrossHairControlButton::~CrossHairControlButton() {
}

void CrossHairControlButton::BeginPlay() {
}

void CrossHairControlButton::Tick(unsigned long long curTick) {
}

void CrossHairControlButton::ClickDownEvent() {
  switch (controlType_) {
    case CrossHairControlType_PlusRow:
      crossHair_->PlusRowOffSet();
      break;
    case CrossHairControlType_SuperPlusRow:
      for (int i = 0; i < 10; ++i) {
        crossHair_->PlusRowOffSet();
      }
      break;
    case CrossHairControlType_MinusRow:
      crossHair_->MinusRowOffSet();
      break;
    case CrossHairControlType_SuperMinusRow:
      for (int i = 0; i < 10; ++i) {
        crossHair_->MinusRowOffSet();
      }
      break;
    case CrossHairControlType_PlusCol1:
      crossHair_->PlusColOffSet1();
      break;
    case CrossHairControlType_SuperPlusCol1:
      for (int i = 0; i < 10; ++i) {
        crossHair_->PlusColOffSet1();
      }
      break;
    case CrossHairControlType_MinusCol1:
      crossHair_->MinusColOffSet1();
      break;
    case CrossHairControlType_SuperMinusCol1:
      for (int i = 0; i < 10; ++i) {
        crossHair_->MinusColOffSet1();
      }
      break;
    case CrossHairControlType_PlusCol2:
      crossHair_->PlusColOffSet2();
      break;
    case CrossHairControlType_SuperPlusCol2:
      for (int i = 0; i < 10; ++i) {
        crossHair_->PlusColOffSet2();
      }
      break;
    case CrossHairControlType_MinusCol2:
      crossHair_->MinusColOffSet2();
      break;
    case CrossHairControlType_SuperMinusCol2:
      for (int i = 0; i < 10; ++i) {
        crossHair_->MinusColOffSet2();
      }
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
  // const Transform transform = GetTransform();
  // renderTexture->DrawRectagle(transform.GetScale(), Color8Bit::RedAlpha, 10.0f);
}
