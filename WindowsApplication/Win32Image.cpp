#include "stdafx.h"
#include "Win32Image.h"
#include "WindowsApplication.h"
#include "Win32GraphicDevice.h"

#include <filesystem>
#include <fstream>
#include <sstream>

#pragma pack(push, 1)
struct TGAHeader {
  BYTE idLength;
  BYTE colorMapType;
  BYTE imageType;
  WORD colorMapStart;
  WORD colorMapLength;
  BYTE colorMapDepth;
  WORD xOffset;
  WORD yOffset;
  WORD width;
  WORD height;
  BYTE PixelDepth;
  BYTE imageDescriptor;
};
#pragma pack(pop)

Win32Image::Win32Image()
    : refCount_(1),
      imageLoadType_(ImageLoadType::One),
      imageCount_(0),
      imageHead_(nullptr),
      imageTail_(nullptr) {
}

Win32Image::~Win32Image() {
  Cleanup();
}

HRESULT __stdcall Win32Image::QueryInterface(REFIID riid, void** ppvObject) {
  return E_NOTIMPL;
}

ULONG __stdcall Win32Image::AddRef() {
  ++refCount_;
  return refCount_;
}

ULONG __stdcall Win32Image::Release() {
  --refCount_;
  ULONG tmpRefCount = refCount_;
  if (0 == refCount_) {
    delete this;
  }

  return tmpRefCount;
}

Vector __stdcall Win32Image::GetScale(unsigned int index /*= 0xffffffff*/) {
  unsigned int tmpIndex = index;
  if (0xffffffff == tmpIndex) {
    tmpIndex = 0;
  }

  ImageInfo* pFind = GetImageInfo(tmpIndex);
  if (nullptr == pFind) {
    return Vector(0.0f, 0.0f);
  }
  if (0xffffffff == index) {
    return pFind->GetScale();
  }

  return pFind->GetRenderScale();
}

void* __stdcall Win32Image::GetHandle() {
  return GetDC();
}

unsigned __int64 __stdcall Win32Image::GetImageCount() {
  return imageCount_;
}

Transform __stdcall Win32Image::RenderTransform(unsigned int index) {
  ImageInfo* pFind = GetImageInfo(index);
  if (nullptr == pFind) {
    return Transform();
  }
  return pFind->transform_;
}

bool Win32Image::GetPixel(const Vector& position, Color8Bit* outColor) {
  if (position.X < 0 || position.Y < 0) {
    return false;
  }

  const Vector scale = GetScale();

  if (scale.IntergerX() < position.IntergerX() || scale.IntergerY() < position.IntergerY()) {
    return false;
  }
  if (nullptr == outColor) {
    return true;
  }

  outColor->Color = ::GetPixel(GetDC(), position.IntergerX(), position.IntergerY());

  return true;
}

bool Win32Image::SetPixel(const Vector& position, const Color8Bit& color) {
  if (position.X < 0 || position.Y < 0) {
    return false;
  }

  const Vector scale = GetScale();

  if (scale.IntergerX() < position.IntergerX() || scale.IntergerY() < position.IntergerY()) {
    return false;
  }

  ::SetPixel(GetDC(), position.IntergerX(), position.IntergerY(), color.Color);
  return true;
}

bool Win32Image::Save(std::string_view filePath, unsigned int index) {
  ImageInfo* pFind = GetImageInfo(index);
  if (nullptr == pFind) {
    return false;
  }

  Path curr(filePath);
  FILE* saveFile = nullptr;
  fopen_s(&saveFile, curr.GetPathString().c_str(), "w+b");
  if (nullptr == saveFile) {
    return false;
  }

  BITMAPFILEHEADER fileHeader = {};
  BITMAPINFOHEADER infoHeader = {};

  fileHeader.bfType = 0x4D42;
  fileHeader.bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));

  infoHeader.biSize = sizeof(BITMAPINFOHEADER);
  infoHeader.biPlanes = 1;
  infoHeader.biWidth = pFind->bitMapInfo_.bmWidth;
  infoHeader.biHeight = pFind->bitMapInfo_.bmHeight;
  infoHeader.biBitCount = 32;
  infoHeader.biSizeImage = infoHeader.biWidth * abs(infoHeader.biHeight) * (infoHeader.biBitCount / 8);

  fileHeader.bfSize = fileHeader.bfOffBits + infoHeader.biSizeImage;

  double physicalWidth = infoHeader.biWidth / 96.0;
  double physicalHeight = infoHeader.biHeight / 96.0;

  double dpiX = infoHeader.biWidth / physicalWidth;
  double dpiY = infoHeader.biHeight / physicalHeight;

  infoHeader.biXPelsPerMeter = 0;  //(int)(dpiX * 39.3701);
  infoHeader.biYPelsPerMeter = 0;  //(int)(dpiY * 39.3701);

  fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, saveFile);
  fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, saveFile);
  fwrite(pFind->bitMapInfo_.bmBits, infoHeader.biSizeImage, 1, saveFile);
  fclose(saveFile);

  return true;
}

bool Win32Image::IsRenderTexture() {
  return false;
}

