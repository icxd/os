#include <libc/stdint.h>
#include <libc/stdlib.h>

uint32_t free_mem_addr = 0x10000;

uint32_t kmalloc(int size, int alignment, uint32_t *physical_address) {
    if (alignment == 1 && (free_mem_addr & 0xFFFFF000)) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }

    if (physical_address)
        *physical_address = free_mem_addr;

    uint32_t ret = free_mem_addr;
    free_mem_addr += size;
    return ret;
}

void *malloc(int size) {
    uint32_t addr;
    kmalloc(size, 0, &addr);
    return (void *)addr;
}

void free(void *ptr) {
    // TODO
}