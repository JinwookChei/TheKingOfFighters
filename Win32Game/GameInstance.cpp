#include "stdafx.h"
#include "GameInstance.h"

GameInstance::GameInstance() {
}

GameInstance::~GameInstance() {
}

bool GameInstance::Initialize() {
  LoadKOFImages();

  return true;
}

GameInstance* GameInstance::Instance() {
  return GGameInstance;
}

void GameInstance::LoadKOFImages() {
  // IMAGES
  IImage* mouseImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\mousePointer.png", (IMGTYPE_MouseImage | IMGMOD_NONE));
  IFileImage* lobyImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\KOF_logo.png", (IMGTYPE_LogoImage | IMGMOD_NONE));
  IFileImage* pressEnterImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Press_Enter.png", (IMGTYPE_PressEnter | IMGMOD_NONE));
  IFileImage* readyImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\READY_alpha.bmp", (IMGTYPE_Ready | IMGMOD_NONE));
  IFileImage* goImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\GO_alpha.bmp", (IMGTYPE_Go | IMGMOD_NONE));
  IFileImage* koImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\KO_alpha.bmp", (IMGTYPE_KO | IMGMOD_NONE));
  IFileImage* backGroundImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\TownStage.png", (IMGTYPE_BackGoundImage | IMGMOD_NONE));
  backGroundImage->CalculateTransformByAuto({.emptyColor = Color8Bit(77, 111, 111, 0), .reCalculateHeight = true, .start = {0.0f, 0.0f}, .end = {779.0f, 2015.0f}});
  IFileImage* blackBoardImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\BlackBoard.png", (IMGTYPE_BlackBoardImage | IMGMOD_NONE));
  IFileImage* whiteBoardImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\WhiteBoard.png", (IMGTYPE_WhiteBoardImage | IMGMOD_NONE));
  IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Alpha.bmp", (IMGTYPE_IoriImage | IMGMOD_NONE));
  ioriImage->CalculateTransformFromCSV("..\\ContentsResource\\CSV\\Iori.csv");
  IFileImage* ioriImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Alpha.bmp", (IMGTYPE_IoriImage | IMGMOD_FLIPPED));
  ioriImageFlipped->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Iori.csv");
  IFileImage* ioriImage_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Alpha_BlueFlame.bmp", (IMGTYPE_IoriImage | IMGMOD_BLUEFLAME));
  ioriImage_BlueFlame->CalculateTransformFromCSV("..\\ContentsResource\\CSV\\Iori.csv");
  IFileImage* ioriImageFlipped_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Alpha_BlueFlame.bmp", (IMGTYPE_IoriImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME));
  ioriImageFlipped_BlueFlame->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Iori.csv");
  IFileImage* changImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Chang Koehan_Alpha.bmp", (IMGTYPE_ChangImage | IMGMOD_NONE));
  changImage->CalculateTransformFromCSV("..\\ContentsResource\\CSV\\Chang.csv");
  IFileImage* changImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Chang Koehan_Alpha.bmp", (IMGTYPE_ChangImage | IMGMOD_FLIPPED));
  changImageFlipped->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Chang.csv");
  IFileImage* changImage_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Chang Koehan_Alpha_BlueFlame.bmp", (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME));
  changImage_BlueFlame->CalculateTransformFromCSV("..\\ContentsResource\\CSV\\Chang.csv");
  IFileImage* changImageFlipped_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Chang Koehan_Alpha_BlueFlame.bmp", (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME));
  changImageFlipped_BlueFlame->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Chang.csv");
  IFileImage* healthBarImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\HealthBar.png", (IMGTYPE_HealthBarImage | IMGMOD_NONE));
  healthBarImage->CalculateTransformFromCSV("..\\ContentsResource\\CSV\\HealthBar.csv");
  IFileImage* healthBarImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\HealthBar.png", (IMGTYPE_HealthBarImage | IMGMOD_FLIPPED));
  healthBarImageFlipped->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\CSV\\HealthBar.csv");
  IFileImage* healthImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Health.png", (IMGTYPE_HealthImage | IMGMOD_NONE));
  healthImage->CalculateTransformFromCSV("..\\ContentsResource\\CSV\\Health.csv");
  IFileImage* hitEffectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\HitEffect01.png", (IMGTYPE_HitEffectImage | IMGMOD_NONE));
  hitEffectImage->CalculateTransformFromCSV("..\\ContentsResource\\CSV\\HitEffect01.csv");
  IFileImage* hitEffectImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\HitEffect01.png", (IMGTYPE_HitEffectImage | IMGMOD_FLIPPED));
  hitEffectImageFlipped->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\CSV\\HitEffect01.csv");
  IFileImage* guardEffectImage01 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\GuardEffect01.png", (IMGTYPE_GuardEffectImage01 | IMGMOD_NONE));
  guardEffectImage01->CalculateTransformFromCSV("..\\ContentsResource\\CSV\\GuardEffect01.csv");
  IFileImage* guardEffectImage01Flipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\GuardEffect01.png", (IMGTYPE_GuardEffectImage01 | IMGMOD_FLIPPED));
  guardEffectImage01Flipped->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\CSV\\GuardEffect01.csv");
  IFileImage* castingEffectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\CastingEffectImage_Box.png", (IMGTYPE_CastingEffectImage | IMGMOD_NONE));
  castingEffectImage->CalculateTransformFromCSV("..\\ContentsResource\\CSV\\CastingEffect.csv");
  IFileImage* youPlayer1 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\YOU_Player1.png", (IMGTYPE_YouPlayer1 | IMGMOD_NONE));
  IFileImage* youPlayer2 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\YOU_Player2.png", (IMGTYPE_YouPlayer2 | IMGMOD_NONE));
  



  // TODO :
  // 반전된 Health는 logic으로, 원본 이미지는 여러 포인터가 가르킥로있고, 이미지를 어떻게 그릴지만 각자 알아서 그림.
  // UI 이미지는 래퍼로 감싸서 position하고, scale 등 정보로 Render를 그림.
  IFileImage* reverseHealthImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Health.png", (IMGTYPE_HealthImage | IMGMOD_FLIPPED));
  reverseHealthImage->CalculateTransformFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Health.csv");
}
