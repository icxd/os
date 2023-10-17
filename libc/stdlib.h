#ifndef _PLUH_OS__LIBC__STDLIB_H_
#define _PLUH_OS__LIBC__STDLIB_H_

#define NULL ((void *)0)

uint32_t kmalloc(int size, int alignment, uint32_t *physical_address);
void *malloc(int size);

#endif // _PLUH_OS__LIBC__STDLIB_H_