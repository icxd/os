#include <drivers/fs.h>
#include <libc/stdint.h>
#include <libc/stdlib.h>
#include <libc/string.h>

directory_t *fs_root;

void init_fs() {
    fs_root = (directory_t *)malloc(sizeof(directory_t));
    fs_root->name = "/";
    fs_root->files = NULL;
    fs_root->files_count = 0;
    fs_root->directories = NULL;
    fs_root->directories_count = 0;

    directory_t *bin = (directory_t *)malloc(sizeof(directory_t));
    bin->name = "bin";
    bin->files = NULL;
    bin->files_count = 0;
    bin->directories = NULL;
    bin->directories_count = 0;

    directory_t *home = (directory_t *)malloc(sizeof(directory_t));
    home->name = "home";
    home->files = NULL;
    home->files_count = 0;
    home->directories = NULL;
    home->directories_count = 0;

    directory_t *dev = (directory_t *)malloc(sizeof(directory_t));
    dev->name = "dev";
    dev->files = NULL;
    dev->files_count = 0;
    dev->directories = NULL;
    dev->directories_count = 0;

    directory_t *tmp = (directory_t *)malloc(sizeof(directory_t));
    tmp->name = "tmp";
    tmp->files = NULL;
    tmp->files_count = 0;
    tmp->directories = NULL;
    tmp->directories_count = 0;

    fs_root->directories = (directory_t **)malloc(sizeof(directory_t *) * 4);
    fs_root->directories[0] = bin;
    fs_root->directories[1] = home;
    fs_root->directories[2] = dev;
    fs_root->directories[3] = tmp;
    fs_root->directories_count = 4;
}