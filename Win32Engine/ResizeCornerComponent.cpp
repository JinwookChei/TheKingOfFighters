#include "stdafx.h"
#include "UIComponent.h"
#include "ResizeCornerComponent.h"

//ResizeCornerComponent::ResizeCornerComponent() {
//}
//
//ResizeCornerComponent::~ResizeCornerComponent() {
//}
//
//void ResizeCornerComponent::BeginPlay() {
//  //SetScale({10.0f, 10.0f});
//  //SetPosition({100.0f,100.0f});
//  UI* owner = GetOwner();
//
//  SetScale(owner->GetScale());
//  SetPosition({owner->GetScale().HalfX(), owner->GetScale().HalfY()});
//}
//
//void ResizeCornerComponent::Tick(unsigned long long curTick) {
//}
//
//void ResizeCornerComponent::ClickDownEvent() {
//}
//
//void ResizeCornerComponent::ClickExit() {
//}
//
//void ResizeCornerComponent::Render(IRenderTexture* renderTexture) {
//  if (nullptr == renderTexture) {
//    return;
//  }
//
//  UI* owner = GetOwner();
//  if (nullptr == owner) {
//    return;
//  }
//  
//  const Transform& transform = GetTransform();
//  renderTexture->DrawRectagle(transform.GetScale(), Color8Bit::RedAlpha, 2.0f);
//  //renderTexture->DrawRectagle({10.0f, 10.0f}, Color8Bit::RedAlpha, 5.0f);
//}
