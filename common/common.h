#ifndef _PLUH_OS__COMMON__COMMON_H_
#define _PLUH_OS__COMMON__COMMON_H_

#include <libc/string.h>

#define UNUSED(x) (void)(x)

typedef struct {
    char *data;
    int size;
} string;
#define SV(s) ((string){s, strlen(s)})

#endif // _PLUH_OS__COMMON__COMMON_H_