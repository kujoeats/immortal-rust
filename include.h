#pragma once
#include <iostream>
#include "GL/glew.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "offsets.h"
#include <tchar.h>
#include <intrin.h>

#include <algorithm>
#include <memory>
#include <string_view>
#include <cstdint>
#include <ctime>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <Lmcons.h>
#include <string_view>
#include <fstream>
#include <sstream>
#include "menu.h"
#include "globals.h"
#include <iomanip>
#include "cache.h"
#include "config.h"

using namespace std;



std::vector<uintptr_t> skinned_pointers;
bool hasEoka;
int ccounter;
bool view_offsetting;
Vector3 View_Offset;
bool view_offset_c = false;
bool localPlayerAlive;
uintptr_t GameMode;
uintptr_t objectList;
std::vector<uint64_t> client_entities = { m_entity_list, 0xB8, 0x10, 0x10, 0x28 };
std::vector<uint64_t> entity_chain = { 0x30, 0x8, 0x38 , 0x90 };
bool wasFakeLagOn;
bool wasThickBulletOn;


typedef struct
{
	UINT uiKey;
	string szKey;
}VIRTUALKEY;

VIRTUALKEY VirtualKeyTable[] =
{
	{ VK_XBUTTON1, string(_("mouse4")) },
	{ VK_XBUTTON2, string(_("mouse5")) },
	{ VK_RBUTTON, string(_("right mouse")) },
	{ VK_CANCEL, string(_("cancel")) },
	{ VK_MBUTTON, string(_("middle-mouse")) },
	{ VK_BACK, string(_("backspace")) },
	{ VK_TAB, string(_("tab")) },
	{ VK_CLEAR, string(_("clear")) },
	{ VK_RETURN, string(_("enter")) },
	{ VK_SHIFT, string(_("shift")) },
	{ VK_CONTROL, string(_("control")) },
	{ VK_MENU, string(_("alt")) },
	{ VK_PAUSE, string(_("pause")) },
	{ VK_CAPITAL, string(_("caps lock")) },
	{ VK_ESCAPE, string(_("escape")) },
	{ VK_SPACE, string(_("spacebar")) },
	{ VK_PRIOR, string(_("page up")) },
	{ VK_NEXT, string(_("page down")) },
	{ VK_END, string(_("end")) },
	{ VK_HOME, string(_("home")) },
	{ VK_LEFT, string(_("left arrow")) },
	{ VK_UP, string(_("up Arrow")) },
	{ VK_RIGHT, string(_("right arrow")) },
	{ VK_DOWN, string(_("down arrow")) },
	{ VK_SELECT, string(_("select")) },
	{ VK_PRINT, string(_("print")) },
	{ VK_EXECUTE, string(_("execute")) },
	{ VK_SNAPSHOT, string(_("printscreen")) },
	{ VK_INSERT, string(_("insert")) },
	{ VK_DELETE, string(_("delete")) },
	{ VK_HELP, string(_("help")) },
	{ 0x30, string(_("0")) },
	{ 0x31, string(_("1")) },
	{ 0x32, string(_("2")) },
	{ 0x33, string(_("3")) },
	{ 0x34, string(_("4")) },
	{ 0x35, string(_("5")) },
	{ 0x36, string(_("6")) },
	{ 0x37, string(_("7")) },
	{ 0x38, string(_("8")) },
	{ 0x39, string(_("9")) },
	{ 0x41, string(_("A")) },
	{ 0x42, string(_("B")) },
	{ 0x43, string(_("C")) },
	{ 0x44, string(_("D")) },
	{ 0x45, string(_("E")) },
	{ 0x46, string(_("F")) },
	{ 0x47, string(_("G")) },
	{ 0x48, string(_("H")) },
	{ 0x49, string(_("I")) },
	{ 0x4A, string(_("J")) },
	{ 0x4B, string(_("K")) },
	{ 0x4C, string(_("L")) },
	{ 0x4D, string(_("M")) },
	{ 0x4E, string(_("N")) },
	{ 0x4F, string(_("O")) },
	{ 0x50, string(_("P")) },
	{ 0x51, string(_("Q")) },
	{ 0x52, string(_("R")) },
	{ 0x53, string(_("S")) },
	{ 0x54, string(_("T")) },
	{ 0x55, string(_("U")) },
	{ 0x56, string(_("V")) },
	{ 0x57, string(_("W")) },
	{ 0x58, string(_("X")) },
	{ 0x59, string(_("Y")) },
	{ 0x5A, string(_("Z")) },
	{ VK_NUMPAD0, string(_("numpad 0")) },
	{ VK_NUMPAD1, string(_("numpad 1")) },
	{ VK_NUMPAD2, string(_("numpad 2")) },
	{ VK_NUMPAD3, string(_("numpad 3")) },
	{ VK_NUMPAD4, string(_("numpad 4")) },
	{ VK_NUMPAD5, string(_("numpad 5")) },
	{ VK_NUMPAD6, string(_("numpad 6")) },
	{ VK_NUMPAD7, string(_("numpad 7")) },
	{ VK_NUMPAD8, string(_("numpad 8")) },
	{ VK_NUMPAD9, string(_("numpad 9")) },
	{ VK_SEPARATOR, string(_("numpad Seperator")) },
	{ VK_SUBTRACT, string(_("numpad Subtract")) },
	{ VK_DECIMAL, string(_("numpad Decimal")) },
	{ VK_DIVIDE, string(_("numpad Devide")) },
	{ VK_F1, string(_("f1")) },
	{ VK_F2, string(_("f2")) },
	{ VK_F3, string(_("f3")) },
	{ VK_F4, string(_("f4")) },
	{ VK_F5, string(_("f5")) },
	{ VK_F6, string(_("f6")) },
	{ VK_F7, string(_("f7")) },
	{ VK_F8, string(_("f8")) },
	{ VK_F9, string(_("f9")) },
	{ VK_F10, string(_("f10")) },
	{ VK_F11, string(_("f11")) },
	{ VK_F12, string(_("f12")) },
	{ VK_NUMLOCK, string(_("numlock")) },
	{ VK_SCROLL, string(_("scroll")) },
	{ VK_LSHIFT, string(_("left-shift")) },
	{ VK_RSHIFT, string(_("right-shift")) },
	{ VK_LCONTROL, string(_("left-control")) },
	{ VK_RCONTROL, string(_("right-control")) },
	{ VK_LMENU, string(_("left-alt")) },
	{ VK_RMENU, string(_("right-alt")) },
	{ VK_PLAY, string(_("vk-play")) },
	{ VK_ZOOM, string(_("vk-zoom")) },
};


