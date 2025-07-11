#include "stdafx.h"
#include "ImageEditLevel.h"
// #include "lodepng.h"

ImageEditLevel::ImageEditLevel() {
}

ImageEditLevel::~ImageEditLevel() {
}

void ImageEditLevel::BeginPlay() {
  /*IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami.png", IMGTYPE_IoriImage);
  ioriImage->MakeColorTransparent(Color8Bit{169, 139, 150, 0});
  ioriImage->Save("..\\ContentsResource\\IoriYagami_Alpha.bmp",0);

  IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami.png", IMGTYPE_IoriImage);
  ioriImage->ScalePixelRGB(0.4f, 0.4f, 3.7f, Color8Bit{169, 139, 150, 0});
  ioriImage->Save("..\\ContentsResource\\IoriYagami_BlueFlame.bmp", 0);*/

  // IFileImage* changImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan.png", IMGTYPE_ChangImage);
  // changImage->ScalePixelRGB(0.4f, 0.4f, 3.7f, Color8Bit{17, 91, 124, 0});
  // changImage->Save("..\\ContentsResource\\Chang Koehan_BlueFlame.bmp", 0);

  // IFileImage* IoriImage_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami_BlueFlame.png", 1);
  // IoriImage_BlueFlame->MakeColorTransparent(Color8Bit{169, 139, 150, 0});
  // IoriImage_BlueFlame->Save("..\\ContentsResource\\IoriYagami_Alpha_BlueFlame.bmp", 0);

  // IFileImage* changImage_BlueFlame = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan_BlueFlame.png", 2);
  // changImage_BlueFlame->MakeColorTransparent(Color8Bit{17, 91, 124, 0});
  // changImage_BlueFlame->Save("..\\ContentsResource\\Chang Koehan_Alpha_BlueFlame.bmp", 0);

  // IFileImage* normalImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Normal.png", 1);
  // IFileImage* blueFameImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Blue.png", 2);
  //
  // normalImage->CalculateTransformByAuto({
  //  .emptyColor = Color8Bit{169, 139, 150, 0},
  //  .reCalculateHeight = true,
  //  .start = Vector{135.0f, 9850.0f},
  //  .end = Vector{211.0f, 9960.0f}});

  // blueFameImage->CalculateTransformByAuto({
  //  .emptyColor = Color8Bit{169, 139, 150, 0},
  //    .reCalculateHeight = true,
  // .start = Vector{643.0f, 9695.0f},
  // .end = Vector{720.0f, 9801.0f}});

  // Vector a = normalImage->GetScale(0);
  // Vector b = blueFameImage->GetScale(0);

  // std::vector<Color8Bit> result1 = normalImage->CountPixelPallet();
  // std::vector<Color8Bit> result2 = blueFameImage->CountPixelPallet();



  // MAKE TRANSPARENT
  //IFileImage* readyImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\READY.png", IMGTYPE_Ready);
  //readyImage->MakeColorTransparent(Color8Bit{100, 100, 100, 0});
  //readyImage->Save("..\\ContentsResource\\KOFImages\\READY_Alpha.bmp", 0);

  //IFileImage* goImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\GO.png", IMGTYPE_Go);
  //goImage->MakeColorTransparent(Color8Bit{100, 100, 100, 0});
  //goImage->Save("..\\ContentsResource\\KOFImages\\GO_Alpha.bmp", 0);

  //IFileImage* koImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\KO.png", IMGTYPE_KO);
  //koImage->MakeColorTransparent(Color8Bit{100, 100, 100, 0});
  //koImage->Save("..\\ContentsResource\\KOFImages\\KO_Alpha.bmp", 0);


  return;
}

void ImageEditLevel::Tick(unsigned long long deltaTime) {
}
