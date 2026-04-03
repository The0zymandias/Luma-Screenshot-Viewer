#include <stdio.h>
#include <3ds/types.h>
#include <3ds/console.h>
#include <3ds/services/hid.h>

#include "states/menu.h"
#include "screenshots.h"

static unsigned int curItemIndex = 0;
static unsigned int curPageIndex = 0;
static unsigned int maxPageIndex = 0;

static const int itemsPerPage = 11;

static const char leftBorderChar = '|';
static const char rightBorderChar = '|';

void moveCursor(u32 row, u32 col) {
    printf("\033[%ld;%ldH", row, col);
}

void printTopBar() {
    moveCursor(1, 1);
    printf("%c%-46s %c\n", leftBorderChar, "- - - - - - - - - - - - - - - - - - - - - - - -", rightBorderChar);
}

void printBottomBar() {
    moveCursor(30, 1);
    printf("%c %-46s%c", leftBorderChar, "- - - - - - - - - - - - - - - - - - - - - - - -", rightBorderChar);
}

void printBorders() {
    moveCursor(2, 1);
    for (int i = 2; i < 30; i++) {
        printf("%c  %-44s  %c\n", leftBorderChar, "", rightBorderChar);
    }
}

void printHeader() {
    moveCursor(3, 3);
    printf("%s%-34s%s", CONSOLE_CYAN, "Luma Screenshot Viewer", CONSOLE_RESET);
    printf("Page %3d/%3d", curPageIndex + 1, maxPageIndex + 1);
}

void printScreenshotName(const char *name, u32 row, bool isCurItem) {
    moveCursor(row, 3);
    char *lineColor = (isCurItem) ? CONSOLE_GREEN : CONSOLE_RESET;
    printf("%s%-46.46s%s ", lineColor, name, CONSOLE_RESET);
}

void beginMenuState() {
    consoleClear();


    printTopBar();
    printBorders();
    printHeader();
    printBottomBar();
    printHeader();

    u32 startingPageIndex = curPageIndex * itemsPerPage;
    for (int i = 0; i < itemsPerPage && (startingPageIndex + i) < numScreenshots; i++) {
        u32 currentConsoleColumn = 6 + i * 2;
        printScreenshotName(screenshotNames[startingPageIndex + i], currentConsoleColumn + 1, i == curItemIndex);

        /*
        if (i == curItemIndex) {
            printf("|  %s%-44.44s%s  |\n", CONSOLE_GREEN, "ITEMadaipdfuvboaidfvboaidbvoiadfvbadioufxbsfgnsfgfnsfvbaiodfvbidf", CONSOLE_RESET);
        } else {
            printf("|  %-44.44s  |\n", "ITEMfgsyhsrtaerihghuiaegbpiebgpieurgbpaeirugbaipdufvbasfgnsfghsfghsgdu");
        }
        */
    }
}

void updateMenuState(u32 kDown) {
    if (kDown & KEY_DOWN) {
        curItemIndex = (curItemIndex + 1) % itemsPerPage;
    } else if (kDown & KEY_UP) {
        curItemIndex -= 1;
        if (curItemIndex > itemsPerPage-1) {
            curItemIndex = itemsPerPage-1;
        }
    } else if (kDown & KEY_LEFT) {
        curItemIndex = 0;
        curPageIndex -= 1;
        if (curPageIndex > maxPageIndex) {
            curPageIndex = maxPageIndex;
        }
    } else if (kDown & KEY_RIGHT) {
        curItemIndex = 0;
        curPageIndex = (curPageIndex + 1) % (maxPageIndex + 1);
    }
}

void menuStatePrint(PrintConsole *top, PrintConsole *bottom) {
    consoleClear();
    printf("|%-46s |\n", "- - - - - - - - - - - - - - - - - - - - - - - -"); // top line
    printf("| %-46s |\n", ""); // blank line

    // Header/title thing, we are just gonna assume for now
    // that no one has tens of thousands of screenshots
    printf("| %s%-34s%s", CONSOLE_CYAN, "Luma Screenshot Viewer", CONSOLE_RESET);
    printf("Page %3d/%3d |\n", curPageIndex + 1, maxPageIndex + 1);

    printf("| %-46s |\n", ""); // blank line

    for (int i = 0; i < itemsPerPage; i++) {
        printf("| %-46s |\n", "");
        if (i == curItemIndex) {
            printf("| %s%-46.46s%s |\n", CONSOLE_GREEN, "ITEMadaipdfuvboaidfvboaidbvoiadfvbadioufvbaiodfvbidf", CONSOLE_RESET);
        } else {
            printf("| %-45.45s  |\n", " ITEMfgsyhsrtaerihghuiaegbpiebgpieurgbpaeirugbaipdufvbadu");
        }
    }
    printf("| %-46s |\n", "");
    printf("| %-46s |\n", "");
    printf("| %-46s|\n", "- - - - - - - - - - - - - - - - - - - - - - - -"); // bottom line
}


