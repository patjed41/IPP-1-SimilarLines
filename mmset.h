// autor - Patryk Jędrzejczak

#ifndef SIMILAR_LINES_MMSET_H
#define SIMILAR_LINES_MMSET_H

#include "mset.h"

// Typ reprezentujący multizbiór multizbiorów typu Mset.
typedef struct MMset {
  int num_of_msets;   // liczba multizbiorów
  int msets_size;     // rozmiar tablicy msets
  Mset **msets;       // tablica przechowująca wskaźniki do multizbiorów
} MMset;

// "Konstruktor" zwracający wskaźnik do nowego obiektu typu MMset.
MMset *mmset_new();

// "Destruktor" zwalniający pamięć zajmowaną przez m.
void mmset_destroy(MMset *m);

// Funkcja dodająca do m multizbiór o identyfikatorze n.
void mmset_add_mset(MMset *m, int n);

// Funkcja dodająca słowo str do ostatnio dodanego do m multizbioru.
void mmset_add_string_to_last_mset(MMset *m, const char *str);

// Funkcja dodająca liczbę zmiennoprzecinkową d do ostatnio dodanego do m
// multizbioru.
void mmset_add_float_to_last_mset(MMset *m, long double d);

// Funkcja sortująca multizbiory przechowywane w m według pewnego porządku
// (kluczowe jest to, że identyczne multizbiory wystąpią obok siebie).
void mmset_sort(MMset *m);

// Funkcja wypisująca w kolejnych wierszach identyfikatory identycznych
// multizbiorów występujących w m. Wyjście jest posortowane. Funkcja zakłada,
// że multizbiory występujące w m są posortowane.
void mmset_print(MMset m);

#endif /* SIMILAR_LINES_MMSET_H */
