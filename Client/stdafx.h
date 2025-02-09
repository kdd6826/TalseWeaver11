// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <time.h>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <iostream>
using namespace std; 


#include "d3d9.h"
//#pragma comment(lib, "d3d9.lib")
#include "d3dx9.h"
//#pragma comment(lib, "d3dx9.lib")


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Typedef.h"
#include "Struct.h"
#include "Define.h"

#include "Function.h"
#include "Enum.h"
#include "Graphic_Device.h"
#include "Texture_Manager.h"
#include "GameObject_Manager.h"
#include "Scroll_Manager.h"
#include "Time_Manager.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <io.h>
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")
#include "SoundMgr.h"