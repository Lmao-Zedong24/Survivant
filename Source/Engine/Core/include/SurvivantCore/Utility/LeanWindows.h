#pragma once
#define WIN32_LEAN_AND_MEAN	// Disables unnecessary windows features
#define NOMINMAX			// Avoids conflicts with LibMath's min and max
#undef APIENTRY				// Avoids conflicts with some other libs (e.g: GLFW)
#include <windows.h>
