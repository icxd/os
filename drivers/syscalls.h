#ifndef _PLUH_OS__KERNEL__SYSCALLS_H_
#define _PLUH_OS__KERNEL__SYSCALLS_H_

#include <cpu/isr.h>
#include <stddef.h>
#include <stdint.h>

typedef uint16_t umode_t;

#define ENUMERATE_SYSCALLS                                                     \
    SYSCALL_ENUM(read, 0x00, uint32_t, char *, size_t)                         \
    SYSCALL_ENUM(write, 0x01, uint32_t, const char *, size_t)                  \
    SYSCALL_ENUM(open, 0x02, const char *, int, umode_t)                       \
    SYSCALL_ENUM(close, 0x03, uint32_t)                                        \
    SYSCALL_ENUM(exit, 0x60, int)

#define SYSCALL_ENUM(name, value, ...) sc_##name = value,
typedef enum { ENUMERATE_SYSCALLS } syscall_t;
#undef SYSCALL_ENUM

#define SYSCALL_ENUM(name, value, ...) uint32_t sys$##name(__VA_ARGS__);
ENUMERATE_SYSCALLS
#undef SYSCALL_ENUM

void init_syscalls();

#endif // _PLUH_OS__KERNEL__SYSCALLS_H_