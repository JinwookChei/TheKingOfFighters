#include "stdafx.h"
#include "KOFLevel.h"
#include "CameraTarget.h"
#include "KOFPlayer.h"
#include "Iori.h"
#include "Chang.h"
#include "BackGround.h"
#include "BackGroundMask.h"
#include "HealthBar.h"
#include "Portrait.h"
#include "Health.h"
#include <thread>

KOFLevel::KOFLevel()
    : channel_(nullptr),
      pCamera_(nullptr),
      pMouse_(nullptr),
      pBackGround_(nullptr),
      pBackGroundMask_(nullptr),
      pPlayer1_(nullptr),
      pPlayer2_(nullptr),
      HUD_(nullptr),
      player1SpawnPostion_({0.0f, 0.0f}),
      player2SpawnPostion_({0.0f, 0.0f}),
      OnFreezeTimer_(false),
      isFreezeInfinite_(false),
      freezedActors_({}),
      freezeDuration_(0),
      freezeTiemr_(0),
      levelLeftBoundary_(0.0f),
      levelRightBoundary_(0.0f),
      screenBoundaryWidth_(0.0f) {
}

KOFLevel::~KOFLevel() {
}

void KOFLevel::BeginPlay() {
  //TimeManager::Instance()->SetTimeScale(0.5f);

  Vector backbufferScale = GEngineCore->GetBackbufferScale();

  // IMAGES
  IImage* mouseImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\mousePointer.png", (IMGTYPE_MouseImage | IMGMOD_NONE));

  IFileImage* backGroundImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\TownStage.png", (IMGTYPE_BackGoundImage | IMGMOD_NONE));
  backGroundImage->CalculateTransformByAuto({.emptyColor = Color8Bit(77, 111, 111, 0), .reCalculateHeight = true, .start = {0.0f, 0.0f}, .end = {779.0f, 2015.0f}});

  IFileImage* blackBoardImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\BlackBoard.png", (IMGTYPE_BlackBoardImage | IMGMOD_NONE));

  IFileImage* whiteBoardImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\WhiteBoard.png", (IMGTYPE_WhiteBoardImage | IMGMOD_NONE));

  IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Alpha.bmp", (IMGTYPE_IoriImage | IMGMOD_NONE));
  ioriImage->CalculateTransformFromCSV("..\\ContentsResource\\Iori.csv");
  IFileImage* ioriImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Alpha.bmp", (IMGTYPE_IoriImage | IMGMOD_FLIPPED));
  ioriImageFlipped->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\Iori.csv");
  IFileImage* ioriImage_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Alpha_BlueFlame.bmp", (IMGTYPE_IoriImage | IMGMOD_BLUEFLAME));
  ioriImage_BlueFlame->CalculateTransformFromCSV("..\\ContentsResource\\Iori.csv");
  IFileImage* ioriImageFlipped_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Alpha_BlueFlame.bmp", (IMGTYPE_IoriImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME));
  ioriImageFlipped_BlueFlame->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\Iori.csv");

  IFileImage* changImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Alpha.bmp", (IMGTYPE_ChangImage | IMGMOD_NONE));
  changImage->CalculateTransformFromCSV("..\\ContentsResource\\Chang.csv");
  IFileImage* changImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Alpha.bmp", (IMGTYPE_ChangImage | IMGMOD_FLIPPED));
  changImageFlipped->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\Chang.csv");
  IFileImage* changImage_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Alpha_BlueFlame.bmp", (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME));
  changImage_BlueFlame->CalculateTransformFromCSV("..\\ContentsResource\\Chang.csv");
  IFileImage* changImageFlipped_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Alpha_BlueFlame.bmp", (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME));
  changImageFlipped_BlueFlame->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\Chang.csv");

  IFileImage* healthBarImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\HealthBar.png", (IMGTYPE_HealthBarImage | IMGMOD_NONE));
  healthBarImage->CalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);

  IFileImage* healthBarImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\HealthBar.png", (IMGTYPE_HealthBarImage | IMGMOD_FLIPPED));
  healthBarImageFlipped->CalculateTransformFromDrawBoxImage_Flip(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);

  IFileImage* healthImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Health.png", (IMGTYPE_HealthImage | IMGMOD_NONE));
  healthImage->CalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);

  IFileImage* hitEffectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\HitEffect01.png", (IMGTYPE_HitEffectImage | IMGMOD_NONE));
  hitEffectImage->CalculateTransformFromDrawBoxImage(Color8Bit{128, 0, 255, 0}, Color8Bit::Magenta);

  IFileImage* castingEffectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\CastingEffectImage_Box.png", (IMGTYPE_CastingEffectImage | IMGMOD_NONE));
  castingEffectImage->CalculateTransformFromDrawBoxImage(Color8Bit{108, 156, 114, 0}, Color8Bit::Magenta);

  // TODO :
  // 반전된 Health는 logic으로, 원본 이미지는 여러 포인터가 가르킥로있고, 이미지를 어떻게 그릴지만 각자 알아서 그림.
  // UI 이미지는 래퍼로 감싸서 position하고, scale 등 정보로 Render를 그림.
  IFileImage* reverseHealthImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Health.png", (IMGTYPE_HealthImage | IMGMOD_FLIPPED));
  reverseHealthImage->CalculateTransformFromDrawBoxImage_Flip(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);

  // MOUSE
  pMouse_ = SpawnMouse();
  pMouse_->SetImage(ImgManager::GetIntance()->GetImg(IMGTYPE_MouseImage));
  pMouse_->SetAlpha(1.0f);
  Vector localScale = {0.1f, 0.1f};
  pMouse_->SetRenderLocalScale(localScale);

  Vector newPosition = {100.0f, -70.0f};
  newPosition = newPosition * localScale;
  pMouse_->SetRenderPosition(newPosition);
  pMouse_->ShowCursor(false);
  pMouse_->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));

  // BLACKBOARD
  pBackGroundMask_ = SpawnActor<BackGroundMask>(ActorGroupEngineType::ActorGroupEngineType_BackGround);
  pBackGroundMask_->SetPosition({0.0f, 0.0f});

  // BACKGROUND
  pBackGround_ = SpawnActor<BackGround>(ActorGroupEngineType::ActorGroupEngineType_BackGround);
  pBackGround_->SetPosition({0.0f, 0.0f});
  pBackGround_->SetUseCameraposition(true);
  Vector backGroundImageScale = pBackGround_->GetBackGroundScale();
  

  // PLAYER SET
  pPlayer1_ = SpawnActor<Iori>(ActorGroupEngineType::ActorGroupEngineType_None);
  player1SpawnPostion_ = Vector(backGroundImageScale.X * 0.5f - 300, backGroundImageScale.Y * 0.5f + 250.0f);
  pPlayer2_ = SpawnActor<Iori>(ActorGroupEngineType::ActorGroupEngineType_None);
  player2SpawnPostion_ = Vector(backGroundImageScale.X * 0.5f + 300, backGroundImageScale.Y * 0.5f + 250.0f);
  /*pPlayer2_ = SpawnActor<Chang>(ActorGroupEngineType::ActorGroupEngineType_None);
  player2SpawnPostion_ = Vector(backGroundImageScale.X * 0.5f + 300, backGroundImageScale.Y * 0.5f + 170.0f);*/

  pPlayer1_->Initialize(true, player1SpawnPostion_, true, pPlayer2_);
  pPlayer2_->Initialize(false, player2SpawnPostion_, true, pPlayer1_);

  // HUD
  HUD_ = SpawnActor<UI>(ActorGroupEngineType::ActorGroupEngineType_UI);
  HUD_->SetPosition({backbufferScale.HalfX(), backbufferScale.HalfY()});
  HUD_->SetScale({backbufferScale.X, backbufferScale.Y});
  HUD_->SetOriginColor(Color8Bit::White); 
  HUD_->ChangeClearColor_(false);

  ImageRenderer* pHUDRenderer_ = HUD_->GetImageRenderer();
  if (nullptr == pHUDRenderer_) {
    return;
  }
  pHUDRenderer_->SetTransparentColor(Color8Bit::White);

  // PLAYER_1 UI
  Portrait* portraitPlayer1 = HUD_->CreateUIComponent<Portrait>();
  portraitPlayer1->Initialize(IMGTYPE_IoriImage | IMGMOD_FLIPPED, 655, ioriTransparentColor);
  portraitPlayer1->SetPosition({90.0f, 100.0f});

  HealthBar* healthBarPlayer1 = HUD_->CreateUIComponent<HealthBar>();
  healthBarPlayer1->Initialize(IMGTYPE_HealthBarImage, 0, Color8Bit(0, 0, 0, 0));
  healthBarPlayer1->SetPosition({490.0f, 102.0f});

  Health* healthPlayer1 = HUD_->CreateUIComponent<Health>();
  healthPlayer1->Initialize(pPlayer1_, IMGTYPE_HealthImage, 0, Color8Bit(0, 0, 0, 0), {490.0f, 102.0f}, false);

  // PLAYER_2 UI
  Portrait* portraitPlayer2 = HUD_->CreateUIComponent<Portrait>();
  portraitPlayer2->Initialize(IMGTYPE_ChangImage, 399, changTransparentColor);
  portraitPlayer2->SetPosition({1810.0f, 100.0f});

  HealthBar* healthBarPlayer2 = HUD_->CreateUIComponent<HealthBar>();
  healthBarPlayer2->Initialize((IMGTYPE_HealthBarImage | IMGMOD_FLIPPED), 0, Color8Bit(0, 0, 0, 0));
  healthBarPlayer2->SetPosition({1415.0f, 102.0f});

  Health* healthPlayer2 = HUD_->CreateUIComponent<Health>();
  healthPlayer2->Initialize(pPlayer2_, (IMGTYPE_HealthImage | IMGMOD_FLIPPED), 0, Color8Bit(0, 0, 0, 0), {1415.0f, 102.0f}, true);

  // CAMERA 
  pCamera_ = SpawnActor<CameraTarget>();
  pCamera_->Initialize(backbufferScale.HalfY(), backGroundImageScale.IntergerY() - backbufferScale.HalfY() + 60, backbufferScale.HalfX(), backGroundImageScale.X - backbufferScale.HalfX() + 20);
  pCamera_->SetPosition({backGroundImageScale.X / 2, pCamera_->GetCameraMaxHeight()});
  CameraManager::Instance()->SetTarget(pCamera_);


  // EFFECT
  if (false == EffectManager::Instance()->RegistEffect(EFKEY_Hit_1, IMGTYPE_HitEffectImage, 7, 10, 50, false, Color8Bit{128, 0, 255, 0})) {
    return;
  }
  if (false == EffectManager::Instance()->RegistEffect(EFKEY_Hit_2, IMGTYPE_HitEffectImage, 19, 22, 50, false, Color8Bit{128, 0, 255, 0})) {
    return;
  }
  if (false == EffectManager::Instance()->RegistEffect(EFKEY_Hit_3, IMGTYPE_HitEffectImage, 31, 34, 50, false, Color8Bit{128, 0, 255, 0})) {
    return;
  }
  if (false == EffectManager::Instance()->RegistEffect(EFKEY_Casting_1, IMGTYPE_CastingEffectImage, 0, 15, 20, false, Color8Bit{108, 156, 114, 0})) {
    return;
  }
  if (false == EffectManager::Instance()->RegistEffect(EFKEY_Casting_2, IMGTYPE_CastingEffectImage, 16, 31, 20, false, Color8Bit{108, 156, 114, 0})) {
    return;
  }
  if (false == EffectManager::Instance()->RegistEffect(EFKEY_Casting_3, IMGTYPE_CastingEffectImage, 32, 47, 20, false, Color8Bit{108, 156, 114, 0})) {
    return;
  }
  if (false == EffectManager::Instance()->RegistEffect(EFKEY_Casting_4, IMGTYPE_CastingEffectImage, 48, 63, 20, false, Color8Bit{108, 156, 114, 0})) {
    return;
  }
  if (false == EffectManager::Instance()->RegistEffect(EFKEY_Casting_5, IMGTYPE_CastingEffectImage, 64, 79, 20, false, Color8Bit{108, 156, 114, 0})) {
    return;
  }
  if (false == EffectManager::Instance()->RegistEffect(EFKEY_Casting_6, IMGTYPE_CastingEffectImage, 80, 95, 20, false, Color8Bit{108, 156, 114, 0})) {
    return;
  }
  if (false == EffectManager::Instance()->RegistEffect(EFKEY_Iori_Explosion, IMGTYPE_IoriImage, 387, 405, 20, false, Color8Bit{0,0,0,0}, true, 1.0f)) {
    return;
  }

  // SOUND
  /*Path soundPath;
  soundPath.MoveParent();
  soundPath.Move("ContentsResource\\Sound\\");
  soundPath.Move("Kyoku-Gen.mp3");
  SoundManager::Instance()->Load(soundPath, 0);
  channel_ = SoundManager::Instance()->SoundPlay(0);*/

  // LEVEL BOUNDARY SETTING
  levelLeftBoundary_ = levelBoundaryMargin_;
  levelRightBoundary_ = backGroundImageScale.X - levelBoundaryMargin_;
}

