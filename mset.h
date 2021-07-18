// autor - Patryk Jędrzejczak

#ifndef SIMILAR_LINES_MSET_H
#define SIMILAR_LINES_MSET_H

// Typ reprezentujący multizbiór słów (nieliczb) i liczb zmiennoprzec. (liczb).
typedef struct Mset {
  int id;               // identyfikator multizbioru
  int num_of_strings;   // ilość słów w multizbiorze
  int strings_size;     // rozmiar tablicy strings
  char **strings;       // tablica przechowująca słowa multizbioru
  int num_of_floats;    // ilość liczb zmiennoprzecinkowych w multizbiorze
  int floats_size;      // rozmiar tablicy floats
  long double *floats;  // tablica przechowująca liczby zmiennoprz. multizbioru
} Mset;

// "Konstruktor" zwracający wskaźnik do nowego obiektu Mset o identyfikatorze n.
Mset *mset_new(int n);

// "Destruktor" zwalniający pamięć zajmowaną przez multizbiór m.
void mset_destroy(Mset *m);

// Funkcja dodająca słowo str do multizbioru m.
void mset_insert_string(Mset *m, const char *str);

// Funkcja dodająca liczbę zmiennoprzecinkową d do multizbioru m.
void mset_insert_float(Mset *m, long double d);

// Fukcja sortująca multizbiór m (osobno słowa i liczby zmiennoprzecinkowe).
void mset_sort(Mset *m);

#endif /* SIMILAR_LINES_MSET_H */
