#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <math.h>

/*
 * Calculates
 * base64encode( SHA256( master + salt + host ) )
 */
char* pass_gen(const char *master, size_t mlen,
               const char *salt, size_t slen,
               const char *host, size_t hlen)
{
  if(master[mlen] != '\0' || salt[slen] != '\0' || host[hlen] != '\0' ||
     strlen(master) != mlen || strlen(salt) != slen || strlen(host) != hlen)
  {
    fprintf(stderr, "FATAL ERROR: Unsafe C String!\n");
    abort();
  }

  char *concat = calloc(1, mlen + slen + hlen + 1);
  if(concat == NULL)
  {
    fprintf(stderr, "FATAL ERROR: Malloc returned null");
    abort();
  }

  strncpy(concat, master, mlen + 1);
  strncpy(concat + mlen, salt, slen + 1);
  strncpy(concat + mlen + slen, host, hlen + 1);

  char *digest = calloc(1, SHA256_DIGEST_LENGTH);
  if(digest == NULL)
  {
    fprintf(stderr, "FATAL ERROR: Malloc returned null");
    abort();
  }

  SHA256((unsigned char*) concat, mlen + slen + hlen, (unsigned char*) digest);

  int encodedSize = 4*ceil((double)(mlen + slen + hlen)/3);

  char *buffer = calloc(1, encodedSize+1);
  if(buffer == NULL)
  {
    fprintf(stderr, "FATAL ERROR: Malloc returned null");
    abort();
  }

  FILE* stream = fmemopen(buffer, encodedSize+1, "w");
  BIO *b64 = BIO_new(BIO_f_base64());
  BIO *bio = BIO_new_fp(stream, BIO_NOCLOSE);
  bio = BIO_push(b64, bio);
  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
  BIO_write(bio, digest, strlen(digest));
  BIO_flush(bio);
  BIO_free_all(bio);
  fclose(stream);

  free(digest);

  return buffer;
}


int main(void)
{
  printf(pass_gen("hi", 2, "lol", 3, "miao", 4));
  printf("\n");
  return 0;
}
