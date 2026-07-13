/* libFuzzer entry point: bridges LLVMFuzzerTestOneInput to the harness's
 * mayhem_process_input(). One-time setup goes through mayhem_init() (weak
 * default is a no-op; the full-stack harness overrides it to boot the stack).
 *
 * Leak detection is disabled: the harnesses are allocate-and-exit batch
 * parsers (each input allocates descriptors/interfaces that are reclaimed on
 * process exit); ASan/UBSan memory-safety checks remain fully enabled. */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern int mayhem_process_input(char *buf, size_t len);
extern int mayhem_init(void);

__attribute__((weak)) int mayhem_init(void)
{
    return 0;
}

const char *__lsan_default_options(void);
const char *__lsan_default_options(void)
{
    return "detect_leaks=0";
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    static int initialized = 0;

    if (!initialized) {
        if (mayhem_init() != 0) {
            exit(1);
        }
        initialized = 1;
    }

    char *buf = malloc(size > 0 ? size : 1);
    if (buf == NULL) {
        return 0;
    }
    memcpy(buf, data, size);
    mayhem_process_input(buf, size);
    free(buf);
    return 0;
}
