#pragma once

#include "Path.h"

class Directory final
    : public Path {
 public:
  MATH_API Directory();

  MATH_API Directory(const Path& path);

  MATH_API ~Directory();

  MATH_API std::list<Path> AllFile(std::vector<std::string> extensions);
};