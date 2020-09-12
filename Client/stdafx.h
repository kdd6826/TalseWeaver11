// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
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


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
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