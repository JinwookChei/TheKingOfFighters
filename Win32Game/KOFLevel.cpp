#include "stdafx.h"
#include "KOFLevel.h"
#include "CameraTarget.h"
#include "Player.h"
#include "Iori.h"
#include "Chang.h"
#include "BackGround.h"

KOFLevel::KOFLevel()
    : cameraTarget(nullptr),
      player1_(nullptr),
      player2_(nullptr) {
}

KOFLevel::~KOFLevel() {
}

void KOFLevel::BeginPlay() {
  Vector backbufferScale = GEngineCore->GetBackbufferScale();

  // MOUSE
  IImage* mouseImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\mousePointer.png", 1);
  Mouse* mouse = SpawnMouse();
  mouse->SetImage(ImgManager::GetIntance()->GetImg(1));
  mouse->SetAlpha(1.0f);
  Vector localScale = {0.1f, 0.1f};
  mouse->SetRenderLocalScale(localScale);

  Vector newPosition = {100.0f, -70.0f};
  newPosition = newPosition * localScale;
  mouse->SetRenderPosition(newPosition);
  mouse->ShowCursor(false);
  mouse->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));

  // BACKGROUND
  IFileImage* backGoundImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\TownStage.png", 2);
  backGoundImage->CalculateTransformByAuto({.emptyColor = Color8Bit(77, 111, 111, 0), .reCalculateHeight = true, .start = {0.0f, 0.0f}, .end = {779.0f, 2015.0f}});
  BackGround* backGround = SpawnActor<BackGround>(ActorGroupEngineType::ActorGroupEngineType_BackGround);
  Vector imageScale = backGoundImage->GetScale(1);
  Vector backGroundImageScale = {imageScale.X * 4.5f, imageScale.Y * 4.5f};
  backGround->SetPosition({backGroundImageScale.X / 2, backGroundImageScale.Y / 2});
  backGround->SetUseCameraposition(true);

  // CAMERA SPAWN
  cameraTarget = SpawnActor<CameraTarget>();

  // IORI
  IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Box.png", 3);
  ioriImage->CalculateTransformFromCSV("..\\ContentsResource\\Iori.csv");
  IFileImage* reverseIoriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Box.png", -3);
  reverseIoriImage->ReverseCalculateTransformFromCSV("..\\ContentsResource\\Iori.csv");
  player1_ = SpawnActor<Iori>(ActorGroupEngineType::ActorGroupEngineType_None);
  player1_->Initialize(Vector(backGroundImageScale.X * 0.5f - 300, backGroundImageScale.Y * 0.5f + 210.0f), true, false);

  // Iori* iori = SpawnActor<Iori>(ActorGroupEngineType::ActorGroupEngineType_None);
  // iori->Initialize(Vector(backGroundImageScale.X * 0.5f - 300, backGroundImageScale.Y * 0.5f + 210.0f), true, false);

  // Iori* iori2 = SpawnActor<Iori>(ActorGroupEngineType::ActorGroupEngineType_None);
  // iori2->Initialize(Vector(backGroundImageScale.X * 0.5f + 300, backGroundImageScale.Y * 0.5f + 210.0f), true, false);

  // CHANG
  IFileImage* changImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Box.png", 4);
  changImage->CalculateTransformFromCSV("..\\ContentsResource\\Chang.csv");
  IFileImage* reverseChangImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Box.png", -4);
  reverseChangImage->ReverseCalculateTransformFromCSV("..\\ContentsResource\\Chang.csv");

  player2_ = SpawnActor<Chang>(ActorGroupEngineType::ActorGroupEngineType_None);
  player2_->Initialize(Vector(backGroundImageScale.X * 0.5f + 200, backGroundImageScale.Y * 0.5f + 130.0f), true, true);
  // Chang* chang = SpawnActor<Chang>(ActorGroupEngineType::ActorGroupEngineType_None);
  // chang->Initialize(Vector(backGroundImageScale.X * 0.5f + 200, backGroundImageScale.Y * 0.5f + 130.0f), true, true);

  // CAMERA SETTING
  cameraTarget->Initialize(backGroundImageScale, backbufferScale.X, 600.0f, player1_, player2_);
  CameraManager::Instance()->SetTarget(cameraTarget);


  // EFFECT
  EffectManager::Instance()->RegistEffect(1, 3, 239, 244, 50, false, Color8Bit{169, 139, 150, 0});
  EffectManager::Instance()->SpawnEffect(this, 1, {500.0f, 500.0f});

  // SOUND
  Path soundPath;
  soundPath.MoveParent();
  soundPath.Move("ContentsResource\\Sound\\");
  soundPath.Move("Kyoku-Gen.mp3");
  SoundManager::Instance()->Load(soundPath, 0);
  channel_ = SoundManager::Instance()->SoundPlay(0);
}

void KOFLevel::Tick(unsigned long long dletaTick) {
  SwapPosition();

  if (false == InputManager::Instance()->IsAnyKeyPress()) {
    return;
  }

  if (InputManager::Instance()->IsDown(VK_F1)) {
    SetDebugRender(!GetDebugRender());
  }

  if (InputManager::Instance()->IsDown(VK_F2)) {
    SetCollisionRender(!GetCollisionRender());
  }
}

void KOFLevel::SwapPosition() {
  const Vector& player1Postion = player1_->GetPosition();
  const Vector& player2Postion = player2_->GetPosition();

  player1_->Flip(!(player1Postion.X < player2Postion.X));
  player2_->Flip(player1Postion.X < player2Postion.X);
}
