#include <stdio.h>
#include <magic.h>
#include <string.h>

int main(int argc, char **argv) {
    magic_t magic_cookie;

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Initialize magic library
    magic_cookie = magic_open(MAGIC_MIME_TYPE);
    if (magic_cookie == NULL) {
        printf("Unable to initialize magic library\n");
        return 1;
    }

    // Load magic database
    if (magic_load(magic_cookie, "school.magic.mgc") != 0) {
        printf("Unable to load magic database %s\n", magic_error(magic_cookie));
        magic_close(magic_cookie);
        return 1;
    }

    // Identify file type
    const char *mime_type = magic_file(magic_cookie, argv[1]);
    if (mime_type == NULL) {
        printf("Unable to determine file type %s\n", magic_error(magic_cookie));
        magic_close(magic_cookie);
        return 1;
    }
    printf("Detected mime type: %s\n", mime_type);

    // Check if file is a School data file
    if (strstr(mime_type, "SCHOOL")) {
        printf("File is a School data file\n");
    } else {
        printf("File is not a School data file\n");
    }

    // Clean up
    magic_close(magic_cookie);

    return 0;
}
