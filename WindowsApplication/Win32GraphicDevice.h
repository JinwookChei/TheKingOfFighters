#pragma once

class Win32RenderTexture;
class Win32GraphicDevice final
    : public IGraphicDevice {
 public:
  Win32GraphicDevice();

  ~Win32GraphicDevice();

  HRESULT __stdcall QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject) override;

  ULONG __stdcall AddRef() override;

  ULONG __stdcall Release() override;

  IFileImage* __stdcall LoadImg(std::string_view path) override;

  IRenderTexture* __stdcall CreateRenderTexture(unsigned int width, unsigned int height, const Color8Bit& clearColor = Color8Bit::Black) override;

  IRenderTexture* __stdcall GetBackBuffer() override;

  Vector __stdcall GetBackbufferScale() override;

  void __stdcall BeginRender() override;

  void __stdcall RenderImgStart(const Transform& transform, float angle, IRenderTexture* rendertexture = nullptr) override;

  void __stdcall RenderImgAlpha(IImage* img, unsigned int index, const Vector& scale, float alpha) override;

  void __stdcall RenderImgTransparent(IImage* img, unsigned int index, const Vector& scale, const Color8Bit& color) override;

  void __stdcall DrawRectagle(const Vector& scale, const Color8Bit& color, float Linethickness = 1.0f) override;

  void __stdcall DrawCircle(const Vector& scale, const Color8Bit& color, float Linethickness = 1.0f) override;

  void __stdcall DrawPoint(const Color8Bit& color, float Linethickness = 1.0f) override;

  void __stdcall DrawLine(const Color8Bit& color, const Vector& start, const Vector& end, float Linethickness = 1.0f) override;

  void __stdcall RenderImgEnd(IRenderTexture* rendertexture = nullptr) override;

  void __stdcall EndRender() override;

  bool Initialize(const Vector& backBufferScale);

  void RefreshWindowSize();

  IRenderTexture* GetMainBuffer() const;

 private:
  ULONG refCount_;

  Color8Bit clearColor_;

  Win32RenderTexture* mainBuffer_;

  Win32RenderTexture* backBuffer_;
};