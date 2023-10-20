#ifndef _PLUH_OS__LIBC__STRING_H_
#define _PLUH_OS__LIBC__STRING_H_

#include <libc/stdbool.h>
#include <libc/stdint.h>

void *memcpy(void *dest, const void *src, uint32_t len);
void *memset(void *dest, uint8_t val, uint32_t len);

char *strcpy(char *dest, const char *src);
bool strcmp(const char *s1, const char *s2);

void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char str[]);
void backspace(char s[]);
void append(char s[], char n);
int index_of(char *s, char c);

char *itoa(int value, char *str, int base);
char *sitoa(int value);

#endif // _PLUH_OS__LIBC__STRING_H_