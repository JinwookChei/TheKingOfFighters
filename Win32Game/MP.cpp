#include "stdafx.h"
#include "MP.h"
#include "KOFPlayer.h"
#include "HealthComponent.h"

MP::MP()
    : pPlayer_(nullptr),
      pImage_(nullptr),
      isFlip_(false),
      imageIndex_(0),
      colorTransparent_({0, 0, 0, 0}),
      originComponentTransform_(),
      originRenderTransform_(),
      componentTransform_(),
      renderTransform_(),
      healthPercentage_(0.0f) {
}

MP::~MP() {
}

void MP::BeginPlay() {
  EnableCollision(false);
}

bool MP::Initialize(KOFPlayer* bindPlayer, unsigned long long imageNum, unsigned int imageIndex, const Color8Bit& colorTransparent, const Vector& position, bool isFlip) {
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
  originRenderTransform_ = pImage_->RenderTransform(imageIndex);
  componentTransform_ = GetTransform();
  renderTransform_ = pImage_->RenderTransform(imageIndex);

  return true;
}

void MP::Tick(unsigned long long curTick) {
  if (nullptr == pPlayer_) {
    return;
  }

  const HealthComponent* pHealthComponent = pPlayer_->GetHealthComponent();
  float maxHealth = pHealthComponent->MaxHealth();
  float curHealth = pHealthComponent->Health();

  healthPercentage_ = curHealth / maxHealth;

  float healthScaleOffset = originComponentTransform_.GetScale().X;
  healthScaleOffset = (healthScaleOffset * (1.0f - healthPercentage_)) * 0.5f;

  if (false == isFlip_) {
    componentTransform_.SetScale({originComponentTransform_.GetScale().X * healthPercentage_, originComponentTransform_.GetScale().Y});
    SetPosition({originComponentTransform_.GetPosition().X - healthScaleOffset, originComponentTransform_.GetPosition().Y});
    renderTransform_.SetScale(componentTransform_.GetScale());
  } else {
    componentTransform_.SetScale({originComponentTransform_.GetScale().X * healthPercentage_, originComponentTransform_.GetScale().Y});
    SetPosition({originComponentTransform_.GetPosition().X + healthScaleOffset, originComponentTransform_.GetPosition().Y});
    renderTransform_.SetScale(componentTransform_.GetScale());
    renderTransform_.SetPosition({originRenderTransform_.GetPosition().X + healthScaleOffset, originRenderTransform_.GetPosition().Y});
  }
}

void MP::Render(IRenderTexture* renderTexture) {
  if (nullptr == renderTexture || nullptr == pPlayer_) {
    return;
  }

  UI* owner = GetOwner();
  if (nullptr == owner) {
    return;
  }

  renderTexture->TransparentWithTransform(pImage_, componentTransform_, renderTransform_, colorTransparent_);
}
