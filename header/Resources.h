#pragma once

#include <cmath>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <initializer_list>

#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

constexpr auto PI = 3.1415926;
constexpr auto maxDepth = 10000;

const std::wstring rootPath = L"model/";