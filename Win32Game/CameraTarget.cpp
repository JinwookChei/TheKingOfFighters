#include "stdafx.h"
#include "Player.h"
#include "CameraTarget.h"

CameraTarget::CameraTarget()
    : backGroundScale_({0.0f, 0.0f}),
      cameraRange_(0.0f),
      cameraHeight_(0.0f),
      pPlayer1_(nullptr),
      pPlayer2_(nullptr),
      player1StartPosition_({0.0f, 0.0f}),
      player2StartPosition_({0.0f, 0.0f}) {
}

CameraTarget::~CameraTarget() {
}

void CameraTarget::BeginPlay() {
}

bool CameraTarget::Initialize(const Vector& backGroundScale, float cameraRange, float cameraHeight, Player* player1, Player* player2) {
  if (nullptr == player1 || nullptr == player2) {
    return false;
  }
  backGroundScale_ = backGroundScale;
  cameraRange_ = cameraRange;
  cameraHeight_ = cameraHeight;

  pPlayer1_ = player1;
  pPlayer2_ = player2;

  player1StartPosition_ = pPlayer1_->GetPosition();
  player2StartPosition_ = pPlayer2_->GetPosition();

  SetPosition({backGroundScale_.X / 2, cameraHeight_});
  return true;
}

void CameraTarget::Tick(unsigned long long curTick) {
  float margin = 15.0f;

  float left = GetPosition().X - cameraRange_ / 2;
  float right = GetPosition().X + cameraRange_ / 2;

  Vector player1Position = pPlayer1_->GetPosition();
  Vector player2Position = pPlayer2_->GetPosition();

  float player1Left = player1Position.X - pPlayer1_->CharacterScale().HalfX();
  float player2Left = player2Position.X - pPlayer2_->CharacterScale().HalfX();

  float player1Right = player1Position.X + pPlayer1_->CharacterScale().HalfX();
  float player2Right = player2Position.X + pPlayer2_->CharacterScale().HalfX();

  // CameraPosition X
  if (player1Position.X < player2Position.X) {
    if (player1Left < left) {
      if (right - player2Right > 0 && left >= margin) {
        SetPosition({player1Left + cameraRange_ / 2, cameraHeight_});
      } else {
        pPlayer1_->SetPosition({left + pPlayer1_->CharacterScale().HalfX(), player1Position.Y});
      }
    }

    if (player2Right > right) {
      if (player1Left - left > 0 && right <= backGroundScale_.X - margin) {
        SetPosition({player2Right - cameraRange_ / 2, cameraHeight_});
      } else {
        pPlayer2_->SetPosition({right - pPlayer2_->CharacterScale().HalfX(), player2Position.Y});
      }
    }

  } else {
    if (player2Left < left) {
      if (right - player1Right > 0 && left >= margin) {
        SetPosition({player2Left + cameraRange_ / 2, cameraHeight_});
      } else {
        pPlayer2_->SetPosition({left + pPlayer2_->CharacterScale().HalfX(), player2Position.Y});
      }
    }

    if (player1Right > right) {
      if (player2Left - left > 0 && right <= backGroundScale_.X - margin) {
        SetPosition({player1Right - cameraRange_ / 2, cameraHeight_});
      } else {
        pPlayer1_->SetPosition({right - pPlayer1_->CharacterScale().HalfX(), player1Position.Y});
      }
    }
  }

  // CameraPosition Y
  float player1JumpHeight = player1StartPosition_.Y - player1Position.Y;
  float player2JumpHeight = player2StartPosition_.Y - player2Position.Y;

  if (player1JumpHeight > 0 || player2JumpHeight > 0) {

    float addHeight = (player1JumpHeight > player2JumpHeight) ? player1JumpHeight : player2JumpHeight;
    const Vector& cameraPosition = GetPosition();
    SetPosition({cameraPosition.X, cameraHeight_ - addHeight/5});
  }
}