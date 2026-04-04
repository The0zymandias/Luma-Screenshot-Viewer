#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include "appstate.h"
#include "screenshots.h"
#include "states/menu.h"

// The startup/initial/current APPSTATE can be found in appstate.c
APPSTATE lastFrameAppState = APPSTATE_EMPTY;

void handlePossibleNewAppState();
void updateCurrentAppState(u32 kDown);
void drawCurrentAppStateTop();
void drawCurrentAppStateBottom();

int main(int argc, char* argv[]) {

    gfxInitDefault();

    // Set up dual console
    PrintConsole topPrintScreen, bottomPrintScreen;
    consoleInit(GFX_TOP, &topPrintScreen);
    consoleInit(GFX_BOTTOM, &bottomPrintScreen);

    loadScreenshotNames();

    consoleSelect(&topPrintScreen);

    while (aptMainLoop()) {

        hidScanInput();
        u32 kDown = hidKeysDown();
        //u32 kHeld = hidKeysHeld();
        //u32 kUp = hidKeysUp();

        if (kDown & KEY_START)
            break; // break in order to end program

        // APPSTATE stuff
        handlePossibleNewAppState();
        updateCurrentAppState(kDown);
        drawCurrentAppStateTop();


        lastFrameAppState = getCurrentAppState();
    } // while (aptMainLoop())

    gfxExit();
}

void handlePossibleNewAppState() {
    if (lastFrameAppState != getCurrentAppState()) {
        switch (getCurrentAppState()) {

            case APPSTATE_EMPTY:
                break;

            case APPSTATE_MENU:
                beginMenuState();
                break;

            default:
                printf("Invalid APPSTATE: %i", getCurrentAppState());
        }

    }
}

void updateCurrentAppState(u32 kDown) {
    switch (getCurrentAppState()) {

        case APPSTATE_EMPTY:
            break;

        case APPSTATE_MENU:
            updateMenuState(kDown);
            break;
    }
}

void drawCurrentAppStateTop() {
    switch (getCurrentAppState()) {

        case APPSTATE_EMPTY:
            break;

        case APPSTATE_MENU:
            printMenuStateTop();
            break;
    }
}

void drawCurrentAppStateBottom() {
    return;
}
