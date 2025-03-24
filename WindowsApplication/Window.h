#pragma once

class Window {
 public:
  Window();

  ~Window();

  HWND GetHwnd() const;

  bool Initialize();

  void Show() const;

 private:
  HWND hWnd_;
};