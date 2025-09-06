#include "stdafx.h"
#include <chrono>
#include <iostream>
#include "ImageLoadTimeCheck.h"

ImageLoadTimeCheck::ImageLoadTimeCheck() {
}

ImageLoadTimeCheck::~ImageLoadTimeCheck() {
}

void ImageLoadTimeCheck::BeginPlay() {
  //IFileImage* ioriImage1 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Box.png", 1);
  //auto start1 = std::chrono::high_resolution_clock::now();
  //ioriImage1->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Iori.csv");
  //auto end1 = std::chrono::high_resolution_clock::now();
  //std::chrono::duration<double, std::milli> elapsed1 = end1 - start1;
  //std::wstring asyncMsg1 = L"ApplyImageInfoFromCSV_Flip_Async - elapsed time: " + std::to_wstring(elapsed1.count()) + L" ms\n";
  //OutputDebugStringW(asyncMsg1.c_str());

  //IFileImage* ioriImage2 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Box.png", 2);
  //auto start2 = std::chrono::high_resolution_clock::now();
  //ioriImage2->ApplyImageInfoFromCSV_Flip("..\\ContentsResource\\CSV\\Iori.csv");
  //auto end2 = std::chrono::high_resolution_clock::now();
  //std::chrono::duration<double, std::milli> elapsed2 = end2 - start2;
  //std::wstring asyncMsg2 = L"ApplyImageInfoFromCSV_Flip      - elapsed time: " + std::to_wstring(elapsed2.count()) + L" ms\n";
  //OutputDebugStringW(asyncMsg2.c_str());

  IFileImage* ioriImage1 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Box.png", 1);
  ioriImage1->ApplyImageInfoFromCSV_Flip_Async("..\\ContentsResource\\CSV\\Iori.csv");

  IFileImage* ioriImage2 = ImgManager::GetIntance()->LoadImg("..\\ContentsResource\\KOFImages\\IoriYagami_Box.png", 2);
  ioriImage2->ApplyImageInfoFromCSV_Flip("..\\ContentsResource\\CSV\\Iori.csv");

}

void ImageLoadTimeCheck::Tick(unsigned long long deltaTick) {
}
