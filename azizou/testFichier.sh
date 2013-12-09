#!/bin/bash
echo "TEST AVEC -V"
echo "------------------------------------"
./filtre -V test01.txt test02.txt test03.txt test04.txt test02.txt -C 0-1 -L 2-4

echo "TEST AVEC -H"
echo "------------------------------------"
./filtre -H test01.txt test02.txt test03.txt test04.txt test02.txt -C 2-4 -L 3-10