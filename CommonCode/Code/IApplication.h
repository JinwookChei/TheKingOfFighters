#pragma once

enum ImageType {
  ImageType_None,
  ImageType_Main,
  ImageType_BMP,
  ImageType_PNG,
  ImageType_TGA,
};

struct CalculateTransformByAutoParameter {
  const Color8Bit& emptyColor;
  bool onlyLine = false;
  bool reCalculateHeight = false;
  Vector start = {0.0f, 0.0f};
  Vector end = {0.0f, 0.0f};
};

struct IImage : public IUnknown {
  virtual Vector __stdcall GetScale(unsigned int index = 0xffffffff) = 0;

  virtual unsigned __int64 __stdcall GetImageCount() = 0;

  virtual void* __stdcall GetHandle() = 0;

  virtual Transform __stdcall RenderTransform(unsigned int index = 0xffffffff) = 0;

  virtual bool GetPixel(const Vector& position, Color8Bit* outColor) = 0;

  virtual bool Save(std::string_view filePath, unsigned int index = 0xffffffff) = 0;

  virtual bool IsRenderTexture() = 0;  // IFileImage인지, IRenderImage인지 flag
};

struct IFileImage : public IImage {
  virtual void __stdcall CalculateTransformByAuto(const CalculateTransformByAutoParameter& parameter) = 0;

  virtual void __stdcall CalculateTransformFromBoundingBoxDatas() = 0;

  virtual void __stdcall CalculateTransformFromCSV(const std::string& filePath) = 0;

  virtual void __stdcall CalculateTransform(unsigned int x, unsigned int y) = 0;

  virtual void __stdcall RefreshImage(unsigned int count) = 0;

  virtual void __stdcall SetTransform(const Transform& transform, int index = 0) = 0;

  virtual ImageType __stdcall GetImageType() = 0;

  virtual const Vector __stdcall GetImagePositionOffSet(unsigned int index) const = 0;

  virtual void __stdcall AddImagePositionOffSet(unsigned int index, const Vector& offSet) = 0;

  virtual bool __stdcall GetCollisionBoxInfo(unsigned int index, unsigned int type, CollisionInfo** outInfo) = 0;

  virtual void __stdcall SetCollisionBoxInfo(unsigned int index, unsigned int type, const CollisionInfo& collisionInfo) = 0;

  virtual void __stdcall AddCollisionBoxPositionOffSet(unsigned int index, const Vector& offSet) = 0;

  virtual void __stdcall ExportImageInfoToCSV(const std::string& filepath) const = 0;

  virtual bool __stdcall DetectBoundBoxes(Color8Bit emptyColor, Color8Bit lineColor) = 0;

};

struct IRenderTexture : public IImage {
  virtual bool __stdcall BitBlt(IImage* srcImg, const Transform& transform) = 0;

  virtual bool __stdcall AlphaBlend(IImage* srcImg, unsigned int index, const Vector& scale, float alpha) = 0;

  virtual bool __stdcall Transparent(IImage* srcImg, unsigned int index, const Vector& scale, const Color8Bit& colorTransparent) = 0;

  virtual bool __stdcall Stretch(IImage* srcImg, const Transform& transform) = 0;

  virtual void __stdcall DrawRectagle(const Vector& scale, const Color8Bit& color, float Linethickness = 1.0f) = 0;

  virtual void __stdcall DrawCircle(const Vector& scale, const Color8Bit& color, float Linethickness = 1.0f) = 0;

  virtual void __stdcall DrawPoint(const Color8Bit& color, float Linethickness = 1.0f) = 0;

  virtual void __stdcall DrawLine(const Color8Bit& color, const Vector& start, const Vector& end, float Linethickness = 1.0f) = 0;

  virtual void __stdcall SetColor(const Color8Bit& color) = 0;

  virtual void __stdcall SetAlpha(float alpha, const Transform& transform, bool useIgnoreColor, const Color8Bit& ignoreColor) = 0;

  virtual void __stdcall Text(const wchar_t* font, const wchar_t* text, unsigned __int64 fontSize, const Vector& position, const Color8Bit& color) = 0;
};

struct IGraphicDevice : public IUnknown {
  virtual IFileImage* __stdcall LoadImg(std::string_view path) = 0;

  virtual IRenderTexture* __stdcall CreateRenderTexture(unsigned int width, unsigned int height, const Color8Bit& clearColor = Color8Bit::Black) = 0;

  virtual IRenderTexture* __stdcall GetBackBuffer() = 0;

  virtual Vector __stdcall GetBackbufferScale() = 0;

  virtual void __stdcall BeginRender() = 0;

  virtual void __stdcall RenderImgStart(const Transform& transform, float angle, IRenderTexture* rendertexture = nullptr) = 0;

  virtual void __stdcall RenderImgAlpha(IImage* img, unsigned int index, const Vector& scale, float alpha) = 0;

  virtual void __stdcall RenderImgTransparent(IImage* img, unsigned int index, const Vector& scale, const Color8Bit& color) = 0;

  virtual void __stdcall DrawRectagle(const Vector& scale, const Color8Bit& color, float Linethickness = 1.0f) = 0;

  virtual void __stdcall DrawCircle(const Vector& scale, const Color8Bit& color, float Linethickness = 1.0f) = 0;

  virtual void __stdcall DrawPoint(const Color8Bit& color, float Linethickness = 1.0f) = 0;

  virtual void __stdcall DrawLine(const Color8Bit& color, const Vector& start, const Vector& end, float Linethickness = 1.0f) = 0;

  virtual void __stdcall RenderImgEnd(IRenderTexture* rendertexture = nullptr) = 0;

  virtual void __stdcall EndRender() = 0;
};

struct IApplication : public IUnknown {
  virtual bool __stdcall InitializeWindow() = 0;

  virtual IGraphicDevice* __stdcall InitializeGraphicDevice(const Vector& backBufferSize) = 0;

  virtual void __stdcall WinPumpMessage() = 0;

  virtual bool __stdcall ApplicationQuit() = 0;

  virtual void __stdcall SetShowCursor(bool show) = 0;

  virtual void __stdcall UpdateMousePosition() = 0;

  virtual const Vector& __stdcall GetMousePosition() const = 0;
};