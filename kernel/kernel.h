#ifndef _PLUH_OS__KERNEL__KERNEL_H_
#define _PLUH_OS__KERNEL__KERNEL_H_

#include <libc/stdint.h>

typedef struct boot_state_t boot_state_t;
struct boot_state_t {
    // file system
    uint32_t error;       // set on error
    uint32_t status;      // status
    uint32_t num_sectors; // number of sectors transferred
};

void user_input(char *input);

#endif // _PLUH_OS__KERNEL__KERNEL_H_