void __stdcall Win32Image::CalculateTransformByAuto(const CalculateTransformByAutoParameter& parameter) {
  if (imageLoadType_ != ImageLoadType::One) {
    return;
  }

  ImageInfo* pInfo = GetImageInfo(0);
  UnLinkFromLinkedList(&imageHead_, &imageTail_, &pInfo->link_);
  --imageCount_;

  Cleanup();

  LINK_ITEM* lineInfoHead = nullptr;
  LINK_ITEM* lineInfoTail = nullptr;
  unsigned int lineCount = 0;

  const unsigned int bytesPerPixel = pInfo->bitMapInfo_.bmBitsPixel / 8;
  const BYTE* pixelData = (BYTE*)pInfo->bitMapInfo_.bmBits;

  Color8Bit currentColor;

  unsigned int tmpStartPositionY = 0xffffffff;
  bool bFindPixel = false;

  const LONG tmpBmStartHeight = (LONG)parameter.start.Y;
  const LONG tmpBmStartWidth = (LONG)parameter.start.X;

  const LONG tmpBmHeight = (LONG)parameter.end.Y == 0 ? pInfo->bitMapInfo_.bmHeight : (LONG)parameter.end.Y;
  const LONG tmpBmWidth = (LONG)parameter.end.X == 0 ? pInfo->bitMapInfo_.bmWidth : (LONG)parameter.end.X;

  // 한 줄씩 픽셀을 확인한다.
  for (LONG height = tmpBmStartHeight; height < tmpBmHeight; ++height) {
    bFindPixel = false;
    for (LONG width = tmpBmStartWidth; width < tmpBmWidth; ++width) {
      LONG realHeight = pInfo->bitMapInfo_.bmHeight - height - 1;
      LONG index = (realHeight * pInfo->bitMapInfo_.bmWidth + width) * bytesPerPixel;
      currentColor.B = pixelData[index];
      currentColor.G = pixelData[index + 1];
      currentColor.R = pixelData[index + 2];
      currentColor.A = parameter.emptyColor.A;

      if (currentColor != parameter.emptyColor) {
        bFindPixel = true;
        if (0xffffffff == tmpStartPositionY) {  // 처음 찾은건지 검사
          tmpStartPositionY = height;
        }
      }
    }

    if (false == bFindPixel && 0xffffffff != tmpStartPositionY) {
      unsigned int endHeight = (unsigned int)height;

      if (parameter.onlyLine) {
        ImageInfo* pNew = new ImageInfo;
        pNew->imageType_ = pInfo->imageType_;
        pNew->hBitMap_ = pInfo->hBitMap_;
        pNew->imageDC_ = pInfo->imageDC_;
        pNew->bitMapInfo_ = pInfo->bitMapInfo_;

        pNew->transform_.SetPosition(Vector(0.0f, (float)tmpStartPositionY));
        pNew->transform_.SetScale(Vector((float)pInfo->bitMapInfo_.bmWidth, (float)(endHeight - tmpStartPositionY)));

        LinkToLinkedListFIFO(&imageHead_, &imageTail_, &pNew->link_);
        pNew->index_ = (unsigned int)imageCount_++;
      } else {
        ImageLineInfo* newLineInfo = new ImageLineInfo;
        newLineInfo->startPositionY_ = tmpStartPositionY;
        newLineInfo->heightY_ = endHeight - 1 - tmpStartPositionY;
        newLineInfo->link_.prev_ = nullptr;
        newLineInfo->link_.next_ = nullptr;
        newLineInfo->link_.item_ = newLineInfo;

        LinkToLinkedListFIFO(&lineInfoHead, &lineInfoTail, &newLineInfo->link_);
        ++lineCount;
      }

      tmpStartPositionY = 0xffffffff;
    }
  }

  if (parameter.onlyLine) {
    delete pInfo;
    pInfo = GetImageInfo(0);
    pInfo->isOwner_ = true;
    return;
  }

  currentColor = {0, 0, 0, 0};
  unsigned int tmpStartPositionX = 0xffffffff;
  bFindPixel = false;

  LINK_ITEM* pCur = lineInfoHead;
  while (pCur) {
    ImageLineInfo* pItem = (ImageLineInfo*)pCur->item_;
    pCur = pCur->next_;

    for (LONG width = tmpBmStartWidth; width < tmpBmWidth; ++width) {
      bFindPixel = false;
      for (LONG height = pItem->startPositionY_; height <= (LONG)(pItem->startPositionY_ + pItem->heightY_); ++height) {
        LONG realHeight = pInfo->bitMapInfo_.bmHeight - height - 1;
        LONG index = (realHeight * pInfo->bitMapInfo_.bmWidth + width) * bytesPerPixel;
        currentColor.B = pixelData[index];
        currentColor.G = pixelData[index + 1];
        currentColor.R = pixelData[index + 2];
        currentColor.A = parameter.emptyColor.A;

        if (currentColor != parameter.emptyColor) {
          bFindPixel = true;
          if (0xffffffff == tmpStartPositionX) {  // 처음 찾은건지 검사
            tmpStartPositionX = width;
          }
        }
      }

      if (false == bFindPixel && 0xffffffff != tmpStartPositionX) {
        unsigned int endWidth = (unsigned int)width;

        ImageInfo* pNew = new ImageInfo;
        pNew->imageType_ = pInfo->imageType_;
        pNew->hBitMap_ = pInfo->hBitMap_;
        pNew->imageDC_ = pInfo->imageDC_;
        pNew->bitMapInfo_ = pInfo->bitMapInfo_;

        pNew->transform_.SetPosition(Vector((long)tmpStartPositionX, (long)pItem->startPositionY_));
        pNew->transform_.SetScale(Vector((long)(endWidth - tmpStartPositionX), (long)pItem->heightY_));

        LinkToLinkedListFIFO(&imageHead_, &imageTail_, &pNew->link_);
        pNew->index_ = (unsigned int)imageCount_++;

        tmpStartPositionX = 0xffffffff;
      }
    }
  }

  while (lineInfoHead) {
    ImageLineInfo* pDel = (ImageLineInfo*)lineInfoHead->item_;
    UnLinkFromLinkedList(&lineInfoHead, &lineInfoTail, &pDel->link_);

    delete pDel;
  }

  if (parameter.reCalculateHeight) {
    bFindPixel = false;
    tmpStartPositionY = 0xffffffff;

    pCur = imageHead_;
    while (pCur) {
      ImageInfo* image = (ImageInfo*)pCur->item_;
      pCur = pCur->next_;

      const Vector& position = image->transform_.GetPosition();
      const Vector& scale = image->transform_.GetScale();

      tmpStartPositionY = 0xffffffff;
      bFindPixel = false;

      for (LONG height = (LONG)position.Y; height < (LONG)(position.Y + scale.Y); ++height) {
        bFindPixel = false;
        for (LONG width = (LONG)position.X; width < (LONG)(position.X + scale.X); ++width) {
          LONG realHeight = pInfo->bitMapInfo_.bmHeight - height - 1;
          LONG index = (realHeight * pInfo->bitMapInfo_.bmWidth + width) * bytesPerPixel;
          currentColor.B = pixelData[index];
          currentColor.G = pixelData[index + 1];
          currentColor.R = pixelData[index + 2];
          currentColor.A = parameter.emptyColor.A;

          if (currentColor != parameter.emptyColor) {
            bFindPixel = true;
            if (0xffffffff == tmpStartPositionY) {  // 처음 찾은건지 검사
              tmpStartPositionY = height;
            }
          }
        }

        if (false == bFindPixel && 0xffffffff != tmpStartPositionY) {
          image->transform_.SetPosition({position.X, (float)(height - scale.Y)});

          tmpStartPositionY = 0xffffffff;
        }
      }
    }
  }

  pInfo->hBitMap_ = nullptr;
  pInfo->imageDC_ = nullptr;
  delete pInfo;

  pInfo = GetImageInfo(0);
  pInfo->isOwner_ = true;
}

