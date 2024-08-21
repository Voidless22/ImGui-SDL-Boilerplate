#pragma once
#include "imgui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include <iostream>


	 void InitializeSDL();
	 void InitializeImGui();
	 void HandleEvents();
	 void RefreshFrame();
	 void Render();
	 void ShutdownImGui();
	 void ShutdownSDL();

	extern SDL_Window* window;
	extern SDL_Renderer* renderer;
	extern ImGuiIO io;
	extern bool closed;

	
