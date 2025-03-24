#include "stdafx.h"
#include "CrossHair.h"

CrossHair::CrossHair()
    : rowOffSet(200.0f),
      colOffSet(-100.0f) {
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
  rowOffSet += 1.0f;
}

void CrossHair::MinusRowOffSet() {
  rowOffSet -= 1.0f;
}

void CrossHair::PlusColOffSet() {
  colOffSet += 1.0f;
}

void CrossHair::MinusColOffSet() {
  colOffSet -= 1.0f;
}

void CrossHair::RowColReset() {
  rowOffSet = 0.0f;
  colOffSet = 0.0f;
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
  renderTexture->DrawLine(Color8Bit::BlackAlpha, {colOffSet, -owner->GetScale().HalfY()}, {colOffSet, owner->GetScale().HalfY()}, 1.0f);
  renderTexture->DrawLine(Color8Bit::BlackAlpha, {-owner->GetScale().HalfX(), rowOffSet}, {owner->GetScale().HalfX(), rowOffSet}, 1.0f);
}