void KOFLevel::Tick(unsigned long long deltaTick) {
  CalculateFreeze(deltaTick);

  SwapPosition();

  if (true == InputManager::Instance()->IsAnyKeyPress()) {
    if (InputManager::Instance()->IsDown(VK_F1)) {
      SetDebugRender(!GetDebugRender());
    }

    if (InputManager::Instance()->IsDown(VK_F2)) {
      SetCollisionRender(!GetCollisionRender());
    }
  }

  Vector backbufferScale = GEngineCore->GetBackbufferScale();
  float cameraHeight = pCamera_->GetCameraMaxHeight();

  pPlayer1_->SetIsAtMapEdge(false);
  pPlayer2_->SetIsAtMapEdge(false);
  screenBoundaryWidth_ = backbufferScale.X - pPlayer1_->CharacterScale().HalfX() - pPlayer2_->CharacterScale().HalfX();

  Vector player1Position = pPlayer1_->GetPosition();
  Vector player2Position = pPlayer2_->GetPosition();

  float player1Left = player1Position.X - pPlayer1_->CharacterScale().HalfX();
  float player2Left = player2Position.X - pPlayer2_->CharacterScale().HalfX();

  float player1Right = player1Position.X + pPlayer1_->CharacterScale().HalfX();
  float player2Right = player2Position.X + pPlayer2_->CharacterScale().HalfX();

  float viewLeft = pCamera_->GetPosition().X - backbufferScale.X / 2;
  float viewRight = pCamera_->GetPosition().X + backbufferScale.X / 2;

  // CameraPosition X
  if (player1Position.X < player2Position.X) {
    if (player1Left < viewLeft) {
      if (viewRight > player2Right && viewLeft > levelLeftBoundary_) {
        pCamera_->SetPosition({player1Left + backbufferScale.X / 2, cameraHeight});
      }
    }
    if (player2Right > viewRight) {
      if (viewLeft < player1Left && viewRight < levelRightBoundary_) {
        pCamera_->SetPosition({player2Right - backbufferScale.X / 2, cameraHeight});
      }
    }
  } else {
    if (player2Left < viewLeft) {
      if (viewRight > player1Right && viewLeft > levelLeftBoundary_) {
        pCamera_->SetPosition({player2Left + backbufferScale.X / 2, cameraHeight});
      }
    }
    if (player1Right > viewRight) {
      if (viewLeft < player2Left && viewRight < levelRightBoundary_) {
        pCamera_->SetPosition({player1Right - backbufferScale.X / 2, cameraHeight});
      }
    }
  }
  
  // CameraClamp X
  if (pCamera_->GetPosition().X < pCamera_->GetCameraMinWidth()) {
    pCamera_->SetPosition({pCamera_->GetCameraMinWidth(), pCamera_->GetPosition().Y});

  } else if (pCamera_->GetPosition().X > pCamera_->GetCameraMaxWidth()) {
    pCamera_->SetPosition({pCamera_->GetCameraMaxWidth(), pCamera_->GetPosition().Y});
  }


  // CameraPosition Y
  float player1JumpHeight = player1SpawnPostion_.Y - player1Position.Y;
  float player2JumpHeight = player2SpawnPostion_.Y - player2Position.Y;

  if (player1JumpHeight > 0 || player2JumpHeight > 0) {
    float addHeight = (player1JumpHeight > player2JumpHeight) ? player1JumpHeight : player2JumpHeight;
    const Vector& cameraPosition = pCamera_->GetPosition();
    pCamera_->SetPosition({cameraPosition.X, cameraHeight - addHeight / 5});
  }

  // CameraClamp Y
  if (pCamera_->GetPosition().Y < pCamera_->GetCameraMinHeight()) {
    pCamera_->SetPosition({pCamera_->GetPosition().X, pCamera_->GetCameraMinHeight()});

  } else if (pCamera_->GetPosition().Y > pCamera_->GetCameraMaxHeight()) {
    pCamera_->SetPosition({pCamera_->GetPosition().X, pCamera_->GetCameraMaxHeight()});
  }


  // CHECK PlAYER POSITION EDGE
  if (player1Left < levelLeftBoundary_ || player1Right > levelRightBoundary_) {
    pPlayer1_->SetIsAtMapEdge(true);
  }
  if (player2Left < levelLeftBoundary_ || player2Right > levelRightBoundary_) {
    pPlayer2_->SetIsAtMapEdge(true);
  }
}

