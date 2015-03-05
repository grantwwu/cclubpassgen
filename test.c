#include "passgen.h"
#include <stdio.h>

int main(void)
{
  char digest[65];
  passgen("", 0, "", 0, "", 0, digest);
  printf(digest);
  printf("\n");
  return 0;
}
