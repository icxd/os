#include <common/common.h>
#include <cpu/ports.h>
#include <kernel/syscalls.h>

uint32_t sys$read(uint32_t fd, char *buffer, size_t count) {
    uint32_t ret;
    asm volatile("int $0x80"
                 : "=a"(ret)
                 : "0"(sc_read), "b"(fd), "c"(buffer), "d"(count));
    return ret;
}

uint32_t sys$write(uint32_t fd, const char *buffer, size_t count) {
    uint32_t ret;
    asm volatile("int $0x80"
                 : "=a"(ret)
                 : "0"(sc_write), "b"(fd), "c"(buffer), "d"(count));
    return ret;
}

uint32_t sys$open(const char *filename, int flags, umode_t mode) {
    uint32_t ret;
    asm volatile("int $0x80"
                 : "=a"(ret)
                 : "0"(sc_open), "b"(filename), "c"(flags), "d"(mode));
    return ret;
}

uint32_t sys$close(uint32_t fd) {
    uint32_t ret;
    asm volatile("int $0x80" : "=a"(ret) : "0"(sc_close), "b"(fd));
    return ret;
}

void syscall_handler(registers_t *regs) {
    DEBUG("syscall_handler: %d\n", regs->eax);
    switch (regs->eax) {
    case sc_read:
        regs->eax = sys$read(regs->ebx, (char *)regs->ecx, regs->edx);
        break;
    case sc_write:
        regs->eax = sys$write(regs->ebx, (const char *)regs->ecx, regs->edx);
        break;
    case sc_open:
        regs->eax = sys$open((const char *)regs->ebx, regs->ecx, regs->edx);
        break;
    case sc_close:
        regs->eax = sys$close(regs->ebx);
        break;
    default:
        break;
    }
}