void KOFLevel::SwapPosition() {
  const Vector& player1Postion = pPlayer1_->GetPosition();
  const Vector& player2Postion = pPlayer2_->GetPosition();

  pPlayer1_->SetPlayerOnLeft(player1Postion.X < player2Postion.X);
  pPlayer2_->SetPlayerOnLeft(!(player1Postion.X < player2Postion.X));
}

CameraTarget* KOFLevel::GetCameraTarget() const {
  return pCamera_;
}


BackGroundMask* KOFLevel::GetBackGroundMask() const {
  return pBackGroundMask_;
}

void KOFLevel::FreezeActors(std::vector<Actor*> actors, bool isInfinite, unsigned long long freezeDuration) {
  for (auto iter = actors.begin(); iter != actors.end(); ++iter) {
    if (nullptr == *iter) {
      continue;
    }

    Actor* pActor = *iter;
    pActor->SetEnableTick(false);
  }

  OnFreezeTimer_ = true;
  isFreezeInfinite_ = isInfinite;
  freezedActors_ = actors;
  freezeDuration_ = freezeDuration;
  freezeTiemr_ = 0;
}

void KOFLevel::DefreezeActors() {
  for (auto iter = freezedActors_.begin(); iter != freezedActors_.end(); ++iter) {
    if (nullptr == *iter) {
      continue;
    }

    Actor* pActor = *iter;
    pActor->SetEnableTick(true);
  }

  OnFreezeTimer_ = false;
  isFreezeInfinite_ = false;
  freezeDuration_ = 0;
  freezeTiemr_ = 0;
}

void KOFLevel::CalculateFreeze(unsigned long long deltaTick) {
  if (true == OnFreezeTimer_) {
    freezeTiemr_ += deltaTick;
    if (freezeTiemr_ >= freezeDuration_ && false == isFreezeInfinite_) {
      DefreezeActors();
    }
  }
}

float KOFLevel::GetLevelLeftBoundary() const {
  return levelLeftBoundary_;
}

float KOFLevel::GetLevelRightBoundary() const {
  return levelRightBoundary_;
}

float KOFLevel::GetScreenBoundaryWidth() const {
  return screenBoundaryWidth_;
}
