#include "appstate.h"

// This is the APPSTATE that the app starts on
static APPSTATE currentAppState = APPSTATE_MENU;

APPSTATE getCurrentAppState() {
    return currentAppState;
}

void setCurrentAppState(APPSTATE state) {
    currentAppState = state;
}
