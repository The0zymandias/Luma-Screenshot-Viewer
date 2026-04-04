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
    printf("%c%-47s%c\n", '\\', "================================================", '/');
}

void printBottomBar() {
    moveCursor(30, 1);
    printf("%c%-47s%c", '/', "================================================", '\\');
}

void printBorders() {
    moveCursor(2, 1);
    for (int i = 2; i < 30; i++) {
        printf("%c  %-44s  %c\n", leftBorderChar, "", rightBorderChar);
    }
}

void printHeader() {
    moveCursor(4, 3);
    printf("%s%-34s%s", CONSOLE_CYAN, "Luma Screenshot Viewer", CONSOLE_RESET);
    printf("Page %3d/%3d", curPageIndex + 1, maxPageIndex + 1);
}

void printScreenshotName(const char *name, u32 row, bool isCurItem) {
    moveCursor(row, 4);
    char *lineColor = (isCurItem) ? CONSOLE_GREEN : CONSOLE_RESET;
    printf("%s%.24s", lineColor, name);

    printf("   3D: ");
    if (row % 3 == 1) {
        printf("Yes");
    } else {
        printf("No ");
    }

    printf("  Wide: ");
    if (row % 3 == 0) {
        printf("Yes");
    } else {
        printf("No ");
    }

    printf("%s", CONSOLE_RESET);
}

void printCurrentPageNames() {
    u32 startingPageIndex = curPageIndex * itemsPerPage;

    int i = 0;
    while (i < itemsPerPage && (startingPageIndex + i) < numScreenshots) {
        u32 currentConsoleColumn = 6 + i * 2;
        printScreenshotName(screenshotNames[startingPageIndex + i], currentConsoleColumn + 1, i == curItemIndex);
        i++;
        /*
         *   if (i == curItemIndex) {
         *       printf("|  %s%-44.44s%s  |\n", CONSOLE_GREEN, "ITEMadaipdfuvboaidfvboaidbvoiadfvbadioufxbsfgnsfgfnsfvbaiodfvbidf", CONSOLE_RESET);
    } else {
        printf("|  %-44.44s  |\n", "ITEMfgsyhsrtaerihghuiaegbpiebgpieurgbpaeirugbaipdufvbasfgnsfghsfghsgdu");
    }
    */
    }

    // this is the funniest while loop of all time
    while (i < itemsPerPage) {
        moveCursor(6 + i * 2 + 1, 4);
        printf("                                             ");
        i++;
    }
}

void beginMenuState() {

    maxPageIndex = numScreenshots / 11;
    if (numScreenshots % 11 == 0 && maxPageIndex > 0)
        maxPageIndex--;

    consoleClear();

    printTopBar();
    printBorders();
    printHeader();
    printBottomBar();

    printCurrentPageNames();
}

void updateMenuState(u32 kDown) {

    u32 itemsOnThisPage = itemsPerPage;
    if (curPageIndex == maxPageIndex) {
        u32 temp = numScreenshots;
        while (temp > 11)
            temp -= 11;
        itemsOnThisPage = temp;
    }

    if (kDown & KEY_DOWN) {
        curItemIndex = (curItemIndex + 1) % itemsOnThisPage;

    } else if (kDown & KEY_UP) {
        // curItemIndex is unsigned so it overflows to big number if less than 0
        // same with curPageIndex I think
        curItemIndex = (curItemIndex - 1 > itemsOnThisPage+1) ? itemsOnThisPage-1 : curItemIndex - 1;

    } else if (kDown & KEY_LEFT) {
        curItemIndex = 0;
        curPageIndex = (curPageIndex - 1 > maxPageIndex) ? curPageIndex = maxPageIndex : curPageIndex - 1;

    } else if (kDown & KEY_RIGHT) {
        curItemIndex = 0;
        curPageIndex = (curPageIndex + 1) % (maxPageIndex + 1);

    } else if (kDown & KEY_L) {
        curItemIndex = 0;
        curPageIndex = (curPageIndex - 5 > maxPageIndex) ? 0 : curPageIndex - 5;

    } else if (kDown & KEY_R) {
        curItemIndex = 0;
        curPageIndex += 5;
        curPageIndex = (curPageIndex > maxPageIndex) ? maxPageIndex : curPageIndex;

    }
}

void printMenuStateTop() {
    printHeader();
    printCurrentPageNames();
}

void printMenuStateBottom() {
    return;
}
/*
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
*/
