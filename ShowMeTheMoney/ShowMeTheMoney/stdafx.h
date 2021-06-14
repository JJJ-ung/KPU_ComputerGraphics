#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <time.h>

#include "glew.h"
#include "freeglut.h"
#include "freeglut_ext.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;
using namespace glm;

// FMOD (Sound Library)
#include <io.h>
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_errors.h"

// Include
#include "Enum.h"
#include "Function.h"
#include "Struct.h"
#include "Macro.h"

// Define
#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

#define WINCX 1280
#define WINCY 720

#define MIN_STR 64
#define MID_STR 128
#define MAX_STR 256

#define PI 3.141592f;
#define MAX_VKEY 0xff
