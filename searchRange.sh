#!/bin/bash

if [[ $# != 2 ]]; then
	echo "Usage: $0 <start> <end>"
	echo "Searches bases from 'start' to 'end' inclusive"
	exit 1
fi

for i in `seq $1 $2`; do
	echo "================= Searching base $i ==================="
	time ./a.out "$i"
done
