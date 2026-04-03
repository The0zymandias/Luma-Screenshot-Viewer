#pragma once

typedef enum {
    APPSTATE_EMPTY,
    APPSTATE_LOADING,
    APPSTATE_MENU,
    APPSTATE_IMAGE
} APPSTATE;

APPSTATE getCurrentAppState();

void setCurrentAppState(APPSTATE state);
