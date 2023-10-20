#ifndef _PLUH_OS__LIBC__STDDEF_H_
#define _PLUH_OS__LIBC__STDDEF_H_

typedef unsigned int size_t;
typedef int ssize_t;

#ifndef NULL
#define NULL ((void *)0)
#endif // NULL

#define offsetof(type, member) ((size_t)(&((type *)0)->member))

#endif // _PLUH_OS__LIBC__STDDEF_H_