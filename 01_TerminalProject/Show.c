#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define defaultNStringsLim 128
#define bufSize 1024
#define offset 2
#define keyEsc 27

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "no filename argument\n");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "failed to open file %s\n", argv[1]);
        exit(1);
    }

    size_t nStringsLim = defaultNStringsLim, nStrings = 0;
    char **strings = calloc(sizeof(char *), nStringsLim);

    char stringBuf[bufSize];

    while (fgets(stringBuf, sizeof(stringBuf), f)) {
        size_t stringLen = strlen(stringBuf);

        if (stringLen > 0 && stringBuf[stringLen - 1] == '\n') {
            stringBuf[stringLen - 1] = '\0';
            stringLen--;
        }

        char *string = malloc(stringLen + 1);
        strcpy(string, stringBuf);

        if (nStrings >= nStringsLim) {
            nStringsLim *= 2;

            char **newStrings = realloc(strings, sizeof(char *) * nStringsLim);
            strings = newStrings;
        }

        strings[nStrings] = string;
        nStrings++;
    }

    fclose(f);

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    printw("%s", argv[1]);
    refresh();

    WINDOW *win;
    win = newwin(LINES - 2 * offset, COLS - 2 * offset, offset, offset);
    keypad(win, true);
    scrollok(win, true);
    box(win, 0, 0);
    wrefresh(win);

    bool run = true;
    size_t stringStart = 0, stringNum = 0;
    int key = 0;

    int maxY, maxX;
    getmaxyx(win, maxY, maxX);

    while (run) {
        werase(win);

        size_t maxStrLen = 0;

        for (int i = 0; stringNum + i < nStrings && i < maxY; i++) {
            char *wStringStart = strings[stringNum + i] + stringStart;

            size_t strLen = strlen(strings[i + stringNum]);
            if (strLen > maxStrLen) {
                maxStrLen = strLen;
            }

            if (strLen <= stringStart) {
                wStringStart = "";
            }

            mvwaddnstr(win, i, 0, wStringStart, maxX);
        }

        wrefresh(win);

        switch (key = wgetch(win)) {
        case keyEsc:
            run = false;
            break;
        case ' ':
        case KEY_DOWN:
            if (stringNum < nStrings - maxY) {
                stringNum++;
            }
            break;
        case KEY_UP:
            if (stringNum > 0) {
                stringNum--;
            }
            break;
        case KEY_NPAGE:
            if (stringNum + maxY >= nStrings - maxY) {
                stringNum = nStrings - maxY;
            } else {
                stringNum += maxY;
            }
            break;
        case KEY_PPAGE:
            if (stringNum - maxY <= 0) {
                stringNum = 0;
            } else {
                stringNum -= maxY;
            }
            break;
        case KEY_RIGHT:
            if (stringStart + maxX < maxStrLen) {
                stringStart++;
            }
            break;
        case KEY_LEFT:
            if (stringStart > 0) {
                stringStart--;
            }
            break;
        default:
            run = true;
        }
    }

    delwin(win);
    endwin();

    for (size_t i = 0; i < nStrings; i++) {
        free(strings[i]);
    }

    free(strings);

    exit(0);
}
