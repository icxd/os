#ifndef _PLUH_OS__DEBUG__QEMU_H_
#define _PLUH_OS__DEBUG__QEMU_H_

#define QEMU_LOG_SERIAL_PORT 0x3f8
#define QEMU_DEBUGCON_PORT 0xe9

unsigned int qemu_init_debug();
void qemu_debug_putc(char c);
void qemu_debug_puts(const char *s);
void debugcon_putc(char c);
void debugcon_puts(const char *s);

#endif // _PLUH_OS__DEBUG__QEMU_H_