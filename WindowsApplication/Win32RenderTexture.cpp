#include "stdafx.h"
#include "Win32RenderTexture.h"

Win32RenderTexture::Win32RenderTexture()
    : refCount_(1),
      isBackBuffer_(false),
      hWnd_(nullptr),
      imageDC_(nullptr),
      hBitMap_(nullptr),
      bitMapInfo_({}) {
}

Win32RenderTexture::~Win32RenderTexture() {
  if (nullptr != hWnd_ && nullptr != imageDC_) {
    ReleaseDC(hWnd_, imageDC_);
  }
  if (nullptr == hWnd_ && nullptr != imageDC_) {
    DeleteObject(hBitMap_);
    DeleteDC(imageDC_);
  }
}

HRESULT __stdcall Win32RenderTexture::QueryInterface(REFIID riid, void** ppvObject) {
  return E_NOTIMPL;
}

ULONG __stdcall Win32RenderTexture::AddRef() {
  ++refCount_;
  return refCount_;
}

ULONG __stdcall Win32RenderTexture::Release() {
  --refCount_;
  ULONG tmpRefCount = refCount_;
  if (0 == refCount_) {
    delete this;
  }

  return tmpRefCount;
}

Vector __stdcall Win32RenderTexture::GetScale(unsigned int index) {
  return Vector(bitMapInfo_.bmWidth, bitMapInfo_.bmHeight);
}

unsigned __int64 __stdcall Win32RenderTexture::GetImageCount() {
  return 1;
}

void* __stdcall Win32RenderTexture::GetHandle() {
  return imageDC_;
}

Transform __stdcall Win32RenderTexture::RenderTransform(unsigned int index) {
  return Transform({0.0f, 0.0f}, GetScale());
}

