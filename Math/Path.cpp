#include "stdafx.h"
#include "Path.h"

Path::Path()
    : currentPath_(std::filesystem::current_path()) {
}

Path::Path(const std::filesystem::path& path)
    : currentPath_(path) {
}

Path::~Path() {
}

bool Path::IsRoot() const {
  return currentPath_.root_path() == currentPath_;
}

bool Path::IsFile() const {
  if (false == IsExists()) {
    return false;
  }
  return !std::filesystem::is_directory(currentPath_);
}

bool Path::IsDirectory() const {
  if (false == IsExists()) {
    return false;
  }
  return std::filesystem::is_directory(currentPath_);
}

bool Path::IsExists() const {
  return std::filesystem::exists(currentPath_);
}

std::string Path::GetPathString() const {
  return currentPath_.string();
}

std::wstring Path::GetPathWString() const {
  return currentPath_.wstring();
}

std::string Path::GetFileName() const {
  std::filesystem::path fileNamePath = currentPath_.filename();
  return fileNamePath.string();
}

std::string Path::GetExtension() const {
  std::filesystem::path fileExtension = currentPath_.extension();
  return fileExtension.string();
}

void Path::MoveParent() {
  currentPath_ = currentPath_.parent_path();
}

bool Path::Move(std::string_view _path) {
  std::filesystem::path nextPath = currentPath_;
  nextPath.append(_path);

  bool check = std::filesystem::exists(nextPath);
  if (false == check) {
    return false;
  }

  currentPath_ = nextPath;

  return true;
}

std::string Path::AppendPath(std::string_view path) {
  return currentPath_.string() + "\\" + std::string(path);
}
