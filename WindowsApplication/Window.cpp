#include "stdafx.h"
#include "Window.h"
#include "WindowsApplication.h"

Window::Window()
    : hWnd_(NULL) {
}

Window::~Window() {
}

HWND Window::GetHwnd() const {
  return hWnd_;
}

bool Window::Initialize() {
  RECT rect = {0, 0, 1280, 720};
  AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

  hWnd_ = CreateWindowEx(
      0,                              
      GApplication->GetClassNameW(),  
      L"The King Of Fighters 2003",
      WS_OVERLAPPEDWINDOW,          
      CW_USEDEFAULT, CW_USEDEFAULT, /*CW_USEDEFAULT, CW_USEDEFAULT,*/
      rect.right - rect.left,       // 윈도우 전체 크기
      rect.bottom - rect.top,
      NULL,                            
      NULL,                            
      GApplication->HandleInstance(),  
      NULL                             
  );

  if (hWnd_ == NULL) {
    return false;
  }


  return true;
}

void Window::Show() const {
  ShowWindow(hWnd_, SW_SHOW);
}