bool Win32RenderTexture::GetPixel(const Vector& position, Color8Bit* outColor) {
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

bool Win32RenderTexture::Save(std::string_view filePath, unsigned int index) {
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
  infoHeader.biWidth = bitMapInfo_.bmWidth;
  infoHeader.biHeight = -bitMapInfo_.bmHeight;
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
  fwrite(bitMapInfo_.bmBits, infoHeader.biSizeImage, 1, saveFile);
  fclose(saveFile);

  return true;
}

bool Win32RenderTexture::IsRenderTexture() {
  return true;
}

bool Win32RenderTexture::BitBlt(IImage* srcImg, const Transform& transform) {
  if (nullptr == srcImg) {
    return false;
  }

  HDC srcHDC = (HDC)srcImg->GetHandle();

  int left = transform.IntergerLeft();
  int top = transform.IntergerTop();
  int right = transform.GetScale().IntergerX();
  int bottom = transform.GetScale().IntergerY();

  BOOL isSuccess = ::BitBlt(
      GetDC(),
      left,    // 그리기 시작 위치 X
      top,     // 그리기 시작 위치 Y
      right,   // 그려야할 이미지의 가로 크기
      bottom,  // 그려야할 이미지의 세로 크기
      srcHDC,
      0,
      0,
      SRCCOPY);

  return TRUE == isSuccess;
}

bool Win32RenderTexture::AlphaBlend(IImage* srcImg, unsigned int index, const Vector& scale, float alpha) {
  HDC srcHDC = (HDC)srcImg->GetHandle();
  Vector srcScale = srcImg->GetScale(index);
  Transform imageTransform = srcImg->RenderTransform(index);

  int RenderLeft = std::lround(0 - scale.HalfX());
  int RenderTop = std::lround(0 - scale.HalfY());
  int RenderRight = scale.IntergerX();
  int RenderBottom = scale.IntergerY();

  int ImageLeft = imageTransform.GetPosition().IntergerX();
  int ImageTop = imageTransform.GetPosition().IntergerY();
  int ImageRight = imageTransform.GetScale().IntergerX();
  int ImageBottom = imageTransform.GetScale().IntergerY();

  BLENDFUNCTION bf = {AC_SRC_OVER, 0, 0, AC_SRC_ALPHA};

  bf.SourceConstantAlpha = (BYTE)(255 * alpha);

  BOOL isSuccess = ::AlphaBlend(
      imageDC_,
      RenderLeft,
      RenderTop,
      RenderRight,
      RenderBottom,
      srcHDC,
      ImageLeft,
      ImageTop,
      ImageRight,
      ImageBottom,
      bf);

  return TRUE == isSuccess;
}

bool Win32RenderTexture::Transparent(IImage* srcImg, unsigned int index, const Vector& scale, const Color8Bit& colorTransparent) {
  HDC srcHDC = (HDC)srcImg->GetHandle();
  //Vector srcScale = srcImg->GetScale(index);
  Transform imageTransform = srcImg->RenderTransform(index);

  int RenderStartX = std::lround(0 - scale.HalfX());
  int RenderStartY = std::lround(0 - scale.HalfY());
  int RenderWidth = scale.IntergerX();
  int RenderHeight = scale.IntergerY();

  int ImageLeft = imageTransform.GetPosition().IntergerX();
  int ImageTop = imageTransform.GetPosition().IntergerY();
  int ImageRight = imageTransform.GetScale().IntergerX();
  int ImageBottom = imageTransform.GetScale().IntergerY();

  BOOL isSuccess = ::TransparentBlt(
      imageDC_,
      RenderStartX,
      RenderStartY,
      RenderWidth,
      RenderHeight,
      srcHDC,
      ImageLeft,
      ImageTop,
      ImageRight,
      ImageBottom,
      colorTransparent.Color);

  return TRUE == isSuccess;
}

bool Win32RenderTexture::Stretch(IImage* srcImg, const Transform& transform) {
  HDC srcHDC = (HDC)srcImg->GetHandle();
  Vector srcScale = srcImg->GetScale();

  int left = transform.IntergerLeft();
  int top = transform.IntergerTop();
  int right = transform.GetScale().IntergerX();
  int bottom = transform.GetScale().IntergerY();

  BOOL isSuccess = ::StretchBlt(
      imageDC_,
      left,
      top,
      right,
      bottom,
      srcHDC,
      0,
      0,
      (int)srcScale.X,
      (int)srcScale.Y,
      SRCCOPY);

  return TRUE == isSuccess;
}

void Win32RenderTexture::DrawRectagle(const Vector& scale, const Color8Bit& color, float Linethickness /*= 1.0f*/) {
  int startX = std::lround(0 - scale.HalfX());
  int startY = std::lround(0 - scale.HalfY());
  int width = scale.IntergerX();
  int height = scale.IntergerY();

  Gdiplus::Graphics graphics(GetDC());
  Gdiplus::Pen pen(Gdiplus::Color(color.A, color.R, color.G, color.B), Linethickness);
  graphics.DrawRectangle(&pen, startX, startY, width, height);
}

void Win32RenderTexture::DrawCircle(const Vector& scale, const Color8Bit& color, float Linethickness) {
  int radius = scale.IntergerX();
  int r = (int)scale.HalfX();

  Gdiplus::Graphics graphics(GetDC());
  Gdiplus::Pen pen(Gdiplus::Color(color.A, color.R, color.G, color.B), Linethickness);
  graphics.DrawEllipse(&pen, -r, -r, radius, radius);
}

void Win32RenderTexture::DrawPoint(const Color8Bit& color, float Linethickness) {
  int radius = 2;

  Gdiplus::Graphics graphics(GetDC());
  Gdiplus::Pen pen(Gdiplus::Color(color.A, color.R, color.G, color.B), Linethickness);
  graphics.DrawEllipse(&pen, -radius, -radius, radius, radius);
}

void __stdcall Win32RenderTexture::DrawLine(const Color8Bit& color, const Vector& start, const Vector& end, float Linethickness) {
  Gdiplus::Graphics graphics(GetDC());
  Gdiplus::Pen pen(Gdiplus::Color(color.A, color.R, color.G, color.B), Linethickness);
  Gdiplus::Point startPoint(start.IntergerX(), start.IntergerY());
  Gdiplus::Point endPoint(end.IntergerX(), end.IntergerY());
  graphics.DrawLine(&pen, startPoint, endPoint);
}

void __stdcall Win32RenderTexture::SetColor(const Color8Bit& color) {
  if (0 == color.A) {
    Vector scale = GetScale();
    HBRUSH hBrush = CreateSolidBrush(color.Color);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(imageDC_, hBrush);
    Rectangle(imageDC_, -1, -1, scale.IntergerX() + 1, scale.IntergerY() + 1);
    SelectObject(imageDC_, hOldBrush);
    DeleteObject(hBrush);
    return;
  }

  if (nullptr == bitMapInfo_.bmBits) {
    return;
  }

  bool isBottomUp = bitMapInfo_.bmHeight > 0;
  int rowSize = ((bitMapInfo_.bmWidth * 4 + 3) & ~3);

  for (int y = 0; y < abs(bitMapInfo_.bmHeight); ++y) {
    int srcY = isBottomUp ? (bitMapInfo_.bmHeight - 1 - y) : y;
    unsigned char* pSrcRow = ((unsigned char*)bitMapInfo_.bmBits) + srcY * rowSize;

    for (int x = 0; x < bitMapInfo_.bmWidth; ++x) {
      int srcIndex = x * 4;

      pSrcRow[srcIndex] = color.B;
      pSrcRow[srcIndex + 1] = color.G;
      pSrcRow[srcIndex + 2] = color.R;
      pSrcRow[srcIndex + 3] = color.A;
    }
  }
}

void __stdcall Win32RenderTexture::SetAlpha(float alpha, const Transform& transform, bool useIgnoreColor, const Color8Bit& ignoreColor) {
  BYTE realAlpha = (BYTE)(255 * alpha);

  int left = (int)transform.Left();
  int top = (int)transform.Top();

  left = left < 0 ? 0 : left;
  top = top < 0 ? 0 : top;

  int right = (int)transform.Right();
  int bottom = (int)transform.Bottom();

  right = right < bitMapInfo_.bmWidth ? right : bitMapInfo_.bmWidth;
  bottom = bottom < bitMapInfo_.bmHeight ? bottom : bitMapInfo_.bmHeight;

  bool isBottomUp = bitMapInfo_.bmHeight < 0;

  int rowSize = ((bitMapInfo_.bmWidth * 4 + 3) & ~3);

  for (int y = top; y < bottom; ++y) {
    int srcY = isBottomUp ? (bitMapInfo_.bmHeight - 1 - y) : y;
    unsigned char* pSrcRow = ((unsigned char*)bitMapInfo_.bmBits) + srcY * rowSize;

    for (int x = left; x < right; ++x) {
      int srcIndex = x * 4;

      if (useIgnoreColor) {
        Color8Bit tmpColor;
        tmpColor.B = pSrcRow[srcIndex];
        tmpColor.G = pSrcRow[srcIndex + 1];
        tmpColor.R = pSrcRow[srcIndex + 2];
        tmpColor.A = ignoreColor.A;

        if (tmpColor == ignoreColor) {
          pSrcRow[srcIndex + 3] = 0;
        } else {
          pSrcRow[srcIndex + 3] = realAlpha;
        }

      } else {
        pSrcRow[srcIndex + 3] = realAlpha;
      }
    }
  }
}

void __stdcall Win32RenderTexture::Text(const wchar_t* font, const wchar_t* text, unsigned __int64 fontSize, const Vector& position, const Color8Bit& color) {
  Gdiplus::StringFormat stringFormat;
  stringFormat.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
  stringFormat.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);

  Gdiplus::Graphics graphics(imageDC_);
  Gdiplus::Font fnt(font, (Gdiplus::REAL)fontSize, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
  Gdiplus::SolidBrush hb(Gdiplus::Color(color.R, color.G, color.B));

  Gdiplus::RectF rectF(position.X, position.Y, 0, 0);

  Gdiplus::Status stat = graphics.DrawString(text, -1, &fnt, rectF, &stringFormat, &hb);
  if (stat == Gdiplus::Status::Ok) {
  }
}

bool Win32RenderTexture::Initialize(const Win32RenderTexture* mainTexture, const Vector& scale) {
  if (nullptr == mainTexture) {
    return false;
  }

  BITMAPINFO bmi = {};
  memset(&bmi, 0x00, sizeof(BITMAPINFO));
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = scale.IntergerX();
  bmi.bmiHeader.biHeight = -scale.IntergerY();
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;

  void* pBits = nullptr;

  hBitMap_ = CreateDIBSection(mainTexture->GetDC(), &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
  if (nullptr == hBitMap_) {
    return false;
  }

  GetObject(hBitMap_, sizeof(BITMAP), &bitMapInfo_);

  imageDC_ = CreateCompatibleDC(mainTexture->GetDC());
  if (nullptr == imageDC_) {
    DeleteObject(hBitMap_);
    return false;
  }

  bool isBottomUp = bitMapInfo_.bmHeight > 0;
  int rowSize = ((bitMapInfo_.bmWidth * 4 + 3) & ~3);

  for (int y = 0; y < abs(bitMapInfo_.bmHeight); ++y) {
    int srcY = isBottomUp ? (bitMapInfo_.bmHeight - 1 - y) : y;
    unsigned char* pSrcRow = ((unsigned char*)pBits) + srcY * rowSize;

    for (int x = 0; x < bitMapInfo_.bmWidth; ++x) {
      int srcIndex = x * 4;

      pSrcRow[srcIndex] = 0;
      pSrcRow[srcIndex + 1] = 0;
      pSrcRow[srcIndex + 2] = 255;
      pSrcRow[srcIndex + 3] = 255;
    }
  }

  DeleteObject(SelectObject(imageDC_, hBitMap_));

  Refresh();

  return true;
}

void Win32RenderTexture::SetHDC(HWND hWnd) {
  if (nullptr == hWnd) {
    return;
  }

  hWnd_ = hWnd;

  imageDC_ = ::GetDC(hWnd_);

  Refresh();
}

HDC Win32RenderTexture::GetDC() const {
  return imageDC_;
}

void Win32RenderTexture::Refresh() {
  hBitMap_ = (HBITMAP)GetCurrentObject(imageDC_, OBJ_BITMAP);

  GetObject(hBitMap_, sizeof(BITMAP), &bitMapInfo_);
}

bool Win32RenderTexture::IsMainBuffer() const {
  return hWnd_ && imageDC_;
}

void Win32RenderTexture::SetBackBuffer() {
  isBackBuffer_ = true;
}

bool Win32RenderTexture::IsBackBuffer() const {
  return isBackBuffer_;
}
