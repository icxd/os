#ifndef _PLUH_OS__COMMON__COMMON_H_
#define _PLUH_OS__COMMON__COMMON_H_

#include <libc/string.h>

#define UNUSED(x) (void)(x)

typedef struct {
    char *data;
    int size;
} string;
#define SV(s) ((string){s, strlen(s)})

#define PANIC(msg) panic(msg, __FILE__, __LINE__)
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

void panic(char *msg, char *file, int line);
void panic_assert(char *file, int line, char *description);

#endif // _PLUH_OS__COMMON__COMMON_H_