void __stdcall Win32Image::CalculateTransformFromDrawBoxImage(Color8Bit emptyColor, Color8Bit lineColor) {
  if (imageLoadType_ != ImageLoadType::One) {
    return;
  }

  Vector partitionLineRowStart = {0.0f, 0.0f};
  Vector partitionLineGridStart;

  std::vector<Vector> gridCorner;
  std::vector<std::vector<float>> boundingBoxDatas;

  while (1) {
    if (false == SearchPartitionLineRow(partitionLineRowStart, &partitionLineGridStart, lineColor)) {
      break;
    }
    SearchPartitionGrid(partitionLineGridStart, &partitionLineRowStart, &gridCorner, emptyColor, lineColor);
  }

  for (int i = 0; i < gridCorner.size(); i += 2) {
    DetectBoundBox(gridCorner[i], gridCorner[i + 1], &boundingBoxDatas, emptyColor, lineColor);
  }

  ImageInfo* pInfo = GetImageInfo(0);
  pInfo->isOwner_ = false;

  UnLinkFromLinkedList(&imageHead_, &imageTail_, &pInfo->link_);

  Cleanup();

  for (unsigned int height = 0; height < boundingBoxDatas.size(); ++height) {
    ImageInfo* pNew = new ImageInfo;
    pNew->imageType_ = pInfo->imageType_;
    pNew->hBitMap_ = pInfo->hBitMap_;
    pNew->imageDC_ = pInfo->imageDC_;
    pNew->bitMapInfo_ = pInfo->bitMapInfo_;

    Vector calcPosition = {boundingBoxDatas[height][0], boundingBoxDatas[height][1]};
    Vector calcScale = {boundingBoxDatas[height][2] - boundingBoxDatas[height][0], boundingBoxDatas[height][3] - boundingBoxDatas[height][1]};
    pNew->transform_.SetPosition(calcPosition);
    pNew->transform_.SetScale(calcScale);

    LinkToLinkedListFIFO(&imageHead_, &imageTail_, &pNew->link_);
    pNew->index_ = (unsigned int)imageCount_++;
  }

  delete pInfo;

  pInfo = GetImageInfo(0);
  pInfo->isOwner_ = true;
}

void __stdcall Win32Image::CalculateTransformFromCSV(const std::string& filePath) {
  if (imageLoadType_ != ImageLoadType::One) {
    return;
  }

  std::vector<std::vector<float>> csvInfo;

  std::ifstream file(filePath);
  if (false == file.is_open()) {
    __debugbreak();
    return;
  }

  std::string line;
  // 3번째 인자 없으면 공백기준으로 나눔.
  // file을 공백단위로 읽어서 line에 저장,
  while (std::getline(file, line)) {
    if ('P' == line[0]) {
      continue;
    }
    // 행
    std::vector<float> row;
    // 문자열스트림에 line을 대입.
    std::stringstream ss(line);
    // Cell
    std::string cell;

    // 문자열 스트림에서 cell에 , 단위로 행에 저장.
    while (std::getline(ss, cell, ',')) {
      float intCell = std::stof(cell);
      row.push_back(intCell);
    }
    csvInfo.push_back(row);
  }
  file.close();

  // imageList를 돌면서 인덱스가 0인 ImageInfo 가져옴.
  ImageInfo* pInfo = GetImageInfo(0);
  pInfo->isOwner_ = false;
  UnLinkFromLinkedList(&imageHead_, &imageTail_, &pInfo->link_);

  // LInkList모든 오소 삭제.
  Cleanup();

  for (unsigned int height = 0; height < csvInfo.size(); ++height) {
    ImageInfo* pNew = new ImageInfo;
    pNew->imageType_ = pInfo->imageType_;
    pNew->hBitMap_ = pInfo->hBitMap_;
    pNew->imageDC_ = pInfo->imageDC_;
    pNew->bitMapInfo_ = pInfo->bitMapInfo_;

    Vector calcPosition = {csvInfo[height][0], csvInfo[height][1]};
    Vector calcScale = {csvInfo[height][2], csvInfo[height][3]};
    pNew->transform_.SetPosition(calcPosition);
    pNew->transform_.SetScale(calcScale);
    pNew->positionOffSet_ = {csvInfo[height][4], csvInfo[height][5]};

    CollisionInfo tempCollisionInfo;

    for (int i = 6; i < csvInfo[height].size(); i += 5) {
      if (1 == csvInfo[height][i]) {
        tempCollisionInfo.hasCollision_ = true;
        tempCollisionInfo.position_ = {csvInfo[height][i + 1], csvInfo[height][i + 2]};
        tempCollisionInfo.scale_ = {csvInfo[height][i + 3], csvInfo[height][i + 4]};
      } else {
        tempCollisionInfo.hasCollision_ = false;
        tempCollisionInfo.position_ = {0.0f, 0.0f};
        tempCollisionInfo.scale_ = {0.0f, 0.0f};
      }

      pNew->collisionBoxInfo_[(i - 6) / 5] = tempCollisionInfo;
    }

    LinkToLinkedListFIFO(&imageHead_, &imageTail_, &pNew->link_);
    pNew->index_ = (unsigned int)imageCount_++;
  }

  delete pInfo;
  pInfo = GetImageInfo(0);
  pInfo->isOwner_ = true;
}

