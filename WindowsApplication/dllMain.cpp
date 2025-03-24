#include "stdafx.h"
#include "WindowsApplication.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
#ifdef _DEBUG
      _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
      //_CrtSetBreakAlloc(352);
#endif  // _DEBUG
      ULONG_PTR gdiplusToken = 0;
      Gdiplus::GdiplusStartupInput gdiplusStartupInput;
      Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    } break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH: {
#ifdef _DEBUG
      _ASSERT(_CrtCheckMemory());
#endif  // _DEBUG
    } break;
  }
  return TRUE;
}

extern "C" __declspec(dllexport) void CreateWindowsApplication(void** pVoid, HINSTANCE hInstance, const wchar_t* imagePath) {
  IApplication* iNew = new WindowsApplication(hInstance, imagePath);
  *pVoid = iNew;
}