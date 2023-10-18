#ifndef _PLUH_OS__DRIVERS__FS_H_
#define _PLUH_OS__DRIVERS__FS_H_

#include <common/common.h>
#include <libc/stdint.h>

typedef struct file_t file_t;
typedef struct directory_t directory_t;

struct file_t {
    char *name;
    uint32_t size;
    uint8_t *data;
};

struct directory_t {
    char *name;
    file_t **files;
    uint32_t files_count;
    directory_t **directories;
    uint32_t directories_count;
};

extern directory_t *fs_root;

void init_fs();

#endif // _PLUH_OS__DRIVERS__FS_H_