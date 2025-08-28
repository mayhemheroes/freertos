#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern int mayhem_process_input(char *buf, size_t len);
extern int mayhem_init(void);

__attribute__((weak)) int mayhem_init(void) { return 0; }


/** returns the contents of the file in a dynamically allocated buffer.

    The file is read until we run out of memory or the descriptor returns EOF.
    In case of any error, the function aborts the program.
    We use malloc/realloc to ensure that asan knows the boundaries. */
char *read_data(int fd, size_t *len) {
    char *ptr = NULL;
    *len = 0;
    while (1) {
        char buf[BUFSIZ];
        ssize_t n = read(fd, buf, sizeof(buf));
        if (n == -1) {
            err(1, "read");
        }
        if (n == 0) {
            break;
        }
        *len += n;
        ptr = realloc(ptr, *len);
        if (ptr == NULL) {
            err(1, "malloc");
        }
        memcpy(ptr + *len - n, buf, n);
    }
    return ptr;
}

int main(int argc, char *argv[]) {
    if (mayhem_init() != 0) {
        errx(1, "aborted by mayhem_init");
    }
    int fd = 0;                 /* if no input read from the stdin */

    if (argc > 1 && argv[1][0] != '-') {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            err(1, "open");
        }
    }
    size_t len = 0;
    char *ptr = read_data(fd, &len);
    close(fd);                  /* it's okay to close stdin as well. */
    int r = mayhem_process_input(ptr, len);
    free(ptr);
    return r;
}
