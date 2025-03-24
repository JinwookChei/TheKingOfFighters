#include "stdafx.h"
#include "KOFLevel.h"
#include "Iori.h"
#include "Chang.h"
#include "BackGround.h"


KOFLevel::KOFLevel() {
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
  backGround->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f - 22));

  // GAME
  IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Box.png", 3);
  ioriImage->CalculateTransformFromCSV("..\\ContentsResource\\Iori1.csv");

  Iori* iori = SpawnActor<Iori>(ActorGroupEngineType::ActorGroupEngineType_None);
  iori->SetPosition(Vector(backbufferScale.X * 0.5f - 200, backbufferScale.Y * 0.5f + 210.0f));

  //IFileImage* changImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Box.png", 4);
  //changImage->CalculateTransformFromCSV("..\\ContentsResource\\ChangBoundBoxes.csv");
  //Chang* chang = SpawnActor<Chang>();
  //chang->SetPosition(Vector(backbufferScale.X * 0.5f + 200, backbufferScale.Y * 0.5f));
}

void KOFLevel::Tick(unsigned long long dletaTick) {
}
