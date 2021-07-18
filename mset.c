// autor - Patryk Jędrzejczak

#include "mset.h"
#include "safefunctions.h"
#include "cmpfloats.h"
#include <string.h>
#include <stdlib.h>

// Funkcja wykorzystywana przez qsort do porównywania słów (typu char*).
static int strings_comparator(const void *ptr1, const void *ptr2) {
  const char **str1 = (const char **)ptr1;
  const char **str2 = (const char **)ptr2;

  return strcmp(*str1, *str2);
}

// Funkcja wykorzystywana przez qsort do porównywania liczb zmiennoprzecinkowych
// (typu long double).
static int floats_comparator(const void *ptr1, const void *ptr2) {
  const long double *d1 = (const long double *)ptr1;
  const long double *d2 = (const long double *)ptr2;

  return cmp_floats(*d1, *d2);
}

Mset *mset_new(int n) {
  Mset *m = (Mset *)safe_malloc(sizeof(Mset));

  m->id = n;
  m->num_of_strings = 0;
  m->strings_size = 1;
  m->strings = (char **)safe_malloc(sizeof(char *));
  m->num_of_floats = 0;
  m->floats_size = 1;
  m->floats = (long double *)safe_malloc(sizeof(long double));

  return m;
}

void mset_destroy(Mset *m) {
  for (int i = 0; i < m->num_of_strings; i++)
    free(m->strings[i]);

  free(m->strings);
  free(m->floats);
  free(m);
}

void mset_insert_string(Mset *m, const char *str) {
  m->num_of_strings++;

  // Dwukrotne powiększenie tablicy strings, jeśli brakuje miejsca.
  if (m->strings_size < m->num_of_strings) {
    m->strings_size *= 2;
    m->strings = (char **)safe_realloc(m->strings,
                                       m->strings_size * sizeof(char *));
  }

  m->strings[m->num_of_strings - 1] =
    (char *)safe_malloc(((int)strlen(str) + 1) * sizeof(char));

  strcpy(m->strings[m->num_of_strings - 1], str);
}

void mset_insert_float(Mset *m, long double d) {
  m->num_of_floats++;

  // Dwukrotne powiększenie tablicy floats, jeśli brakuje miejsca.
  if (m->floats_size < m->num_of_floats) {
    m->floats_size *= 2;
    m->floats = (long double *)
                safe_realloc(m->floats, m->floats_size * sizeof(long double));
  }

  m->floats[m->num_of_floats - 1] = d;
}

void mset_sort(Mset *m) {
  qsort(m->strings, m->num_of_strings, sizeof(char *), strings_comparator);
  qsort(m->floats, m->num_of_floats, sizeof(long double), floats_comparator);
}