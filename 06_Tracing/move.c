#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void print_help() {
    printf("Usage: move INFILE OUTFILE\n");
    printf("Arguments:\n");
    printf("  INFILE   - source file\n");
    printf("  OUTFILE  - destination file\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "got wrong number of arguments\n");
        print_help();
        return 1;
    }

    char* infile_name = argv[1];
    char* outfile_name = argv[2];

    if (!strcmp(infile_name, outfile_name)) {
        fprintf(stderr, "got the same source and destination file\n");
        return 2;
    }

    FILE* infile = fopen(infile_name, "rb");
    if (infile == NULL) {
		fprintf(stderr, "failed to open the source file\n");
		return 3;
	}

    int infile_size = ftell(infile);
    if (infile_size == -1) {
		fclose(infile);
		fprintf(stderr, "failed to calculate source file size\n");
		return 4;
	}

    char* infile_buf = (char*)malloc(infile_size + 1);
	if (infile_buf == NULL && infile_size > 0) {
		fclose(infile);
		fprintf(stderr, "failed to allocate memory\n");
		return 5;
	}

    if (infile_size > 0) {
		size_t infile_bytes = fread(infile_buf, 1, infile_size, infile);
		if (infile_bytes != (size_t)infile_size) {
			fclose(infile);
			free(infile_buf);
			fprintf(stderr, "failed to read the source file fully\n");
			return 6;
		}

		infile_buf[infile_size] = '\0';
	}

    if (fclose(infile)) {
		free(infile_buf);
		fprintf(stderr, "failed to close the source file\n");
		return 7;
	}

    FILE* outfile = fopen(outfile_name, "wb");
	if (outfile == NULL) {
		free(infile_buf);
		fprintf(stderr, "failed to open the destination file\n");
		return 8;
	}

	if (infile_size > 0) {
		size_t outfile_bytes = fwrite(infile_buf, 1, infile_size, outfile);
		if (outfile_bytes != (size_t)infile_size) {
			free(infile_buf);
			fclose(outfile);
			fprintf(stderr, "failed to write the destination file fully\n");
			return 9;
		}
	}

	if (fclose(outfile)) {
		free(infile_buf);
		fprintf(stderr, "failed to close the destination file\n");
		return 10;
	}

    if (remove(infile_name)) {
		free(infile_buf);
		fprintf(stderr, "failed to remove the source file\n");
		return 11;
	}

    free(infile_buf);

    return 0;
}
