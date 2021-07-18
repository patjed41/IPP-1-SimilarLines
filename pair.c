// autor - Patryk Jędrzejczak

#include "pair.h"
#include "safefunctions.h"

Pair *pair_new(int fst, int snd) {
  Pair *pair = (Pair *)safe_malloc(sizeof(Pair));

  pair->first = fst;
  pair->second = snd;

  return pair;
}

int pairs_comparator(const void *ptr1, const void *ptr2) {
  const Pair **pair1 = (const Pair **)ptr1;
  const Pair **pair2 = (const Pair **)ptr2;

  if ((*pair1)->first != (*pair2)->first)
    return (*pair1)->first - (*pair2)->first;
  else
    return (*pair1)->second - (*pair2)->second;
}