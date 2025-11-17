#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include "config.h"

#define _(STRING) gettext(STRING)

int main() {
    int low = 1;
    int high = 100;
    int guess;

    char resp[8];

    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    printf(_("Think of a number between 1 and 100.\n"));

    while (1) {
        guess = (low + high) / 2;

        if (low == high) {
            printf(_("I think your number is %d\n"), guess);
            break;
        }

        printf(_("Is your number bigger than %d? (y/n): "), guess);

        if (fgets(resp, sizeof(resp), stdin) == NULL) {
            fprintf(stderr, _("failed to get response\n"));
            return 1;
        }

        resp[strcspn(resp, "\n")] = 0;

        if (strcmp(resp, _("y")) == 0) {
            low = guess + 1;
        } else if (strcmp(resp, _("n")) == 0) {
            high = guess;
        } else {
            printf(_("got invalid response, it should be either 'y' or 'n'\n"));
            continue;
        }
    }

    return 0;
}
