#!/bin/bash
# Usage: ./run A B C

DATA="testdata"
TEMP="/tmp/problem_QAQ"
GCC="g++ -std=c++17 -Wall -Wextra -pedantic -O2"
TIM="/usr/bin/time -f %e"

for prob in $@; do
  cd "$prob"*
  rm -rf $TEMP
  mkdir -p $TEMP
  $GCC val.cpp -o $TEMP/val

  for (( i=1; i<=100; i++ )); do
    inp="$DATA/input$i.txt"
    [[ -r $inp ]] || break
    $TEMP/val < $inp
  done

  for sol in $(ls sol*); do
    echo $sol
    exe="$TEMP/${prob}_$(basename $sol .cpp)"
    $GCC $sol -o $exe
    tot=0

    for (( i=1; i<=100; i++ )); do
      inp="$DATA/input$i.txt"
      out="$DATA/output$i.txt"
      res="${exe}_$i.txt"
      [[ -r $inp ]] || break
      $TIM $exe < $inp > $res
      diff -y $res $out
    done
  done

  cd ..
done
