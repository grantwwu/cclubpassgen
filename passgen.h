#include <stddef.h>
#include <openssl/sha.h>

#define DIGEST_LENGTH (SHA512_DIGEST_LENGTH)
#define HEX_DIGEST_LENGTH (SHA512_DIGEST_LENGTH * 2)

#ifndef PASSGEN_H_INCLUDED
#define PASSGEN_H_INCLUDED
void passgen(const char *master, size_t mlen,
             const char *salt, size_t slen,
             const char *host, size_t hlen, char *dst);
#endif

