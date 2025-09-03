#pragma once

enum class ImageLoadType {
  One,
  Folder
};

struct ImageInfo {
  bool isOwner_;
  LINK_ITEM link_;
  unsigned int index_;
  ImageType imageType_;
  Transform transform_;
  Vector positionOffSet_;
  std::vector<CollisionInfo> collisionBoxInfo_;

  HBITMAP hBitMap_;
  HDC imageDC_;
  BITMAP bitMapInfo_;

  ImageInfo()
      : isOwner_(false),
        link_({nullptr, nullptr, this}),
        index_(-1),
        positionOffSet_{0.0f,0.0f},
        collisionBoxInfo_(5),
        imageType_(ImageType::ImageType_None),
        hBitMap_(nullptr),
        imageDC_(nullptr),
        bitMapInfo_({}) 
  {
  }

  ~ImageInfo() {
    if (true == isOwner_) {
      DeleteObject(hBitMap_);
      DeleteDC(imageDC_);
    }
  }

  Vector GetScale() const {
    return Vector(bitMapInfo_.bmWidth, bitMapInfo_.bmHeight);
  }

  const Vector& GetRenderScale() const {
    return transform_.GetScale();
  }
};

class Win32Image final
    : public IFileImage {
  friend class Win32GraphicDevice;

 public:
  Win32Image();

  ~Win32Image();

  HRESULT __stdcall QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject) override;

  ULONG __stdcall AddRef() override;

  ULONG __stdcall Release() override;

  Vector __stdcall GetScale(unsigned int index = 0xffffffff) override;

  void* __stdcall GetHandle() override;

  unsigned __int64 __stdcall GetImageCount() override;

  Transform __stdcall RenderTransform(unsigned int index = 0xffffffff) override;

  bool GetPixel(const Vector& position, Color8Bit* outColor) override;

  bool SetPixel(const Vector& position, const Color8Bit& color) override;

  bool Save(std::string_view filePath, unsigned int index = 0xffffffff) override;

  bool IsRenderTexture() override;

  void __stdcall CalculateTransform(unsigned int x, unsigned int y) override;

  void __stdcall CalculateTransformByAuto(const CalculateTransformByAutoParameter& parameter) override;

  void __stdcall CalculateTransformFromDrawBoxImage(Color8Bit emptyColor, Color8Bit lineColor) override;

  void __stdcall CalculateTransformFromDrawBoxImage_Flip(Color8Bit emptyColor, Color8Bit lineColor) override;

  void __stdcall ApplyImageInfoFromCSV(const std::string& filePath) override;

  void __stdcall ApplyImageInfoFromCSV_Flip(const std::string& filePath) override;

  void __stdcall ApplyImageInfoFromCSV_Flip_Async(const std::string& filePath) override;

  void ImportImageInfoFromCSV(const std::string& filePath, std::vector<ImageInfo>* outCSVInfo, bool isFlip = false);

  void __stdcall RefreshImage(unsigned int count) override;

  void __stdcall SetTransform(const Transform& transform, int index = 0) override;

  ImageType __stdcall GetImageType() override;

  const Vector __stdcall GetImagePositionOffSet(unsigned int index) const override;

  void __stdcall AddImagePositionOffSet(unsigned int index, const Vector& offSet) override;

  bool __stdcall GetCollisionBoxInfo(unsigned int index, unsigned int type, CollisionInfo** outInfo) override;

  void __stdcall SetCollisionBoxInfo(unsigned int index, unsigned int type, const CollisionInfo& collisionInfo) override;

  void __stdcall AddCollisionBoxPositionOffSet(unsigned int index, const Vector& offSet) override;

  void __stdcall ExportImageInfoToCSV(const std::string& filepath) const override;

  void __stdcall MakeColorTransparent(const Color8Bit& transColor) override;

  void __stdcall ScalePixelRGB(float rScale, float gScale, float bScale, const Color8Bit& transColor) override;

  void __stdcall ChangePixelRGB(const Color8Bit& srcColor, const Color8Bit& destColor) override;

  std::vector<Color8Bit> __stdcall CountPixelPallet() override;

  void SetPath(std::string_view path);

  bool __stdcall Load();

  HDC GetDC() const;

  void Cleanup();

  ImageInfo* GetImageInfo(unsigned __int64 index);

  const ImageInfo* GetImageInfo(unsigned __int64 index) const;

 private:
  bool LoadFile();

  bool LoadFolder();

  bool LoadBMP(IRenderTexture* mainBuffer);

  bool LoadPNG(IRenderTexture* mainBuffer);

  bool LoadTGA(IRenderTexture* mainBuffer);

  void ConvertToGrayscale(BYTE* pPixels, int width, int height, int bytesPerPixel);

  ULONG refCount_;

  ImageLoadType imageLoadType_;

  Path currentPath_;

  unsigned __int64 imageCount_;
  LINK_ITEM* imageHead_;
  LINK_ITEM* imageTail_;

 private:
  bool SearchPartitionLineRow(const Vector& startPoint, Vector* outLeftTopPoint, Color8Bit lineColor);

  void SearchPartitionGrid(const Vector& leftTopPoint, Vector* outNextSearchStartPoint, std::vector<Vector>* pGridCorner, Color8Bit emptyColor, Color8Bit lineColor);

  void DetectBoundBox(const Vector& leftTopPoint, const Vector& rightBottomPoint, std::vector<std::vector<float>>* pBoundingBoxDatas, Color8Bit emptyColor, Color8Bit lineColor);
};