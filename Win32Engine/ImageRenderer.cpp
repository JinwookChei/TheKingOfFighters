#include "stdafx.h"
#include "ImageRenderer.h"

unsigned int AnimationInfo::Update(unsigned long long curTick) {
  if (false == loop_ && true == isEnd_) {
    return indices_[curFrame_];
  }

  isEnd_ = false;
  curTime_ -= curTick;
  if (curTime_ <= 0) {
    curTime_ = times_[curFrame_];

    ++curFrame_;

    if (1 == indices_.size()) {
      isEnd_ = true;
    }

    if (false == loop_ && indices_.size() <= curFrame_) {
      isEnd_ = true;
    }
  }

  if (indices_.size() <= curFrame_) {
    if (1 < indices_.size()) {
      isEnd_ = true;
    }
    if (true == loop_) {
      curFrame_ = 0;
    } else {
      curFrame_ = indices_.size() - 1;
    }
  }

  unsigned int index = indices_[curFrame_];

  return index;
}

ImageRenderer::ImageRenderer()
    : image_(nullptr),
      imageIndex_(0),
      imageRenderType_(ImageRenderType::Center),
      sceneLink_({nullptr, nullptr, this}),
      renderActorLink_({nullptr, nullptr, this}),
      alpha_(1.0f),
      angle_(0.0f),
      transparentColor_(Color8Bit::White),
      isAlpha_(false),
      pCurAnimation_(nullptr) {
  animations_.Initialize(8, 8);
}

ImageRenderer::~ImageRenderer() {
  if (nullptr != image_) {
    image_->Release();
    image_ = nullptr;
  }

  for (HashTableIterator iter = animations_.begin(); iter != animations_.end();) {
    AnimationInfo* pDel = (AnimationInfo*)*iter;

    iter = animations_.erase(iter);

    if (nullptr != pDel->image_) {
      pDel->image_->Release();
    }

    delete pDel;
  }
  animations_.Cleanup();
}

void ImageRenderer::BeginPlay() {
}

void ImageRenderer::Tick(unsigned long long curTick) {
  if (nullptr != pCurAnimation_) {
    if (nullptr != image_) {
      image_->Release();
      image_ = nullptr;
    }

    image_ = pCurAnimation_->image_;
    imageIndex_ = pCurAnimation_->Update(curTick);

    if (nullptr != image_) {
      image_->AddRef();
      SetScale(image_->GetScale(imageIndex_));
    }
  }
}

void ImageRenderer::SetImage(IImage* image, unsigned int index /*= 0*/) {
  if (nullptr != image_) {
    image_->Release();
    image_ = nullptr;
  }

  image_ = image;
  imageIndex_ = index;

  if (nullptr != image_) {
    image_->AddRef();

    SetScale(image_->GetScale(index));
  }
}

IImage* ImageRenderer::GetImage() const {
  return image_;
}

unsigned int ImageRenderer::GetImageIndex() const {
  return imageIndex_;
}

void ImageRenderer::SetAngle(float angle) {
  angle_ = angle;
}

float ImageRenderer::GetAngle() const {
  return angle_;
}

void ImageRenderer::SetAlpha(float alpha) {
  isAlpha_ = true;
  alpha_ = alpha;
}

void ImageRenderer::SetTransparentColor(const Color8Bit& color) {
  isAlpha_ = false;
  transparentColor_ = color;
}

void ImageRenderer::SetImageRenderType(ImageRenderType newType) {
  imageRenderType_ = newType;
}