void __stdcall Win32Image::ReverseCalculateTransformFromCSV(const std::string& filePath) {
  if (imageLoadType_ != ImageLoadType::One) {
    return;
  }

  std::vector<std::vector<float>> csvInfo;

  std::ifstream file(filePath);
  if (false == file.is_open()) {
    __debugbreak();
    return;
  }

  std::string line;
  // 3번째 인자 없으면 공백기준으로 나눔.
  // file을 공백단위로 읽어서 line에 저장,
  while (std::getline(file, line)) {
    if ('P' == line[0]) {
      continue;
    }
    // 행
    std::vector<float> row;
    // 문자열스트림에 line을 대입.
    std::stringstream ss(line);
    // Cell
    std::string cell;

    // 문자열 스트림에서 cell에 , 단위로 행에 저장.
    while (std::getline(ss, cell, ',')) {
      float intCell = std::stof(cell);
      row.push_back(intCell);
    }
    csvInfo.push_back(row);
  }
  file.close();

  // imageList를 돌면서 인덱스가 0인 ImageInfo 가져옴.
  ImageInfo* pInfo = GetImageInfo(0);

  // REVERSE IMAGE
  HDC imageDC = pInfo->imageDC_;
  for (int i = 0; i < csvInfo.size(); ++i) {
    float positionX = csvInfo[i][0];
    float positionY = csvInfo[i][1];
    float scaleX = csvInfo[i][2];
    float scaleY = csvInfo[i][3];

    unsigned int pixelScale = scaleX * scaleY;
    Color8Bit* horizontalFlipPixels = (Color8Bit*)malloc(sizeof(Color8Bit) * pixelScale);

    for (int col = positionY; col < positionY + scaleY; ++col) {
      for (int row = positionX + scaleX; row > positionX; --row) {
        Color8Bit tempPixel;
        Vector pixelPosition{(float)row, (float)col};

        if (false == GetPixel(pixelPosition, &tempPixel)) {
          __debugbreak();
          return;
        }
        int flipPixelIndex = (col - positionY) * scaleX + (positionX + scaleX - row);
        horizontalFlipPixels[flipPixelIndex] = tempPixel;
      }
    }

    for (int col = positionY; col < positionY + scaleY; ++col) {
      for (int row = positionX; row < positionX + scaleX; ++row) {
        int flipPixelIndex = (col - positionY) * scaleX + (row - positionX);
        Vector pixelPosition{(float)row, (float)col};
        if (false == SetPixel(pixelPosition, horizontalFlipPixels[flipPixelIndex])) {
          __debugbreak();
          return;
        }
      }
    }

    free(horizontalFlipPixels);
  }
  // REVERSE IMAGE END


  // CALCULATE IMAGE INFO
  pInfo->isOwner_ = false;

  UnLinkFromLinkedList(&imageHead_, &imageTail_, &pInfo->link_);

  Cleanup();


  for (unsigned int height = 0; height < csvInfo.size(); ++height) {
    ImageInfo* pNew = new ImageInfo;
    pNew->imageType_ = pInfo->imageType_;
    pNew->hBitMap_ = pInfo->hBitMap_;
    pNew->imageDC_ = pInfo->imageDC_;
    pNew->bitMapInfo_ = pInfo->bitMapInfo_;

    Vector calcPosition = {csvInfo[height][0], csvInfo[height][1]};
    Vector calcScale = {csvInfo[height][2], csvInfo[height][3]};
    pNew->transform_.SetPosition(calcPosition);
    pNew->transform_.SetScale(calcScale);
    pNew->positionOffSet_ = {-csvInfo[height][4], csvInfo[height][5]};

    CollisionInfo tempCollisionInfo;

    for (int i = 6; i < csvInfo[height].size(); i += 5) {
      if (1 == csvInfo[height][i]) {
        tempCollisionInfo.hasCollision_ = true;
        tempCollisionInfo.position_ = {-csvInfo[height][i + 1] /*- csvInfo[height][i + 3]*/, csvInfo[height][i + 2]};
        tempCollisionInfo.scale_ = {csvInfo[height][i + 3], csvInfo[height][i + 4]};
      } else {
        tempCollisionInfo.hasCollision_ = false;
        tempCollisionInfo.position_ = {0.0f, 0.0f};
        tempCollisionInfo.scale_ = {0.0f, 0.0f};
      }

      pNew->collisionBoxInfo_[(i - 6) / 5] = tempCollisionInfo;
    }

    LinkToLinkedListFIFO(&imageHead_, &imageTail_, &pNew->link_);
    pNew->index_ = (unsigned int)imageCount_++;
  }
  // CALCULATE IMAGE INFO END

  delete pInfo;
  pInfo = GetImageInfo(0);
  pInfo->isOwner_ = true;
}

void __stdcall Win32Image::CalculateTransform(unsigned int x, unsigned int y) {
  if (imageLoadType_ != ImageLoadType::One) {
    return;
  }

  ImageInfo* pInfo = GetImageInfo(0);
  pInfo->isOwner_ = false;
  UnLinkFromLinkedList(&imageHead_, &imageTail_, &pInfo->link_);
  --imageCount_;

  Cleanup();

  Vector imgScale = pInfo->GetScale();
  Vector calcScale = {imgScale.X / x, imgScale.Y / y};
  Vector calcPosition = {0.0f, 0.0f};

  for (unsigned int height = 0; height < y; ++height) {
    for (unsigned int width = 0; width < x; ++width) {
      ImageInfo* pNew = new ImageInfo;
      pNew->imageType_ = pInfo->imageType_;
      pNew->hBitMap_ = pInfo->hBitMap_;
      pNew->imageDC_ = pInfo->imageDC_;
      pNew->bitMapInfo_ = pInfo->bitMapInfo_;

      pNew->transform_.SetPosition(calcPosition);
      pNew->transform_.SetScale(calcScale);

      LinkToLinkedListFIFO(&imageHead_, &imageTail_, &pNew->link_);
      pNew->index_ = (unsigned int)imageCount_++;

      calcPosition.X += calcScale.X;
    }

    calcPosition.X = 0;
    calcPosition.Y += calcScale.Y;
  }

  delete pInfo;  // hBitMap 제거.

  pInfo = GetImageInfo(0);
  pInfo->isOwner_ = true;
}

void __stdcall Win32Image::RefreshImage(unsigned int count) {
  if (0 == count) {
    return;
  }

  ImageInfo* pInfo = GetImageInfo(0);
  pInfo->isOwner_ = false;

  UnLinkFromLinkedList(&imageHead_, &imageTail_, &pInfo->link_);
  --imageCount_;

  Cleanup();

  Vector imgScale = pInfo->GetScale();
  Vector calcScale = {imgScale.X / count, imgScale.Y / count};
  Vector calcPosition = {0.0f, 0.0f};

  for (unsigned int width = 0; width < count; ++width) {
    ImageInfo* pNew = new ImageInfo;
    pNew->imageType_ = pInfo->imageType_;
    pNew->hBitMap_ = pInfo->hBitMap_;
    pNew->imageDC_ = pInfo->imageDC_;
    pNew->bitMapInfo_ = pInfo->bitMapInfo_;

    pNew->transform_.SetPosition(calcPosition);
    pNew->transform_.SetScale(calcScale);

    LinkToLinkedListFIFO(&imageHead_, &imageTail_, &pNew->link_);
    pNew->index_ = (unsigned int)imageCount_++;

    calcPosition.X += calcScale.X;
  }

  delete pInfo;

  pInfo = GetImageInfo(0);
  pInfo->isOwner_ = true;
}

void __stdcall Win32Image::SetTransform(const Transform& transform, int index) {
  ImageInfo* pFindInfo = GetImageInfo(index);
  if (nullptr == pFindInfo) {
    return;
  }
  pFindInfo->transform_ = transform;
}

void __stdcall Win32Image::SetPath(std::string_view path) {
  currentPath_ = Path(path);
}

ImageType __stdcall Win32Image::GetImageType() {
  ImageInfo* pImg = GetImageInfo(0);
  if (nullptr == pImg) {
    return ImageType::ImageType_None;
  }
  return pImg->imageType_;
}

const Vector Win32Image::GetImagePositionOffSet(unsigned int index) const {
  const ImageInfo* pImg = GetImageInfo(index);

  if (nullptr == pImg) {
    return {0.0f, 0.0f};
  }

  return pImg->positionOffSet_;
}

