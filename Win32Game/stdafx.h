#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif  // _DEBUG

#define MATH_API __declspec(dllimport)
#define JO_API __declspec(dllimport)

#include <Windows.h>
#include <string>
#include <filesystem>

#include <Math/Math.h>
#include <Math/Path.h>
#include <Math/LinkedList.h>
#include <Math/HashTable.h>
#include <Math/Transform.h>

#include <Code/IApplication.h>

#include <Win32Engine/EngineCore.h>
#include <Win32Engine/Level.h>
#include <Win32Engine/Actor.h>
#include <Win32Engine/Player.h>
#include <Win32Engine/ImgManager.h>
#include <Win32Engine/InputManager.h>
#include <Win32Engine/ActorComponent.h>
#include <Win32Engine/SceneComponent.h>
#include <Win32Engine/ImageRenderer.h>
#include <Win32Engine/CollisionComponent.h>
#include <Win32Engine/Mouse.h>
#include <Win32Engine/UI.h>
#include <Win32Engine/UIComponent.h>
#include <Win32Engine/TextComponent.h>
#include <Win32Engine/CameraManager.h>
#include <Win32Engine/EffectManager.h>
#include <Win32Engine/SoundManager.h>
#include <Win32Engine/TimeManager.h>

#include "KOFCommon.h"
#include "Types.h"

extern EngineCore* GEngineCore;