VIRTUALKEY get_async_key_state() {
	bool found{};
	VIRTUALKEY choice;
	while (!found) {
		Sleep(1);
		for (int i = 0; i < 102; i++) {
			if (GetAsyncKeyState(VirtualKeyTable[i].uiKey)) {
				choice = VirtualKeyTable[i];
				found = true;

			}
		}
	}
	return choice;
}





inline void hkp() {//handle_key_press
	CloseHandle(GetCurrentThread());
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (GetAsyncKeyState(VK_INSERT)) { // just so we dont call this shit a million times
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			g_width = glfwGetVideoMode(monitor)->width;
			g_height = glfwGetVideoMode(monitor)->height;//incase of a resolution change
			g_overlay_visible = !g_overlay_visible;
			glfwSetWindowAttrib(g_window, GLFW_MOUSE_PASSTHROUGH, !g_overlay_visible);
			if (g_overlay_visible) {
				HWND overlay_window = glfwGetWin32Window(g_window);
				SetForegroundWindow(overlay_window);
			}
			else { SetForegroundWindow(game_window); }
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		while (!g_overlay_visible && settings->features.shoot_anywhere && GetAsyncKeyState(VK_SPACE) && cache::local_player) {
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
			if (!cache::modelstate->hasFlag(Flags::OnGround)) {
				cache::modelstate->setFlag(Flags::OnGround);
			}
			else {
				std::this_thread::yield();
			}
			if (cache::movement->get_grounded() != 1.0f) {
				cache::movement->set_grounded(1.f);
			}
			else {
				std::this_thread::yield();
			}
		}
	
	
	}
}
bool show_overlay = true;
void setupWindow() {

	glfwSetErrorCallback(NULL);
	Sleep(20);//race condition fix
	if (!glfwInit())return;
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	Sleep(20);//race condition fix
	if (!monitor)return;
	g_width = glfwGetVideoMode(monitor)->width,
		g_height = glfwGetVideoMode(monitor)->height;
	glfwWindowHint(GLFW_FLOATING, true);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_MAXIMIZED, true);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
	g_window = glfwCreateWindow(g_width, g_height, "Word", NULL, NULL);//window name
	Sleep(20);//race condition fix
	if (g_window == NULL)return;
	glfwSetWindowAttrib(g_window, GLFW_DECORATED, false);
	glfwSetWindowAttrib(g_window, GLFW_MOUSE_PASSTHROUGH, true);
	glfwSetWindowMonitor(g_window, NULL, 0, 0, g_width, g_height + 1, 0);//required
	glfwMakeContextCurrent(g_window);
	Sleep(20);//race condition fix
	if (glewInit() != GLEW_OK)return;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(g_window, true);
	ImGui_ImplOpenGL3_Init(e("#version 130").decrypt());
	io.Fonts->AddFontFromMemoryTTF(&mysi, sizeof mysi, 15.f);
	fonts.font1 = io.Fonts->AddFontFromMemoryTTF(&mysi, sizeof mysi, 12.f);
	fonts.font3 = io.Fonts->AddFontFromMemoryTTF(&arial, sizeof arial, 11.f);
	fonts.font2 = io.Fonts->AddFontFromMemoryTTF(&arial, sizeof arial, 9.f);
	fonts.font4 = io.Fonts->AddFontFromMemoryTTF(&arial, sizeof arial, 8.f);
	ktheme();
}

inline void set_cursor(float x, float y) {
	ImGui::SetCursorPosX(x);
	ImGui::SetCursorPosY(y);
}

