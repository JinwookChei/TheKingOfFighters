#include "stdafx.h"
#include "Player.h"
#include "CameraTarget.h"
#include "CameraLimitComponent.h"

CameraTarget::CameraTarget()
    : backGroundScale_({0.0f, 0.0f}),
      cameraRange_(0.0f),
      cameraHeight_(0.0f),
      pPlayer1_(nullptr),
      pPlayer2_(nullptr) {
}

CameraTarget::~CameraTarget() {
}

void CameraTarget::BeginPlay() {
}

bool CameraTarget::Initialize(const Vector& backGroundScale, float cameraRange, float cameraHeight) {
  backGroundScale_ = backGroundScale;
  cameraRange_ = cameraRange;
  cameraHeight_ = cameraHeight;

  SetPosition({backGroundScale_.X / 2, cameraHeight_});
  return true;
}

void CameraTarget::Tick(unsigned long long curTick) {
  float left = GetPosition().X - cameraRange_ / 2 + 30.0f;
  float right = GetPosition().X + cameraRange_ / 2 - 30.0f;

  Vector player1Position = pPlayer1_->GetPosition();
  Vector player2Position = pPlayer2_->GetPosition();
  
  float player1Left = player1Position.X - pPlayer1_->CharacterScale().HalfX();
  float player2Left = player2Position.X - pPlayer2_->CharacterScale().HalfX();

  float player1Right = player1Position.X + pPlayer1_->CharacterScale().HalfX();
  float player2Right = player2Position.X + pPlayer2_->CharacterScale().HalfX();


  if (player1Position.X < player2Position.X) {
    if (player1Left < left) {
      if (right - player2Right > 0 && left >= 0.0f) {
        SetPosition({player1Left + cameraRange_ / 2, cameraHeight_});
      } else {
        pPlayer1_->SetPosition({left + pPlayer1_->CharacterScale().HalfX(), player1Position.Y});
      }
    }

    if (player2Right > right) {
      if (player1Left - left > 0 && right <= backGroundScale_.X) {
        SetPosition({player2Right - cameraRange_ / 2, cameraHeight_});
      } else {
        pPlayer2_->SetPosition({right - pPlayer2_->CharacterScale().HalfX(), player2Position.Y });
      }
    }

  } else {
    if (player2Left < left) {
      if (right - player1Right > 0 && left >= 0.0f) {
        SetPosition({player2Left + cameraRange_ / 2, cameraHeight_});
      } else {
        pPlayer2_->SetPosition({left + pPlayer2_->CharacterScale().HalfX(), player2Position.Y});
      }
    }

    if (player1Right > right) {
      if (player2Left - left > 0 && right <= backGroundScale_.X) {
        SetPosition({player1Right - cameraRange_ / 2, cameraHeight_});
      } else {
        pPlayer1_->SetPosition({right - pPlayer1_->CharacterScale().HalfX(), player1Position.Y});
      }
    }

  }
}

void CameraTarget::BindPlayer1(Player* player1) {
  pPlayer1_ = player1;
}

void CameraTarget::BindPlayer2(Player* player2) {
  pPlayer2_ = player2;
}
