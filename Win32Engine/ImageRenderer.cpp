#include "stdafx.h"
#include "ImageRenderer.h"

unsigned int AnimationInfo::Update(unsigned long long curTick) {
  if (false == loop_ && true == isEnd_) {
    return indices_[curFrame_];
  }

  if (loop_ == true) {
    isEnd_ = true;
  } else {
    isEnd_ = false;
  }

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
      curFrame_ = loopStartFrame_;
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
      pCurAnimInfo_(nullptr) {
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
  if (nullptr != pCurAnimInfo_) {
    if (nullptr != image_) {
      image_->Release();
      image_ = nullptr;
    }

    image_ = pCurAnimInfo_->image_;
    imageIndex_ = pCurAnimInfo_->Update(curTick);

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

AnimationInfo* ImageRenderer::GetCurAnimationInfo() const {
  return pCurAnimInfo_;
}

void ImageRenderer::SetImageIndex(unsigned int iamgeIndex) {
  imageIndex_ = iamgeIndex;
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

Color8Bit ImageRenderer::GetTransparentColor() const {
  return transparentColor_;
}

void ImageRenderer::SetTransparentColor(const Color8Bit& color) {
  isAlpha_ = false;
  transparentColor_ = color;
}

ImageRenderType ImageRenderer::GetImageRenderType() const {
  return imageRenderType_;
}

void ImageRenderer::SetImageRenderType(ImageRenderType newType) {
  imageRenderType_ = newType;
}

void ImageRenderer::Render(IRenderTexture* renderTexture) {
  if (nullptr == image_ || nullptr == renderTexture) {
    return;
  }
  Transform renderTransform = GetViewTransform();
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
  // Actor* owner = GetOwner();
  // GGraphicDevice->DrawRectagle(owner->GetPosition(), Color8Bit::RedAlpha, 1.0f);

  GGraphicDevice->RenderImgEnd(renderTexture);
}

LINK_ITEM* ImageRenderer::GetSceneLink() {
  return &sceneLink_;
}

LINK_ITEM* ImageRenderer::GetRenderActorLink() {
  return &renderActorLink_;
}

bool ImageRenderer::CreateAnimation(
    unsigned long long animationTag,
    unsigned long long imageIndex,
    unsigned int startIndex,
    unsigned int endIndex,
    unsigned long long interval,
    bool loop,
    unsigned long long loopStartFrame) {
  std::vector<unsigned int> indices;

  int size = (int)(endIndex - startIndex);

  indices.reserve(abs(size));

  if (size > 0) {
    for (unsigned int n = startIndex; n <= endIndex; ++n) {
      indices.push_back(n);
    }
  } else {
    for (unsigned int n = startIndex; n >= endIndex; --n) {
      indices.push_back(n);
    }
  }

  return CreateAnimation(animationTag, imageIndex, indices, interval, loop, loopStartFrame);
}

bool ImageRenderer::CreateAnimation(
    unsigned long long animationTag,
    unsigned long long imageIndex,
    const std::vector<unsigned int>& indices,
    unsigned long long interval,
    bool loop,
    unsigned long long loopStartFrame) {
  std::vector<unsigned long long> intervals;
  intervals.reserve(indices.size());

  for (size_t n = 0; n < indices.size(); ++n) {
    intervals.push_back(interval);
  }

  return CreateAnimation(animationTag, imageIndex, indices, intervals, loop, loopStartFrame);
}

bool ImageRenderer::CreateAnimation(
    unsigned long long animationTag,
    unsigned long long imageIndex,
    const std::vector<unsigned int>& indices,
    const std::vector<unsigned long long> intervals,
    bool loop,
    unsigned long long loopStartFrame) {
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
  pNew->loopStartFrame_ = loopStartFrame - indices[0];
  pNew->times_ = intervals;
  pNew->indices_ = indices;

  pNew->searchHandle_ = animations_.Insert(pNew, &animationTag, 8);

  return nullptr != pNew->searchHandle_;
}

bool ImageRenderer::ChangeAnimation(unsigned long long animationTag, bool isForce, int startFrame, unsigned long long time) {
  AnimationInfo* pFind = nullptr;
  if (0 == animations_.Select((void**)&pFind, 1, &animationTag, 8)) {
    return false;
  }

  if (nullptr != pCurAnimInfo_ && pCurAnimInfo_->loop_ && pCurAnimInfo_->animationTag_ == pFind->animationTag_) {
    return false;
  }

  pCurAnimInfo_ = pFind;
  pCurAnimInfo_->curFrame_ = startFrame;
  if (pCurAnimInfo_->curFrame_ < pCurAnimInfo_->times_.size()) {
    pCurAnimInfo_->curTime_ = pCurAnimInfo_->times_[startFrame];
  }
  if (0 < time) {
    pCurAnimInfo_->curTime_ = time;
  }
  pCurAnimInfo_->isEnd_ = false;

  if (true == isForce) {
    if (nullptr != pCurAnimInfo_) {
      if (nullptr != image_) {
        image_->Release();
        image_ = nullptr;
      }

      image_ = pCurAnimInfo_->image_;
      imageIndex_ = pCurAnimInfo_->indices_[startFrame];

      if (nullptr != image_) {
        image_->AddRef();
        SetScale(image_->GetScale(imageIndex_));
      }
    }
  }

  return true;
}

bool ImageRenderer::IsAnimationEnd() {
  if (nullptr == pCurAnimInfo_) {
    return false;
  }

  return pCurAnimInfo_->isEnd_;
}

void ImageRenderer::DebugRender(IRenderTexture* renderTexture) {
  if (!parameter_.on_ || nullptr == renderTexture) {
    return;
  }

  Transform renderTransform = GetViewTransform();
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