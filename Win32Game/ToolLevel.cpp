#include "stdafx.h"
#include "ToolLevel.h"
#include "Button.h"
#include "Object.h"
#include "CrossHair.h"
#include "CrossHairControlButton.h"
#include "WriteButton.h"
#include "ImageMoveButton.h"
#include "NextImageButton.h"




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

  // OBJECT
  IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_Box.png", 1);
  //ioriImage->DetectBoundBoxes(Color8Bit{169, 139, 150, 0}, Color8Bit::Magenta);
  //ioriImage->CalculateTransformFromBoundingBoxDatas();
  ioriImage->CalculateTransform(100,50);
  Object* object = SpawnActor<Object>();
  object->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));

  /*IFileImage* ChangImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_Box.png", 1);
  ChangImage->DetectBoundBoxes(Color8Bit{17, 91, 124, 0}, Color8Bit::Magenta);
  ChangImage->CalculateTransformFromBoundingBoxDatas();
  Object* object = SpawnActor<Object>();
  object->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));*/

  // CROSSHAIR
  UI* crossHairUI = SpawnActor<UI>();
  crossHairUI->SetPosition(Vector(backbufferScale.X * 0.5f, backbufferScale.Y * 0.5f));
  crossHairUI->SetScale({600.0f, 600.0f});
  CrossHair* crossHair = crossHairUI->CreateUIComponent<CrossHair>();

  // CROSSHAIR CONTROL
  UI* crossHairPlusRow = SpawnActor<UI>();
  crossHairPlusRow->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairPlusRow->SetPosition(Vector(200.0f, 100.0f));
  crossHairPlusRow->SetScale({200.0f, 50.0f});
  crossHairPlusRow->MakeCollision();
  CrossHairControlButton* crossHairButtonPlusRow = crossHairPlusRow->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonPlusRow->SetControlType(CrossHairControlType_PlusRow);
  crossHairButtonPlusRow->SetCrossHair(crossHair);
  TextComponent* plusRowTextComponent = crossHairPlusRow->CreateUIComponent<TextComponent>();
  plusRowTextComponent->SetText(L"Row++", 20, Color8Bit::Red);
  plusRowTextComponent->SetFont(L"CONSOLELAS");
  plusRowTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairMinusRow = SpawnActor<UI>();
  crossHairMinusRow->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairMinusRow->SetPosition(Vector(400.0f, 100.0f));
  crossHairMinusRow->SetScale({200.0f, 50.0f});
  crossHairMinusRow->MakeCollision();
  CrossHairControlButton* crossHairButtonMinusRow = crossHairMinusRow->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonMinusRow->SetControlType(CrossHairControlType_MinusRow);
  crossHairButtonMinusRow->SetCrossHair(crossHair);
  TextComponent* minusRowTextComponent = crossHairMinusRow->CreateUIComponent<TextComponent>();
  minusRowTextComponent->SetText(L"Row--", 20, Color8Bit::Red);
  minusRowTextComponent->SetFont(L"CONSOLELAS");
  minusRowTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairPlusCol = SpawnActor<UI>();
  crossHairPlusCol->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairPlusCol->SetPosition(Vector(200.0f, 200.0f));
  crossHairPlusCol->SetScale({200.0f, 50.0f});
  crossHairPlusCol->MakeCollision();
  CrossHairControlButton* crossHairButtonPlusCol = crossHairPlusCol->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonPlusCol->SetControlType(CrossHairControlType_PlusCol);
  crossHairButtonPlusCol->SetCrossHair(crossHair);
  TextComponent* plusColTextComponent = crossHairPlusCol->CreateUIComponent<TextComponent>();
  plusColTextComponent->SetText(L"Col++", 20, Color8Bit::Red);
  plusColTextComponent->SetFont(L"CONSOLELAS");
  plusColTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairMinusCol = SpawnActor<UI>();
  crossHairMinusCol->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairMinusCol->SetPosition(Vector(400.0f, 200.0f));
  crossHairMinusCol->SetScale({200.0f, 50.0f});
  crossHairMinusCol->MakeCollision();
  CrossHairControlButton* crossHairButtonMinusCol = crossHairMinusCol->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonMinusCol->SetControlType(CrossHairControlType_MinusCol);
  crossHairButtonMinusCol->SetCrossHair(crossHair);
  TextComponent* minusColTextComponent = crossHairMinusCol->CreateUIComponent<TextComponent>();
  minusColTextComponent->SetText(L"Col--", 20, Color8Bit::Red);
  minusColTextComponent->SetFont(L"CONSOLELAS");
  minusColTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairReset = SpawnActor<UI>();
  crossHairReset->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairReset->SetPosition(Vector(300.0f, 300.0f));
  crossHairReset->SetScale({400.0f, 50.0f});
  crossHairReset->MakeCollision();
  CrossHairControlButton* crossHairButtonReset = crossHairReset->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonReset->SetControlType(CrossHairControlType_Reset);
  crossHairButtonReset->SetCrossHair(crossHair);
  TextComponent* resetTextComponent = crossHairReset->CreateUIComponent<TextComponent>();
  resetTextComponent->SetText(L"RESET", 20, Color8Bit::Red);
  resetTextComponent->SetFont(L"CONSOLELAS");
  resetTextComponent->SetPosition({200.0f, 20.0f});


  // WRITE
  UI* writeToCSV = SpawnActor<UI>();
  writeToCSV->SetOriginColor(Color8Bit::CyanAlpha);
  writeToCSV->SetPosition(Vector(300.0f, 900.0f));
  writeToCSV->SetScale({400.0f, 50.0f});
  writeToCSV->MakeCollision();
  WriteButton* writeToCSVButton = writeToCSV->CreateUIComponent<WriteButton>();
  writeToCSVButton->BindObject(object);
  writeToCSVButton->SetFilePath("../ContentsResource/Iori.csv");
  TextComponent* writeTextComponent = writeToCSV->CreateUIComponent<TextComponent>();
  writeTextComponent->SetText(L"WriteToCSV", 20, Color8Bit::Red);
  writeTextComponent->SetFont(L"CONSOLELAS");
  writeTextComponent->SetPosition({200.0f, 20.0f});

  // MOVEOBEJCT
  UI* moveImagePlusRow = SpawnActor<UI>();
  moveImagePlusRow->SetOriginColor(Color8Bit::CyanAlpha);
  moveImagePlusRow->SetPosition(Vector(200.0f, 400.0f));
  moveImagePlusRow->SetScale({200.0f, 50.0f});
  moveImagePlusRow->MakeCollision();
  ImageMoveButton* moveImagePlusRowButton = moveImagePlusRow->CreateUIComponent<ImageMoveButton>();
  moveImagePlusRowButton->BindObject(object);
  moveImagePlusRowButton->SetImageMoveDirType(ImageMoveDirType::IMD_PlusRow);
  TextComponent* movePlusRowTextComponent = moveImagePlusRow->CreateUIComponent<TextComponent>();
  movePlusRowTextComponent->SetText(L"MoveRow++", 20, Color8Bit::Red);
  movePlusRowTextComponent->SetFont(L"CONSOLELAS");
  movePlusRowTextComponent->SetPosition({100.0f, 20.0f});

  UI* moveImageMinusRow = SpawnActor<UI>();
  moveImageMinusRow->SetOriginColor(Color8Bit::CyanAlpha);
  moveImageMinusRow->SetPosition(Vector(400.0f, 400.0f));
  moveImageMinusRow->SetScale({200.0f, 50.0f});
  moveImageMinusRow->MakeCollision();
  ImageMoveButton* moveImageMinusRowButton = moveImageMinusRow->CreateUIComponent<ImageMoveButton>();
  moveImageMinusRowButton->BindObject(object);
  moveImageMinusRowButton->SetImageMoveDirType(ImageMoveDirType::IMD_MinusRow);
  TextComponent* moveMinusRowTextComponent = moveImageMinusRow->CreateUIComponent<TextComponent>();
  moveMinusRowTextComponent->SetText(L"MoveRow--", 20, Color8Bit::Red);
  moveMinusRowTextComponent->SetFont(L"CONSOLELAS");
  moveMinusRowTextComponent->SetPosition({100.0f, 20.0f});

  UI* moveImagePlusCol = SpawnActor<UI>();
  moveImagePlusCol->SetOriginColor(Color8Bit::CyanAlpha);
  moveImagePlusCol->SetPosition(Vector(200.0f, 500.0f));
  moveImagePlusCol->SetScale({200.0f, 50.0f});
  moveImagePlusCol->MakeCollision();
  ImageMoveButton* moveImagePlusColButton = moveImagePlusCol->CreateUIComponent<ImageMoveButton>();
  moveImagePlusColButton->BindObject(object);
  moveImagePlusColButton->SetImageMoveDirType(ImageMoveDirType::IMD_PlusCol);
  TextComponent* movePlusColTextComponent = moveImagePlusCol->CreateUIComponent<TextComponent>();
  movePlusColTextComponent->SetText(L"MoveCol++", 20, Color8Bit::Red);
  movePlusColTextComponent->SetFont(L"CONSOLELAS");
  movePlusColTextComponent->SetPosition({100.0f, 20.0f});

  UI* moveImageMinusCol = SpawnActor<UI>();
  moveImageMinusCol->SetOriginColor(Color8Bit::CyanAlpha);
  moveImageMinusCol->SetPosition(Vector(400.0f, 500.0f));
  moveImageMinusCol->SetScale({200.0f, 50.0f});
  moveImageMinusCol->MakeCollision();
  ImageMoveButton* moveImageMinusColButton = moveImageMinusCol->CreateUIComponent<ImageMoveButton>();
  moveImageMinusColButton->BindObject(object);
  moveImageMinusColButton->SetImageMoveDirType(ImageMoveDirType::IMD_MinusCol);
  TextComponent* moveMinusColTextComponent = moveImageMinusCol->CreateUIComponent<TextComponent>();
  moveMinusColTextComponent->SetText(L"MoveCol--", 20, Color8Bit::Red);
  moveMinusColTextComponent->SetFont(L"CONSOLELAS");
  moveMinusColTextComponent->SetPosition({100.0f, 20.0f});

  UI* moveImageReset = SpawnActor<UI>();
  moveImageReset->SetOriginColor(Color8Bit::CyanAlpha);
  moveImageReset->SetPosition(Vector(300.0f, 600.0f));
  moveImageReset->SetScale({400.0f, 50.0f});
  moveImageReset->MakeCollision();
  ImageMoveButton* moveImageResetButton = moveImageReset->CreateUIComponent<ImageMoveButton>();
  moveImageResetButton->BindObject(object);
  moveImageResetButton->SetImageMoveDirType(ImageMoveDirType::IMD_Reset);
  TextComponent* moveResetTextComponent = moveImageReset->CreateUIComponent<TextComponent>();
  moveResetTextComponent->SetText(L"MoveReset", 20, Color8Bit::Red);
  moveResetTextComponent->SetFont(L"CONSOLELAS");
  moveResetTextComponent->SetPosition({200, 20.0f});


  // NEXT IMAGE
  UI* nextImage = SpawnActor<UI>();
  nextImage->SetOriginColor(Color8Bit::CyanAlpha);
  nextImage->SetPosition(Vector(200.0f, 700.0f));
  nextImage->SetScale({200.0f, 50.0f});
  nextImage->MakeCollision();
  NextImageButton* nextImageButton = nextImage->CreateUIComponent<NextImageButton>();
  nextImageButton->BindObject(object);
  nextImageButton->SetNextImageType(NextImageType::NextImage_Next);
  TextComponent* nextImageTextComponent = nextImage->CreateUIComponent<TextComponent>();
  nextImageTextComponent->SetText(L"NEXT", 20, Color8Bit::Red);
  nextImageTextComponent->SetFont(L"CONSOLELAS");
  nextImageTextComponent->SetPosition({100.0f, 20.0f});


  UI* prevImage = SpawnActor<UI>();
  prevImage->SetOriginColor(Color8Bit::CyanAlpha);
  prevImage->SetPosition(Vector(400.0f, 700.0f));
  prevImage->SetScale({200.0f, 50.0f});
  prevImage->MakeCollision();
  NextImageButton* prevImageButton = prevImage->CreateUIComponent<NextImageButton>();
  prevImageButton->BindObject(object);
  prevImageButton->SetNextImageType(NextImageType::NextImage_Prev);
  TextComponent* prevImageTextComponent = prevImage->CreateUIComponent<TextComponent>();
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
}
