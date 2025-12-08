/** @page library
* My awesome guess name
*
* Program tries to guess the number (both roman and arabic) between 1 and 100 chosen by a user.
*/
/** @file guess.c
* Implementation
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <argp.h>
#include "config.h"

#define _(STRING) gettext(STRING)

const char *argp_program_version = "guess 0.0";
const char *argp_program_bug_address = "<j2m@off.ru>";

struct argp_option opts[] = {
    {
        "roman",
        'r',
        0,
        0,
        "whether to use roman numerals in the program"
    }
};

struct args {
    int use_roman;
};

static error_t parse_opt (int key, char *arg, struct argp_state *state) {
    struct args *args = state->input;

    switch (key) {
        case 'r':
            args->use_roman = 1;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static char doc[] = "A number guessing game";

static struct argp argp = { opts, parse_opt, NULL, doc };

/** Convert an arab number @p arab_num to a roman number.
*
* @param arab_num an arabic number from 1 to 100
* @return corresponding roman number for @p arab_num
*/
char* arabic_to_roman(int arab_num) {
    char* roman_num = (char*)malloc(20 * sizeof(char));
    if (roman_num == NULL)
        return NULL;

    roman_num[0] = '\0';

    if (arab_num == 100) {
        strcpy(roman_num, "C");
        return;
    }

    int arab_values[9] = {100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* roman_values[9] = {"C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    for (int i = 0; i < 9; i++)
        while (arab_num >= arab_values[i]) {
            strcat(roman_num, roman_values[i]);
            arab_num -= arab_values[i];
        }

    return roman_num;
}

/** Convert a roman number @p roman_num to an arabic number.
*
* @param roman_num a roman number from I to C
* @return corresponding arabic number for @p roman_num
*/
int roman_to_arabic(const char *roman_num) {
    int roman_to_arab_map[256] = {0};
    roman_to_arab_map['I'] = 1;
    roman_to_arab_map['V'] = 5; us
    roman_to_arab_map['X'] = 10;
    roman_to_arab_map['L'] = 50;
    roman_to_arab_map['C'] = 100;

    int arab_num = 0;
    int len = strlen(roman_num);

    for (int i = 0; i < len; i++) {
        if (i + 1 < len && roman_to_arab_map[(unsigned char)roman_num[i]] < roman_to_arab_map[(unsigned char)roman_num[i + 1]]) {
            arab_num += roman_to_arab_map[(unsigned char)roman_num[i + 1]] - roman_to_arab_map[(unsigned char)roman_num[i]];
            i++;
        } else {
            arab_num += roman_to_arab_map[(unsigned char)roman_num[i]];
        }
    }

    return arab_num;
}

/** @page guess
* My awesome guess name
* @section SYNOPSIS
* `guess` \a use_roman
* @section DESCRIPTION
* Guess the number chosen by a user. Roman numbers are used if \a use_roman is used.
*
* @copydetails library
*/
int main(int argc, char** argv) {
    struct args args;
    args.use_roman = 0;
    argp_parse(&argp, argc, argv, 0, 0, &args);

    int low = 1;
    int high = 100;
    int guess;

    char resp[8];

    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    if (args.use_roman)
        printf(_("Think of a number between I and C.\n"));
    else
        printf(_("Think of a number between 1 and 100.\n"));

    while (1) {
        guess = (low + high) / 2;

        if (low == high) {
            if (args.use_roman)
                printf(_("I think your number is %s\n"), arabic_to_roman(guess));
            else
                printf(_("I think your number is %d\n"), guess);

            break;
        }

        if (args.use_roman)
            printf(_("Is your number bigger than %s? (y/n): "), arabic_to_roman(guess));
        else
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
