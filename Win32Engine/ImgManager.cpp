#include "stdafx.h"


ImgManager* ImgManager::GetIntance() {
  return GImgManager;
}

ImgManager::ImgManager() {
}

ImgManager::~ImgManager() {
  for (HashTableIterator iter = imgTable_.begin(); iter != imgTable_.end();) {
    IImage* delImg = (IImage*)*iter;
    iter = imgTable_.erase(iter);
    delImg->Release();
  }
  imgTable_.Cleanup();
}

bool ImgManager::Initialize() {
  return imgTable_.Initialize(8, 8);
}

IFileImage* ImgManager::LoadImg(std::string_view path, unsigned long long key) {
  IFileImage* findImg = nullptr;
  if (0 != imgTable_.Select((void**)&findImg, 1, &key, 8)) {
    return nullptr;
  }

  IFileImage* newImg = GGraphicDevice->LoadImg(path);
  if (nullptr == newImg) {
    __debugbreak();
    return nullptr;
  }

  if (nullptr == imgTable_.Insert(newImg, &key, 8)) {
    newImg->Release();
    return nullptr;
  }

  return newImg;
}

IFileImage* ImgManager::GetImg(unsigned long long key) {
  IFileImage* findImg = nullptr;
  if (0 == imgTable_.Select((void**)&findImg, 1, &key, 8)) {
    return nullptr;
  }
  return findImg;
}

//IFileImage* ImgManager::GetCopyImg(unsigned long long key) {
//  IFileImage* findImg = nullptr;
//  if (0 == imgTable_.Select((void**)&findImg, 1, &key, 8)) {
//    return nullptr;
//  }
//
//  IFileImage* newImg = GGraphicDevice->LoadImg(path);
//
//  return findImg;
//}
