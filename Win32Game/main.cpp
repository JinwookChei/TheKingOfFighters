#include "stdafx.h"

#include "ToolLevel.h"
#include "TestLevel.h"
#include "KOFLevel.h"

typedef void (*DLL_INSTANCE_PRINT)(void**, HINSTANCE, const wchar_t*);

EngineCore* GEngineCore = nullptr;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
#ifdef _DEBUG
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  //_CrtSetBreakAlloc(352);
#endif  // _DEBUG

  // const wchar_t* dynamicLibAName = L"..\\Dll\\WindowsApplication_x64_Debug.dll";

  Path dllPath(pCmdLine);
  if (false == dllPath.IsExists()) {
    __debugbreak();
  }
  if (false == dllPath.IsFile()) {
    __debugbreak();
  }
  Path iconPath(L"..\\ContentsResource\\app_icon.ico");
  if (false == iconPath.IsExists()) {
    __debugbreak();
  }
  if (false == iconPath.IsFile()) {
    __debugbreak();
  }

  HMODULE dynamicLibAModule = LoadLibrary(pCmdLine);
  if (!dynamicLibAModule) {
    __debugbreak();
  }

  DLL_INSTANCE_PRINT loadFunction = (DLL_INSTANCE_PRINT)GetProcAddress(dynamicLibAModule, "CreateWindowsApplication");
  if (!loadFunction) {
    __debugbreak();
  }

  IApplication* application = nullptr;
  loadFunction((void**)&application, hInstance, iconPath.GetPathWString().c_str());
  if (nullptr == application) {
    __debugbreak();
  }

  GEngineCore = new EngineCore();
  if (false == GEngineCore->Initialize(application)) {
    __debugbreak();
    return -1;
  }
  application->Release();
  application = nullptr;

  GEngineCore->ChangeLevel<KOFLevel>();

  GEngineCore->EngineLoop();

  delete GEngineCore;
  GEngineCore = nullptr;

  FreeLibrary(dynamicLibAModule);
  dynamicLibAModule = nullptr;

#ifdef _DEBUG
  _ASSERT(_CrtCheckMemory());
#endif  // _DEBUG
  return 0;
}