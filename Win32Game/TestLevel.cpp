#include "stdafx.h"
#include "TestLevel.h"
#include "Player.h"
#include "Enemy.h"
#include "Button.h"

TestLevel::TestLevel() {
}

TestLevel::~TestLevel() {
}

void TestLevel::BeginPlay() {
  IFileImage* image = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Box.png", 0);
  //image->CalculateTransformByAuto({.emptyColor = Color8Bit(86, 177, 222, 0), .reCalculateHeight = true, .start = {0.0f, 260.0f}, .end = {910.0f, 511.0f}});
  image = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\mousePointer.png", 1);

  /*image = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Iori.png", 2);
  image->CalculateTransformByAuto({.emptyColor = Color8Bit(240, 0, 240, 0), .reCalculateHeight = true});*/

  // ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\test.tga", 1);
  IImage* pImage1 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\test.png", 2);
  // IImage* pImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\TestPlayer_Left.png", 3);
  //pImage->CalculateTransform(5, 8);

  scale_ = pImage1->GetScale();

  Player* player = SpawnActor<Player>();

  //Enemy* enemy = SpawnActor<Enemy>();





  Vector backbufferScale = GEngineCore->GetBackbufferScale();

  UI* button = SpawnActor<UI>();
  button->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));
  button->SetScale({300.0f, 500.0f});
  button->SetOriginColor(Color8Bit::Red);
  button->MakeCollision();
  //button->SetUseMousePosition(true);
  button->CreateUIComponent<Button>();

  button = SpawnActor<UI>();
  button->SetPosition({400.0f, 500.0f});
  button->SetScale({200.0f, 200.0f});
  button->SetOriginColor(Color8Bit::RedAlpha);
  button->MakeCollision();
  TextComponent* newTextComponent = button->CreateUIComponent<TextComponent>();
  newTextComponent->SetText(L"SetText", 50, Color8Bit::Yellow);
  newTextComponent->SetFont(L"CONSOLELAS");
  newTextComponent->SetPosition({100.0f, 100.0f});

  button = SpawnActor<UI>();
  button->SetPosition({300.0f, 500.0f});
  button->SetScale({200.0f, 200.0f});
  button->SetOriginColor(Color8Bit::RedAlpha);
  button->MakeCollision();
  newTextComponent = button->CreateUIComponent<TextComponent>();
  newTextComponent->SetText(L"SetText", 50, Color8Bit::Yellow);
  newTextComponent->SetFont(L"consolelas");
  newTextComponent->SetPosition({100.0f, 100.0f});
  button->SetUseMousePosition(true);

  Mouse* mouse = SpawnMouse();
  mouse->SetImage(ImgManager::GetIntance()->GetImg(1));
  mouse->SetAlpha(1.0f);
  Vector localScale = {0.1f, 0.1f};
  mouse->SetRenderLocalScale(localScale);

  Vector newPosition = {100.0f, -70.0f};
  newPosition = newPosition * localScale;
  mouse->SetRenderPosition(newPosition);
  mouse->ShowCursor(false);

  //player->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));
  //enemy->SetPosition(player->GetPosition());
  mouse->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));

  // player->GetRender()->SetScale({10.0f, 10.0f});



  // TOOLS
}

void TestLevel::Tick(unsigned long long deltaTick) {
  if (false == InputManager::Instance()->IsAnyKeyPress()) {
    return;
  }

  if (InputManager::Instance()->IsDown(VK_F1)) {
    SetDebugRender(!GetDebugRender());
  }

  /*IImage* pFind = ImgManager::GetIntance()->GetImg(2);
  if (nullptr == pFind) {
    return;
  }

  if (InputManager::Instance()->IsDown('Q')) {
    position_.X += 1;
  } else if (InputManager::Instance()->IsDown('W')) {
    position_.X -= 1;
  }
  if (InputManager::Instance()->IsDown('E')) {
    position_.Y += 1;
  } else if (InputManager::Instance()->IsDown('D')) {
    position_.Y -= 1;
  }
  if (InputManager::Instance()->IsPress('O')) {
    scale_.X += 1;
  } else if (InputManager::Instance()->IsPress('P')) {
    scale_.X -= 1;
  }
  if (InputManager::Instance()->IsPress('I')) {
    scale_.Y += 1;
  } else if (InputManager::Instance()->IsPress('L')) {
    scale_.Y -= 1;
  }

  Transform newTransform;
  newTransform.SetPosition(position_);
  newTransform.SetScale(scale_ - position_);
  pFind->SetTransform(newTransform, 0);*/
}