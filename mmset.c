// autor - Patryk Jędrzejczak

#include "mmset.h"
#include "safefunctions.h"
#include "cmpfloats.h"
#include "pair.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Funkcja porównująca elementy m1, m2 typu Mset** według pewnego porządku
// typu Mset. Ma sygnaturę wymaganą przez qsort. Zwraca
//  - liczbę ujemną, jeśli **m1 < **m2
//  - liczbę dodatnią, jeśli **m2 > **m1
//  - 0, jeśli **m1 == **m2
static int mset_comparator(const void *ptr1, const void *ptr2) {
  const Mset **m1 = (const Mset **)ptr1;
  const Mset **m2 = (const Mset **)ptr2;

  // Jeśli multizbiory **m1 i **m2 zawierają inną liczbę słów, to są różne
  // (ten co ma mniej, jest mniejszy).
  if ((*m1)->num_of_strings != (*m2)->num_of_strings)
    return (*m1)->num_of_strings - (*m2)->num_of_strings;

  // Jak wyżej, tylko liczby zmiennoprzecinkowe.
  if ((*m1)->num_of_floats != (*m2)->num_of_floats)
    return (*m1)->num_of_floats - (*m2)->num_of_floats;

  // Jeśli i-te słowo multizbioru **m1 jest różne od i-tego słowa multizbioru
  // **m2, to te multizbiory są różne. Zakładamy, że oba multizbiory mają
  // posortowane słowa.
  for (int i = 0; i < (*m1)->num_of_strings; i++) {
    int cmp = strcmp((*m1)->strings[i], (*m2)->strings[i]);
    if (cmp != 0)
      return cmp;
  }

  // Jak wyżej, tylko liczby zmiennoprzecinkowe.
  for (int i = 0; i < (*m1)->num_of_floats; i++) {
    int cmp = cmp_floats((*m1)->floats[i], (*m2)->floats[i]);
    if (cmp != 0)
      return cmp;
  }

  // Jeśli doszliśmy tutaj, to multizbiory **m1 i **m2 muszą być równe.
  return 0;
}

MMset *mmset_new() {
  MMset *m = (MMset *)safe_malloc(sizeof(MMset));

  m->num_of_msets = 0;
  m->msets_size = 1;
  m->msets = (Mset **)safe_malloc(sizeof(Mset *));

  return m;
}

void mmset_destroy(MMset *m) {
  for (int i = 0; i < m->num_of_msets; i++)
    mset_destroy(m->msets[i]);

  free(m->msets);
  free(m);
}

void mmset_add_mset(MMset *m, int n) {
  m->num_of_msets++;

  // Dwukrotne powiększenie tablicy msets, jeśli brakuje miejsca.
  if (m->msets_size < m->num_of_msets) {
    m->msets_size *= 2;
    m->msets = (Mset **)safe_realloc(m->msets, m->msets_size * sizeof(Mset *));
  }

  m->msets[m->num_of_msets - 1] = mset_new(n);
}

void mmset_add_string_to_last_mset(MMset *m, const char *str) {
  mset_insert_string(m->msets[m->num_of_msets - 1], str);
}

void mmset_add_float_to_last_mset(MMset *m, long double d) {
  mset_insert_float(m->msets[m->num_of_msets - 1], d);
}

void mmset_sort(MMset *m) {
  for (int i = 0; i < m->num_of_msets; i++)
    mset_sort(m->msets[i]);

  qsort(m->msets, m->num_of_msets, sizeof(Mset *), mset_comparator);
}

void mmset_print(MMset m) {
  // Tablica wskaźników do par (id, pozycja w m.msets) multizbiorów początkowych
  // w tablicy m.msets. Multizbiorem początkowym jest multizbiór, który jest
  // pierwszy w m.msets albo ma różnego od siebie poprzednika w m.msets.
  Pair **beginnings = (Pair **)safe_malloc(sizeof(Pair *));
  // Rozmiar tablicy beginnings.
  int beginnings_size = 1;
  // Liczba multizbiorów początkowych.
  int num_of_beginnings = 0;

  // Znalenienie wszystkich multizbiorów początkowych.
  for (int i = 0; i < m.num_of_msets; i++)
    if (i == 0 || mset_comparator(&m.msets[i - 1], &m.msets[i]) != 0) {
      num_of_beginnings++;

      // Dwukrotne powiększenie tablicy beginnings, jeśli brakuje miejsca.
      if (beginnings_size < num_of_beginnings) {
        beginnings_size *= 2;
        beginnings = (Pair **)safe_realloc(beginnings,
                                           beginnings_size * sizeof(Pair *));
      }

      beginnings[num_of_beginnings - 1] = pair_new(m.msets[i]->id, i);
    }

  qsort(beginnings, num_of_beginnings, sizeof(Pair *), pairs_comparator);

  for (int i = 0; i < num_of_beginnings; i++) {
    // Wypisanie id najmniejszego niewypisanego multizbioru początkowego.
    safe_printf_int(beginnings[i]->first, false);

    // Wypisanie w kolejności rosnącej id multizbiorów identycznych do aktualnie
    // przetwarzanego multizbioru początkowego.
    int position = beginnings[i]->second + 1;
    while (position < m.num_of_msets && !mset_comparator(&m.msets[position - 1],
                                                         &m.msets[position])) {
      safe_printf_int(m.msets[position]->id, true);
      position++;
    }

    safe_newline();
  }

  for (int i = 0; i < num_of_beginnings; i++)
    free(beginnings[i]);
  free(beginnings);
}
