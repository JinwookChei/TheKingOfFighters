#pragma once

class Win32RenderTexture final
    : public IRenderTexture {
  friend class Win32GraphicDevice;

 public:
  Win32RenderTexture();

  ~Win32RenderTexture();

  HRESULT __stdcall QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject) override;

  ULONG __stdcall AddRef() override;

  ULONG __stdcall Release() override;

  Vector __stdcall GetScale(unsigned int index = 0xffffffff) override;

  unsigned __int64 __stdcall GetImageCount() override;

  void* __stdcall GetHandle() override;

  Transform __stdcall RenderTransform(unsigned int index = 0xffffffff) override;

  bool GetPixel(const Vector& position, Color8Bit* outColor) override;

  bool __stdcall BitBlt(IImage* srcImg, const Transform& transform) override;

  bool __stdcall AlphaBlend(IImage* srcImg, unsigned int index, const Vector& scale, float alpha) override;

  bool __stdcall Transparent(IImage* srcImg, unsigned int index, const Vector& scale, const Color8Bit& colorTransparent) override;

  bool __stdcall Stretch(IImage* srcImg, const Transform& transform) override;

  void __stdcall DrawRectagle(const Vector& scale, const Color8Bit& color, float Linethickness = 1.0f) override;

  void __stdcall DrawCircle(const Vector& scale, const Color8Bit& color, float Linethickness = 1.0f) override;

  void __stdcall DrawPoint(const Color8Bit& color, float Linethickness = 1.0f) override;

  void __stdcall DrawLine(const Color8Bit& color, const Vector& start, const Vector& end, float Linethickness = 1.0f) override;

  void __stdcall SetColor(const Color8Bit& color) override;

  void __stdcall SetAlpha(float alpha, const Transform& transform, bool useIgnoreColor, const Color8Bit& ignoreColor) override;

  void __stdcall Text(const wchar_t* font, const wchar_t* text, unsigned __int64 fontSize, const Vector& position, const Color8Bit& color) override;

  bool Initialize(const Win32RenderTexture* mainTexture, const Vector& scale);

  void SetHDC(HWND hWnd);

  HDC GetDC() const;

  void Refresh();

  bool IsMainBuffer() const;

  void SetBackBuffer();

  bool IsBackBuffer() const;

 private:
  ULONG refCount_;

  bool isBackBuffer_;

  HWND hWnd_;

  HDC imageDC_;

  HBITMAP hBitMap_;

  BITMAP bitMapInfo_;
};