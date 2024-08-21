#include "gui.h"



int main(int, char**) {
	InitializeSDL();
	InitializeImGui();
	
	while (!closed) {

		HandleEvents();
		RefreshFrame();

		Render();
	}
	ShutdownImGui();
	ShutdownSDL();
	return 0;
}