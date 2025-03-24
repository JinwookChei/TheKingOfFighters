#pragma once

class ImgManager final {
 public:
  JO_API ImgManager();

  JO_API  ~ImgManager();

  JO_API static ImgManager* GetIntance();

  JO_API bool Initialize();

  JO_API IFileImage* LoadImg(std::string_view path, unsigned long long key);

  JO_API IFileImage* GetImg(unsigned long long key);

 private:
  HashTable imgTable_;
};

