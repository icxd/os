#include <common/common.h>
#include <cpu/isr.h>
#include <cpu/ports.h>
#include <drivers/screen.h>
#include <drivers/syscalls.h>

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

uint32_t sys$exit(int error_code) {
    uint32_t ret;
    asm volatile("int $0x80" : "=a"(ret) : "0"(sc_exit), "b"(error_code));
    return ret;
}

static void syscall_callback(registers_t *regs) {
    uint32_t eax = regs->eax;
    kprint("Syscall: ");
    char s[256];
    itoa(eax, s, 16);
    kprint(s);
    kprint("\n");
}

void init_syscalls() { register_interrupt_handler(IRQ2, syscall_callback); }