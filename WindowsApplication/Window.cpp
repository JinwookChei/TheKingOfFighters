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
  hWnd_ = CreateWindowEx(
      0,                              // Optional window styles.
      GApplication->GetClassNameW(),  // Window class
      L"The King Of Fighters - 2003",                          // Window text
      WS_OVERLAPPEDWINDOW,            // Window style

      // Size and position
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

      NULL,                            // Parent window
      NULL,                            // Menu
      GApplication->HandleInstance(),  // Instance handle
      NULL                             // Additional application data
  );

  if (hWnd_ == NULL) {
    return false;
  }
  return true;
}

void Window::Show() const {
  ShowWindow(hWnd_, SW_SHOW);
}
