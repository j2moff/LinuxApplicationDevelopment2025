#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <rhash.h>

// #define USE_READLINE

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#define MAX_HASH_SIZE 128

int get_alg (char* alg_name) {
    if (strcasecmp(alg_name, "MD5") == 0)
        return RHASH_MD5;
    if (strcasecmp(alg_name, "SHA1") == 0)
        return RHASH_SHA1;
    if (strcasecmp(alg_name, "TTH") == 0)
        return RHASH_TTH;
    return -1;
}

void execute_command(char* command) {
        char* alg_name = strtok(command, " ");
        if (!alg_name)
            return;

        char* input = strtok(command, " ");
        if (!input) {
            fprintf(stderr, "found no input\n");
            return;
        }

        int alg = get_alg(alg_name);
        if (alg == -1) {
            fprintf(stderr, "got unknown algorithm name %s\n", alg_name);
            return;
        }

        unsigned char digest[64];
        char output[130];
        int res;
        int output_mode = isupper((unsigned char)alg_name[0]) ? RHPR_HEX : RHPR_BASE64;

        if (input[0] == '"') {
            size_t len = strlen(input);
            if (input[len-1] == '"') {
                input[len-1] = '\0';
                input++;
            }

            res = rhash_msg(alg, input, strlen(input), digest);
            if (res < 0)
                return;

            rhash_print_bytes(output, digest, rhash_get_digest_size(alg), output_mode);
        } else {
            FILE* file = fopen(input, "rb");
            if (!file) {
                fprintf(stderr, "failed to open file\n");
                return;
            }

            fseek(file, 0, SEEK_END);
            long file_size = ftell(file);
            fseek(file, 0, SEEK_SET);

            char* buf = malloc(file_size);
            if (!buf) {
                fclose(file);
                fprintf(stderr, "failed to allocate memory\n");
                return;
            }

            size_t file_bytes = fread(buf, 1, file_size, file);
            if (file_bytes != (size_t)file_size) {
                fprintf(stderr, "failed to read file fully\n");
                free(buf);
                fclose(file);
                return;
            }

            res = rhash_msg(alg, buf, file_size, digest);
            if (res < 0)
                return;

            rhash_print_bytes(output, digest, rhash_get_digest_size(alg), output_mode);
            free(buf);
            fclose(file);
        }

        printf("%s\n", output);
}

int main () {
    rhash_library_init();
    char* line = NULL;

    while (1) {
#ifdef USE_READLINE
        line = readline("rhasher> ");
        if (!line)
            break;
        if (*line)
            add_history(line);
#else
        size_t len = 0;
        ssize_t read = getline(&line, &len, stdin);
        if (read == -1) {
            free(line);
            break;
        }
#endif

#ifdef USE_READLINE
        free(line);
#else
        free(line);
        line = NULL;
#endif
    }

    return 0;
}
