#pragma once

class Path {
 public:
  MATH_API Path();

  MATH_API Path(const std::filesystem::path& path);

  MATH_API  ~Path();

  bool MATH_API IsRoot() const;

  bool MATH_API IsFile() const;

  bool MATH_API IsDirectory() const;

  bool MATH_API IsExists() const;

  std::string MATH_API GetPathString() const;

  std::wstring MATH_API GetPathWString() const;

  std::string MATH_API GetFileName() const;

  std::string MATH_API GetExtension() const;

  void MATH_API MoveParent();

  bool MATH_API Move(std::string_view _path);

  std::string MATH_API AppendPath(std::string_view path);

 protected:
  std::filesystem::path currentPath_;
};