void __stdcall Win32Image::AddImagePositionOffSet(unsigned int index, const Vector& offSet) {
  ImageInfo* pImg = GetImageInfo(index);

  if (nullptr == pImg) {
    return;
  }
  pImg->positionOffSet_ += offSet;

  for (int i = 0; i < pImg->collisionBoxInfo_.size(); ++i) {
    pImg->collisionBoxInfo_[i].position_ += offSet;
  }
}

bool __stdcall Win32Image::GetCollisionBoxInfo(unsigned int index, unsigned int type, CollisionInfo** outInfo) {
  ImageInfo* pImageInfo = GetImageInfo(index);

  if (nullptr == pImageInfo) {
    outInfo = nullptr;
    return false;
  }

  *outInfo = &pImageInfo->collisionBoxInfo_[type];
  return true;
}

void __stdcall Win32Image::SetCollisionBoxInfo(unsigned int index, unsigned int type, const CollisionInfo& collisionInfo) {
  ImageInfo* pImageInfo = GetImageInfo(index);

  if (nullptr == pImageInfo) {
    return;
  }

  pImageInfo->collisionBoxInfo_[type] = collisionInfo;
}

void __stdcall Win32Image::AddCollisionBoxPositionOffSet(unsigned int index, const Vector& offSet) {
  ImageInfo* pImageInfo = GetImageInfo(index);

  if (nullptr == pImageInfo) {
    return;
  }

  for (int i = 0; i < pImageInfo->collisionBoxInfo_.size(); ++i) {
    pImageInfo->collisionBoxInfo_[i].position_ += offSet;
  }
}

void __stdcall Win32Image::ExportImageInfoToCSV(const std::string& filepath) const {
  std::filesystem::path path(filepath);
  std::filesystem::create_directories(path.parent_path());
  std::ofstream outputFile(filepath);

  outputFile << "Position_X" << ",";
  outputFile << "Position_Y" << ",";
  outputFile << "Scale_X" << ",";
  outputFile << "Scale_Y" << ",";
  outputFile << "Offset_X" << ",";
  outputFile << "Offset_Y" << ",";

  outputFile << "HasHitBoxTop" << ",";
  outputFile << "HitBoxTopPosition_X" << ",";
  outputFile << "HitBoxTopPosition_Y" << ",";
  outputFile << "HitBoxTopScale_X" << ",";
  outputFile << "HitBoxTopScale_Y" << ",";

  outputFile << "HasHitBoxBottom" << ",";
  outputFile << "HitBoxBottomPosition_X" << ",";
  outputFile << "HitBoxBottomPosition_Y" << ",";
  outputFile << "HitBoxBottomScale_X" << ",";
  outputFile << "HitBoxBottomScale_Y" << ",";

  outputFile << "HasAttackBox" << ",";
  outputFile << "AttackBoxPosition_X" << ",";
  outputFile << "AttackBoxPosition_Y" << ",";
  outputFile << "AttackBoxScale_X" << ",";
  outputFile << "AttackBoxScale_Y" << ",";

  outputFile << "HasPushBox" << ",";
  outputFile << "PushBoxPosition_X" << ",";
  outputFile << "PushBoxPosition_Y" << ",";
  outputFile << "PushBoxScale_X" << ",";
  outputFile << "PushBoxScale_Y" << ",";

  outputFile << "HasGrabBox" << ",";
  outputFile << "GrabBoxPosition_X" << ",";
  outputFile << "GrabBoxPosition_Y" << ",";
  outputFile << "GrabBoxScale_X" << ",";
  outputFile << "GrabBoxScale_Y" << ",";
  outputFile << "\n";

  LINK_ITEM* pCur = imageHead_;
  while (pCur) {
    ImageInfo* pImg = (ImageInfo*)pCur->item_;
    pCur = pCur->next_;

    if (outputFile.is_open()) {
      outputFile << pImg->transform_.GetPosition().X << ",";
      outputFile << pImg->transform_.GetPosition().Y << ",";
      outputFile << pImg->transform_.GetScale().X << ",";
      outputFile << pImg->transform_.GetScale().Y << ",";
      outputFile << pImg->positionOffSet_.X << ",";
      outputFile << pImg->positionOffSet_.Y << ",";

      outputFile << ((pImg->collisionBoxInfo_[0].hasCollision_) ? 1.0f : 0.0f) << ",";
      outputFile << ((pImg->collisionBoxInfo_[0].hasCollision_) ? pImg->collisionBoxInfo_[0].position_.X : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[0].hasCollision_) ? pImg->collisionBoxInfo_[0].position_.Y : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[0].hasCollision_) ? pImg->collisionBoxInfo_[0].scale_.X : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[0].hasCollision_) ? pImg->collisionBoxInfo_[0].scale_.Y : 0) << ",";

      outputFile << ((pImg->collisionBoxInfo_[1].hasCollision_) ? 1.0f : 0.0f) << ",";
      outputFile << ((pImg->collisionBoxInfo_[1].hasCollision_) ? pImg->collisionBoxInfo_[1].position_.X : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[1].hasCollision_) ? pImg->collisionBoxInfo_[1].position_.Y : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[1].hasCollision_) ? pImg->collisionBoxInfo_[1].scale_.X : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[1].hasCollision_) ? pImg->collisionBoxInfo_[1].scale_.Y : 0) << ",";

      outputFile << ((pImg->collisionBoxInfo_[2].hasCollision_) ? 1.0f : 0.0f) << ",";
      outputFile << ((pImg->collisionBoxInfo_[2].hasCollision_) ? pImg->collisionBoxInfo_[2].position_.X : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[2].hasCollision_) ? pImg->collisionBoxInfo_[2].position_.Y : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[2].hasCollision_) ? pImg->collisionBoxInfo_[2].scale_.X : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[2].hasCollision_) ? pImg->collisionBoxInfo_[2].scale_.Y : 0) << ",";

      outputFile << ((pImg->collisionBoxInfo_[3].hasCollision_) ? 1.0f : 0.0f) << ",";
      outputFile << ((pImg->collisionBoxInfo_[3].hasCollision_) ? pImg->collisionBoxInfo_[3].position_.X : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[3].hasCollision_) ? pImg->collisionBoxInfo_[3].position_.Y : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[3].hasCollision_) ? pImg->collisionBoxInfo_[3].scale_.X : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[3].hasCollision_) ? pImg->collisionBoxInfo_[3].scale_.Y : 0) << ",";

      outputFile << ((pImg->collisionBoxInfo_[4].hasCollision_) ? 1.0f : 0.0f) << ",";
      outputFile << ((pImg->collisionBoxInfo_[4].hasCollision_) ? pImg->collisionBoxInfo_[4].position_.X : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[4].hasCollision_) ? pImg->collisionBoxInfo_[4].position_.Y : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[4].hasCollision_) ? pImg->collisionBoxInfo_[4].scale_.X : 0) << ",";
      outputFile << ((pImg->collisionBoxInfo_[4].hasCollision_) ? pImg->collisionBoxInfo_[4].scale_.Y : 0) << ",";

      outputFile << "\n";
    }
  }
  outputFile.close();
}

