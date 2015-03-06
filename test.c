#include "passgen.h"
#include <stdio.h>

int main(void)
{
  char digest[HEX_DIGEST_LENGTH + 1];
  passgen("", 0, "", 0, "", 0, digest);
  printf(digest);
  printf("\n");
  return 0;
}
