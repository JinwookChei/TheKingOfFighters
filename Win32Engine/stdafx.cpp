#include "stdafx.h"

#ifdef _DEBUG
#pragma comment(lib, "Math_x64_Debug")
#pragma comment(lib, "fmodL")
#else
#pragma comment(lib, "Math_x64_Release")
#pragma comment(lib, "fmod")
#endif  // _DEBUG