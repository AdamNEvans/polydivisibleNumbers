#!/bin/bash

for i in `seq 30 50`; do
	echo "================= Searching base $i ==================="
	time ./a.out "$i"
done
