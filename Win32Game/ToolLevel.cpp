#include "stdafx.h"
#include "ToolLevel.h"
#include "Button.h"
#include "ViewPortImage.h"
#include "CrossHair.h"
#include "CrossHairControlButton.h"
#include "WriteButton.h"
#include "ImageMoveButton.h"
#include "NextImageButton.h"
#include "HitBoxButton.h"
#include "ToolIori.h"

ToolLevel::ToolLevel() {
  Vector backbufferScale = GEngineCore->GetBackbufferScale();

  // MOUSE
  IFileImage* mouseImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\mousePointer.png", 0);
  Mouse* mouse = SpawnMouse();
  mouse->SetImage(ImgManager::GetIntance()->GetImg(0));
  mouse->SetAlpha(1.0f);
  Vector localScale = {0.1f, 0.1f};
  mouse->SetRenderLocalScale(localScale);
  Vector newPosition = {100.0f, -70.0f};
  newPosition = newPosition * localScale;
  mouse->SetRenderPosition(newPosition);
  mouse->ShowCursor(false);
  mouse->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));

  // IMAGEOBJECT
  IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Box.png", 1);
  // ioriImage->DetectBoundBoxes(Color8Bit{169, 139, 150, 0}, Color8Bit::Magenta);
  // ioriImage->CalculateTransformFromBoundingBoxDatas();
  ioriImage->CalculateTransform(10, 100);

  UI* ViewPortUI = SpawnActor<UI>();
  ViewPortUI->SetPosition(Vector(backbufferScale.HalfX(), backbufferScale.HalfY()));
  ViewPortUI->SetScale({600.0f, 600.0f});
  ViewPortUI->MakeCollision();
  ViewPortUI->SetOriginColor(Color8Bit::Magenta);
  ViewPortUI->ChangeClearColor_(false);

  ViewPortImage* viewPortImage = ViewPortUI->CreateUIComponent<ViewPortImage>();
  CrossHair* crossHair = ViewPortUI->CreateUIComponent<CrossHair>();

  /*IFileImage* ChangImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Box.png", 1);
  ChangImage->DetectBoundBoxes(Color8Bit{17, 91, 124, 0}, Color8Bit::Magenta);
  ChangImage->CalculateTransformFromBoundingBoxDatas();
  Object* object = SpawnActor<Object>();
  object->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));*/



   // COLLISION POINT
   UI* CollisionCreateUI = SpawnActor<UI>();
   CollisionCreateUI->SetOriginColor(Color8Bit::CyanAlpha);
   CollisionCreateUI->SetPosition({1500.0f, 100.0f});
   CollisionCreateUI->SetScale({200.0f, 50.0f});
   CollisionCreateUI->MakeCollision();
   HitBoxButton* temp = CollisionCreateUI->CreateUIComponent<HitBoxButton>();
   temp->BindUI(ViewPortUI);
   temp->SetScale({200.0f, 50.0f});
   temp->SetPosition({CollisionCreateUI->GetScale().HalfX(), CollisionCreateUI->GetScale().HalfY()});


  // CROSSHAIR CONTROL
  UI* crossHairPlusRowUI = SpawnActor<UI>();
  crossHairPlusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairPlusRowUI->SetPosition(Vector(400.0f, 100.0f));
  crossHairPlusRowUI->SetScale({200.0f, 50.0f});
  crossHairPlusRowUI->MakeCollision();
  CrossHairControlButton* crossHairButtonPlusRow = crossHairPlusRowUI->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonPlusRow->SetControlType(CrossHairControlType_PlusRow);
  crossHairButtonPlusRow->SetCrossHair(crossHair);
  crossHairButtonPlusRow->SetScale({200.0f, 50.0f});
  crossHairButtonPlusRow->SetPosition({crossHairPlusRowUI->GetScale().HalfX(), crossHairPlusRowUI->GetScale().HalfY()});
  TextComponent* plusRowTextComponent = crossHairPlusRowUI->CreateUIComponent<TextComponent>();
  plusRowTextComponent->SetText(L"Row++", 20, Color8Bit::Red);
  plusRowTextComponent->SetFont(L"CONSOLELAS");
  plusRowTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairMinusRowUI = SpawnActor<UI>();
  crossHairMinusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairMinusRowUI->SetPosition(Vector(200.0f, 100.0f));
  crossHairMinusRowUI->SetScale({200.0f, 50.0f});
  crossHairMinusRowUI->MakeCollision();
  CrossHairControlButton* crossHairButtonMinusRow = crossHairMinusRowUI->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonMinusRow->SetControlType(CrossHairControlType_MinusRow);
  crossHairButtonMinusRow->SetCrossHair(crossHair);
  crossHairButtonMinusRow->SetScale({200.0f, 50.0f});
  crossHairButtonMinusRow->SetPosition({crossHairMinusRowUI->GetScale().HalfX(), crossHairMinusRowUI->GetScale().HalfY()});
  TextComponent* minusRowTextComponent = crossHairMinusRowUI->CreateUIComponent<TextComponent>();
  minusRowTextComponent->SetText(L"Row--", 20, Color8Bit::Red);
  minusRowTextComponent->SetFont(L"CONSOLELAS");
  minusRowTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairPlusColUI = SpawnActor<UI>();
  crossHairPlusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairPlusColUI->SetPosition(Vector(400.0f, 200.0f));
  crossHairPlusColUI->SetScale({200.0f, 50.0f});
  crossHairPlusColUI->MakeCollision();
  CrossHairControlButton* crossHairButtonPlusCol = crossHairPlusColUI->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonPlusCol->SetControlType(CrossHairControlType_PlusCol);
  crossHairButtonPlusCol->SetCrossHair(crossHair);
  crossHairButtonPlusCol->SetScale({200.0f, 50.0f});
  crossHairButtonPlusCol->SetPosition({crossHairPlusColUI->GetScale().HalfX(), crossHairPlusColUI->GetScale().HalfY()});
  TextComponent* plusColTextComponent = crossHairPlusColUI->CreateUIComponent<TextComponent>();
  plusColTextComponent->SetText(L"Col++", 20, Color8Bit::Red);
  plusColTextComponent->SetFont(L"CONSOLELAS");
  plusColTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairMinusColUI = SpawnActor<UI>();
  crossHairMinusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairMinusColUI->SetPosition(Vector(200.0f, 200.0f));
  crossHairMinusColUI->SetScale({200.0f, 50.0f});
  crossHairMinusColUI->MakeCollision();
  CrossHairControlButton* crossHairButtonMinusCol = crossHairMinusColUI->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonMinusCol->SetControlType(CrossHairControlType_MinusCol);
  crossHairButtonMinusCol->SetCrossHair(crossHair);
  crossHairButtonMinusCol->SetScale({200.0f, 50.0f});
  crossHairButtonMinusCol->SetPosition({crossHairMinusColUI->GetScale().HalfX(), crossHairMinusColUI->GetScale().HalfY()});
  TextComponent* minusColTextComponent = crossHairMinusColUI->CreateUIComponent<TextComponent>();
  minusColTextComponent->SetText(L"Col--", 20, Color8Bit::Red);
  minusColTextComponent->SetFont(L"CONSOLELAS");
  minusColTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairResetUI = SpawnActor<UI>();
  crossHairResetUI->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairResetUI->SetPosition(Vector(300.0f, 300.0f));
  crossHairResetUI->SetScale({400.0f, 50.0f});
  crossHairResetUI->MakeCollision();
  CrossHairControlButton* crossHairButtonReset = crossHairResetUI->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonReset->SetControlType(CrossHairControlType_Reset);
  crossHairButtonReset->SetCrossHair(crossHair);
  crossHairButtonReset->SetScale({400.0f, 50.0f});
  crossHairButtonReset->SetPosition({crossHairResetUI->GetScale().HalfX(), crossHairResetUI->GetScale().HalfY()});
  TextComponent* resetTextComponent = crossHairResetUI->CreateUIComponent<TextComponent>();
  resetTextComponent->SetText(L"RESET", 20, Color8Bit::Red);
  resetTextComponent->SetFont(L"CONSOLELAS");
  resetTextComponent->SetPosition({200.0f, 20.0f});

  // WRITE
  UI* writeToCSVUI = SpawnActor<UI>();
  writeToCSVUI->SetOriginColor(Color8Bit::CyanAlpha);
  writeToCSVUI->SetPosition(Vector(300.0f, 900.0f));
  writeToCSVUI->SetScale({400.0f, 50.0f});
  writeToCSVUI->MakeCollision();
  WriteButton* writeToCSVButton = writeToCSVUI->CreateUIComponent<WriteButton>();
  writeToCSVButton->BindObject(viewPortImage);
  writeToCSVButton->SetFilePath("../ContentsResource/Iori.csv");
  writeToCSVButton->SetScale({400.0f, 50.0f});
  writeToCSVButton->SetPosition({writeToCSVUI->GetScale().HalfX(), writeToCSVUI->GetScale().HalfY()});
  TextComponent* writeTextComponent = writeToCSVUI->CreateUIComponent<TextComponent>();
  writeTextComponent->SetText(L"WriteToCSV", 20, Color8Bit::Red);
  writeTextComponent->SetFont(L"CONSOLELAS");
  writeTextComponent->SetPosition({200.0f, 20.0f});

  // MOVEOBEJCT
  UI* moveImagePlusRowUI = SpawnActor<UI>();
  moveImagePlusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  moveImagePlusRowUI->SetPosition(Vector(400.0f, 400.0f));
  moveImagePlusRowUI->SetScale({200.0f, 50.0f});
  moveImagePlusRowUI->MakeCollision();
  ImageMoveButton* moveImagePlusRowButton = moveImagePlusRowUI->CreateUIComponent<ImageMoveButton>();
  moveImagePlusRowButton->BindObject(viewPortImage);
  moveImagePlusRowButton->SetImageMoveDirType(ImageMoveDirType::IMD_PlusRow);
  moveImagePlusRowButton->SetScale({200.0f, 50.0f});
  moveImagePlusRowButton->SetPosition({moveImagePlusRowUI->GetScale().HalfX(), moveImagePlusRowUI->GetScale().HalfY()});
  TextComponent* movePlusRowTextComponent = moveImagePlusRowUI->CreateUIComponent<TextComponent>();
  movePlusRowTextComponent->SetText(L"MoveRow++", 20, Color8Bit::Red);
  movePlusRowTextComponent->SetFont(L"CONSOLELAS");
  movePlusRowTextComponent->SetPosition({100.0f, 20.0f});

  UI* moveImageMinusRowUI = SpawnActor<UI>();
  moveImageMinusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  moveImageMinusRowUI->SetPosition(Vector(200.0f, 400.0f));
  moveImageMinusRowUI->SetScale({200.0f, 50.0f});
  moveImageMinusRowUI->MakeCollision();
  ImageMoveButton* moveImageMinusRowButton = moveImageMinusRowUI->CreateUIComponent<ImageMoveButton>();
  moveImageMinusRowButton->BindObject(viewPortImage);
  moveImageMinusRowButton->SetImageMoveDirType(ImageMoveDirType::IMD_MinusRow);
  moveImageMinusRowButton->SetScale({200.0f, 50.0f});
  moveImageMinusRowButton->SetPosition({moveImageMinusRowUI->GetScale().HalfX(), moveImageMinusRowUI->GetScale().HalfY()});
  TextComponent* moveMinusRowTextComponent = moveImageMinusRowUI->CreateUIComponent<TextComponent>();
  moveMinusRowTextComponent->SetText(L"MoveRow--", 20, Color8Bit::Red);
  moveMinusRowTextComponent->SetFont(L"CONSOLELAS");
  moveMinusRowTextComponent->SetPosition({100.0f, 20.0f});

  
  UI* moveImagePlusColUI = SpawnActor<UI>();
  moveImagePlusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  moveImagePlusColUI->SetPosition(Vector(400.0f, 500.0f));
  moveImagePlusColUI->SetScale({200.0f, 50.0f});
  moveImagePlusColUI->MakeCollision();
  ImageMoveButton* moveImagePlusColButton = moveImagePlusColUI->CreateUIComponent<ImageMoveButton>();
  moveImagePlusColButton->BindObject(viewPortImage);
  moveImagePlusColButton->SetImageMoveDirType(ImageMoveDirType::IMD_PlusCol);
  moveImagePlusColButton->SetScale({200.0f, 50.0f});
  moveImagePlusColButton->SetPosition({moveImagePlusColUI->GetScale().HalfX(), moveImagePlusColUI->GetScale().HalfY()});
  TextComponent* movePlusColTextComponent = moveImagePlusColUI->CreateUIComponent<TextComponent>();
  movePlusColTextComponent->SetText(L"MoveCol++", 20, Color8Bit::Red);
  movePlusColTextComponent->SetFont(L"CONSOLELAS");
  movePlusColTextComponent->SetPosition({100.0f, 20.0f});

  UI* moveImageMinusColUI = SpawnActor<UI>();
  moveImageMinusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  moveImageMinusColUI->SetPosition(Vector(200.0f, 500.0f));
  moveImageMinusColUI->SetScale({200.0f, 50.0f});
  moveImageMinusColUI->MakeCollision();
  ImageMoveButton* moveImageMinusColButton = moveImageMinusColUI->CreateUIComponent<ImageMoveButton>();
  moveImageMinusColButton->BindObject(viewPortImage);
  moveImageMinusColButton->SetImageMoveDirType(ImageMoveDirType::IMD_MinusCol);
  moveImageMinusColButton->SetScale({200.0f, 50.0f});
  moveImageMinusColButton->SetPosition({moveImageMinusColUI->GetScale().HalfX(), moveImageMinusColUI->GetScale().HalfY()});
  TextComponent* moveMinusColTextComponent = moveImageMinusColUI->CreateUIComponent<TextComponent>();
  moveMinusColTextComponent->SetText(L"MoveCol--", 20, Color8Bit::Red);
  moveMinusColTextComponent->SetFont(L"CONSOLELAS");
  moveMinusColTextComponent->SetPosition({100.0f, 20.0f});

  UI* moveImageResetUI = SpawnActor<UI>();
  moveImageResetUI->SetOriginColor(Color8Bit::CyanAlpha);
  moveImageResetUI->SetPosition(Vector(300.0f, 600.0f));
  moveImageResetUI->SetScale({400.0f, 50.0f});
  moveImageResetUI->MakeCollision();
  ImageMoveButton* moveImageResetButton = moveImageResetUI->CreateUIComponent<ImageMoveButton>();
  moveImageResetButton->BindObject(viewPortImage);
  moveImageResetButton->SetImageMoveDirType(ImageMoveDirType::IMD_Reset);
  moveImageResetButton->SetScale({400.0f, 50.0f});
  moveImageResetButton->SetPosition({moveImageResetUI->GetScale().HalfX(), moveImageResetUI->GetScale().HalfY()});
  TextComponent* moveResetTextComponent = moveImageResetUI->CreateUIComponent<TextComponent>();
  moveResetTextComponent->SetText(L"MoveReset", 20, Color8Bit::Red);
  moveResetTextComponent->SetFont(L"CONSOLELAS");
  moveResetTextComponent->SetPosition({200, 20.0f});

  // NEXT IMAGE
  UI* nextImageUI = SpawnActor<UI>();
  nextImageUI->SetOriginColor(Color8Bit::CyanAlpha);
  nextImageUI->SetPosition(Vector(400.0f, 700.0f));
  nextImageUI->SetScale({200.0f, 50.0f});
  nextImageUI->MakeCollision();
  NextImageButton* nextImageButton = nextImageUI->CreateUIComponent<NextImageButton>();
  nextImageButton->BindObject(viewPortImage);
  nextImageButton->SetNextImageType(NextImageType::NextImage_Next);
  nextImageButton->SetScale({200.0f, 50.0f});
  nextImageButton->SetPosition({nextImageUI->GetScale().HalfX(), nextImageUI->GetScale().HalfY()});
  TextComponent* nextImageTextComponent = nextImageUI->CreateUIComponent<TextComponent>();
  nextImageTextComponent->SetText(L"NEXT", 20, Color8Bit::Red);
  nextImageTextComponent->SetFont(L"CONSOLELAS");
  nextImageTextComponent->SetPosition({100.0f, 20.0f});

  UI* prevImageUI = SpawnActor<UI>();
  prevImageUI->SetOriginColor(Color8Bit::CyanAlpha);
  prevImageUI->SetPosition(Vector(200.0f, 700.0f));
  prevImageUI->SetScale({200.0f, 50.0f});
  prevImageUI->MakeCollision();
  NextImageButton* prevImageButton = prevImageUI->CreateUIComponent<NextImageButton>();
  prevImageButton->BindObject(viewPortImage);
  prevImageButton->SetNextImageType(NextImageType::NextImage_Prev);
  prevImageButton->SetScale({200.0f, 50.0f});
  prevImageButton->SetPosition({prevImageUI->GetScale().HalfX(), prevImageUI->GetScale().HalfY()});
  TextComponent* prevImageTextComponent = prevImageUI->CreateUIComponent<TextComponent>();
  prevImageTextComponent->SetText(L"PREV", 20, Color8Bit::Red);
  prevImageTextComponent->SetFont(L"CONSOLELAS");
  prevImageTextComponent->SetPosition({100.0f, 20.0f});

  // BUTTON
  // UI* UI2 = SpawnActor<UI>();
  // UI2->SetPosition({400.0f, 500.0f});
  // UI2->SetScale({200.0f, 200.0f});
  // UI2->SetOriginColor(Color8Bit::RedAlpha);
  // UI2->MakeCollision();
  // Button* Button2 = UI2->CreateUIComponent<Button>();
  // TextComponent* Text2 = UI2->CreateUIComponent<TextComponent>();
  // Text2->SetText(L"SetText", 50, Color8Bit::Yellow);
  // Text2->SetFont(L"CONSOLELAS");
  // Text2->SetPosition({100.0f, 100.0f});

  // UI* UI3 = SpawnActor<UI>();
  // UI3->SetPosition({300.0f, 500.0f});
  // UI3->SetScale({200.0f, 200.0f});
  // UI3->SetOriginColor(Color8Bit::RedAlpha);
  // UI3->MakeCollision();
  // TextComponent* Text3 = UI3->CreateUIComponent<TextComponent>();
  // Text3->SetText(L"SetText1", 50, Color8Bit::Yellow);
  // Text3->SetFont(L"consolelas");
  // Text3->SetPosition({100.0f, 100.0f});
  // UI3->SetUseMousePosition(true);

  // LINE

  // TOOLS
}

ToolLevel::~ToolLevel() {
}

void ToolLevel::BeginPlay() {
}

void ToolLevel::Tick(unsigned long long dletaTick) {
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
