#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "passgen.h"

/*
 * Calculates
 * hexencode( SHA512( master + salt + host ) ) and writes it to dst
 * dst should be able to hold at least DIGEST_LENGTH chars followed by a null terminator
 */
void passgen(const char *master, size_t mlen,
             const char *salt, size_t slen,
             const char *host, size_t hlen, char *dst)
{
  //Check that inputs are valid c strings
  if(master[mlen] != '\0' || salt[slen] != '\0' || host[hlen] != '\0' ||
     strlen(master) != mlen || strlen(salt) != slen || strlen(host) != hlen)
  {
    fprintf(stderr, "%s", "FATAL ERROR: Unsafe C String!\n");
    abort();
  }

  //Allocate c string for concatenation
  char *concat = calloc(1, mlen + slen + hlen + 1);
  if(concat == NULL)
  {
    fprintf(stderr, "%s", "FATAL ERROR: Malloc returned null");
    abort();
  }

  strncpy(concat, master, mlen + 1);
  strncpy(concat + mlen, salt, slen + 1);
  strncpy(concat + mlen + slen, host, hlen + 1);

  //digest is *not* a c string and contains binary data.
  char digest[DIGEST_LENGTH];

  SHA512((unsigned char*) concat, mlen + slen + hlen, (unsigned char*) digest);

  memset(concat, 0, mlen + slen + hlen);
  free(concat);

  char table[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

  //Calculate hex conversion
  for(int i = 0; i < DIGEST_LENGTH; i++)
  {
    char left = (digest[i] >> 4) & 0x0F;
    char right = digest[i] & 0x0F;
    dst[2*i] = table[(int) left];
    dst[2*i+1] = table[(int) right];
  }

  dst[HEX_DIGEST_LENGTH] = '\0';

  memset(digest, 0, DIGEST_LENGTH);
}
