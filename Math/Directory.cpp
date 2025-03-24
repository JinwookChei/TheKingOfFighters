#include "stdafx.h"
#include "LinkedList.h"
#include "Directory.h"

Directory::Directory() {
}

Directory::Directory(const Path& path)
    : Path(path) {
}

Directory::~Directory() {
}

std::list<Path> Directory::AllFile(std::vector<std::string> extensions) {
  std::list<Path> results;

  if (false == IsDirectory()) {
    return results;
  }

  // ".bmp", ".BMP"
  for (std::string& s : extensions) {
    for (char& ch : s) {
      ch = (char)std::toupper(ch);
    }
  }

  std::filesystem::directory_iterator iter = std::filesystem::directory_iterator(currentPath_);
  for (const std::filesystem::directory_entry& entry : iter) {
    std::filesystem::path path = entry.path();
    if (entry.is_directory()) {
      continue;
    }

    std::filesystem::path ext = entry.path().extension();
    std::string extString = ext.string();
    for (char& ch : extString) {
      ch = (char)std::toupper(ch);
    }

    for (const std::string& tmpEx : extensions) {
      if (extString != tmpEx) {
        continue;
      }
      results.push_back(Path(path));
    }
  }

  return results;
}