bool __stdcall Win32Image::Load() {
  if (currentPath_.IsFile()) {
    return LoadFile();
  } else if (currentPath_.IsDirectory()) {
    return LoadFolder();
  }
  __debugbreak();
  return false;
}

HDC Win32Image::GetDC() const {
  const ImageInfo* img = GetImageInfo(0);
  if (nullptr == img) {
    return nullptr;
  }
  return img->imageDC_;
}

void Win32Image::Cleanup() {
  while (imageHead_) {
    ImageInfo* clearImg = (ImageInfo*)imageHead_->item_;

    UnLinkFromLinkedList(&imageHead_, &imageTail_, &clearImg->link_);

    delete clearImg;
  }
  imageCount_ = 0;
}

ImageInfo* Win32Image::GetImageInfo(unsigned __int64 index) {
  if (0 == imageCount_) {
    return nullptr;
  }
  if (imageCount_ <= index) {
    return nullptr;
  }

  LINK_ITEM* pCur = imageHead_;
  while (pCur) {
    ImageInfo* pImg = (ImageInfo*)pCur->item_;
    pCur = pCur->next_;

    if (pImg->index_ != index) {
      continue;
    }
    return pImg;
  }

  return nullptr;
}

const ImageInfo* Win32Image::GetImageInfo(unsigned __int64 index) const {
  if (0 == imageCount_) {
    return nullptr;
  }
  if (imageCount_ <= index) {
    return nullptr;
  }

  LINK_ITEM* pCur = imageHead_;
  while (pCur) {
    ImageInfo* pImg = (ImageInfo*)pCur->item_;
    pCur = pCur->next_;

    if (pImg->index_ != index) {
      continue;
    }
    return pImg;
  }

  return nullptr;
}

bool Win32Image::LoadFile() {
  imageLoadType_ = ImageLoadType::One;

  Win32GraphicDevice* graphicDevice = GApplication->GetGraphicDevice();
  if (nullptr == graphicDevice) {
    __debugbreak();
    return false;
  }
  IRenderTexture* mainBuffer = graphicDevice->GetMainBuffer();
  if (nullptr == mainBuffer) {
    __debugbreak();
    return false;
  }

  std::string extensionStr = currentPath_.GetExtension();
  for (char& ch : extensionStr) {
    ch = static_cast<char>(std::toupper(ch));
  }
  if (0 == extensionStr.compare(".BMP")) {
    if (false == LoadBMP(mainBuffer)) {
      return false;
    }

  } else if (0 == extensionStr.compare(".PNG")) {
    if (false == LoadPNG(mainBuffer)) {
      return false;
    }
  } else if (0 == extensionStr.compare(".TGA")) {
    if (false == LoadTGA(mainBuffer)) {
      return false;
    }
  } else {
    __debugbreak();
    return false;
  }

  return true;
}

bool Win32Image::LoadFolder() {
  imageLoadType_ = ImageLoadType::Folder;

  Win32GraphicDevice* graphicDevice = GApplication->GetGraphicDevice();
  if (nullptr == graphicDevice) {
    __debugbreak();
    return false;
  }
  IRenderTexture* mainBuffer = graphicDevice->GetMainBuffer();
  if (nullptr == mainBuffer) {
    __debugbreak();
    return false;
  }

  Directory dir = currentPath_;

  std::list<Path> newPath = dir.AllFile({".BMP", ".PNG", ".TGA"});

  for (Path& file : newPath) {
    std::string extensionStr = file.GetExtension();
    for (char& ch : extensionStr) {
      ch = static_cast<char>(std::toupper(ch));
    }
    if (0 == extensionStr.compare(".BMP")) {
      if (false == LoadBMP(mainBuffer)) {
        return false;
      }
    } else if (0 == extensionStr.compare(".PNG")) {
      if (false == LoadPNG(mainBuffer)) {
        return false;
      }
    } else if (0 == extensionStr.compare(".TGA")) {
      if (false == LoadTGA(mainBuffer)) {
        return false;
      }
    }
  }

  return false;
}

bool Win32Image::LoadBMP(IRenderTexture* mainBuffer) {
  /*HANDLE imageHandle = LoadImageA(nullptr, currentPath_.GetPathString().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_SHARED);
  hBitMap_ = (HBITMAP)imageHandle;*/

  FILE* file = nullptr;
  fopen_s(&file, currentPath_.GetPathString().c_str(), "rb");
  if (nullptr == file) {
    return false;
  }
  BITMAPFILEHEADER fileHeader = {};
  fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);

  if (fileHeader.bfType != 0x4D42) {  // 'BM' 확인
    fclose(file);
    return false;
  }

  BITMAPINFOHEADER infoHeader = {};
  fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

  LONG imageHeight = abs(infoHeader.biHeight);

  int imageSize = infoHeader.biSizeImage;
  if (imageSize == 0) {
    imageSize = infoHeader.biWidth * imageHeight * (infoHeader.biBitCount / 8);
  }

  BYTE* bitmapData = (BYTE*)malloc(imageSize);
  BYTE* convertBItmapData = (BYTE*)malloc(infoHeader.biWidth * imageHeight * 4);
  fseek(file, fileHeader.bfOffBits, SEEK_SET);
  fread(bitmapData, imageSize, 1, file);
  fclose(file);

  WORD bytesPerPixel = infoHeader.biBitCount / 8;
  bool isBottomUp = (infoHeader.biHeight < 0);
  int rowSize = ((infoHeader.biWidth * bytesPerPixel + 3) & ~3);

  for (int y = 0; y < imageHeight; ++y) {
    int srcY = isBottomUp ? (imageHeight - 1 - y) : y;
    unsigned char* pSrcRow = bitmapData + srcY * rowSize;

    for (int x = 0; x < infoHeader.biWidth; ++x) {
      int srcIndex = x * bytesPerPixel;

      BYTE B = pSrcRow[srcIndex + 0];
      BYTE G = pSrcRow[srcIndex + 1];
      BYTE R = pSrcRow[srcIndex + 2];

      convertBItmapData[y * infoHeader.biWidth * 4 + x * 4 + 0] = B;
      convertBItmapData[y * infoHeader.biWidth * 4 + x * 4 + 1] = G;
      convertBItmapData[y * infoHeader.biWidth * 4 + x * 4 + 2] = R;

      if (4 == bytesPerPixel) {
        convertBItmapData[y * infoHeader.biWidth * 4 + x * 4 + 3] = pSrcRow[srcIndex + 3];
      } else {
        convertBItmapData[y * infoHeader.biWidth * 4 + x * 4 + 3] = (BYTE)255;
      }
    }
  }

  // ConvertToGrayscale(convertBItmapData, infoHeader.biWidth, infoHeader.biHeight, 4);

  BITMAPINFO bmi = {};
  memset(&bmi, 0x00, sizeof(BITMAPINFO));
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = infoHeader.biWidth;
  bmi.bmiHeader.biHeight = imageHeight;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;

  HBITMAP hBitMap = CreateDIBSection((HDC)mainBuffer->GetHandle(), &bmi, DIB_RGB_COLORS, NULL, NULL, 0);
  if (nullptr == hBitMap) {
    return false;
  }

  BITMAP bmp = {};
  GetObject(hBitMap, sizeof(BITMAP), &bmp);
  memcpy(bmp.bmBits, convertBItmapData, infoHeader.biWidth * imageHeight * 4);

  free(convertBItmapData);
  free(bitmapData);

  ImageInfo* newImageInfo = new ImageInfo;
  newImageInfo->imageType_ = ImageType::ImageType_BMP;

  newImageInfo->imageDC_ = CreateCompatibleDC((HDC)mainBuffer->GetHandle());
  if (nullptr == newImageInfo->imageDC_) {
    delete newImageInfo;
    return false;
  }

  newImageInfo->hBitMap_ = hBitMap;

  DeleteObject(SelectObject(newImageInfo->imageDC_, newImageInfo->hBitMap_));

  GetObject(newImageInfo->hBitMap_, sizeof(BITMAP), &newImageInfo->bitMapInfo_);

  newImageInfo->transform_.SetScale(newImageInfo->GetScale());
  newImageInfo->index_ = (unsigned int)imageCount_++;
  LinkToLinkedListFIFO(&imageHead_, &imageTail_, &newImageInfo->link_);

  newImageInfo->isOwner_ = true;
  return true;
}

