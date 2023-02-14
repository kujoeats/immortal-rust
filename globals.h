#pragma once
#include <unordered_map>
HWND game_window;
GLFWwindow* g_window;
bool g_overlay_visible{ true };
bool p_open = true;

class c_globals {
public:
	ImFont* font1;
	ImFont* font2;
	ImFont* font3;
	ImFont* font4;

};


inline c_globals fonts;