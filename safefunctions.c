// autor - Patryk Jędrzejczak

#include "safefunctions.h"
#include <stdlib.h>

void *safe_malloc(size_t size) {
  void *ptr = malloc(size);

  if (ptr == NULL)
    exit(1);

  return ptr;
}

void *safe_realloc(void *memblock, size_t size) {
  void *ptr = realloc(memblock, size);

  if (ptr == NULL)
    exit(1);

  return ptr;
}

void safe_printf_int(int n, bool space_before_value) {
  if (space_before_value && printf(" %d", n) < 0)
    exit(1);
  if (!space_before_value && printf("%d", n) < 0)
    exit(1);
}

void safe_newline() {
  if (printf("\n") < 0)
    exit(1);
}