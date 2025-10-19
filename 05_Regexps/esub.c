#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 10

void print_help() {
    printf("Usage: esub REGEXP SUBSTITUTION STRING\n");
    printf("Arguments:\n");
    printf("  REGEXP        - regular expression to substitute\n");
    printf("  SUBSTITUTION  - substitute string\n");
    printf("  STRING        - string where the first REGEXP match will be substituted by SUBSTITUTION\n");
    printf("\n");
    printf("Examples:\n");
    printf("  esub \"awesome\" \"AWESOME\" \"myawesometest\"  -> myAWESOMEtest\n");
    printf("  esub \"[0-9]\" \"13\" \"myawesometest037\"      -> myawesometest1337\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "got wrong number of arguments\n");
        print_help();
        return 1;
    }

    char* regexp_string = argv[1];
    char* substitution = argv[2];
    char* string_input = argv[3];

    regex_t regexp;
    int err;

    if ((err = regcomp(&regexp, regexp_string, REG_EXTENDED)) != 0) {
        char error_msg[100];
        regerror(err, &regexp, error_msg, sizeof(error_msg));
        fprintf(stderr, "failed to compile regexp: %s\n", error_msg);
        return 1;
    }

    regmatch_t regexp_matches[MAX_MATCHES];
    int substitution_len = strlen(substitution);

    if (regexec(&regexp, string_input, MAX_MATCHES, regexp_matches, 0) == 0) {
        for (int i = 0; i < strlen(string_input); i++) {
            if (i < regexp_matches[0].rm_so || i >= regexp_matches[0].rm_eo) {
                putchar(string_input[i]);
                continue;
            }

            for (int j = 0; j < substitution_len; j++) {
                if (j < substitution_len - 1 && substitution[j] == '\\' && substitution[j+1] >= '0' && substitution[j+1] <= '9') {
                    int regexp_match_idx = substitution[j+1] - '0';
                    printf("%.*s", regexp_matches[regexp_match_idx].rm_eo - regexp_matches[regexp_match_idx].rm_so, string_input + regexp_matches[regexp_match_idx].rm_so);
                    j++;
                } else
                    putchar(substitution[j]);

                if (j < substitution_len - 1 && substitution[j] == '\\' && substitution[j+1] == '\\')
                    j++;
            }
            i = regexp_matches[0].rm_eo - 1;
        }

        putchar('\n');
    }

    return 0;
}
