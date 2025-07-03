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
    return mayhem_process_input(buf, len);
}
