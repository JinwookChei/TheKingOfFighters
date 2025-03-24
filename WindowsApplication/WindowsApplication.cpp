#include "stdafx.h"
#include "WindowsApplication.h"
#include "Window.h"
#include "Win32GraphicDevice.h"
#include "Win32Image.h"

WindowsApplication* GApplication = nullptr;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_SIZE: {
      /*WORD width = LOWORD(lParam);
      WORD height = HIWORD(lParam);*/
      if (nullptr != GApplication && nullptr != GApplication->GetGraphicDevice()) {
        GApplication->GetGraphicDevice()->RefreshWindowSize();
      }
    } break;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

WindowsApplication::WindowsApplication(HINSTANCE hInstance, const wchar_t* imagePath)
    : hInstance_(hInstance),
      mainWindow_(nullptr),
      applicationQuit_(false),
      refCount_(1),
      graphicDevice_(nullptr) {
  GApplication = this;
  Initialize(imagePath);
}

WindowsApplication::~WindowsApplication() {
  if (nullptr != graphicDevice_) {
    delete graphicDevice_;
  }
  if (nullptr != mainWindow_) {
    delete mainWindow_;
  }
}

HRESULT __stdcall WindowsApplication::QueryInterface(REFIID riid, void** ppvObject) {
  return E_NOTIMPL;
}

ULONG __stdcall WindowsApplication::AddRef() {
  ++refCount_;
  return refCount_;
}

ULONG __stdcall WindowsApplication::Release() {
  --refCount_;
  ULONG tmpRefCount = refCount_;
  if (0 == refCount_) {
    delete this;
  }

  return tmpRefCount;
}

bool __stdcall WindowsApplication::InitializeWindow() {
  mainWindow_ = new Window;

  if (false == mainWindow_->Initialize()) {
    delete mainWindow_;
    return false;
  }

  mainWindow_->Show();

  return true;
}

IGraphicDevice* __stdcall WindowsApplication::InitializeGraphicDevice(const Vector& backBufferSize) {
  if (nullptr != graphicDevice_) {
    return graphicDevice_;
  }

  graphicDevice_ = new Win32GraphicDevice;

  if (false == graphicDevice_->Initialize(backBufferSize)) {
    return nullptr;
  }

  return graphicDevice_;
}

void __stdcall WindowsApplication::WinPumpMessage() {
  MSG message = {};
  while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&message);
    DispatchMessage(&message);

    if (message.message == WM_DESTROY) {
      if (applicationQuit_) {
        break;
      }
    }
    if (message.message == WM_QUIT) {
      applicationQuit_ = true;
    }
  }
}

bool __stdcall WindowsApplication::ApplicationQuit() {
  return applicationQuit_;
}

void __stdcall WindowsApplication::SetShowCursor(bool show) {
  if (show) {
    ShowCursor(TRUE);
  } else {
    ShowCursor(FALSE);
  }
}

void __stdcall WindowsApplication::UpdateMousePosition() {
  if (nullptr == graphicDevice_) {
    return;
  }

  {
    POINT mousePoint;
    GetCursorPos(&mousePoint);
    ScreenToClient(mainWindow_->GetHwnd(), &mousePoint);

    mousePosition_.X = (float)mousePoint.x;
    mousePosition_.Y = (float)mousePoint.y;
    mousePosition_.Z = 0.0f;
    mousePosition_.W = 1.0f;
  }

  Vector mainBufferScale = graphicDevice_->GetMainBuffer()->GetScale();
  Vector backBufferScale = graphicDevice_->GetBackbufferScale();

  float fX = mousePosition_.X / mainBufferScale.X;
  float fY = mousePosition_.Y / mainBufferScale.Y;

  mousePosition_.X = fX * backBufferScale.X;
  mousePosition_.Y = fY * backBufferScale.Y;
}

const Vector& __stdcall WindowsApplication::GetMousePosition() const {
  return mousePosition_;
}

HINSTANCE WindowsApplication::HandleInstance() const {
  return hInstance_;
}

const wchar_t* WindowsApplication::GetClassNameW() const {
  return L"Sample Window Class";
}

Win32GraphicDevice* WindowsApplication::GetGraphicDevice() const {
  return graphicDevice_;
}

Window* WindowsApplication::GetMainWindow() const {
  return mainWindow_;
}

void WindowsApplication::Initialize(const wchar_t* imagePath) const {
  WNDCLASS wc = {};

  HICON hIcon = (HICON)LoadImage(NULL,
                                 imagePath,
                                 IMAGE_ICON,
                                 0,
                                 0,
                                 LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);

#ifdef _DEBUG
  if (NULL == hIcon) {
    __debugbreak();
  }
#endif  // _DEBUG

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance_;
  wc.lpszClassName = GetClassNameW();
  wc.hIcon = hIcon;

  RegisterClass(&wc);
}
