#include "stdafx.h"
#include "ToolIori.h"

ToolIori::ToolIori()
    : pRender_(nullptr),
      imagePtrIndex_(0),
      imageIndex_ (0){
}

ToolIori::~ToolIori() {
}

void ToolIori::BeginPlay() {
}

void ToolIori::Tick(unsigned long long curTick) {
}

bool ToolIori::Initialize(Color8Bit TransparentColor, unsigned int imagePtrIndex, unsigned int imageIndex /*= 0*/) {
  /*Iori : Color8Bit{169, 139, 150, 0}*/

  imagePtrIndex_ = imagePtrIndex;
  imageIndex_ = imageIndex;

  IImage* pImg = ImgManager::GetIntance()->GetImg(imagePtrIndex_);
  if (nullptr == pImg) {
    return false;
  }

  pRender_ = CreateImageRender();
  pRender_->SetImage(pImg, imageIndex_);
  pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetTransparentColor(TransparentColor);
  pRender_->SetLocalScale({4.0f, 4.0f});

  return true;
}

unsigned int ToolIori::GetImagePtrIndex() const {
  return imagePtrIndex_;
}

void ToolIori::SetImagePtrIndex(unsigned int ptrIndex) {   
    imagePtrIndex_ = ptrIndex;
}

unsigned int ToolIori::GetImageIndex() const {
  return imageIndex_;
}

void ToolIori::SetImageIndex(unsigned int index) {
  imageIndex_ = index;
}
