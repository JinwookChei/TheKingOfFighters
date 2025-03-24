#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif  // _DEBUG

#define MATH_API __declspec(dllimport)

#include <Windows.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

#if defined(new) && defined(_DEBUG)
#pragma push_macro("new")
#undef new
#include <gdiplus.h>
#pragma pop_macro("new")
#else
#include <gdiplus.h>
#endif

#include <Math/Math.h>
#include <Math/Path.h>
#include <Math/Transform.h>
#include <Math/LinkedList.h>
#include <Math/Directory.h>

#include <Code/IApplication.h>

#include "Structure.h"

extern class WindowsApplication* GApplication;