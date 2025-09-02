#pragma once

class ImgManager final {
 public:
  ENGINE_API ImgManager();

  ENGINE_API  ~ImgManager();

  ENGINE_API static ImgManager* GetIntance();

  ENGINE_API bool Initialize();

  ENGINE_API IFileImage* LoadImg(std::string_view path, unsigned long long key);

  ENGINE_API IFileImage* GetImg(unsigned long long key);

  //JO_API IFileImage* GetCopyImg(unsigned long long key);

 private:
  HashTable imgTable_;
};

