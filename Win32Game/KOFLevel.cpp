#include "stdafx.h"
#include "KOFLevel.h"
#include "CameraTarget.h"
#include "KOFPlayer.h"
#include "Iori.h"
#include "Chang.h"
#include "BackGround.h"
#include "HealthBar.h"
#include "Portrait.h"
#include "Health.h"

KOFLevel::KOFLevel()
    : backGroundImageScale_({0.0f, 0.0f}),
      channel_(nullptr),
      pCamera_(nullptr),
      pMouse_(nullptr),
      pBackGround_(nullptr),
      pPlayer1_(nullptr),
      pPlayer2_(nullptr),
      HUD_(nullptr),
      player1SpawnPostion_({0.0f, 0.0f}),
      player2SpawnPostion_({0.0f, 0.0f}) {
}

KOFLevel::~KOFLevel() {
}

void KOFLevel::BeginPlay() {
  Vector backbufferScale = GEngineCore->GetBackbufferScale();

  // IMAGES
  IImage* mouseImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\mousePointer.png", IMGKEY_MouseImage);
  IFileImage* backGoundImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\TownStage.png", IMGKEY_BackGoundImage);
  backGoundImage->CalculateTransformByAuto({.emptyColor = Color8Bit(77, 111, 111, 0), .reCalculateHeight = true, .start = {0.0f, 0.0f}, .end = {779.0f, 2015.0f}});
  IFileImage* blackBoardImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\TownStage.png", IMGKEY_BlackBoardImage);
  //blackBoardImage->CalculateTransformByAuto({.emptyColor = Color8Bit(77, 111, 111, 0), .reCalculateHeight = true, .start = {0.0f, 0.0f}, .end = {779.0f, 2015.0f}});
  IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Box.png", IMGKEY_IoriImage);
  ioriImage->CalculateTransformFromCSV("..\\ContentsResource\\Iori.csv");
  IFileImage* reverseIoriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Box.png", -IMGKEY_IoriImage);
  reverseIoriImage->ReverseCalculateTransformFromCSV_Async("..\\ContentsResource\\Iori.csv");
  IFileImage* changImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Box.png", IMGKEY_ChangImage);
  changImage->CalculateTransformFromCSV("..\\ContentsResource\\Chang.csv");
  IFileImage* reverseChangImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Box.png", -IMGKEY_ChangImage);
  reverseChangImage->ReverseCalculateTransformFromCSV_Async("..\\ContentsResource\\Chang.csv");
  IFileImage* healthBarImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\HealthBar.png", IMGKEY_HealthBarImage);
  healthBarImage->CalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);
  IFileImage* reverseHealthBarImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\HealthBar.png", -IMGKEY_HealthBarImage);
  reverseHealthBarImage->ReverseCalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);
  IFileImage* healthImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Health.png", IMGKEY_HealthImage);
  healthImage->CalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);
  IFileImage* effectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\effect01.png", IMGKEY_EffectImage);
  effectImage->CalculateTransformFromDrawBoxImage(Color8Bit{128, 0, 255, 0}, Color8Bit::Magenta);
  

  // TODO : 
  // 반전된 Health는 logic으로, 원본 이미지는 여러 포인터가 가르킥로있고, 이미지를 어떻게 그릴지만 각자 알아서 그림.
  // UI 이미지는 래퍼로 감싸서 position하고, scale 등 정보로 Render를 그림.
  IFileImage* reverseHealthImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Health.png", -IMGKEY_HealthImage);
  reverseHealthImage->ReverseCalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);

  // MOUSE
  pMouse_ = SpawnMouse();
  pMouse_->SetImage(ImgManager::GetIntance()->GetImg(IMGKEY_MouseImage));
  pMouse_->SetAlpha(1.0f);
  Vector localScale = {0.1f, 0.1f};
  pMouse_->SetRenderLocalScale(localScale);

  Vector newPosition = {100.0f, -70.0f};
  newPosition = newPosition * localScale;
  pMouse_->SetRenderPosition(newPosition);
  pMouse_->ShowCursor(false);
  pMouse_->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));

  // BACKGROUND
  pBackGround_ = SpawnActor<BackGround>(ActorGroupEngineType::ActorGroupEngineType_BackGround);
  Vector imageScale = backGoundImage->GetScale(1);
  backGroundImageScale_ = imageScale * levelLocalScale_;
  pBackGround_->SetPosition({backGroundImageScale_.X / 2, backGroundImageScale_.Y / 2});
  pBackGround_->SetUseCameraposition(true);

  // BACKGROUND
  //pBackGround_ = SpawnActor<BackGround>(ActorGroupEngineType::ActorGroupEngineType_BackGround);
  //Vector imageScale = backGoundImage->GetScale(1);
  //backGroundImageScale_ = imageScale * levelLocalScale_;
  //pBackGround_->SetPosition({backGroundImageScale_.X / 2, backGroundImageScale_.Y / 2});
  //pBackGround_->SetUseCameraposition(true);

  // CAMERA SPAWN
  pCamera_ = SpawnActor<CameraTarget>();

  // IORI
  pPlayer1_ = SpawnActor<Iori>(ActorGroupEngineType::ActorGroupEngineType_None);
  player1SpawnPostion_ = Vector(backGroundImageScale_.X * 0.5f - 300, backGroundImageScale_.Y * 0.5f + 210.0f);
  pPlayer1_->Initialize(player1SpawnPostion_, true, false);

  // CHANG
  pPlayer2_ = SpawnActor<Chang>(ActorGroupEngineType::ActorGroupEngineType_None);
  player2SpawnPostion_ = Vector(backGroundImageScale_.X * 0.5f + 200, backGroundImageScale_.Y * 0.5f + 130.0f);
  pPlayer2_->Initialize(player2SpawnPostion_, true, true);

  // HUD
  HUD_ = SpawnActor<UI>(ActorGroupEngineType::ActorGroupEngineType_UI);
  HUD_->SetPosition({backbufferScale.HalfX(), backbufferScale.HalfY()});
  HUD_->SetScale({backbufferScale.X, backbufferScale.Y});
  HUD_->SetOriginColor(Color8Bit::White);  // 디버그 할때는 오리지널 컬러로 변경.
  HUD_->ChangeClearColor_(false);
  ImageRenderer* pHUDRenderer_ = HUD_->GetImageRenderer();
  if (nullptr == pHUDRenderer_) {
    return;
  }
  pHUDRenderer_->SetTransparentColor(Color8Bit::White);

  // PLAYER_1 UI
  Portrait* portraitPlayer1 = HUD_->CreateUIComponent<Portrait>();
  portraitPlayer1->Initialize(-IMGKEY_IoriImage, 655, ioriTransparentColor);
  portraitPlayer1->SetPosition({90.0f, 100.0f});

  HealthBar* healthBarPlayer1 = HUD_->CreateUIComponent<HealthBar>();
  healthBarPlayer1->Initialize(IMGKEY_HealthBarImage, 0, Color8Bit(0, 0, 0, 0));
  healthBarPlayer1->SetPosition({490.0f, 102.0f});

  Health* healthPlayer1 = HUD_->CreateUIComponent<Health>();
  healthPlayer1->Initialize(pPlayer1_, IMGKEY_HealthImage, 0, Color8Bit(0, 0, 0, 0), {490.0f, 102.0f}, false);

  // PLAYER_2 UI
  Portrait* portraitPlayer2 = HUD_->CreateUIComponent<Portrait>();
  portraitPlayer2->Initialize(IMGKEY_ChangImage, 399, changTransparentColor);
  portraitPlayer2->SetPosition({1810.0f, 100.0f});

  HealthBar* healthBarPlayer2 = HUD_->CreateUIComponent<HealthBar>();
  healthBarPlayer2->Initialize(-IMGKEY_HealthBarImage, 0, Color8Bit(0, 0, 0, 0));
  healthBarPlayer2->SetPosition({1415.0f, 102.0f});

  Health* healthPlayer2 = HUD_->CreateUIComponent<Health>();
  healthPlayer2->Initialize(pPlayer2_, -IMGKEY_HealthImage, 0, Color8Bit(0, 0, 0, 0), {1415.0f, 102.0f}, true);

  // CAMERA SETTING
  pCamera_->SetPosition({backGroundImageScale_.X / 2, pCamera_->GetCameraHeight()});
  CameraManager::Instance()->SetTarget(pCamera_);

  // EFFECT
  EffectManager::Instance()->RegistEffect(1, IMGKEY_EffectImage, 7, 10, 50, false, Color8Bit{128, 0, 255, 0});
  EffectManager::Instance()->RegistEffect(2, IMGKEY_EffectImage, 19, 22, 50, false, Color8Bit{128, 0, 255, 0});
  EffectManager::Instance()->RegistEffect(3, IMGKEY_EffectImage, 31, 34, 50, false, Color8Bit{128, 0, 255, 0});

  /*EffectManager::Instance()->RegistEffect(1, 3, 239, 244, 50, false, Color8Bit{169, 139, 150, 0});
  EffectManager::Instance()->SpawnEffect(this, 1, {500.0f, 500.0f});*/

  // SOUND
  /*Path soundPath;
  soundPath.MoveParent();
  soundPath.Move("ContentsResource\\Sound\\");
  soundPath.Move("Kyoku-Gen.mp3");
  SoundManager::Instance()->Load(soundPath, 0);
  channel_ = SoundManager::Instance()->SoundPlay(0);*/
}

