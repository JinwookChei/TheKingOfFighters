#pragma once

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif  // _DEBUG

#define JO_API __declspec(dllexport)
#define MATH_API __declspec(dllimport)

#include <Windows.h>
#include <string>
#include <filesystem>
#include <vector>
#include <list>

#include <Math/Math.h>
#include <Math/Path.h>
#include <Math/LinkedList.h>
#include <Math/HashTable.h>
#include <Math/Transform.h>

#include <Code/IApplication.h>

#include "ImgManager.h"
#include "InputManager.h"
#include "CameraManager.h"
#include "EngineCore.h"

extern ImgManager* GImgManager;
extern InputManager* GInputManager;

extern IGraphicDevice* GGraphicDevice;
extern EngineCore* GEngine;
extern CameraManager* GCamera;