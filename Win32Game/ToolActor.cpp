#include "stdafx.h"
#include "CollisionBox.h"
#include "ImageController.h"
#include "ToolActor.h"

ToolActor::ToolActor()
    : pRender_(nullptr),
      hitBoxTop_(nullptr),
      hitBoxBottom_(nullptr),
      attackBox_(nullptr),
      pushBox_(nullptr),
      grabBox_(nullptr) {
}

ToolActor::~ToolActor() {
}

void ToolActor::BeginPlay() {
  IImage* pImage = ImgManager::GetIntance()->GetImg(1);
  Color8Bit transColor;
  if (false == pImage->GetPixel({0.0f, 0.0f}, &transColor)) {
    return;
  }

  pRender_ = CreateImageRenderFIFO();
  //pRender_->SetImageRenderType(ImageRenderType::Center);
  pRender_->SetImageRenderType(ImageRenderType::Bottom);

  pRender_->SetTransparentColor(transColor);  //
  pRender_->SetLocalScale({4.2f, 4.2f});
  unsigned int imageIndex = pRender_->GetImageIndex();
  if (nullptr != pImage) {
    pRender_->SetImage(pImage, imageIndex);
  }

  // COLLISION
  hitBoxTop_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxTop);
  hitBoxBottom_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_HitBoxBottom);
  attackBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_AttackBox);
  pushBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_PushBox);
  grabBox_ = CreateCollision(CollisionGroupEngineType::CollisionGroupEngineType_GrabBox);

  SetDebugParameter({.on_ = true, .linethickness_ = 2.0f});
  pRender_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Cyan});
  hitBoxTop_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  hitBoxBottom_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Blue});
  attackBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Red});
  pushBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::White});
  grabBox_->SetDebugParameter({.on_ = true, .withRectangle_ = true, .linethickness_ = 2.0f, .color_ = Color8Bit::Yellow});
}

void ToolActor::Tick(unsigned long long curTick) {
  CollisionUpdate();
}

bool ToolActor::Initialize(UI* ui) {
  bindUI_ = ui;
  if (nullptr == bindUI_) {
    return false;
  }

  Vector uiPosition = bindUI_->GetPosition();
  SetPosition({uiPosition.X, uiPosition.Y + 200.0f});

  return true;
}

ImageRenderer* ToolActor::GetImageRenderer() const {
  return pRender_;
}

IImage* ToolActor::GetImage() const {
  if (nullptr == pRender_) {
    return nullptr;
  }

  IImage* pImage = pRender_->GetImage();
  if (nullptr == pImage) {
    return nullptr;
  }

  return pImage;
}

unsigned int ToolActor::GetImageIndex() const {
  if (nullptr == pRender_) {
    return -1;
  }

  return pRender_->GetImageIndex();
}

void ToolActor::ChangeImage(unsigned int index) {
  IImage* pImage = pRender_->GetImage();

  if (nullptr == pImage) {
    return;
  }

  if (index > pImage->GetImageCount() - 1) {
    index = 0;
  }

  pRender_->SetImage(pImage, index);
}

void ToolActor::AddPositionOffSet(const Vector& offSet) {
  unsigned int imageIndex = pRender_->GetImageIndex();
  IImage* pImage = pRender_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  pFileImage->AddImagePositionOffSet(imageIndex, offSet);
}

void ToolActor::ResetPostionOffset() {
  unsigned int imageIndex = pRender_->GetImageIndex();
  IImage* pImage = pRender_->GetImage();

  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }
  IFileImage* pFileImage = (IFileImage*)pImage;

  const Vector& offSet = pFileImage->GetImagePositionOffSet(imageIndex);
  pFileImage->AddImagePositionOffSet(imageIndex, -offSet);
}

CollisionComponent* ToolActor::GetCollisionBox(CollisionBoxType boxType) {
  switch (boxType) {
    case CBT_HitBoxTop:
      return hitBoxTop_;
      break;
    case CBT_HitBoxBottom:
      return hitBoxBottom_;
      break;
    case CBT_AttackBox:
      return attackBox_;
      break;
    case CBT_PushBox:
      return pushBox_;
      break;
    case CBT_GrabBox:
      return grabBox_;
      break;
    default:
      return nullptr;
      break;
  }
}

void ToolActor::CollisionUpdate() {
  if (nullptr == hitBoxTop_ || nullptr == hitBoxBottom_ || nullptr == attackBox_ || nullptr == pushBox_ || nullptr == grabBox_) {
    return;
  }

  unsigned int imageIndex = pRender_->GetImageIndex();
  IImage* pImage = pRender_->GetImage();
  if (nullptr == pImage || true == pImage->IsRenderTexture()) {
    return;
  }

  IFileImage* pFileImage = (IFileImage*)pImage;
  CollisionInfo* pCollisionInfo;

  // Vector actorPosition = GetPosition();
  // Vector imagePosition = pFileImage->RenderTransform(imageIndex).GetPosition();
  // Vector imageScale = pFileImage->GetScale(imageIndex);

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_HitBoxTop, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      hitBoxTop_->SetActive(true);
      // Vector newPosition = {0.0f, 0.0f};
      //  hitBoxTop_->SetPosition(newPosition);
      hitBoxTop_->SetPosition(pCollisionInfo->position_);
      hitBoxTop_->SetScale(pCollisionInfo->scale_);
    } else {
      hitBoxTop_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_HitBoxBottom, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      hitBoxBottom_->SetActive(true);
      hitBoxBottom_->SetPosition(pCollisionInfo->position_);
      hitBoxBottom_->SetScale(pCollisionInfo->scale_);
    } else {
      hitBoxBottom_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_AttackBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      attackBox_->SetActive(true);
      attackBox_->SetPosition(pCollisionInfo->position_);
      attackBox_->SetScale(pCollisionInfo->scale_);
    } else {
      attackBox_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_PushBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      pushBox_->SetActive(true);
      pushBox_->SetPosition(pCollisionInfo->position_);
      pushBox_->SetScale(pCollisionInfo->scale_);
    } else {
      pushBox_->SetActive(false);
    }
  }

  if (true == pFileImage->GetCollisionBoxInfo(imageIndex, CollisionBoxType::CBT_GrabBox, &pCollisionInfo)) {
    if (true == pCollisionInfo->hasCollision_) {
      grabBox_->SetActive(true);
      grabBox_->SetPosition(pCollisionInfo->position_);
      grabBox_->SetScale(pCollisionInfo->scale_);
    } else {
      grabBox_->SetActive(false);
    }
  }
}