void ImageRenderer::Render(IRenderTexture* renderTexture) {
  if (nullptr == image_ || nullptr == renderTexture) {
    return;
  }

  Transform renderTransform = GetTransform();
  switch (imageRenderType_) {
    case ImageRenderType::Left:
      renderTransform.AddPostion({renderTransform.GetScale().HalfX(), 0.0f});
      break;
    case ImageRenderType::Right:
      renderTransform.AddPostion({-renderTransform.GetScale().HalfX(), 0.0f});
      break;
    case ImageRenderType::Top:
      renderTransform.AddPostion({0.0f, renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::Bottom:
      renderTransform.AddPostion({0.0f, -renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::LeftTop:
      renderTransform.AddPostion({renderTransform.GetScale().HalfX(), renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::LeftBottom:
      renderTransform.AddPostion({renderTransform.GetScale().HalfX(), -renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::RightTop:
      renderTransform.AddPostion({-renderTransform.GetScale().HalfX(), renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::RightBottom:
      renderTransform.AddPostion({-renderTransform.GetScale().HalfX(), -renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::Center:
    default:
      break;
  }

  // ImagePosition OffSet 적용.
  if (false == image_->IsRenderTexture()) {
    IFileImage* fileImage = (IFileImage*)image_;
    const Vector& imageOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
    renderTransform.AddPostion(imageOffSet);
  }

  GGraphicDevice->RenderImgStart(renderTransform, angle_, renderTexture);

  if (isAlpha_) {
    renderTexture->AlphaBlend(image_, imageIndex_, renderTransform.GetScale(), alpha_);
  } else {
    renderTexture->Transparent(image_, imageIndex_, renderTransform.GetScale(), transparentColor_);
  }

  // 나중에 디버깅 모드로 무언가 그리기 모드를 켰을경우 이곳에서 그리기 작업
  // GGraphicDevice->DrawRectagle({100.0f, 100.0f}, Color8Bit::RedAlpha, 10.0f);

  GGraphicDevice->RenderImgEnd(renderTexture);
}

LINK_ITEM* ImageRenderer::GetSceneLink() {
  return &sceneLink_;
}

LINK_ITEM* ImageRenderer::GetRenderActorLink() {
  return &renderActorLink_;
}

bool ImageRenderer::CreateAnimation(unsigned long long animationTag, unsigned long long imageIndex, unsigned int startIndex, unsigned int endIndex, unsigned long long interval, bool loop) {
  std::vector<unsigned int> indices;

  int size = (int)(endIndex - startIndex);
  if (size < 0) {
    return false;
  }

  indices.reserve(size);

  for (unsigned int n = startIndex; n <= endIndex; ++n) {
    indices.push_back(n);
  }

  return CreateAnimation(animationTag, imageIndex, indices, interval, loop);
}

bool ImageRenderer::CreateAnimation(unsigned long long animationTag, unsigned long long imageIndex, const std::vector<unsigned int>& indices, unsigned long long interval, bool loop) {
  std::vector<unsigned long long> intervals;
  intervals.reserve(indices.size());

  for (size_t n = 0; n < indices.size(); ++n) {
    intervals.push_back(interval);
  }

  return CreateAnimation(animationTag, imageIndex, indices, intervals, loop);
}

bool ImageRenderer::CreateAnimation(unsigned long long animationTag, unsigned long long imageIndex, const std::vector<unsigned int>& indices, const std::vector<unsigned long long> intervals, bool loop) {
  AnimationInfo* pFind = nullptr;
  if (0 != animations_.Select((void**)&pFind, 1, &animationTag, 8)) {
    return false;
  }

  IImage* pImg = ImgManager::GetIntance()->GetImg(imageIndex);
  if (nullptr == pImg) {
    return false;
  }

  pImg->AddRef();

  AnimationInfo* pNew = new AnimationInfo;
  pNew->image_ = pImg;
  pNew->animationTag_ = animationTag;
  pNew->curFrame_ = 0;
  pNew->curTime_ = 0;
  pNew->loop_ = loop;
  pNew->times_ = intervals;
  pNew->indices_ = indices;

  pNew->searchHandle_ = animations_.Insert(pNew, &animationTag, 8);

  return nullptr != pNew->searchHandle_;
}

bool ImageRenderer::ChangeAnimation(unsigned long long animationTag, int startFrame, unsigned long long time) {
  if (nullptr != pCurAnimation_ && false == pCurAnimation_->isEnd_ && false == pCurAnimation_->loop_) {
    return false;
  }

  AnimationInfo* pFind = nullptr;
  if (0 == animations_.Select((void**)&pFind, 1, &animationTag, 8)) {
    return false;
  }

  if (nullptr != pCurAnimation_ && pCurAnimation_->animationTag_ == pFind->animationTag_) {
    return false;
  }

  pCurAnimation_ = pFind;
  pCurAnimation_->curFrame_ = startFrame;
  if (pCurAnimation_->curFrame_ < pCurAnimation_->times_.size()) {
    pCurAnimation_->curTime_ = pCurAnimation_->times_[startFrame];
  }
  if (0 < time) {
    pCurAnimation_->curTime_ = time;
  }
  pCurAnimation_->isEnd_ = false;

  return true;
}

void ImageRenderer::DebugRender(IRenderTexture* renderTexture) {
  if (!parameter_.on_ || nullptr == renderTexture) {
    return;
  }

  Transform renderTransform = GetTransform();
  switch (imageRenderType_) {
    case ImageRenderType::Left:
      renderTransform.AddPostion({renderTransform.GetScale().HalfX(), 0.0f});
      break;
    case ImageRenderType::Right:
      renderTransform.AddPostion({-renderTransform.GetScale().HalfX(), 0.0f});
      break;
    case ImageRenderType::Top:
      renderTransform.AddPostion({0.0f, renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::Bottom:
      renderTransform.AddPostion({0.0f, -renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::LeftTop:
      renderTransform.AddPostion({renderTransform.GetScale().HalfX(), renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::LeftBottom:
      renderTransform.AddPostion({renderTransform.GetScale().HalfX(), -renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::RightTop:
      renderTransform.AddPostion({-renderTransform.GetScale().HalfX(), renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::RightBottom:
      renderTransform.AddPostion({-renderTransform.GetScale().HalfX(), -renderTransform.GetScale().HalfY()});
      break;
    case ImageRenderType::Center:
    default:
      break;
  }

  GGraphicDevice->RenderImgStart(renderTransform, angle_, renderTexture);

  renderTexture->DrawPoint(parameter_.color_, parameter_.linethickness_);

  if (parameter_.withRectangle_) {
    renderTexture->DrawRectagle(renderTransform.GetScale(), parameter_.color_, parameter_.linethickness_);
  }
  if (parameter_.withCircle_) {
    renderTexture->DrawCircle(renderTransform.GetScale(), parameter_.color_, parameter_.linethickness_);
  }

  GGraphicDevice->RenderImgEnd(renderTexture);
}

// void ImageRenderer::CollisionRender(IRenderTexture* renderTexture) {
//   if (!parameter_.on_ || nullptr == renderTexture) {
//     return;
//   }
//
//   Transform renderTransform = GetTransform();
//   switch (imageRenderType_) {
//     case ImageRenderType::Left:
//       renderTransform.AddPostion({renderTransform.GetScale().HalfX(), 0.0f});
//       break;
//     case ImageRenderType::Right:
//       renderTransform.AddPostion({-renderTransform.GetScale().HalfX(), 0.0f});
//       break;
//     case ImageRenderType::Top:
//       renderTransform.AddPostion({0.0f, renderTransform.GetScale().HalfY()});
//       break;
//     case ImageRenderType::Bottom:
//       renderTransform.AddPostion({0.0f, -renderTransform.GetScale().HalfY()});
//       break;
//     case ImageRenderType::LeftTop:
//       renderTransform.AddPostion({renderTransform.GetScale().HalfX(), renderTransform.GetScale().HalfY()});
//       break;
//     case ImageRenderType::LeftBottom:
//       renderTransform.AddPostion({renderTransform.GetScale().HalfX(), -renderTransform.GetScale().HalfY()});
//       break;
//     case ImageRenderType::RightTop:
//       renderTransform.AddPostion({-renderTransform.GetScale().HalfX(), renderTransform.GetScale().HalfY()});
//       break;
//     case ImageRenderType::RightBottom:
//       renderTransform.AddPostion({-renderTransform.GetScale().HalfX(), -renderTransform.GetScale().HalfY()});
//       break;
//     case ImageRenderType::Center:
//     default:
//       break;
//   }
//
//   //// TODO :  콜리전 위치 만큼 offset 해야함.
//   // if (false == image_->IsRenderTexture()) {
//   //   IFileImage* fileImage = (IFileImage*)image_;
//
//   //  CollisionInfo collisionInfo;
//
//   //  Vector imageOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
//   //  if (false == fileImage->GetHitBoxTopInfo(imageIndex_, &collisionInfo)) {
//   //    return;
//   //  }
//
//   //  renderTransform.AddPostion(collisionInfo.position_);
//
//   //  GGraphicDevice->RenderImgStart(renderTransform, angle_, renderTexture);
//
//   //  renderTexture->DrawRectagle(collisionInfo.scale_, parameter_.color_, parameter_.linethickness_);
//
//   //  GGraphicDevice->RenderImgEnd(renderTexture);
//   //}
//
//   //// TODO :  콜리전 위치 만큼 offset 해야함.
//   // if (false == image_->IsRenderTexture()) {
//   //   IFileImage* fileImage = (IFileImage*)image_;
//   //
//   //   Vector imageOffSet = fileImage->GetImagePositionOffSet(imageIndex_);
//   //   Vector hitBoxStart = fileImage->GetHitBoxStart(imageIndex_) + imageOffSet;
//   //   Vector hitBoxEnd = fileImage->GetHitBoxEnd(imageIndex_) + imageOffSet;
//   //   Vector hitBoxSize = hitBoxEnd - hitBoxStart;
//
//   //  renderTransform.AddPostion(hitBoxStart);
//
//   //  GGraphicDevice->RenderImgStart(renderTransform, angle_, renderTexture);
//
//   //  renderTexture->DrawRectagle(hitBoxSize, parameter_.color_, parameter_.linethickness_);
//
//   //  GGraphicDevice->RenderImgEnd(renderTexture);
//   //}
// }
