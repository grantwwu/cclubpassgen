#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <openssl/sha.h>

/*
 * Calculates
 * base64encode( SHA256( master + salt + host ) )
 */
char* pass_gen(const char *master, size_t mlen,
               const char *salt, size_t slen,
               const char *host, size_t hlen)
{
  //Check that inputs are valid c strings
  if(master[mlen] != '\0' || salt[slen] != '\0' || host[hlen] != '\0' ||
     strlen(master) != mlen || strlen(salt) != slen || strlen(host) != hlen)
  {
    fprintf(stderr, "FATAL ERROR: Unsafe C String!\n");
    abort();
  }

  //Allocate c string for concatenation
  char *concat = calloc(1, mlen + slen + hlen + 1);
  if(concat == NULL)
  {
    fprintf(stderr, "FATAL ERROR: Malloc returned null");
    abort();
  }

  //Concatenate
  strncpy(concat, master, mlen + 1);
  strncpy(concat + mlen, salt, slen + 1);
  strncpy(concat + mlen + slen, host, hlen + 1);

  //Allocate c string for digest
  char *digest = calloc(1, SHA256_DIGEST_LENGTH + 1);
  if(digest == NULL)
  {
    fprintf(stderr, "FATAL ERROR: Malloc returned null");
    abort();
  }

  //Do hash
  SHA256((unsigned char*) concat, mlen + slen + hlen, (unsigned char*) digest);

  //Dispose of concat
  memset(concat, 0, mlen + slen + hlen);
  free(concat);

  //Allocate memory for hex conversion
  char *hex = calloc(1, 2*SHA256_DIGEST_LENGTH + 1);
  if(hex == NULL)
  {
    fprintf(stderr, "FATAL ERROR: Malloc returned null");
    abort();
  }

  char table[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

  //Calculate hex conversion
  for(int i = 0; i < 32; i++)
  {
    char left = (digest[i] >> 4) & 0x0F;
    char right = digest[i] & 0x0F;
    hex[2*i] = table[(int) left];
    hex[2*i+1] = table[(int) right];
  }

  //Dispose of digest
  memset(digest, 0, SHA256_DIGEST_LENGTH);
  free(digest);

  return hex;
}

int main(void)
{
  char *result = pass_gen("hi", 2, "lol", 3, "miao", 4);
  printf(result);
  free(result);
  printf("\n");
  return 0;
}
