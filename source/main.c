#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include "loadingState.h"
#include "menuState.h"

typedef enum {
	APPSTATE_LOADING,
	APPSTATE_MENU,
	APPSTATE_IMAGE
} APPSTATE;

void handleDrawing(APPSTATE currentAppState, u32 kDown, PrintConsole *bottomPrintScreen, PrintConsole *topPrintScreen) {
	consoleSelect(bottomPrintScreen);
	consoleClear();
	printf("\n Use the D-Pad/Circle Pad to nagivate.\n Press A to select, B to go back.\n");
	consoleSelect(topPrintScreen);

	if (currentAppState == APPSTATE_LOADING) {
		loadingStatePrint();
	} else if (currentAppState == APPSTATE_MENU) {
		menuStateHandleInput(kDown);
		menuStatePrint();
	}
}

int main(int argc, char* argv[]) {

	gfxInitDefault();
	gfxSetDoubleBuffering(GFX_TOP, true);
	gfxSetDoubleBuffering(GFX_BOTTOM, true);

	// Set up dual console
	PrintConsole topPrintScreen, bottomPrintScreen;
	consoleInit(GFX_TOP, &topPrintScreen);
	consoleInit(GFX_BOTTOM, &bottomPrintScreen);

	APPSTATE currentAppState = APPSTATE_MENU;

	handleDrawing(currentAppState, 0, &bottomPrintScreen, &topPrintScreen);

	while (aptMainLoop())
	{

		hidScanInput();
		u32 kDown = hidKeysDown();
		//u32 kHeld = hidKeysHeld();
		//u32 kUp = hidKeysUp();

		if (kDown & KEY_START)
			break; // break in order to end program

		// if no keys are pressed
		if (!kDown)
			continue; // Don't do anything this loop

		handleDrawing(currentAppState, kDown, &bottomPrintScreen, &topPrintScreen);

		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	} // end aptMainLoop

	gfxExit();
	return 0;
}