bool Win32Image::LoadPNG(IRenderTexture* mainBuffer) {
  std::wstring wPath = currentPath_.GetPathWString();

  Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
  Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)pImage->Clone();

  HBITMAP hBitMap = nullptr;

  Gdiplus::Status stat = pBitmap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitMap);
  bool isFailed = false;
  if (Gdiplus::Status::Ok != stat) {
    isFailed = true;
  }

  delete pBitmap;
  delete pImage;

  if (isFailed) {
    __debugbreak();
    return false;
  }

  ImageInfo* newImageInfo = new ImageInfo;
  newImageInfo->imageType_ = ImageType::ImageType_PNG;

  newImageInfo->imageDC_ = CreateCompatibleDC((HDC)mainBuffer->GetHandle());
  if (nullptr == newImageInfo->imageDC_) {
    delete newImageInfo;
    return false;
  }

  newImageInfo->hBitMap_ = hBitMap;

  DeleteObject(SelectObject(newImageInfo->imageDC_, newImageInfo->hBitMap_));

  GetObject(newImageInfo->hBitMap_, sizeof(BITMAP), &newImageInfo->bitMapInfo_);

  newImageInfo->transform_.SetScale(newImageInfo->GetScale());
  newImageInfo->index_ = (unsigned int)imageCount_++;
  LinkToLinkedListFIFO(&imageHead_, &imageTail_, &newImageInfo->link_);

  newImageInfo->isOwner_ = true;
  return true;
}

bool Win32Image::LoadTGA(IRenderTexture* mainBuffer) {
  FILE* file = nullptr;
  fopen_s(&file, currentPath_.GetPathString().c_str(), "rb");
  if (nullptr == file) {
    return false;
  }
  TGAHeader tgaHeader = {};
  fread(&tgaHeader, sizeof(TGAHeader), 1, file);

  DWORD imageSize = tgaHeader.width * tgaHeader.height * (tgaHeader.PixelDepth / 8);
  BYTE* pixelData = (BYTE*)malloc(imageSize);
  BYTE* convertPixelData = (BYTE*)malloc(tgaHeader.width * tgaHeader.height * 4);

  fread(pixelData, sizeof(BYTE), imageSize, file);
  fclose(file);

  DWORD line = tgaHeader.height;
  DWORD dwWidthBytes = tgaHeader.width * 4;

  for (int y = 0; y < tgaHeader.height; ++y) {
    --line;
    for (int x = 0; x < tgaHeader.width; ++x) {
      convertPixelData[line * dwWidthBytes + x * 4 + 0] = pixelData[y * tgaHeader.width * 3 + x * 3 + 0];
      convertPixelData[line * dwWidthBytes + x * 4 + 1] = pixelData[y * tgaHeader.width * 3 + x * 3 + 1];
      convertPixelData[line * dwWidthBytes + x * 4 + 2] = pixelData[y * tgaHeader.width * 3 + x * 3 + 2];
      convertPixelData[line * dwWidthBytes + x * 4 + 3] = (BYTE)255;
    }
  }

  // ConvertToGrayscale(convertPixelData, tgaHeader.width, tgaHeader.height, 4);

  BITMAPINFO bmi = {};
  memset(&bmi, 0x00, sizeof(BITMAPINFO));
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = tgaHeader.width;
  bmi.bmiHeader.biHeight = tgaHeader.height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;

  HBITMAP hBitMap = CreateDIBSection((HDC)mainBuffer->GetHandle(), &bmi, DIB_RGB_COLORS, NULL, NULL, 0);
  if (nullptr == hBitMap) {
    return false;
  }

  BITMAP bmp = {};
  GetObject(hBitMap, sizeof(BITMAP), &bmp);
  memcpy(bmp.bmBits, convertPixelData, tgaHeader.width * tgaHeader.height * 4);

  free(convertPixelData);
  free(pixelData);

  ImageInfo* newImageInfo = new ImageInfo;
  newImageInfo->imageType_ = ImageType::ImageType_TGA;

  newImageInfo->imageDC_ = CreateCompatibleDC((HDC)mainBuffer->GetHandle());
  if (nullptr == newImageInfo->imageDC_) {
    delete newImageInfo;
    return false;
  }

  newImageInfo->hBitMap_ = hBitMap;

  DeleteObject(SelectObject(newImageInfo->imageDC_, newImageInfo->hBitMap_));

  GetObject(newImageInfo->hBitMap_, sizeof(BITMAP), &newImageInfo->bitMapInfo_);

  newImageInfo->transform_.SetScale(newImageInfo->GetScale());
  newImageInfo->index_ = (unsigned int)imageCount_++;
  LinkToLinkedListFIFO(&imageHead_, &imageTail_, &newImageInfo->link_);

  newImageInfo->isOwner_ = true;
  return true;
}

