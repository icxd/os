#ifndef _PLUH_OS__LIBC__STDINT_H_
#define _PLUH_OS__LIBC__STDINT_H_

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#define low_16(addr) (uint16_t)((addr) & 0xFFFF)
#define high_16(addr) (uint16_t)((addr >> 16) & 0xFFFF)

#endif // _PLUH_OS__LIBC__STDINT_H_