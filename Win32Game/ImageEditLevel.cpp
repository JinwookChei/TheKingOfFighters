#include "stdafx.h"
#include "ImageEditLevel.h"
// #include "lodepng.h"

ImageEditLevel::ImageEditLevel() {
}

ImageEditLevel::~ImageEditLevel() {
}

void ImageEditLevel::BeginPlay() {
  IFileImage* ioriImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\IoriYagami.png", IMGTYPE_IoriImage);
  ioriImage->MakeColorTransparent(Color8Bit{169, 139, 150, 0});
  ioriImage->Save("..\\ContentsResource\\IoriYagami_Alpha.bmp",0);

  IFileImage* changImage = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\Chang Koehan.png", IMGTYPE_ChangImage);
  changImage->MakeColorTransparent(Color8Bit{17, 91, 124, 0});
  changImage->Save("..\\ContentsResource\\Chang Koehan_Alpha.bmp", 0);

  return;
}

void ImageEditLevel::Tick(unsigned long long deltaTime) {
}
