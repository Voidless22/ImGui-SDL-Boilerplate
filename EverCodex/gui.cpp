
#include "gui.h"


SDL_Window* window;
SDL_Renderer* renderer;
ImGuiIO io;
bool closed = false;
ImVec4 wndBGCol = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


void InitializeSDL() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
		printf("Error: %s\n", SDL_GetError());
		throw std::runtime_error("Failed to initialize SDL");
	}
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
		std::cout << "Error SDL2_image Initialization";
		throw std::runtime_error("Failed to initialize SDL");
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(!(SDL_WINDOW_RESIZABLE) | SDL_WINDOW_ALLOW_HIGHDPI);
	window = SDL_CreateWindow("Boilerplate", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
	if (window == nullptr) {
		printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
		throw std::runtime_error("Failed to create SDL window");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		SDL_Log("Error creating SDL_Renderer!");
		throw std::runtime_error("Failed to create SDL renderer");
	}
}
void InitializeImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	io.Fonts->AddFontDefault();


	IM_ASSERT(titleFont != nullptr);


}
void HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))) {
			closed = true;
		}
	}
}
void RefreshFrame()
{
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	SDL_SetRenderDrawColor(renderer, (Uint8)(wndBGCol.x * 255), (Uint8)(wndBGCol.y * 255), (Uint8)(wndBGCol.z * 255), (Uint8)(wndBGCol.w * 255));
	SDL_RenderClear(renderer);
}
void Render()
{
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
	SDL_RenderPresent(renderer);
}

void ShutdownImGui() {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}
void ShutdownSDL() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

