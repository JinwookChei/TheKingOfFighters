#include "stdafx.h"
#include "CrossHair.h"

CrossHair::CrossHair()
    : rowOffSet_(200.0f),
      colOffSet1_(-100.0f),
      colOffSet2_(100.0f) {
}

CrossHair::~CrossHair() {
}

void CrossHair::BeginPlay() {
  UI* owner = GetOwner();

  SetScale(owner->GetScale());
  SetPosition({owner->GetScale().HalfX(), owner->GetScale().HalfY()});
}

void CrossHair::Tick(unsigned long long curTick) {
}

void CrossHair::ClickDownEvent() {
}

void CrossHair::PlusRowOffSet() {
  rowOffSet_ += 1.0f;
}

void CrossHair::MinusRowOffSet() {
  rowOffSet_ -= 1.0f;
}

void CrossHair::PlusColOffSet1() {
  colOffSet1_ += 1.0f;
}

void CrossHair::MinusColOffSet1() {
  colOffSet1_ -= 1.0f;
}

void CrossHair::PlusColOffSet2() {
  colOffSet2_ += 1.0f;
}

void CrossHair::MinusColOffSet2() {
  colOffSet2_ -= 1.0f;
}

void CrossHair::RowColReset() {
  rowOffSet_ = 0.0f;
  colOffSet1_ = 0.0f;
  colOffSet2_ = 0.0f;
}

void CrossHair::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Transform& transform = GetTransform();
  renderTexture->DrawRectagle(transform.GetScale(), Color8Bit::BlackAlpha, 2.0f);
  renderTexture->DrawLine(Color8Bit::BlackAlpha, {colOffSet1_, -owner->GetScale().HalfY()}, {colOffSet1_, owner->GetScale().HalfY()}, 1.0f);
  renderTexture->DrawLine(Color8Bit::BlackAlpha, {colOffSet2_, -owner->GetScale().HalfY()}, {colOffSet2_, owner->GetScale().HalfY()}, 1.0f);
  renderTexture->DrawLine(Color8Bit::BlackAlpha, {-owner->GetScale().HalfX(), rowOffSet_}, {owner->GetScale().HalfX(), rowOffSet_}, 1.0f);

}

