#!/bin/bash
# Stress test: sol vs brute, validated by checker.
# usage: ./stress.sh <rounds> [maxn] [maxm]
ROUNDS=${1:-500}
MAXN=${2:-8}
MAXM=${3:-4}
for i in $(seq 1 "$ROUNDS"); do
  ./gen "$i" "$MAXN" "$MAXM" > in.txt
  ./sol < in.txt > out.txt
  ./brute < in.txt > ans.txt
  if ! ./checker in.txt out.txt ans.txt > /dev/null; then
    echo "STRESS FAILED at seed $i (maxn=$MAXN maxm=$MAXM)"
    echo "--- input ---"; cat in.txt
    echo "--- sol ---"; cat out.txt
    echo "--- brute ---"; cat ans.txt
    ./checker in.txt out.txt ans.txt
    exit 1
  fi
done
echo "STRESS PASSED: $ROUNDS rounds (maxn=$MAXN maxm=$MAXM)"
