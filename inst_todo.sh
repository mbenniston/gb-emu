#!/bin/bash

make clean
make 

./bin/gb-asm -l > output.txt
comm -13 <(sort -u output.txt) <(sort -u mnenonics) > diff.txt
cat diff.txt
cat diff.txt | wc -l