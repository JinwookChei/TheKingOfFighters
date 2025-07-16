#include "stdafx.h"
#include "ToolLevel.h"

// innclude "ViewPortImage.h"
#include "ToolActor.h"
#include "CollisionBox.h"
#include "ImageController.h"
#include "CreateCollisionButton.h"
#include "DeleteCollisionButton.h"
#include "CrossHair.h"
#include "CrossHairControlButton.h"
#include "WriteButton.h"
#include "ReadButton.h"
#include "ImageMoveButton.h"
#include "NextImageButton.h"

ToolLevel::ToolLevel()
    : position_(0.0f, 0.0f),
      scale_(0.0f, 0.0f),
      toolActor_(nullptr),
      imageIndexTextComponent_(nullptr),
      imageIndexTextBuffer_(nullptr) {
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

  // VIEWPORT
  //!!!!!!!!!!!! 주의!!!!!!!!! - IORI
  // IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Box.png", 1);
  // ioriImage->CalculateTransformFromDrawBoxImage(Color8Bit{169, 139, 150, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\Iori.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\Iori_new.csv");

  //!!!!!!!!!!!! 주의!!!!!!!!! - CHANG
  // IFileImage* changImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Chang Koehan_Box.png", 1);
  // changImage->CalculateTransformFromDrawBoxImage(Color8Bit{17, 91, 124, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\Chang.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\Chang_new.csv");

  //!!!!!!!!!!!! 주의!!!!!!!!! - IMAGES
  // IFileImage* healthBarImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\HealthBar.png", 1);
  // healthBarImage->CalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\HealthBar.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\HealthBar_new.csv");

  // IFileImage* healthImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Health.png", 1);
  // healthImage->CalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\Health.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\Health_new.csv");

  // IFileImage* hitEffectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\HitEffect01.png", 1);
  // hitEffectImage->CalculateTransformFromDrawBoxImage(Color8Bit{128, 0, 255, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\HitEffect01.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\HitEffect01_new.csv");

  // IFileImage* guardEffectImage01 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\GuardEffect01.png", 1);
  // guardEffectImage01->CalculateTransformFromDrawBoxImage(Color8Bit{103, 167, 141, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\GuardEffect01.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\GuardEffect01_new.csv");

  // IFileImage* guardEffectImage02 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\GuardEffect02.png", 1);
  // guardEffectImage02->CalculateTransformFromDrawBoxImage(Color8Bit{34, 177, 76, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\GuardEffect02.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\GuardEffect02_new.csv");

  // IFileImage* castingEffectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\CastingEffectImage_Box.png", 1);
  // castingEffectImage->CalculateTransformFromDrawBoxImage(Color8Bit{108, 156, 114, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\CastingEffect.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\CastingEffect_new.csv");

  // IFileImage* mpBarImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\MPBar_Box.png", 1);
  // mpBarImage->CalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\MPBar.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\MPBar_new.csv");

  // IFileImage* mpImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\MP_Box.png", 1);
  // mpImage->CalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\MP.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\MP_new.csv");

  // IFileImage* skillPointImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\SkillPoint_Box.png", 1);
  // skillPointImage->CalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);
  // const std::string& readFilePath("..\\ContentsResource\\CSV\\SkillPoint.csv");
  // const std::string& writeFilePath("..\\ContentsResource\\CSV\\SkillPoint_new.csv");

  IFileImage* effectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\PlayerLabel_Box.png", 1);
  effectImage->CalculateTransformFromDrawBoxImage(Color8Bit{0, 0, 0, 0}, Color8Bit::Magenta);
  const std::string& readFilePath("..\\ContentsResource\\CSV\\PlayerLabelImage.csv");
  const std::string& writeFilePath("..\\ContentsResource\\CSV\\PlayerLabelImage_new.csv");

  UI* ViewPortUI = SpawnActor<UI>();
  ViewPortUI->SetPosition(Vector(backbufferScale.HalfX(), backbufferScale.HalfY()));
  ViewPortUI->SetScale({800.0f, 800.0f});
  ViewPortUI->MakeCollision();
  ViewPortUI->SetOriginColor(Color8Bit::Magenta);
  ViewPortUI->ChangeClearColor_(false);

  toolActor_ = SpawnActor<ToolActor>();
  if (false == toolActor_->Initialize(ViewPortUI)) {
    return;
  }

  CrossHair* crossHair = ViewPortUI->CreateUIComponent<CrossHair>();
  crossHair->EnableCollision(false);

  ImageController* imageControlBox = ViewPortUI->CreateUIComponent<ImageController>();
  if (false == imageControlBox->Initialize(toolActor_)) {
    return;
  }

  // ViewPortImage* viewPortImage = ViewPortUI->CreateUIComponent<ViewPortImage>();
  CollisionBox* hitBoxTop = ViewPortUI->CreateUIComponent<CollisionBox>();
  hitBoxTop->Initialize(toolActor_, imageControlBox, CollisionBoxType::CBT_HitBoxTop);
  CollisionBox* hitBoxBottom = ViewPortUI->CreateUIComponent<CollisionBox>();
  hitBoxBottom->Initialize(toolActor_, imageControlBox, CollisionBoxType::CBT_HitBoxBottom);
  CollisionBox* attackBox = ViewPortUI->CreateUIComponent<CollisionBox>();
  attackBox->Initialize(toolActor_, imageControlBox, CollisionBoxType::CBT_AttackBox);
  CollisionBox* pushBox = ViewPortUI->CreateUIComponent<CollisionBox>();
  pushBox->Initialize(toolActor_, imageControlBox, CollisionBoxType::CBT_PushBox);
  CollisionBox* grabBox = ViewPortUI->CreateUIComponent<CollisionBox>();
  grabBox->Initialize(toolActor_, imageControlBox, CollisionBoxType::CBT_GrabBox);

  // CREATE COLLISION BUTTON
  UI* createHitBoxTopUI = SpawnActor<UI>();
  createHitBoxTopUI->SetOriginColor(Color8Bit::CyanAlpha);
  createHitBoxTopUI->SetPosition(Vector(1500.0f, 100.0f));
  createHitBoxTopUI->SetScale({200.0f, 50.0f});
  createHitBoxTopUI->MakeCollision();
  createHitBoxTopUI->SetOriginColor({0, 0, 255, 255});
  CreateCollisionButton* createHitBoxTopButton = createHitBoxTopUI->CreateUIComponent<CreateCollisionButton>();
  createHitBoxTopButton->Initialize(toolActor_, hitBoxTop, CollisionBoxType::CBT_HitBoxTop);
  createHitBoxTopButton->SetScale({200.0f, 50.0f});
  createHitBoxTopButton->SetPosition({createHitBoxTopUI->GetScale().HalfX(), createHitBoxTopUI->GetScale().HalfY()});

  UI* deleteHitBoxTopUI = SpawnActor<UI>();
  deleteHitBoxTopUI->SetOriginColor(Color8Bit::CyanAlpha);
  deleteHitBoxTopUI->SetPosition(Vector(1700.0f, 100.0f));
  deleteHitBoxTopUI->SetScale({200.0f, 50.0f});
  deleteHitBoxTopUI->MakeCollision();
  deleteHitBoxTopUI->SetOriginColor({0, 0, 255, 255});
  DeleteCollisionButton* deleteHitBoxTopButton = deleteHitBoxTopUI->CreateUIComponent<DeleteCollisionButton>();
  deleteHitBoxTopButton->Initialize(toolActor_, hitBoxTop, CollisionBoxType::CBT_HitBoxTop);
  deleteHitBoxTopButton->SetScale({200.0f, 50.0f});
  deleteHitBoxTopButton->SetPosition({deleteHitBoxTopUI->GetScale().HalfX(), deleteHitBoxTopUI->GetScale().HalfY()});

  UI* createHitBoxBottomUI = SpawnActor<UI>();
  createHitBoxBottomUI->SetOriginColor(Color8Bit::CyanAlpha);
  createHitBoxBottomUI->SetPosition(Vector(1500.0f, 250.0f));
  createHitBoxBottomUI->SetScale({200.0f, 50.0f});
  createHitBoxBottomUI->MakeCollision();
  createHitBoxBottomUI->SetOriginColor({150, 100, 255, 255});
  CreateCollisionButton* createHitBoxBottomButton = createHitBoxBottomUI->CreateUIComponent<CreateCollisionButton>();
  createHitBoxBottomButton->Initialize(toolActor_, hitBoxBottom, CollisionBoxType::CBT_HitBoxBottom);
  createHitBoxBottomButton->SetScale({200.0f, 50.0f});
  createHitBoxBottomButton->SetPosition({createHitBoxBottomUI->GetScale().HalfX(), createHitBoxBottomUI->GetScale().HalfY()});

  UI* deleteHitBoxBottomUI = SpawnActor<UI>();
  deleteHitBoxBottomUI->SetOriginColor(Color8Bit::CyanAlpha);
  deleteHitBoxBottomUI->SetPosition(Vector(1700.0f, 250.0f));
  deleteHitBoxBottomUI->SetScale({200.0f, 50.0f});
  deleteHitBoxBottomUI->MakeCollision();
  deleteHitBoxBottomUI->SetOriginColor({150, 100, 255, 255});
  DeleteCollisionButton* deleteHitBoxBottomButton = deleteHitBoxBottomUI->CreateUIComponent<DeleteCollisionButton>();
  deleteHitBoxBottomButton->Initialize(toolActor_, hitBoxBottom, CollisionBoxType::CBT_HitBoxBottom);
  deleteHitBoxBottomButton->SetScale({200.0f, 50.0f});
  deleteHitBoxBottomButton->SetPosition({deleteHitBoxBottomUI->GetScale().HalfX(), deleteHitBoxBottomUI->GetScale().HalfY()});

  UI* createAttackBoxUI = SpawnActor<UI>();
  createAttackBoxUI->SetOriginColor(Color8Bit::CyanAlpha);
  createAttackBoxUI->SetPosition(Vector(1500.0f, 400.0f));
  createAttackBoxUI->SetScale({200.0f, 50.0f});
  createAttackBoxUI->MakeCollision();
  createAttackBoxUI->SetOriginColor({255, 0, 0, 255});
  CreateCollisionButton* createAttackBoxButton = createAttackBoxUI->CreateUIComponent<CreateCollisionButton>();
  createAttackBoxButton->Initialize(toolActor_, attackBox, CollisionBoxType::CBT_AttackBox);
  createAttackBoxButton->SetScale({200.0f, 50.0f});
  createAttackBoxButton->SetPosition({createAttackBoxUI->GetScale().HalfX(), createAttackBoxUI->GetScale().HalfY()});

  UI* deleteAttackBoxUI = SpawnActor<UI>();
  deleteAttackBoxUI->SetOriginColor(Color8Bit::CyanAlpha);
  deleteAttackBoxUI->SetPosition(Vector(1700.0f, 400.0f));
  deleteAttackBoxUI->SetScale({200.0f, 50.0f});
  deleteAttackBoxUI->MakeCollision();
  deleteAttackBoxUI->SetOriginColor({255, 0, 0, 255});
  DeleteCollisionButton* deleteAttackBoxButton = deleteAttackBoxUI->CreateUIComponent<DeleteCollisionButton>();
  deleteAttackBoxButton->Initialize(toolActor_, attackBox, CollisionBoxType::CBT_AttackBox);
  deleteAttackBoxButton->SetScale({200.0f, 50.0f});
  deleteAttackBoxButton->SetPosition({deleteAttackBoxUI->GetScale().HalfX(), deleteAttackBoxUI->GetScale().HalfY()});

  UI* createPushBoxUI = SpawnActor<UI>();
  createPushBoxUI->SetOriginColor(Color8Bit::CyanAlpha);
  createPushBoxUI->SetPosition(Vector(1500.0f, 550.0f));
  createPushBoxUI->SetScale({200.0f, 50.0f});
  createPushBoxUI->MakeCollision();
  createPushBoxUI->SetOriginColor({255, 255, 255, 255});
  CreateCollisionButton* createPushBoxButton = createPushBoxUI->CreateUIComponent<CreateCollisionButton>();
  createPushBoxButton->Initialize(toolActor_, pushBox, CollisionBoxType::CBT_PushBox);
  createPushBoxButton->SetScale({200.0f, 50.0f});
  createPushBoxButton->SetPosition({createPushBoxUI->GetScale().HalfX(), createPushBoxUI->GetScale().HalfY()});

  UI* deletePushBoxUI = SpawnActor<UI>();
  deletePushBoxUI->SetOriginColor(Color8Bit::CyanAlpha);
  deletePushBoxUI->SetPosition(Vector(1700.0f, 550.0f));
  deletePushBoxUI->SetScale({200.0f, 50.0f});
  deletePushBoxUI->MakeCollision();
  deletePushBoxUI->SetOriginColor({255, 255, 255, 255});
  DeleteCollisionButton* deletePushBoxButton = deletePushBoxUI->CreateUIComponent<DeleteCollisionButton>();
  deletePushBoxButton->Initialize(toolActor_, pushBox, CollisionBoxType::CBT_PushBox);
  deletePushBoxButton->SetScale({200.0f, 50.0f});
  deletePushBoxButton->SetPosition({deletePushBoxUI->GetScale().HalfX(), deletePushBoxUI->GetScale().HalfY()});

  UI* createGrabBoxUI = SpawnActor<UI>();
  createGrabBoxUI->SetOriginColor(Color8Bit::CyanAlpha);
  createGrabBoxUI->SetPosition(Vector(1500.0f, 700.0f));
  createGrabBoxUI->SetScale({200.0f, 50.0f});
  createGrabBoxUI->MakeCollision();
  createGrabBoxUI->SetOriginColor({255, 255, 0, 255});
  CreateCollisionButton* createGrabBoxButton = createGrabBoxUI->CreateUIComponent<CreateCollisionButton>();
  createGrabBoxButton->Initialize(toolActor_, grabBox, CollisionBoxType::CBT_GrabBox);
  createGrabBoxButton->SetScale({200.0f, 50.0f});
  createGrabBoxButton->SetPosition({createGrabBoxUI->GetScale().HalfX(), createGrabBoxUI->GetScale().HalfY()});

  UI* deleteGrabBoxUI = SpawnActor<UI>();
  deleteGrabBoxUI->SetOriginColor(Color8Bit::CyanAlpha);
  deleteGrabBoxUI->SetPosition(Vector(1700.0f, 700.0f));
  deleteGrabBoxUI->SetScale({200.0f, 50.0f});
  deleteGrabBoxUI->MakeCollision();
  deleteGrabBoxUI->SetOriginColor({255, 255, 0, 255});
  DeleteCollisionButton* deleteGrabBoxButton = deleteGrabBoxUI->CreateUIComponent<DeleteCollisionButton>();
  deleteGrabBoxButton->Initialize(toolActor_, grabBox, CollisionBoxType::CBT_GrabBox);
  deleteGrabBoxButton->SetScale({200.0f, 50.0f});
  deleteGrabBoxButton->SetPosition({deleteGrabBoxUI->GetScale().HalfX(), deleteGrabBoxUI->GetScale().HalfY()});

  // CROSSHAIR CONTROL
  UI* crossHairPlusRowUI = SpawnActor<UI>();
  crossHairPlusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairPlusRowUI->SetPosition(Vector(350.0f, 100.0f));
  crossHairPlusRowUI->SetScale({100.0f, 50.0f});
  crossHairPlusRowUI->MakeCollision();
  CrossHairControlButton* crossHairButtonPlusRow = crossHairPlusRowUI->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonPlusRow->SetControlType(CrossHairControlType_PlusRow);
  crossHairButtonPlusRow->SetCrossHair(crossHair);
  crossHairButtonPlusRow->SetScale({100.0f, 50.0f});
  crossHairButtonPlusRow->SetPosition({crossHairPlusRowUI->GetScale().HalfX(), crossHairPlusRowUI->GetScale().HalfY()});
  TextComponent* plusRowTextComponent = crossHairPlusRowUI->CreateUIComponent<TextComponent>();
  plusRowTextComponent->SetText(L"Row++", 20, Color8Bit::Color8Bit::Black);
  plusRowTextComponent->SetFont(L"CONSOLELAS");
  plusRowTextComponent->SetPosition({50.0f, 20.0f});

  UI* superCrossHairPlusRowUI = SpawnActor<UI>();
  superCrossHairPlusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  superCrossHairPlusRowUI->SetPosition(Vector(450.0f, 100.0f));
  superCrossHairPlusRowUI->SetScale({100.0f, 50.0f});
  superCrossHairPlusRowUI->MakeCollision();
  CrossHairControlButton* superCrossHairButtonPlusRow = superCrossHairPlusRowUI->CreateUIComponent<CrossHairControlButton>();
  superCrossHairButtonPlusRow->SetControlType(CrossHairControlType_SuperPlusRow);
  superCrossHairButtonPlusRow->SetCrossHair(crossHair);
  superCrossHairButtonPlusRow->SetScale({100.0f, 50.0f});
  superCrossHairButtonPlusRow->SetPosition({superCrossHairPlusRowUI->GetScale().HalfX(), superCrossHairPlusRowUI->GetScale().HalfY()});
  TextComponent* SuperPlusRowTextComponent = superCrossHairPlusRowUI->CreateUIComponent<TextComponent>();
  SuperPlusRowTextComponent->SetText(L"SRow++", 20, Color8Bit::Color8Bit::Black);
  SuperPlusRowTextComponent->SetFont(L"CONSOLELAS");
  SuperPlusRowTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairMinusRowUI = SpawnActor<UI>();
  crossHairMinusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairMinusRowUI->SetPosition(Vector(250.0f, 100.0f));
  crossHairMinusRowUI->SetScale({100.0f, 50.0f});
  crossHairMinusRowUI->MakeCollision();
  CrossHairControlButton* crossHairButtonMinusRow = crossHairMinusRowUI->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonMinusRow->SetControlType(CrossHairControlType_MinusRow);
  crossHairButtonMinusRow->SetCrossHair(crossHair);
  crossHairButtonMinusRow->SetScale({100.0f, 50.0f});
  crossHairButtonMinusRow->SetPosition({crossHairMinusRowUI->GetScale().HalfX(), crossHairMinusRowUI->GetScale().HalfY()});
  TextComponent* minusRowTextComponent = crossHairMinusRowUI->CreateUIComponent<TextComponent>();
  minusRowTextComponent->SetText(L"Row--", 20, Color8Bit::Color8Bit::Black);
  minusRowTextComponent->SetFont(L"CONSOLELAS");
  minusRowTextComponent->SetPosition({50.0f, 20.0f});

  UI* SuperCrossHairMinusRowUI = SpawnActor<UI>();
  SuperCrossHairMinusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  SuperCrossHairMinusRowUI->SetPosition(Vector(150.0f, 100.0f));
  SuperCrossHairMinusRowUI->SetScale({100.0f, 50.0f});
  SuperCrossHairMinusRowUI->MakeCollision();
  CrossHairControlButton* SuperCrossHairButtonMinusRow = SuperCrossHairMinusRowUI->CreateUIComponent<CrossHairControlButton>();
  SuperCrossHairButtonMinusRow->SetControlType(CrossHairControlType_SuperMinusRow);
  SuperCrossHairButtonMinusRow->SetCrossHair(crossHair);
  SuperCrossHairButtonMinusRow->SetScale({100.0f, 50.0f});
  SuperCrossHairButtonMinusRow->SetPosition({SuperCrossHairMinusRowUI->GetScale().HalfX(), SuperCrossHairMinusRowUI->GetScale().HalfY()});
  TextComponent* superMinusRowTextComponent = SuperCrossHairMinusRowUI->CreateUIComponent<TextComponent>();
  superMinusRowTextComponent->SetText(L"SRow--", 20, Color8Bit::Color8Bit::Black);
  superMinusRowTextComponent->SetFont(L"CONSOLELAS");
  superMinusRowTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairPlusColUI = SpawnActor<UI>();
  crossHairPlusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairPlusColUI->SetPosition(Vector(350.0f, 200.0f));
  crossHairPlusColUI->SetScale({100.0f, 50.0f});
  crossHairPlusColUI->MakeCollision();
  CrossHairControlButton* crossHairButtonPlusCol = crossHairPlusColUI->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonPlusCol->SetControlType(CrossHairControlType_PlusCol);
  crossHairButtonPlusCol->SetCrossHair(crossHair);
  crossHairButtonPlusCol->SetScale({100.0f, 50.0f});
  crossHairButtonPlusCol->SetPosition({crossHairPlusColUI->GetScale().HalfX(), crossHairPlusColUI->GetScale().HalfY()});
  TextComponent* plusColTextComponent = crossHairPlusColUI->CreateUIComponent<TextComponent>();
  plusColTextComponent->SetText(L"Col++", 20, Color8Bit::Color8Bit::Black);
  plusColTextComponent->SetFont(L"CONSOLELAS");
  plusColTextComponent->SetPosition({50.0f, 20.0f});

  UI* superCrossHairPlusColUI = SpawnActor<UI>();
  superCrossHairPlusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  superCrossHairPlusColUI->SetPosition(Vector(450.0f, 200.0f));
  superCrossHairPlusColUI->SetScale({100.0f, 50.0f});
  superCrossHairPlusColUI->MakeCollision();
  CrossHairControlButton* superCrossHairButtonPlusCol = superCrossHairPlusColUI->CreateUIComponent<CrossHairControlButton>();
  superCrossHairButtonPlusCol->SetControlType(CrossHairControlType_SuperPlusCol);
  superCrossHairButtonPlusCol->SetCrossHair(crossHair);
  superCrossHairButtonPlusCol->SetScale({100.0f, 50.0f});
  superCrossHairButtonPlusCol->SetPosition({superCrossHairPlusColUI->GetScale().HalfX(), superCrossHairPlusColUI->GetScale().HalfY()});
  TextComponent* superPlusColTextComponent = superCrossHairPlusColUI->CreateUIComponent<TextComponent>();
  superPlusColTextComponent->SetText(L"SCol++", 20, Color8Bit::Color8Bit::Black);
  superPlusColTextComponent->SetFont(L"CONSOLELAS");
  superPlusColTextComponent->SetPosition({50.0f, 20.0f});

  UI* crossHairMinusColUI = SpawnActor<UI>();
  crossHairMinusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  crossHairMinusColUI->SetPosition(Vector(250.0f, 200.0f));
  crossHairMinusColUI->SetScale({100.0f, 50.0f});
  crossHairMinusColUI->MakeCollision();
  CrossHairControlButton* crossHairButtonMinusCol = crossHairMinusColUI->CreateUIComponent<CrossHairControlButton>();
  crossHairButtonMinusCol->SetControlType(CrossHairControlType_MinusCol);
  crossHairButtonMinusCol->SetCrossHair(crossHair);
  crossHairButtonMinusCol->SetScale({100.0f, 50.0f});
  crossHairButtonMinusCol->SetPosition({crossHairMinusColUI->GetScale().HalfX(), crossHairMinusColUI->GetScale().HalfY()});
  TextComponent* minusColTextComponent = crossHairMinusColUI->CreateUIComponent<TextComponent>();
  minusColTextComponent->SetText(L"Col--", 20, Color8Bit::Color8Bit::Black);
  minusColTextComponent->SetFont(L"CONSOLELAS");
  minusColTextComponent->SetPosition({50.0f, 20.0f});

  UI* superCrossHairMinusColUI = SpawnActor<UI>();
  superCrossHairMinusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  superCrossHairMinusColUI->SetPosition(Vector(150.0f, 200.0f));
  superCrossHairMinusColUI->SetScale({100.0f, 50.0f});
  superCrossHairMinusColUI->MakeCollision();
  CrossHairControlButton* superCrossHairButtonMinusCol = superCrossHairMinusColUI->CreateUIComponent<CrossHairControlButton>();
  superCrossHairButtonMinusCol->SetControlType(CrossHairControlType_SuperMinusCol);
  superCrossHairButtonMinusCol->SetCrossHair(crossHair);
  superCrossHairButtonMinusCol->SetScale({100.0f, 50.0f});
  superCrossHairButtonMinusCol->SetPosition({superCrossHairMinusColUI->GetScale().HalfX(), superCrossHairMinusColUI->GetScale().HalfY()});
  TextComponent* superMinusColTextComponent = superCrossHairMinusColUI->CreateUIComponent<TextComponent>();
  superMinusColTextComponent->SetText(L"Col--", 20, Color8Bit::Color8Bit::Black);
  superMinusColTextComponent->SetFont(L"CONSOLELAS");
  superMinusColTextComponent->SetPosition({50.0f, 20.0f});

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
  resetTextComponent->SetText(L"RESET", 20, Color8Bit::Color8Bit::Black);
  resetTextComponent->SetFont(L"CONSOLELAS");
  resetTextComponent->SetPosition({200.0f, 20.0f});

  // WRITE
  UI* writeToCSVUI = SpawnActor<UI>();
  writeToCSVUI->SetOriginColor(Color8Bit::CyanAlpha);
  writeToCSVUI->SetPosition(Vector(300.0f, 900.0f));
  writeToCSVUI->SetScale({400.0f, 50.0f});
  writeToCSVUI->MakeCollision();
  WriteButton* writeToCSVButton = writeToCSVUI->CreateUIComponent<WriteButton>();
  writeToCSVButton->BindObject(toolActor_);
  writeToCSVButton->SetFilePath(writeFilePath);
  writeToCSVButton->SetScale({400.0f, 50.0f});
  writeToCSVButton->SetPosition({writeToCSVUI->GetScale().HalfX(), writeToCSVUI->GetScale().HalfY()});
  TextComponent* writeTextComponent = writeToCSVUI->CreateUIComponent<TextComponent>();
  writeTextComponent->SetText(L"WriteToCSV", 20, Color8Bit::Color8Bit::Black);
  writeTextComponent->SetFont(L"CONSOLELAS");
  writeTextComponent->SetPosition({200.0f, 20.0f});

  // READ
  UI* readFromCSVUI = SpawnActor<UI>();
  readFromCSVUI->SetOriginColor(Color8Bit::CyanAlpha);
  readFromCSVUI->SetPosition(Vector(300.0f, 800.0f));
  readFromCSVUI->SetScale({400.0f, 50.0f});
  readFromCSVUI->MakeCollision();
  ReadButton* readFromCSVButton = readFromCSVUI->CreateUIComponent<ReadButton>();
  readFromCSVButton->BindObject(toolActor_);
  readFromCSVButton->SetFilePath(readFilePath);
  readFromCSVButton->SetScale({400.0f, 50.0f});
  readFromCSVButton->SetPosition({readFromCSVUI->GetScale().HalfX(), readFromCSVUI->GetScale().HalfY()});
  TextComponent* readTextComponent = readFromCSVUI->CreateUIComponent<TextComponent>();
  readTextComponent->SetText(L"ReadFromCSV", 20, Color8Bit::Color8Bit::Black);
  readTextComponent->SetFont(L"CONSOLELAS");
  readTextComponent->SetPosition({200.0f, 20.0f});

  // MOVEOBEJCT
  UI* moveImagePlusRowUI = SpawnActor<UI>();
  moveImagePlusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  moveImagePlusRowUI->SetPosition(Vector(350.0f, 400.0f));
  moveImagePlusRowUI->SetScale({100.0f, 50.0f});
  moveImagePlusRowUI->MakeCollision();
  ImageMoveButton* moveImagePlusRowButton = moveImagePlusRowUI->CreateUIComponent<ImageMoveButton>();
  moveImagePlusRowButton->BindObject(toolActor_);
  moveImagePlusRowButton->SetImageMoveDirType(ImageMoveDirType::IMD_PlusRow);
  moveImagePlusRowButton->SetScale({100.0f, 50.0f});
  moveImagePlusRowButton->SetPosition({moveImagePlusRowUI->GetScale().HalfX(), moveImagePlusRowUI->GetScale().HalfY()});
  TextComponent* movePlusRowTextComponent = moveImagePlusRowUI->CreateUIComponent<TextComponent>();
  movePlusRowTextComponent->SetText(L"Move\nRow++", 18, Color8Bit::Color8Bit::Black);
  movePlusRowTextComponent->SetFont(L"CONSOLELAS");
  movePlusRowTextComponent->SetPosition({60.0f, 25.0f});

  UI* superMoveImagePlusRowUI = SpawnActor<UI>();
  superMoveImagePlusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  superMoveImagePlusRowUI->SetPosition(Vector(450.0f, 400.0f));
  superMoveImagePlusRowUI->SetScale({100.0f, 50.0f});
  superMoveImagePlusRowUI->MakeCollision();
  ImageMoveButton* superMoveImagePlusRowButton = superMoveImagePlusRowUI->CreateUIComponent<ImageMoveButton>();
  superMoveImagePlusRowButton->BindObject(toolActor_);
  superMoveImagePlusRowButton->SetImageMoveDirType(ImageMoveDirType::IMD_SuperPlusRow);
  superMoveImagePlusRowButton->SetScale({100.0f, 50.0f});
  superMoveImagePlusRowButton->SetPosition({superMoveImagePlusRowUI->GetScale().HalfX(), superMoveImagePlusRowUI->GetScale().HalfY()});
  TextComponent* superMovePlusRowTextComponent = superMoveImagePlusRowUI->CreateUIComponent<TextComponent>();
  superMovePlusRowTextComponent->SetText(L"SMove\nRow++", 18, Color8Bit::Color8Bit::Black);
  superMovePlusRowTextComponent->SetFont(L"CONSOLELAS");
  superMovePlusRowTextComponent->SetPosition({60.0f, 25.0f});

  UI* moveImageMinusRowUI = SpawnActor<UI>();
  moveImageMinusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  moveImageMinusRowUI->SetPosition(Vector(250.0f, 400.0f));
  moveImageMinusRowUI->SetScale({100.0f, 50.0f});
  moveImageMinusRowUI->MakeCollision();
  ImageMoveButton* moveImageMinusRowButton = moveImageMinusRowUI->CreateUIComponent<ImageMoveButton>();
  moveImageMinusRowButton->BindObject(toolActor_);
  moveImageMinusRowButton->SetImageMoveDirType(ImageMoveDirType::IMD_MinusRow);
  moveImageMinusRowButton->SetScale({100.0f, 50.0f});
  moveImageMinusRowButton->SetPosition({moveImageMinusRowUI->GetScale().HalfX(), moveImageMinusRowUI->GetScale().HalfY()});
  TextComponent* moveMinusRowTextComponent = moveImageMinusRowUI->CreateUIComponent<TextComponent>();
  moveMinusRowTextComponent->SetText(L"Move\nRow--", 18, Color8Bit::Color8Bit::Black);
  moveMinusRowTextComponent->SetFont(L"CONSOLELAS");
  moveMinusRowTextComponent->SetPosition({60.0f, 25.0f});

  UI* superMoveImageMinusRowUI = SpawnActor<UI>();
  superMoveImageMinusRowUI->SetOriginColor(Color8Bit::CyanAlpha);
  superMoveImageMinusRowUI->SetPosition(Vector(150.0f, 400.0f));
  superMoveImageMinusRowUI->SetScale({100.0f, 50.0f});
  superMoveImageMinusRowUI->MakeCollision();
  ImageMoveButton* superMoveImageMinusRowButton = superMoveImageMinusRowUI->CreateUIComponent<ImageMoveButton>();
  superMoveImageMinusRowButton->BindObject(toolActor_);
  superMoveImageMinusRowButton->SetImageMoveDirType(ImageMoveDirType::IMD_SuperMinusRow);
  superMoveImageMinusRowButton->SetScale({100.0f, 50.0f});
  superMoveImageMinusRowButton->SetPosition({superMoveImageMinusRowUI->GetScale().HalfX(), superMoveImageMinusRowUI->GetScale().HalfY()});
  TextComponent* superMoveMinusRowTextComponent = superMoveImageMinusRowUI->CreateUIComponent<TextComponent>();
  superMoveMinusRowTextComponent->SetText(L"SMove\nRow--", 18, Color8Bit::Color8Bit::Black);
  superMoveMinusRowTextComponent->SetFont(L"CONSOLELAS");
  superMoveMinusRowTextComponent->SetPosition({60.0f, 25.0f});

  UI* moveImagePlusColUI = SpawnActor<UI>();
  moveImagePlusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  moveImagePlusColUI->SetPosition(Vector(350.0f, 500.0f));
  moveImagePlusColUI->SetScale({100.0f, 50.0f});
  moveImagePlusColUI->MakeCollision();
  ImageMoveButton* moveImagePlusColButton = moveImagePlusColUI->CreateUIComponent<ImageMoveButton>();
  moveImagePlusColButton->BindObject(toolActor_);
  moveImagePlusColButton->SetImageMoveDirType(ImageMoveDirType::IMD_PlusCol);
  moveImagePlusColButton->SetScale({100.0f, 50.0f});
  moveImagePlusColButton->SetPosition({moveImagePlusColUI->GetScale().HalfX(), moveImagePlusColUI->GetScale().HalfY()});
  TextComponent* movePlusColTextComponent = moveImagePlusColUI->CreateUIComponent<TextComponent>();
  movePlusColTextComponent->SetText(L"Move\nCol++", 18, Color8Bit::Color8Bit::Black);
  movePlusColTextComponent->SetFont(L"CONSOLELAS");
  movePlusColTextComponent->SetPosition({60.0f, 25.0f});

  UI* superMoveImagePlusColUI = SpawnActor<UI>();
  superMoveImagePlusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  superMoveImagePlusColUI->SetPosition(Vector(450.0f, 500.0f));
  superMoveImagePlusColUI->SetScale({100.0f, 50.0f});
  superMoveImagePlusColUI->MakeCollision();
  ImageMoveButton* superMoveImagePlusColButton = superMoveImagePlusColUI->CreateUIComponent<ImageMoveButton>();
  superMoveImagePlusColButton->BindObject(toolActor_);
  superMoveImagePlusColButton->SetImageMoveDirType(ImageMoveDirType::IMD_SuperPlusCol);
  superMoveImagePlusColButton->SetScale({100.0f, 50.0f});
  superMoveImagePlusColButton->SetPosition({superMoveImagePlusColUI->GetScale().HalfX(), superMoveImagePlusColUI->GetScale().HalfY()});
  TextComponent* superMovePlusColTextComponent = superMoveImagePlusColUI->CreateUIComponent<TextComponent>();
  superMovePlusColTextComponent->SetText(L"SMove\nCol++", 18, Color8Bit::Color8Bit::Black);
  superMovePlusColTextComponent->SetFont(L"CONSOLELAS");
  superMovePlusColTextComponent->SetPosition({60.0f, 25.0f});

  UI* moveImageMinusColUI = SpawnActor<UI>();
  moveImageMinusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  moveImageMinusColUI->SetPosition(Vector(250.0f, 500.0f));
  moveImageMinusColUI->SetScale({100.0f, 50.0f});
  moveImageMinusColUI->MakeCollision();
  ImageMoveButton* moveImageMinusColButton = moveImageMinusColUI->CreateUIComponent<ImageMoveButton>();
  moveImageMinusColButton->BindObject(toolActor_);
  moveImageMinusColButton->SetImageMoveDirType(ImageMoveDirType::IMD_MinusCol);
  moveImageMinusColButton->SetScale({100.0f, 50.0f});
  moveImageMinusColButton->SetPosition({moveImageMinusColUI->GetScale().HalfX(), moveImageMinusColUI->GetScale().HalfY()});
  TextComponent* moveMinusColTextComponent = moveImageMinusColUI->CreateUIComponent<TextComponent>();
  moveMinusColTextComponent->SetText(L"Move\nCol--", 18, Color8Bit::Color8Bit::Black);
  moveMinusColTextComponent->SetFont(L"CONSOLELAS");
  moveMinusColTextComponent->SetPosition({60.0f, 25.0f});

  UI* superMoveImageMinusColUI = SpawnActor<UI>();
  superMoveImageMinusColUI->SetOriginColor(Color8Bit::CyanAlpha);
  superMoveImageMinusColUI->SetPosition(Vector(150.0f, 500.0f));
  superMoveImageMinusColUI->SetScale({100.0f, 50.0f});
  superMoveImageMinusColUI->MakeCollision();
  ImageMoveButton* superMoveImageMinusColButton = superMoveImageMinusColUI->CreateUIComponent<ImageMoveButton>();
  superMoveImageMinusColButton->BindObject(toolActor_);
  superMoveImageMinusColButton->SetImageMoveDirType(ImageMoveDirType::IMD_SuperMinusCol);
  superMoveImageMinusColButton->SetScale({100.0f, 50.0f});
  superMoveImageMinusColButton->SetPosition({superMoveImageMinusColUI->GetScale().HalfX(), superMoveImageMinusColUI->GetScale().HalfY()});
  TextComponent* superMoveMinusColTextComponent = superMoveImageMinusColUI->CreateUIComponent<TextComponent>();
  superMoveMinusColTextComponent->SetText(L"SMove\nCol--", 18, Color8Bit::Color8Bit::Black);
  superMoveMinusColTextComponent->SetFont(L"CONSOLELAS");
  superMoveMinusColTextComponent->SetPosition({60.0f, 25.0f});

  UI* moveImageResetUI = SpawnActor<UI>();
  moveImageResetUI->SetOriginColor(Color8Bit::CyanAlpha);
  moveImageResetUI->SetPosition(Vector(300.0f, 600.0f));
  moveImageResetUI->SetScale({400.0f, 50.0f});
  moveImageResetUI->MakeCollision();
  ImageMoveButton* moveImageResetButton = moveImageResetUI->CreateUIComponent<ImageMoveButton>();
  moveImageResetButton->BindObject(toolActor_);
  moveImageResetButton->SetImageMoveDirType(ImageMoveDirType::IMD_Reset);
  moveImageResetButton->SetScale({400.0f, 50.0f});
  moveImageResetButton->SetPosition({moveImageResetUI->GetScale().HalfX(), moveImageResetUI->GetScale().HalfY()});
  TextComponent* moveResetTextComponent = moveImageResetUI->CreateUIComponent<TextComponent>();
  moveResetTextComponent->SetText(L"MoveReset", 18, Color8Bit::Color8Bit::Black);
  moveResetTextComponent->SetFont(L"CONSOLELAS");
  moveResetTextComponent->SetPosition({200, 20.0f});

  // NEXT IMAGE
  UI* nextImageUI = SpawnActor<UI>();
  nextImageUI->SetOriginColor(Color8Bit::CyanAlpha);
  nextImageUI->SetPosition(Vector(350.0f, 700.0f));
  nextImageUI->SetScale({100.0f, 50.0f});
  nextImageUI->MakeCollision();
  NextImageButton* nextImageButton = nextImageUI->CreateUIComponent<NextImageButton>();
  nextImageButton->BindObject(toolActor_);
  nextImageButton->SetNextImageType(NextImageType::NextImage_Next);
  nextImageButton->SetScale({100.0f, 50.0f});
  nextImageButton->SetPosition({nextImageUI->GetScale().HalfX(), nextImageUI->GetScale().HalfY()});
  TextComponent* nextImageTextComponent = nextImageUI->CreateUIComponent<TextComponent>();
  nextImageTextComponent->SetText(L"NEXT", 20, Color8Bit::Color8Bit::Black);
  nextImageTextComponent->SetFont(L"CONSOLELAS");
  nextImageTextComponent->SetPosition({50.0f, 20.0f});

  UI* prevImageUI = SpawnActor<UI>();
  prevImageUI->SetOriginColor(Color8Bit::CyanAlpha);
  prevImageUI->SetPosition(Vector(250.0f, 700.0f));
  prevImageUI->SetScale({100.0f, 50.0f});
  prevImageUI->MakeCollision();
  NextImageButton* prevImageButton = prevImageUI->CreateUIComponent<NextImageButton>();
  prevImageButton->BindObject(toolActor_);
  prevImageButton->SetNextImageType(NextImageType::NextImage_Prev);
  prevImageButton->SetScale({100.0f, 50.0f});
  prevImageButton->SetPosition({prevImageUI->GetScale().HalfX(), prevImageUI->GetScale().HalfY()});
  TextComponent* prevImageTextComponent = prevImageUI->CreateUIComponent<TextComponent>();
  prevImageTextComponent->SetText(L"PREV", 20, Color8Bit::Color8Bit::Black);
  prevImageTextComponent->SetFont(L"CONSOLELAS");
  prevImageTextComponent->SetPosition({50.0f, 20.0f});

  UI* superNextImageUI = SpawnActor<UI>();
  superNextImageUI->SetOriginColor(Color8Bit::CyanAlpha);
  superNextImageUI->SetPosition(Vector(450.0f, 700.0f));
  superNextImageUI->SetScale({100.0f, 50.0f});
  superNextImageUI->MakeCollision();
  NextImageButton* superNextImageButton = superNextImageUI->CreateUIComponent<NextImageButton>();
  superNextImageButton->BindObject(toolActor_);
  superNextImageButton->SetNextImageType(NextImageType::NextImage_SuperNext);
  superNextImageButton->SetScale({100.0f, 50.0f});
  superNextImageButton->SetPosition({superNextImageUI->GetScale().HalfX(), superNextImageUI->GetScale().HalfY()});
  TextComponent* superNextImageTextComponent = superNextImageUI->CreateUIComponent<TextComponent>();
  superNextImageTextComponent->SetText(L"SNEXT", 20, Color8Bit::Color8Bit::Black);
  superNextImageTextComponent->SetFont(L"CONSOLELAS");
  superNextImageTextComponent->SetPosition({50.0f, 20.0f});

  UI* superPrevImageUI = SpawnActor<UI>();
  superPrevImageUI->SetOriginColor(Color8Bit::CyanAlpha);
  superPrevImageUI->SetPosition(Vector(150.0f, 700.0f));
  superPrevImageUI->SetScale({100.0f, 50.0f});
  superPrevImageUI->MakeCollision();
  NextImageButton* superPrevImageButton = superPrevImageUI->CreateUIComponent<NextImageButton>();
  superPrevImageButton->BindObject(toolActor_);
  superPrevImageButton->SetNextImageType(NextImageType::NextImage_SuperPrev);
  superPrevImageButton->SetScale({100.0f, 50.0f});
  superPrevImageButton->SetPosition({superPrevImageUI->GetScale().HalfX(), superPrevImageUI->GetScale().HalfY()});
  TextComponent* superPrevImageTextComponent = superPrevImageUI->CreateUIComponent<TextComponent>();
  superPrevImageTextComponent->SetText(L"SPREV", 20, Color8Bit::Color8Bit::Black);
  superPrevImageTextComponent->SetFont(L"CONSOLELAS");
  superPrevImageTextComponent->SetPosition({50.0f, 20.0f});

  UI* imageIndexViewUI = SpawnActor<UI>();
  imageIndexViewUI->SetOriginColor(Color8Bit::YellowAlpha);
  imageIndexViewUI->SetPosition(Vector(980.0f, 50.0f));
  imageIndexViewUI->SetScale({200.0f, 50.0f});
  imageIndexTextComponent_ = imageIndexViewUI->CreateUIComponent<TextComponent>();

  imageIndexTextBuffer_ = new wchar_t[32];
  imageIndexTextComponent_->SetText(L" ", 30, Color8Bit::Black);
  imageIndexTextComponent_->SetFont(L"CONSOLELAS");
  imageIndexTextComponent_->SetPosition({100.0f, 25.0f});

  // TOOLS
}

ToolLevel::~ToolLevel() {
  if (nullptr != imageIndexTextBuffer_) {
    delete[] imageIndexTextBuffer_;
    imageIndexTextBuffer_ = nullptr;
  }
}

void ToolLevel::BeginPlay() {
}

void ToolLevel::Tick(unsigned long long deltaTick) {
  if (false == InputManager::Instance()->IsAnyKeyPress()) {
    return;
  }

  if (InputManager::Instance()->IsDown(VK_F1)) {
    SetDebugRender(!GetDebugRender());
  }

  if (InputManager::Instance()->IsDown(VK_F2)) {
    SetCollisionRender(!GetCollisionRender());
  }

  unsigned int imageIndex = toolActor_->GetImageIndex();
  swprintf(imageIndexTextBuffer_, 32, L"%u", imageIndex);
  imageIndexTextComponent_->SetText(imageIndexTextBuffer_, 40, Color8Bit::Black);
}