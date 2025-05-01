#include "stdafx.h"
#include "Health.h"
#include "KOFPlayer.h"
#include "HealthComponent.h";

Health::Health()
    : pPlayer_(nullptr),
      pImage_(nullptr),
      isFlip_(false),
      imageIndex_(0),
      colorTransparent_({0, 0, 0, 0}),
      originComponentTransform_(),
      originImageTransform_(),
      healthPercentage_(0.0f) {
}

Health::~Health() {
}

void Health::BeginPlay() {
  EnableCollision(false);
}

bool Health::Initialize(KOFPlayer* bindPlayer, unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent, const Vector& position, bool isFlip) {
  if (nullptr == bindPlayer) {
    return false;
  }

  pImage_ = ImgManager::GetIntance()->GetImg(imageNum);
  if (nullptr == pImage_) {
    return false;
  }

  SetScale(pImage_->GetScale(imageIndex));
  SetPosition(position);
  pPlayer_ = bindPlayer;
  isFlip_ = isFlip;
  imageIndex_ = imageIndex;
  colorTransparent_ = colorTransparent;
  originComponentTransform_ = GetTransform();
  originImageTransform_ = pImage_->RenderTransform(imageIndex);

  return true;
}

void Health::Tick(unsigned long long curTick) {
  if (nullptr == pPlayer_) {
    return;
  }

  // Calculate Health Start
  if (false == isFlip_) {
    HealthComponent* pHealthComponent = pPlayer_->GetHealthComponent();
    float maxHealth = pHealthComponent->MaxHealth();
    float curHealth = pHealthComponent->Health();

    healthPercentage_ = curHealth / maxHealth;

    if (nullptr == pImage_ || true == pImage_->IsRenderTexture()) {
      return;
    }

    IFileImage* pFileImage = (IFileImage*)pImage_;
    Transform newImageTransform = originImageTransform_;

    Vector renderScale = newImageTransform.GetScale();
    renderScale = {renderScale.X * healthPercentage_, renderScale.Y};
    newImageTransform.SetScale(renderScale);

    pFileImage->SetTransform(newImageTransform, imageIndex_);

    Vector positionOffset = {(originImageTransform_.GetScale().X - renderScale.X) * 0.5f, 0.0f};
    Vector componentPosition = {originComponentTransform_.GetPosition() - positionOffset};
    SetPosition(componentPosition);

  } else {
    HealthComponent* pHealthComponent = pPlayer_->GetHealthComponent();
    float maxHealth = pHealthComponent->MaxHealth();
    float curHealth = pHealthComponent->Health();

    healthPercentage_ = curHealth / maxHealth;

    if (nullptr == pImage_ || true == pImage_->IsRenderTexture()) {
      return;
    }

    IFileImage* pFileImage = (IFileImage*)pImage_;
    Transform newImageTransform = originImageTransform_;

    Vector renderScale = newImageTransform.GetScale();
    renderScale = {renderScale.X * healthPercentage_, renderScale.Y};
    newImageTransform.SetScale(renderScale);

    Vector renderPosition = originImageTransform_.GetPosition();
    Vector renderImageOffset = {(originImageTransform_.GetScale().X - renderScale.X), 0.0f};
    renderPosition = renderPosition + renderImageOffset;
    newImageTransform.SetPosition(renderPosition);

    pFileImage->SetTransform(newImageTransform, imageIndex_);


    Vector positionOffset = {(originImageTransform_.GetScale().X - renderScale.X) * 0.5f, 0.0f};
    Vector componentPosition = {originComponentTransform_.GetPosition() + positionOffset};
    
    SetPosition(componentPosition);
  }
  // Calculate Health End
}

void Health::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture || nullptr == pPlayer_) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  const Vector& imageScale = pImage_->GetScale(imageIndex_);
  renderTexture->Transparent(pImage_, imageIndex_, imageScale, colorTransparent_);
}
