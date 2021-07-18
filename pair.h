// autor - Patryk Jędrzejczak

#ifndef SIMILAR_LINES_PAIR_H
#define SIMILAR_LINES_PAIR_H

// Typ reprezentujący parę dwóch liczb typu int.
typedef struct Pair {
  int first;
  int second;
} Pair;

// Funkcja zwracająca wskaźnik do nowo utworzonej pary o wartościach
// first == fst i second == snd.
Pair *pair_new(int fst, int snd);

// Funkcja przyjmująca argumenty typu Pair** i porównująca wartości par
// ukrytych pod wskaźnikami leksykograficznie. Sygnatura wymagana przez qsort.
// Funkcja zakłada, że różnice liczb nie przakraczają zakresu int. Zwraca:
//  liczbę ujemną, jeśli **ptr1 < **ptr2
//  liczbę dodatnią, jeśli **ptr1 > **ptr2
//  0, jeśli **ptr1 == **ptr2
int pairs_comparator(const void *ptr1, const void *ptr2);

#endif //SIMILAR_LINES_PAIR_H
