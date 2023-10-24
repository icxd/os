#include <cpu/ports.h>
#include <debug/qemu.h>
#include <kernel/serial.h>

unsigned int qemu_init_debug() { return init_serial(QEMU_LOG_SERIAL_PORT); }

void qemu_debug_putc(char c) {
    while ((port_byte_in(QEMU_LOG_SERIAL_PORT + 5) & 0x20) == 0)
        ;
    port_byte_out(QEMU_LOG_SERIAL_PORT, c);
}

void qemu_debug_puts(const char *s) {
    while (*s != '\0') {
        qemu_debug_putc(*s);
        s++;
    }
}

void debugcon_putc(char c) { port_byte_out(QEMU_DEBUGCON_PORT, c); }

void debugcon_puts(const char *s) {
    while (*s != '\0') {
        debugcon_putc(*s);
        s++;
    }
}