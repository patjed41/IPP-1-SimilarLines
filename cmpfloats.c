// autor - Patryk Jędrzejczak

#include "cmpfloats.h"

int cmp_floats(long double d1, long double d2) {
  if (d1 < d2)
    return -1;
  else if (d1 > d2)
    return 1;
  else
    return 0;
}