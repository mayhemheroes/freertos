#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>

extern int mayhem_process_input(char *buf, size_t len);

int main(int argc, char *argv[]) {
    int fd = 0;                 /* if no input read from the stdin */
    char buf[BUFSIZ];

    if (argc > 1 && argv[1][0] != '-') {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            err(1, "open");
        }
    }

    ssize_t len = read(fd, buf, sizeof(buf));
    if (len == -1) {
        err(1, "read");
    }
    close(fd);                  /* it's okay to close stdin as well. */

    /* we copy from the input buffer to make sure that address sanitizer
     * knows perfectly where is the end of the buffer.  */
    char *ptr = malloc(len);
    if (ptr == NULL) {
        err(1, "malloc");
    }

    int r = mayhem_process_input(memcpy(ptr, buf, len), len);
    free(ptr);
    return r;
}