void Win32Image::ConvertToGrayscale(BYTE* pPixels, int width, int height, int bytesPerPixel) {
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int index = (y * width + x) * bytesPerPixel;

      BYTE r = pPixels[index];
      BYTE g = pPixels[index + 1];
      BYTE b = pPixels[index + 2];

      BYTE gray = (BYTE)(0.299 * r + 0.587 * g + 0.114 * b);

      pPixels[index] = gray;
      pPixels[index + 1] = gray;
      pPixels[index + 2] = gray;
    }
  }
}

bool Win32Image::SearchPartitionLineRow(const Vector& startPoint, Vector* outLeftTopPoint, Color8Bit lineColor) {
  if (nullptr == outLeftTopPoint) {
    __debugbreak();
    return false;
  }

  ImageInfo* pImage = GetImageInfo(0);
  if (nullptr == pImage) {
    __debugbreak();
    return false;
  }

  Vector endPoint = pImage->transform_.GetScale();

  Color8Bit pixelColor;
  Vector curPosition = startPoint;

  bool doLineSearch = true;

  while (curPosition.Y < endPoint.Y && doLineSearch) {
    while (curPosition.X < endPoint.X && doLineSearch) {
      if (false == GetPixel(curPosition, &pixelColor)) {
        __debugbreak();
        return false;
      }
      if (pixelColor == lineColor) {
        *outLeftTopPoint = curPosition;
        return true;
        doLineSearch = false;
      } else {
        curPosition.X += 1.0f;
      }
    }
    curPosition.X = 0;
    curPosition.Y += 1;
  }

  return false;
}

void Win32Image::SearchPartitionGrid(const Vector& leftTopPoint, Vector* outNextSearchStartPoint, std::vector<Vector>* pGridCorner, Color8Bit emptyColor, Color8Bit lineColor) {
  if (nullptr == outNextSearchStartPoint) {
    __debugbreak();
    return;
  }

  if (nullptr == pGridCorner) {
    __debugbreak();
    return;
  }

  pGridCorner->push_back(leftTopPoint);

  Vector xMovePoint = leftTopPoint;
  Vector yMovePoint;

  Color8Bit pixelColor1;
  Color8Bit pixelColor2;

  while (1) {
    xMovePoint.X += 1.0f;
    yMovePoint.X = xMovePoint.X;
    yMovePoint.Y = xMovePoint.Y + 1.0f;

    if (false == GetPixel(xMovePoint, &pixelColor1) || false == GetPixel(yMovePoint, &pixelColor2)) {
      __debugbreak();
    }

    if (pixelColor2 == lineColor) {
      while (1) {
        yMovePoint.Y += 1.0f;
        if (false == GetPixel(yMovePoint, &pixelColor2)) {
          __debugbreak();
        }

        if (pixelColor2 != lineColor) {
          pGridCorner->push_back({yMovePoint.X, yMovePoint.Y - 1});
          pGridCorner->push_back(xMovePoint);
          *outNextSearchStartPoint = {0.0f, yMovePoint.Y};
          break;
        }
      }
    }

    if (pixelColor1 != lineColor) {
      pGridCorner->pop_back();
      break;
    }
  }
}

void Win32Image::DetectBoundBox(const Vector& leftTopPoint, const Vector& rightBottomPoint, std::vector<std::vector<float>>* pBoundingBoxDatas, Color8Bit emptyColor, Color8Bit lineColor) {
  std::vector<float> boundBox;

  Vector searchLeftPos = {leftTopPoint.X + 1.0f, leftTopPoint.Y + 1.0f};
  Vector searchTopPos = {leftTopPoint.X + 1.0f, leftTopPoint.Y + 1.0f};

  Vector searchRightPos = {rightBottomPoint.X - 1.0f, rightBottomPoint.Y - 1.0f};
  Vector searchBottomPos = {rightBottomPoint.X - 1.0f, rightBottomPoint.Y - 1.0f};

  Color8Bit pixelColor;

  bool doSearch = true;

  // LeftTop_X
  while (searchLeftPos.X < rightBottomPoint.X && doSearch) {
    while (searchLeftPos.Y < rightBottomPoint.Y && doSearch) {
      if (false == GetPixel(searchLeftPos, &pixelColor)) {
        __debugbreak();
      }

      if (pixelColor == emptyColor) {
        searchLeftPos.Y += 1.0f;
      } else if (pixelColor != emptyColor) {
        boundBox.push_back(searchLeftPos.X - 1);
        doSearch = false;
      }
    }
    searchLeftPos.Y = leftTopPoint.Y + 1.0f;
    searchLeftPos.X += 1.0f;
  }

  // LeftTop_Y
  doSearch = true;
  while (searchTopPos.Y < rightBottomPoint.Y && doSearch) {
    while (searchTopPos.X < rightBottomPoint.X && doSearch) {
      if (false == GetPixel(searchTopPos, &pixelColor)) {
        __debugbreak();
      }

      if (pixelColor == emptyColor) {
        searchTopPos.X += 1.0f;
      } else if (pixelColor != lineColor) {
        boundBox.push_back(searchTopPos.Y - 1);
        doSearch = false;
      }
    }
    searchTopPos.X = leftTopPoint.X + 1.0f;
    searchTopPos.Y += 1.0f;
  }

  // RightBottom_X
  doSearch = true;
  while (searchRightPos.X > leftTopPoint.X && doSearch) {
    while (searchRightPos.Y > leftTopPoint.Y && doSearch) {
      if (false == GetPixel(searchRightPos, &pixelColor)) {
        __debugbreak();
      }

      if (pixelColor == emptyColor) {
        searchRightPos.Y -= 1.0f;
      } else if (pixelColor != lineColor) {
        boundBox.push_back(searchRightPos.X + 1);
        doSearch = false;
      }
    }
    searchRightPos.Y = rightBottomPoint.Y - 1.0f;
    searchRightPos.X -= 1.0f;
  }

  // RightBottom_Y
  doSearch = true;
  while (searchBottomPos.Y > leftTopPoint.Y && doSearch) {
    while (searchBottomPos.X > leftTopPoint.X && doSearch) {
      if (false == GetPixel(searchBottomPos, &pixelColor)) {
        __debugbreak();
      }

      if (pixelColor == emptyColor) {
        searchBottomPos.X -= 1.0f;
      } else if (pixelColor != lineColor) {
        boundBox.push_back(searchBottomPos.Y + 1);
        doSearch = false;
      }
    }
    searchBottomPos.X = rightBottomPoint.X - 1.0f;
    searchBottomPos.Y -= 1.0f;
  }

  pBoundingBoxDatas->push_back(boundBox);
}