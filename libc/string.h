#ifndef _PLUH_OS__LIBC__STRING_H_
#define _PLUH_OS__LIBC__STRING_H_

#include <libc/stdint.h>

void *memcpy(void *dest, const void *src, uint32_t len);
void *memset(void *dest, uint8_t val, uint32_t len);

void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char str[]);
void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
int index_of(char *s, char c);

char *itoa(int n);

#endif // _PLUH_OS__LIBC__STRING_H_