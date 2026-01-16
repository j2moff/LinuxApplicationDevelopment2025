/** @mainpage romanizer
 *
 * Util to romanize russian cyrillic texts.
 *
 * The texts can be provided either by a text file or by program input.
 *
 * @section synopsis SYNOPSIS
 * romanizer [INFILE OUTFILE]
 *
 * @section arguments ARGUMENTS
 * @par
 * INFILE
 *     Cyrillic text input file.
 *
 * @par
 * OUTFILE
 *     Latin text output file
 *
 * If INFILE and OUTFILE are not provided, STDIN and STDOUT will be used respectively.
 */

 #include <locale.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <libintl.h>
#include <stdlib.h>
#include "dict.h"
#include "config.h"

#define _(STRING) gettext(STRING)

/**
 * @brief Display help information
 */
static void print_help() {
    fprintf(stderr, _("Usage: romanizer [INFILE OUTFILE]\n"));
    fprintf(stderr, _("Arguments:\n"));
    fprintf(stderr, _("  INFILE  - cyrillic text input file\n"));
    fprintf(stderr, _("  OUTFILE - latin text output file\n"));
    fprintf(stderr, _("If INFILE and OUTFILE are not provided, STDIN and STDOUT will be used respectively.\n"));
}

/** @page romanizer
 *
 * Util to romanize russian cyrillic texts.
 *
 * The texts can be provided either by a text file or by program input.
 *
 * @section synopsis SYNOPSIS
 * romanizer [INFILE OUTFILE]
 *
 * @section arguments ARGUMENTS
 * @par
 * INFILE
 *     Cyrillic text input file.
 *
 * @par
 * OUTFILE
 *     Latin text output file
 *
 * If INFILE and OUTFILE are not provided, STDIN and STDOUT will be used respectively.
 */
int main(int argc, char** argv) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALE_PATH);
    textdomain(PACKAGE);

    if (argc != 1 && argc != 3) {
        fprintf(stderr, _("got wrong number of arguments\n"));
        print_help();
        return 1;
    }

    if (argc == 1) {
        fprintf(stderr, _("Write your cyrillic text:\n"));
        fprintf(stderr, _("(Press Enter or Ctrl+D to get the romanized text)\n"));
        fprintf(stderr, _("(Press Enter+Ctrl+D or Ctrl+D twice to quit)\n"));

        wint_t curr_char, prev_char;

        while ((curr_char = fgetwc(stdin)) != WEOF) {
            convert_and_print(curr_char, prev_char, stdout);
            prev_char = curr_char;
        }

        return 0;
    }

    char* infile_name = argv[1];
    char* outfile_name = argv[2];

    if (!strcmp(infile_name, outfile_name)) {
        fprintf(stderr, _("got the same input and output file\n"));
        print_help();
        return 1;
    }

    FILE* infile = fopen(infile_name, "rb, ccs=UTF-8");
    if (infile == NULL) {
        fprintf(stderr, _("failed to open the input file\n"));
        print_help();
        return 1;
    }

    FILE* outfile = fopen(outfile_name, "wb, ccs=UTF-8");
    if (outfile == NULL) {
        fprintf(stderr, _("failed to open the output file\n"));
        print_help();
        fclose(infile);
        return 1;
    }

    wint_t curr_char, prev_char;

    while ((curr_char = fgetwc(infile)) != WEOF) {
        convert_and_print(curr_char, prev_char, outfile);
        prev_char = curr_char;
    }

    fclose(outfile);
    fclose(infile);

    return 0;
}
