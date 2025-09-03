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
  //IImage* mouseImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\mousePointer.png", (IMGTYPE_MouseImage | IMGMOD_NONE));
  //IFileImage* lobyImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\KOF_logo.png", (IMGTYPE_LogoImage | IMGMOD_NONE));
  //IFileImage* pressEnterImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Press_Enter.png", (IMGTYPE_PressEnter | IMGMOD_NONE));
  //IFileImage* readyImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\READY_alpha.bmp", (IMGTYPE_Ready | IMGMOD_NONE));
  //IFileImage* goImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\GO_alpha.bmp", (IMGTYPE_Go | IMGMOD_NONE));
  //IFileImage* koImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\KO_alpha.bmp", (IMGTYPE_KO | IMGMOD_NONE));
  //IFileImage* backGroundImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\TownStage.png", (IMGTYPE_BackGoundImage | IMGMOD_NONE));
  //backGroundImage->CalculateTransformByAuto({.emptyColor = Color8Bit(77, 111, 111, 0), .reCalculateHeight = true, .start = {0.0f, 0.0f}, .end = {779.0f, 2015.0f}});
  //IFileImage* blackBoardImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\BlackBoard.png", (IMGTYPE_BlackBoardImage | IMGMOD_NONE));
  //IFileImage* whiteBoardImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\WhiteBoard.png", (IMGTYPE_WhiteBoardImage | IMGMOD_NONE));
  //IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Alpha.bmp", (IMGTYPE_IoriImage | IMGMOD_NONE));
  //ioriImage->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\Iori.csv");
  //IFileImage* ioriImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Alpha.bmp", (IMGTYPE_IoriImage | IMGMOD_FLIPPED));
  //ioriImageFlipped->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Iori.csv");
  //IFileImage* ioriImage_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Alpha_BlueFlame.bmp", (IMGTYPE_IoriImage | IMGMOD_BLUEFLAME));
  //ioriImage_BlueFlame->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\Iori.csv");
  //IFileImage* ioriImageFlipped_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Alpha_BlueFlame.bmp", (IMGTYPE_IoriImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME));
  //ioriImageFlipped_BlueFlame->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Iori.csv");
  //IFileImage* changImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Chang_Koehan_Alpha.bmp", (IMGTYPE_ChangImage | IMGMOD_NONE));
  //changImage->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\Chang.csv");
  //IFileImage* changImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Chang_Koehan_Alpha.bmp", (IMGTYPE_ChangImage | IMGMOD_FLIPPED));
  //changImageFlipped->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Chang.csv");
  //IFileImage* changImage_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Chang_Koehan_Alpha_BlueFlame.bmp", (IMGTYPE_ChangImage | IMGMOD_BLUEFLAME));
  //changImage_BlueFlame->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\Chang.csv");
  //IFileImage* changImageFlipped_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\Chang_Koehan_Alpha_BlueFlame.bmp", (IMGTYPE_ChangImage | IMGMOD_FLIPPED | IMGMOD_BLUEFLAME));
  //changImageFlipped_BlueFlame->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Chang.csv");
  //IFileImage* healthHUDImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\HUD_Health.png", (IMGTYPE_HealthHUD | IMGMOD_NONE));
  //healthHUDImage->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\HUD_Health.csv");
  //IFileImage* healthHUDImageFlippped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\HUD_Health.png", (IMGTYPE_HealthHUD | IMGMOD_FLIPPED));
  //healthHUDImageFlippped->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\HUD_Health.csv");
  //IFileImage* skillPointImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\SkillPoint.png", (IMGTYPE_SkillPoint | IMGMOD_NONE));
  //skillPointImage->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\SkillPoint.csv");
  //IFileImage* hitEffectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\HitEffect01.png", (IMGTYPE_HitEffectImage | IMGMOD_NONE));
  //hitEffectImage->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\HitEffect01.csv");
  //IFileImage* hitEffectImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\HitEffect01.png", (IMGTYPE_HitEffectImage | IMGMOD_FLIPPED));
  //hitEffectImageFlipped->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\HitEffect01.csv");
  //IFileImage* guardEffectImage01 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\GuardEffect01.png", (IMGTYPE_GuardEffectImage01 | IMGMOD_NONE));
  //guardEffectImage01->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\GuardEffect01.csv");
  //IFileImage* guardEffectImage01Flipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\GuardEffect01.png", (IMGTYPE_GuardEffectImage01 | IMGMOD_FLIPPED));
  //guardEffectImage01Flipped->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\GuardEffect01.csv");
  //IFileImage* castingEffectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\CastingEffectImage_Box.png", (IMGTYPE_CastingEffectImage | IMGMOD_NONE));
  //castingEffectImage->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\CastingEffect.csv");
  //IFileImage* castingEffectImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\CastingEffectImage_Box.png", (IMGTYPE_CastingEffectImage | IMGMOD_FLIPPED));
  //castingEffectImageFlipped->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\CastingEffect.csv");
  //IFileImage* playerLayerImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\PlayerLabel_Box.png", (IMGTYPE_PlayerLabel | IMGMOD_NONE));
  //playerLayerImage->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\PlayerLabel.csv");
  //IFileImage* effectImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\EffectImage_Box.png", (IMGTYPE_Effect | IMGMOD_NONE));
  //effectImage->ApplyImageInfoFromCSV("..\\ContentsResource\\CSV\\Effect.csv");
  //IFileImage* effectImageFlipped = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\EffectImage_Box.png", (IMGTYPE_Effect | IMGMOD_FLIPPED));
  //effectImageFlipped->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Effect.csv");
}
