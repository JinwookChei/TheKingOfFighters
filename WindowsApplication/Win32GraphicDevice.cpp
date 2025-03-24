#include "stdafx.h"
#include "Win32GraphicDevice.h"
#include "Win32Image.h"
#include "Win32RenderTexture.h"
#include "WindowsApplication.h"
#include "Window.h"

Win32GraphicDevice::Win32GraphicDevice()
    : clearColor_(Color8Bit::Magenta),
      mainBuffer_(nullptr),
      backBuffer_(nullptr),
      refCount_(1) {
}

Win32GraphicDevice::~Win32GraphicDevice() {
  if (nullptr != backBuffer_) {
    backBuffer_->Release();
    backBuffer_ = nullptr;
  }
  if (nullptr != mainBuffer_) {
    mainBuffer_->Release();
    mainBuffer_ = nullptr;
  }
}

HRESULT __stdcall Win32GraphicDevice::QueryInterface(REFIID riid, void** ppvObject) {
  return E_NOTIMPL;
}

ULONG __stdcall Win32GraphicDevice::AddRef() {
  ++refCount_;
  return refCount_;
}

ULONG __stdcall Win32GraphicDevice::Release() {
  --refCount_;
  ULONG tmpRefCount = refCount_;
  if (0 == refCount_) {
    delete this;
  }

  return tmpRefCount;
}

IFileImage* __stdcall Win32GraphicDevice::LoadImg(std::string_view path) {
  Win32Image* newImg = new Win32Image;

  newImg->SetPath(path);

  if (false == newImg->Load()) {
    newImg->Release();
    return nullptr;
  }

  return newImg;
}

IRenderTexture* __stdcall Win32GraphicDevice::CreateRenderTexture(unsigned int width, unsigned int height, const Color8Bit& clearColor) {
  Win32RenderTexture* renderTexture = new Win32RenderTexture;
  if (false == renderTexture->Initialize(mainBuffer_, {(long)width, (long)height})) {
    renderTexture->Release();
    return nullptr;
  }

  renderTexture->SetColor(clearColor);

  SetGraphicsMode(renderTexture->GetDC(), GM_ADVANCED);

  return renderTexture;
}

IRenderTexture* __stdcall Win32GraphicDevice::GetBackBuffer() {
  return backBuffer_;
}

Vector __stdcall Win32GraphicDevice::GetBackbufferScale() {
  if (nullptr == backBuffer_) {
    return Vector();
  }
  return backBuffer_->GetScale();
}

void Win32GraphicDevice::BeginRender() {
  if (nullptr == backBuffer_) {
    return;
  }
  backBuffer_->SetColor(clearColor_);
}

void __stdcall Win32GraphicDevice::RenderImgStart(const Transform& transform, float angle, IRenderTexture* rendertexture /*= nullptr*/) {
  float radian = angle * (3.141592f / 180.0f);
  float cosAngle = cosf(radian);
  float sinAngle = sinf(radian);

  Vector pivot;
  float dx = pivot.X * cosAngle - pivot.Y * sinAngle + transform.GetPosition().X;
  float dy = pivot.X * sinAngle + pivot.Y * cosAngle + transform.GetPosition().Y;

  XFORM xTransform = {};
  xTransform.eM11 = cosAngle;
  xTransform.eM12 = -sinAngle;
  xTransform.eM21 = sinAngle;
  xTransform.eM22 = cosAngle;

  xTransform.eDx = dx;
  xTransform.eDy = dy;

  if (nullptr == rendertexture) {
    SetWorldTransform(backBuffer_->GetDC(), &xTransform);
  } else {
    SetWorldTransform((HDC)rendertexture->GetHandle(), &xTransform);
  }
}

void __stdcall Win32GraphicDevice::RenderImgAlpha(IImage* img, unsigned int index, const Vector& scale, float alpha) {
  if (nullptr == img) {
    return;
  }

  backBuffer_->AlphaBlend((Win32Image*)img, index, scale, alpha);

  /*backBuffer_->DrawPoint(renderTransform, Color8Bit::GreenAlpha, 10.0f);

  backBuffer_->DrawRectagle(renderTransform, Color8Bit::RedAlpha, 2.0f);

  ModifyWorldTransform(backBuffer_->GetDC(), nullptr, MWT_IDENTITY);*/
}

void __stdcall Win32GraphicDevice::RenderImgTransparent(IImage* img, unsigned int index, const Vector& scale, const Color8Bit& color) {
  if (nullptr == img) {
    return;
  }

  backBuffer_->Transparent((Win32Image*)img, index, scale, color);

  // backBuffer_->DrawPoint(renderTransform, Color8Bit::GreenAlpha, 10.0f);

  // backBuffer_->DrawRectagle(renderTransform, Color8Bit::RedAlpha, 2.0f);

  // ModifyWorldTransform(backBuffer_->GetDC(), nullptr, MWT_IDENTITY);
}

void __stdcall Win32GraphicDevice::DrawRectagle(const Vector& scale, const Color8Bit& color, float Linethickness) {
  backBuffer_->DrawRectagle(scale, color, Linethickness);
}

void __stdcall Win32GraphicDevice::DrawCircle(const Vector& scale, const Color8Bit& color, float Linethickness) {
  backBuffer_->DrawCircle(scale, color, Linethickness);
}

void __stdcall Win32GraphicDevice::DrawPoint(const Color8Bit& color, float Linethickness) {
  backBuffer_->DrawPoint(color, Linethickness);
}

void __stdcall Win32GraphicDevice::DrawLine(const Color8Bit& color, const Vector& start, const Vector& end, float Linethickness) {
  backBuffer_->DrawLine(color, start, end, Linethickness);
}

void __stdcall Win32GraphicDevice::RenderImgEnd(IRenderTexture* rendertexture /*= nullptr*/) {
  if (nullptr == rendertexture) {
    ModifyWorldTransform(backBuffer_->GetDC(), nullptr, MWT_IDENTITY);
  } else {
    ModifyWorldTransform((HDC)rendertexture->GetHandle(), nullptr, MWT_IDENTITY);
  }
}

void Win32GraphicDevice::EndRender() {
  Vector mainScale = mainBuffer_->GetScale();
  Transform renderTransform;
  renderTransform.SetPosition(Vector{mainScale.X * 0.5f, mainScale.Y * 0.5f});
  renderTransform.SetScale(mainScale);

  mainBuffer_->Stretch(backBuffer_, renderTransform);
}

bool Win32GraphicDevice::Initialize(const Vector& backBufferScale) {
  Window* mainWindow = GApplication->GetMainWindow();
  if (nullptr == mainWindow) {
    return false;
  }

  mainBuffer_ = new Win32RenderTexture;

  mainBuffer_->SetHDC(mainWindow->GetHwnd());

  backBuffer_ = (Win32RenderTexture*)CreateRenderTexture(backBufferScale.IntergerX(), backBufferScale.IntergerY(), clearColor_);

  backBuffer_->SetBackBuffer();

  return true;
}

void Win32GraphicDevice::RefreshWindowSize() {
  if (nullptr == mainBuffer_) {
    return;
  }

  mainBuffer_->Refresh();
}

IRenderTexture* Win32GraphicDevice::GetMainBuffer() const {
  return mainBuffer_;
}
