#ifndef _PLUH_OS__DRIVERS__PORTS_H_
#define _PLUH_OS__DRIVERS__PORTS_H_

#include <libc/stdint.h>

uint8_t port_byte_in(uint16_t port);
void port_byte_out(uint16_t port, uint8_t data);

uint16_t port_word_in(uint16_t port);
void port_word_out(uint16_t port, uint16_t data);

#endif // _PLUH_OS__DRIVERS__PORTS_H_