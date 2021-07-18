#!/bin/bash
prog=$1
dir=$2

output=$(mktemp /tmp/test-XXXXX)
error=$(mktemp /tmp/test-XXXXX)
valgrind_output=$(mktemp /tmp/test-XXXXX)

for test in $dir/*.in
do

  # Sprawdzenie poprawności. W przypadku błędnej odpowiedzi skrypt informuje,
  # na którym wyjściu pojawiła się błędna odpowiedź i wypisuje (jak komenda
  # diff), jak wygląda pierwsza różnica między wyjściem programu a plikiem .out.
  test="${test%.in}"
  ./$prog < "${test}.in" > $output 2> $error
  if [ $? -ne 0 ] ; then
    echo "Test ${test#${dir}/}: Wystapil blad!"
    continue
  elif diff $output "${test}.out" > /dev/null && \
      diff $error "${test}.err" > /dev/null ; then
    echo "Test ${test#${dir}/}: OK."
  else
    echo "Test ${test#${dir}/}: Zla odpowiedz!"
    if ! diff $output "${test}.out" > /dev/null ; then
      echo "Roznica w wyjsciu stdout:"
      diff $output "${test}.out" | head -n 1
    fi
    if ! diff $error "${test}.err" > /dev/null ; then
      echo "Roznica w wyjsciu stderr:"
      diff $error "${test}.err" | head -n 1
    fi
  fi

  # Sprawdzenie, czy nie wystąpiły błędy pamięci.
  valgrind --log-file=$valgrind_output --error-exitcode=123 --leak-check=full \
  --show-leak-kinds=all --errors-for-leak-kinds=all \
  ./$prog < "${test}.in" > $output 2> $error
  if [ $? -ne 0 ] ; then
    echo "Blad pamieci!"
  fi

done

rm $output $error $valgrind_output