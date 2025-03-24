#pragma once

class Window;
class Win32GraphicDevice;
class WindowsApplication final : public IApplication {
 public:
  WindowsApplication(HINSTANCE hInstance, const wchar_t* imagePath);

  ~WindowsApplication();

  HRESULT __stdcall QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject) override;

  ULONG __stdcall AddRef() override;

  ULONG __stdcall Release() override;

  bool __stdcall InitializeWindow() override;

  IGraphicDevice* __stdcall InitializeGraphicDevice(const Vector& backBufferSize) override;

  void __stdcall WinPumpMessage() override;

  bool __stdcall ApplicationQuit() override;

  void __stdcall SetShowCursor(bool show) override;

  void __stdcall UpdateMousePosition() override;

  const Vector& __stdcall GetMousePosition() const override;

  HINSTANCE HandleInstance() const;

  const wchar_t* GetClassNameW() const;

  Win32GraphicDevice* GetGraphicDevice() const;

  Window* GetMainWindow() const;

 private:
  void Initialize(const wchar_t* imagePath) const;

  ULONG refCount_;

  bool applicationQuit_;

  Vector mousePosition_;

  HINSTANCE hInstance_;

  Window* mainWindow_;

  Win32GraphicDevice* graphicDevice_;
};