void KOFLevel::Tick(unsigned long long dletaTick) {
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


  pPlayer1_->SetIsAtMapEdge(false);
  pPlayer2_->SetIsAtMapEdge(false);

  float margin = 15.0f;
  float cameraHeight = pCamera_->GetCameraHeight();

  float left = pCamera_->GetPosition().X - backbufferScale.X / 2;
  float right = pCamera_->GetPosition().X + backbufferScale.X / 2;

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
        pCamera_->SetPosition({player1Left + backbufferScale.X / 2, cameraHeight});
      } else {
        pPlayer1_->SetPosition({left + pPlayer1_->CharacterScale().HalfX(), player1Position.Y});
        pPlayer1_->SetIsAtMapEdge(true);
      }
    }

    if (player2Right > right) {
      if (player1Left - left > 0 && right <= backGroundImageScale_.X - margin) {
        pCamera_->SetPosition({player2Right - backbufferScale.X / 2, cameraHeight});
      } else {
        pPlayer2_->SetPosition({right - pPlayer2_->CharacterScale().HalfX(), player2Position.Y});
        pPlayer2_->SetIsAtMapEdge(true);
      }
    }

  } else {
    if (player2Left < left) {
      if (right - player1Right > 0 && left >= margin) {
        pCamera_->SetPosition({player2Left + backbufferScale.X / 2, cameraHeight});
      } else {
        pPlayer2_->SetPosition({left + pPlayer2_->CharacterScale().HalfX(), player2Position.Y});
        pPlayer2_->SetIsAtMapEdge(true);
      }
    }

    if (player1Right > right) {
      if (player2Left - left > 0 && right <= backGroundImageScale_.X - margin) {
        pCamera_->SetPosition({player1Right - backbufferScale.X / 2, cameraHeight});
      } else {
        pPlayer1_->SetPosition({right - pPlayer1_->CharacterScale().HalfX(), player1Position.Y});
        pPlayer1_->SetIsAtMapEdge(true);
      }
    }
  }

  // CameraPosition Y
  float player1JumpHeight = player1SpawnPostion_.Y - player1Position.Y;
  float player2JumpHeight = player2SpawnPostion_.Y - player2Position.Y;

  if (player1JumpHeight > 0 || player2JumpHeight > 0) {
    float addHeight = (player1JumpHeight > player2JumpHeight) ? player1JumpHeight : player2JumpHeight;
    const Vector& cameraPosition = pCamera_->GetPosition();
    pCamera_->SetPosition({cameraPosition.X, cameraHeight - addHeight / 5});
  }
}

void KOFLevel::SwapPosition() {
  const Vector& player1Postion = pPlayer1_->GetPosition();
  const Vector& player2Postion = pPlayer2_->GetPosition();

  pPlayer1_->SetFacingRight(player1Postion.X < player2Postion.X);
  pPlayer2_->SetFacingRight(!(player1Postion.X < player2Postion.X));
}

Vector KOFLevel::GetBackGroundImageScale() const {
  return backGroundImageScale_;
}
