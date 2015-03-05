#include <stddef.h>

#ifndef PASSGEN_H_INCLUDED
#define PASSGEN_H_INCLUDED
void passgen(const char *master, size_t mlen,
             const char *salt, size_t slen,
             const char *host, size_t hlen, char *dst);
#endif

