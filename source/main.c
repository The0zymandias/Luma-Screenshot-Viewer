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

int main(int argc, char* argv[])
{

	gfxInitDefault();

	// Set up dual console
	PrintConsole topPrintScreen, bottomPrintScreen;
	consoleInit(GFX_TOP, &topPrintScreen);
	consoleInit(GFX_BOTTOM, &bottomPrintScreen);

	APPSTATE currentAppState = APPSTATE_MENU;

	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();

		hidScanInput();
		u32 kDown = hidKeysDown();
		//u32 kHeld = hidKeysHeld();
		//u32 kUp = hidKeysUp();

		if (kDown & KEY_START)
			break; // break in order to end program

		// if no keys are pressed and the app state is not LOADING
		//if (!kDown && currentAppState != APPSTATE_LOADING)
		//	continue; // Don't do anything this loop

		//printf("\x1b[2J\x1b[H");

		consoleSelect(&bottomPrintScreen);
		consoleClear();
		printf("\n Use the D-Pad/Circle Pad to nagivate.");
		consoleSelect(&topPrintScreen);

		if (currentAppState == APPSTATE_LOADING) {
			loadingStatePrint();
		} else if (currentAppState == APPSTATE_MENU) {
			menuStateHandleInput(kDown);
			menuStatePrint();
		}


		gfxFlushBuffers();
	} // end aptMainLoop

	gfxExit();
	return 0;
}
